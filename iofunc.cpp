#pragma once
#include "iofunc.h"
#include <iostream>
#include <fstream>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cstddef>
#include <cryptopp/pwdbased.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cstring>
#include <algorithm>
#include <cctype>




void IO::setMasterPass(std::string userMasterPass) {
	masterPass = userMasterPass;
}


std::string IO::encrypt(std::string password) {
	using namespace CryptoPP;
	byte iv[AES::BLOCKSIZE] = { '0','0' };

	// Derive Key From masterPass

	byte key[SHA256::DIGESTSIZE];

	PKCS12_PBKDF<SHA256> derive;
	derive.DeriveKey((byte*)key, sizeof(key), (byte*)masterPass.data(), masterPass.size());

	// Encrypt with key
	CFB_Mode<AES>::Encryption cfbEncryption(key, sizeof(key), iv);
	const char* passwordEncryptCStr = password.c_str();
	cfbEncryption.ProcessData((byte*)passwordEncryptCStr, (byte*)passwordEncryptCStr, strlen(passwordEncryptCStr) + 1);

	std::string passwordEncrypted(passwordEncryptCStr);

	return passwordEncrypted;
}



std::string IO::decrypt(std::string password) {
	using namespace CryptoPP;
	byte iv[AES::BLOCKSIZE] = { '0','0' };

	// Derive Key From masterPass
	byte key[SHA256::DIGESTSIZE];

	PKCS12_PBKDF<SHA256> derive;
	derive.DeriveKey((byte*)key, sizeof(key), (byte*)masterPass.data(), masterPass.size());


	// Decrypt with key
	CFB_Mode<AES>::Decryption cfbDecryption((byte*)key, sizeof(key), iv);
	const char* passwordDecryptCStr = password.c_str();
	cfbDecryption.ProcessData((byte*)passwordDecryptCStr, (byte*)passwordDecryptCStr, strlen(passwordDecryptCStr) + 1);

	std::string passwordDecrypted(passwordDecryptCStr);

	return passwordDecrypted;
}






void Print::printAccnt(std::string username, std::string password) {
	std::cout << "Username:" << username << "\t"
			  << "Password:" << password << std::endl;
}


/*Parse Functions*/

std::tuple<std::string, std::string, std::string> IO::parseFormatted(std::string sourceString) {

		std::string URL;
		std::string username;
		std::string password;

		std::stringstream ss(sourceString);

		for (int i = 0; i < 3; ++i) { 

			if (i == 0) {
				std::getline(ss, URL, ',');
			}
			else if (i == 1) {
				std::getline(ss, username, ',');
			}
			else if (i == 2) {
				std::getline(ss, password, ',');
			}
		}
		return std::make_tuple(URL, username, password);
}
	
bool IO::masterPassDirectoryCheck(std::string initString) {
	std::string URL;
	std::string username;
	std::string password;
	std::string  checkString;
	std::stringstream ss(initString);
	for (int i = 0; i < 4; ++i) {

		if (i == 0) {
			std::getline(ss, URL, ',');
		}
		else if (i == 1) {
			std::getline(ss, username, ',');
		}
		else if (i == 2) {
			std::getline(ss, password, ',');
		}
		else if (i == 3) {
			std::getline(ss, checkString, ',');
		}
	}
	

	if (decrypt(checkString)  == "0000000000000000") {   
		return true;
	}
	else {
		return false;
	}

}





//Get input  URL User Paass
std::tuple<std::string,std::string, std::string> IO::siteUserPass() {
	Menu menu;
	std::string siteIn = menu.siteInMenu();
	std::string userIn = menu.userInMenu();
	std::string passIn = encrypt(menu.passInMenu());
	auto siteUserPass = std::make_tuple(siteIn,userIn,passIn);
	return siteUserPass;
}
//Get input User Pass
std::pair<std::string, std::string> IO::userPass() {
	Menu menu;
	std::string userIn = menu.userInMenu();
	std::string passIn = encrypt(menu.passInMenu());
	auto userPass = std::make_pair(userIn, passIn);
	return userPass;
}
//Get Password
std::string IO::password() {
	Menu menu;
	return encrypt(menu.passInMenu());
}

std::string IO::passwordPlain() {
	Menu menu;
	return menu.passInMenu();
}


bool IO::validatePass(std::string passwordEntered, std::string passwordOnFile) {
	if (passwordEntered == passwordOnFile) {
		return true;
		std::cout << "password:" << passwordEntered << "     passwordFile:" << passwordOnFile <<std::endl;
	}
	else {
		return false;
	}
}










