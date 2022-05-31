#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "iofunc.h"
#include "menu.h"

class Account {

public:
	Account();
	Account(std::string username, std::string password);

	std::string getUsername();
	std::string getPassword();
	void setPassword(std::string password);
private:

	std::string username;
	std::string password;
};



class SiteURL {

public:

	/*constructor*/
	SiteURL();
	SiteURL(std::string siteURL);
	SiteURL(std::string siteURL, std::string username, std::string password);
	~SiteURL();

	
	
	void                                              removeAccount(int index);
	void                                              setNewAccnt(std::string username, std::string password);
	std::pair<int, int>                               checkIfUserExist(std::string username);
	std::string                                       getURL();
	std::string                                       fetchUserPass(int index);
	void                                              changeAccntPassword(int index,std::string);
	void                                              printUserPass();
	void                                              printUserMasked();
	size_t                                            getAccountSize();
	std::pair<std::string, std::string>               accountOut(int index);
	std::tuple<std::string, std::string, std::string> writeHeader();

	

	
private:

	std::string siteURL;
	std::vector<Account* > accntList;

};


