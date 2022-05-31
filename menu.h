 #pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <iterator>


enum YNQuit {
	N = 0,
	Y = 1,
	A = 2,
	Q = 3
};

enum class MENUTOP {
	DISPLAY            = 1,
	EDIT               = 2,
	ADVANCED           = 3,
	QUIT               = 7,
};
enum class MENUDISPLAY {
	ACCOUNT            = 1,
	URLMASKED          = 2,
	URLUNMASKED        = 3,
	ALLMASKED          = 4,
	ALLUNMASKED        = 5,
	QUIT               = 7
};
enum class MENUEDIT {
	ADDSITE            = 1,
	ADDACCOUNT         = 2,
	CHANGEPASS         = 3,
	REMOVEACCOUNT      = 4,
	REMOVESITE         = 5,
	QUIT               = 7
};





class Menu {

public:
	static void   headerMasterPass();
	void          menuEditPrint();
	void          menuDisplayPrint();
	void          menuAdvancedPrint();
	void          menuTopPrint();
	MENUTOP       menuTopReturn();
	MENUDISPLAY   menuDisplayReturn();
	MENUEDIT      menuEditReturn();
	
		


	YNQuit      yesNoGet();
	YNQuit      yesNoQuitGet();
	YNQuit      contPromtSite();
	YNQuit      contPromtUser();
	std::string siteInMenu();
	std::string userInMenu();
	std::string passInMenu();
	std::string getSite();
	std::string getUser();
	std::string getPass();
	std::string getName();
	std::string toLower(std::string stringToLower);
	std::string formatURL(std::string URL);

private:

	std::string siteIn;
	std::string userIn;
	std::string passIn;


};

