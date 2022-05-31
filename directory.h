#pragma once
#include "site.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <boost/filesystem.hpp>
class Directory {

public:
	void                        addExist(std::string SiteURL);
	void                        addExist(int index);
	void                        add(std::string siteURL);
	void                        removeAccount(std::string siteURL, std::string username);
	void                        removeSite(std::string siteURL);
	void				        changePassword(std::string siteURL);
	void                        addParsedInternal(std::string sourceFile);
	void                        saveDirectory(std::string directoryName);
	void                        displayPWSingle(std::string siteURL, std::string username);
	void                        displayPWSiteMasked(std::string siteURL);
	void                        displayPWSiteUnmasked(std::string siteURL);
	void                        displayPWAllSiteMasked();
	void                        displayPWAllSiteUnmaked();
	void                        parseExternal(std:: string sourceFile);
	void                        createDirectory(std::string);


	std::pair<int, std::size_t> checkIfExist(std::string siteURL);
	//std::ifstream               sourceFile;


private:
	std::ifstream               sourceFile;
	std::vector<std::string>    sourceLines;
	std::vector<SiteURL* >      siteDirectory;
	std::vector<std::string>    exportStrings;
	const std::string           defaultDirectoryFile = "DB\\passwordDB.db";

};