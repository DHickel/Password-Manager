#pragma once
#include "site.h"

/*Constructors*/
SiteURL::SiteURL() {
	this->siteURL = "URL";
	accntList.push_back(new Account("USERNAME", "PASSWORD"));
}


SiteURL::SiteURL(std::string siteURL) {
	this->siteURL = siteURL;
}

SiteURL::SiteURL(std::string siteURL, std::string username, std::string password) {
	this->siteURL = siteURL;
	setNewAccnt(username, password);
}


Account::Account(std::string username, std::string password) {
	this->username = username;
	this->password = password;
}
Account::Account() {

}


SiteURL::~SiteURL(){
}
/*Setters*/

void SiteURL::setNewAccnt(std::string username,std::string password) {
	accntList.push_back(new Account(username, password));
}


void SiteURL::changeAccntPassword(int index, std::string password) {
	accntList[index]->setPassword(password);
}


/*getters*/

std::string SiteURL::getURL() {
	return this->siteURL;
}

std::string Account::getUsername() {
	return this->username;
}

std::string Account::getPassword() {
	return this->password;
}

void Account::setPassword(std::string password) {
	this->password = password;
}
size_t SiteURL::getAccountSize() {
	return this ->accntList.size();
}


/*Check Function*/

std::pair<int, int> SiteURL::checkIfUserExist(std::string username) {

	for (size_t i = 0; i < accntList.size(); ++i) {
		if (accntList[i]->getUsername() == username) {
			return std::make_pair(1, i);
			
		}
	}
	return std::make_pair(0, 0);
}



/*Fetch Function  !temp print aswell! !FixMe! */

std::string SiteURL::fetchUserPass(int index) {
	return accntList[index]->getPassword();
}



void SiteURL::printUserPass(){

	for (size_t i = 0; i < accntList.size(); ++i) {
		std::cout << accntList[i]->getUsername() << "\n"
		          << IO::decrypt(accntList[i]->getPassword()) << "\n\n" << std::endl;
	}
	return;
}

void SiteURL::printUserMasked() {

	for (size_t i = 0; i < accntList.size(); ++i) {
		std::cout << accntList[i]->getUsername() << "\n" << std::endl;
	}
	return;
}

std::pair<std::string, std::string> SiteURL::accountOut(int index) {
	return std::make_pair(accntList[index]->getUsername(), accntList[index]->getPassword());
}

std::tuple<std::string, std::string, std::string> SiteURL::writeHeader() {
	return std::make_tuple("USER", "PASSWORD", "0000000000000000");
}

/*Remove Account*/

void SiteURL::removeAccount(int index) {
	accntList.erase(accntList.begin() + index);
}