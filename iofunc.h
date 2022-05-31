#pragma once
#include <iostream>
#include <tuple>
#include "menu.h"
#include <sstream>
#include <vector>


class Print {
public:

	void printAccnt(std::string username, std::string password);
};

class IO {
//Swap tuples for struct
public:
	std::tuple<std::string,std::string,std::string>   parseFormatted(std::string sourceString);
	std::tuple<std::string, std::string, std::string> siteUserPass();
	std::pair<std::string, std::string>               userPass();
	std::string                                       password();
	static std::string                                passwordPlain();
	bool	                                          validatePass(std::string newPassword, std::string existPassword);
	static std::string                                decrypt(std::string password);
	static std::string                                encrypt(std::string password);
	static void                                       setMasterPass(std::string userMasterPass);
	bool                                              masterPassDirectoryCheck(std::string initString);


	
private:
	std::stringstream ss;
	inline static std::string masterPass;
	
};

