#pragma once
#include "directory.h"
#include <tuple>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <boost/filesystem.hpp>


/*
* Notes:
* 
*  ____ExistIndex/checkIfExist calls return (bool,index) (if found, where found)
* 
*  userPass/siteUserPass calls return (user,pass) and (site,user,pass)
* 
*/





//Check for existing URL entry, pair passed bool/index location as return
std::pair<int,std::size_t>Directory::checkIfExist(std::string siteURL) {

	for (size_t i = 0; i < siteDirectory.size(); ++i) {
		if (siteDirectory[i]->getURL() == siteURL) {
			return std::make_pair(1, i);
		}
	}
	return std::make_pair(0, 0);
}



//Add URL to Directory
void Directory::add(std::string siteURL) {

	Menu menu;
	IO io;
	std::string username = "";
	std::string password = "";
	YNQuit ynState = Y;
	
	auto doesExist = checkIfExist(siteURL);

	if (std::get<0>(doesExist) == 0) {

		std::cout << "\nEnter Account Infomation For: " << siteURL << "\n" << std::endl;
		auto userPass = io.userPass();
		siteDirectory.push_back(new SiteURL(siteURL, std::get<0>(userPass), std::get<1>(userPass)));
	}
	else if (std::get<0>(doesExist) == 1) {

		std::cout << siteURL << " Already Exists. Do You Wish To Edit An Existing Account \nOr ";
		ynState = menu.contPromtUser();

		if (ynState == Y) {
			addExist(std::get<1>(doesExist));
			return;
		}
		else {
			return;
		}
	}

	ynState = menu.contPromtUser();
	//FIXME!!! Errors if creating another accoutn for a site that already exist, needs fed its index in that context
	if (ynState == Y) {
		addExist(siteDirectory.size() - 1);
	}
	else {
		return;
	}
	return;
}

void Directory::addParsedInternal(std::string sourceFile) {
	IO io;

	if (!boost::filesystem::exists(sourceFile)) {
		createDirectory(defaultDirectoryFile);
		return;
	}

	this->sourceFile.open(sourceFile);
	std::string parsedLine;

	while (!this->sourceFile.eof()) {
		this->sourceFile >> parsedLine;
		sourceLines.push_back(parsedLine);
	}

	if (io.masterPassDirectoryCheck(sourceLines[0]) == true) {
		std::cout << "\nMaster Password Valid.\n" << std::endl;
		for (size_t i = 0; i < sourceLines.size() - 1; i++) {
		//returns tuple of site,user,pass
			auto parseReturn = io.parseFormatted(sourceLines[i]);
			auto doesExist = checkIfExist(std::get<0>(parseReturn));
			if (std::get<0>(doesExist) == 0) {
				siteDirectory.push_back(new SiteURL(std::get<0>(parseReturn), std::get<1>(parseReturn), std::get<2>(parseReturn)));
			}
			else if (std::get<0>(doesExist) == 1) {
				siteDirectory[std::get<1>(doesExist)]->setNewAccnt(std::get<1>(parseReturn), std::get<2>(parseReturn));
			}
		}
	}
	else {
		std::cout << "\n!!!Invalid Master Passwood Or Corrupted File!!!\n\t\tExiting........" ;
		std::exit(0);
	}
}

void Directory::saveDirectory(std::string directoryName) { 
	
	for (size_t i = 0; i < siteDirectory.size(); ++i) {

		//new ofstream
		std::ofstream ofs (directoryName);

		std::string URL;
		std::string comma = ",";
		URL = siteDirectory[i]->getURL();

		for (size_t j = 0; j < siteDirectory[i]->getAccountSize(); ++j) {
			
			std::string lineout = "";
			auto accountOut = siteDirectory[i]->accountOut(j);

			if (i == 0) {
				lineout = URL + comma + std::get<0>(accountOut) + comma + std::get<1>(accountOut) + comma + IO::encrypt("0000000000000000");
				exportStrings.push_back(lineout);
			}
			else {
				lineout = URL + comma + std::get<0>(accountOut) + comma + std::get<1>(accountOut);
				exportStrings.push_back(lineout);
			}
		}
	}
		//std::ofstream destinFile(directoryName);
		std::ofstream destinFile(directoryName, std::ofstream::trunc);
		for (size_t i = 0; i < exportStrings.size(); ++i) { //fix i issue
			destinFile << exportStrings[i] << std::endl;
		}
		exportStrings.clear();
		destinFile.flush();
		destinFile.close();
}


//Add to existing URL by index
void Directory::addExist(int index) {

	IO io;
	Menu menu;
	YNQuit ynState = Y;

	while (ynState == Y) {
		auto userpass = io.userPass();
		siteDirectory[index]->setNewAccnt(std::get<0>(userpass), std::get<1>(userpass));
		ynState = menu.contPromtUser();
	}
	return;
}



//add to existing URL by URL
void Directory::addExist(std::string siteURL) {
	
	IO io;
	Menu menu;


	auto siteExistIndex = checkIfExist(siteURL);
	int index = std::get<1>(siteExistIndex);

	if (std::get<0>(siteExistIndex) == 1) {
		addExist(index);
	}
	else if (std::get<0>(siteExistIndex) == 0) {
		std::cout << "\nSite " << siteURL << " Does Not Exist In Directory.\n"
			<< "\nDo You Wish To Add An Entry For " << siteURL << "?" << std::endl
			<< "(y/n): ";

		YNQuit ynState = menu.contPromtUser();
		while (ynState == Y) {
			std::string username;
			std::string password;
			std::cout << "\n\nEnter Account Infomation For: " << siteURL << std::endl;
			auto userPass = io.userPass();
			siteDirectory.push_back(new SiteURL(siteURL, std::get<0>(userPass), std::get<1>(userPass)));
			ynState = menu.contPromtUser();
		}
	}
	return;
}

/*Change Password On Existing Account*/  
void Directory::changePassword(std::string siteURL) {
	Menu menu;
	IO io;
	YNQuit ynState = Y;


	auto siteExistIndex = checkIfExist(siteURL);
	int siteIndex = std::get<1>(siteExistIndex);

	if (std::get<0>(siteExistIndex) == 1) {

		std::string username = menu.getUser();
		
		auto userExistIndex = siteDirectory[siteIndex]->checkIfUserExist(username);
		if (std::get<0>(userExistIndex) == 1) {
			std::cout << "\nExisting ";

			if (io.validatePass(menu.getPass(), siteDirectory[siteIndex]->fetchUserPass(std::get<1>(userExistIndex))) == true) { //FIXME!!!!  Remove password validation?
				siteDirectory[siteIndex]->changeAccntPassword(std::get<1>(userExistIndex), io.password());
				
			}
			else {
				std::cout << "\n\nPasswords Did Not Match.\n";  
				changePassword(siteURL);
			}
		}
		else {
			std::cout << "\nNo Account With Username: " << username << std::endl
				<< "\nAdd New User Under: " << username << " ?" << std::endl
				<< "(y/n): ";

			ynState = menu.yesNoGet();

			if (ynState == Y) {
				addExist(std::get<1>(siteExistIndex));
			}
			else {
				return;
			}
		}
	}
	else {
			std::cout << "\nsite Not Found\n\n";
	}
}

/*Remove Functions*/

void Directory::removeAccount(std::string username, std::string siteURL) {
	
	auto siteExistIndex = checkIfExist(siteURL);
	int siteIndex = std::get<1>(siteExistIndex);

	if (std::get<0>(siteExistIndex) == 1 && siteURL != "URL" ) {
		auto userExistIndex = siteDirectory[siteIndex]->checkIfUserExist(username);

		if (std::get<0>(userExistIndex) == 1) {
			siteDirectory[siteIndex]->removeAccount(std::get<1>(userExistIndex));
		}
		else {
			std::cout << "\nUsername: " << username << " Not Found." << std::endl;
			return;
		}
	}
	else {
		std::cout << "\nSite: " << siteURL << " Not Found." << std::endl;
		return;
	}
		
}


void Directory::removeSite(std::string siteURL) {
	auto siteExistIndex = checkIfExist(siteURL);
	
	if (std::get<0>(siteExistIndex)== 1 && siteURL != "URL") {
		siteDirectory.erase(siteDirectory.begin() + std::get<1>(siteExistIndex));
	}
	else {
		std::cout <<  "Site Not Found" << std::endl;
	}
}

//Display accounts for a URL
void Directory::displayPWSiteMasked(std::string siteURL) {
	for (size_t i = 0; i < siteDirectory.size(); ++i) {
		if (siteDirectory[i]->getURL() == siteURL) {
		    siteDirectory[i]->printUserPass();
		}
	}
}

void Directory::displayPWSiteUnmasked(std::string siteURL) {
	for (size_t i = 0; i < siteDirectory.size(); ++i) {
		if (siteDirectory[i]->getURL() == siteURL) {
			siteDirectory[i]->printUserMasked();
		}
	}
}

void Directory::displayPWSingle(std::string siteURL, std::string username) {
	for (size_t i = 0; i < siteDirectory.size(); ++i) {
		if (siteDirectory[i]->getURL() == siteURL) {
			auto userExistIndex = siteDirectory[i]->checkIfUserExist(username);
			if (std::get<0>(userExistIndex) == 1)
				std::cout << "\t" << siteDirectory[i]->fetchUserPass(std::get<1>(userExistIndex))
				          << "\n" << std::endl;
		}
	}
}

void Directory::displayPWAllSiteUnmaked() { //fix i issue
	for (size_t i = 1; i < siteDirectory.size(); ++i) {
		
			std::cout << "" << siteDirectory[i]->getURL() << "\n" << std::endl;
			siteDirectory[i]->printUserPass();
		
	}
}

void Directory::displayPWAllSiteMasked() { //fix i issue
	for (size_t i = 1; i < siteDirectory.size(); ++i) {
		
			std::cout << "\t" << siteDirectory[i]->getURL() << "\n" << std::endl;
			siteDirectory[i]->printUserMasked();
		
	}
}

void Directory::parseExternal(std::string sourceFile) {

	IO io;

	this->sourceFile.open(sourceFile);
	std::string parsedLine;

	while (!this->sourceFile.eof()) {
		this->sourceFile >> parsedLine;
		sourceLines.push_back(parsedLine);
	}
		for (size_t i = 0; i < sourceLines.size() - 1; i++) {
			//returns tuple of site,user,pass
			auto parseReturn = io.parseFormatted(sourceLines[i]);
			auto doesExist = checkIfExist(std::get<0>(parseReturn));
			if (std::get<0>(doesExist) == 0) {
				siteDirectory.push_back(new SiteURL(std::get<0>(parseReturn), std::get<1>(parseReturn), IO::encrypt(std::get<2>(parseReturn))));
			}
			else if (std::get<0>(doesExist) == 1) {
				siteDirectory[std::get<1>(doesExist)]->setNewAccnt(std::get<1>(parseReturn), IO::encrypt(std::get<2>(parseReturn)));
			}
		}
	
	std::cout << "\nExternal Files Data Added To Directory\n\n";

}

void Directory::createDirectory(std::string directoryName) {
	Menu menu;
	YNQuit ynState;

	std::cout << "\nDefault Directory Not Found......."
		      << "\nCreate One Now? (Y/N): ";

	ynState = menu.yesNoGet();

	if (ynState == N) {
		exit(0);
	}
	else {

		std::cout << "\nEnter a Master Password\n\n";
		Menu::headerMasterPass();
		IO::setMasterPass(IO::passwordPlain());

		std::string directoryFileheader = "URL,USERNAME,PASSWORD," + IO::encrypt("0000000000000000");
		std::ofstream destinFile(directoryName, std::ofstream::trunc);
		destinFile << directoryFileheader << std::endl;
		destinFile.flush();
		destinFile.close();

		std::cout << "Directory File: " << directoryName << " Created!\n\n";
	}
}




