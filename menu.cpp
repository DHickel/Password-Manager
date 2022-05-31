#include "menu.h"


/*Display Headers (For Menus)*/

void Menu::headerMasterPass() {
	std::cout << "-----------------------\n"
		      << "         ENTER         \\\n"
		      << "    MASTER PASSWORD     \\\n"
		      << "--------------------------\n\n";
}


/*Main Menu*/
void Menu::menuTopPrint() {
	std::cout << "-----------------------\n"
		      << "    PASSWORD MANAGER   \\\n"
		      << "        PICK MODE       \\\n"
		      << "--------------------------"
		      << " \n 1. Display Passwords.\n 2. Edit Password(s).\n"
		      << " 3. Advanced Features.\n 7. Quit To Desktop.\n" << std::endl;
}
void Menu::menuDisplayPrint(){
	std::cout << "-----------------------\n"
			  << "    PASSWORD MANAGER   \\\n"
			  << "      DISPLAY MODE      \\\n"
			  << "--------------------------"
			  << " \n 1. Password For An Account.\n 2. All Accounts For A Site.\n"
			  << " 3. All Accounts & Passwords For A Site.\n 4. All Accounts For All Sites.\n"
		      << " 5. All Accounts & Passwords For All Sites.\n 7. Quit.\n" << std::endl;
}

void Menu::menuEditPrint() {
	std::cout << "-----------------------\n"
		      << "    PASSWORD MANAGER   \\\n"
		      << "        EDIT MODE       \\\n"
		      << "--------------------------"
		      << " \n 1. Add A New Site Entry.\n 2. Add Account to Site.\n"
		      << " 3. Change A Password.\n 4. Remove A Account.\n"
		      << " 5. Remove A Site.\n 7. Quit.\n" 
		      << std::endl;
}

void Menu::menuAdvancedPrint() {
	std::cout << "-----------------------\n"
		      << "    PASSWORD MANAGER   \\\n"
		      << "        ADVANCED        \\\n"
		      << "--------------------------"
		      << " \n 1. Create New Directory.\n 2. Import Directory.\n"
		      << " 3. Find/Remove Duplicates.\n 4. Change Master Password.\n"
		      << " 5. Export PlainText.\n 7. Quit.\n 0. Settings."
		      << std::endl;
}
 

MENUTOP Menu::menuTopReturn() {

	MENUTOP     rtnValue;
	std::string  userInput;

	std::cout << "    Action: ";
	std::cin >> userInput;
	if (userInput == "1") {
		rtnValue = MENUTOP::DISPLAY;
	}
	else if (userInput == "2") {
		rtnValue = MENUTOP::EDIT;
	}
	else if (userInput == "3") {
		rtnValue = MENUTOP::ADVANCED;
	}
	else if (userInput == "7") {
		rtnValue = MENUTOP::QUIT;
	}
	else {
		std::cout << "\n!Invalid Input!\n\n";
	}
	return rtnValue;
}

MENUEDIT Menu::menuEditReturn() {
	MENUEDIT     rtnValue;
	std::string  userInput;

	std::cout << "    Action: ";
	std::cin >> userInput;
	if (userInput == "1") {
		rtnValue = MENUEDIT::ADDSITE;
	}
	else if (userInput == "2") {
		rtnValue = MENUEDIT::ADDACCOUNT;
	}
	else if (userInput == "3") {
		rtnValue = MENUEDIT::CHANGEPASS;
	}
	else if (userInput == "4") {
		rtnValue = MENUEDIT::REMOVEACCOUNT;
	}
	else if (userInput == "5") {
		rtnValue = MENUEDIT::REMOVESITE;
	}
	/*else if (userInput == "6") {
		rtnValue = MENUEDIT::SWITCHMENU;
	}*/
	else if (userInput == "7") {
		rtnValue = MENUEDIT::QUIT;
	}
	else {
		std::cout << "\n!Invalid Input!\n\n";
	}
	return rtnValue;
}

MENUDISPLAY Menu::menuDisplayReturn() {
	MENUDISPLAY     rtnValue;
	std::string     userInput;

	std::cout << "    Action: ";
	std::cin >> userInput;
	if (userInput == "1") {
		rtnValue = MENUDISPLAY::ACCOUNT;
	}
	else if (userInput == "2") {
		rtnValue = MENUDISPLAY::URLMASKED;
	}
	else if (userInput == "3") {
		rtnValue = MENUDISPLAY::URLUNMASKED;
	}
	else if (userInput == "4") {
		rtnValue = MENUDISPLAY::ALLMASKED;
	}
	else if (userInput == "5") {
		rtnValue = MENUDISPLAY::ALLUNMASKED;
	}
	/*else if (userInput == "6") {
		rtnValue = MENUDISPLAY::SWITCHMENU;
	}*/
	else if (userInput == "7") {
		rtnValue = MENUDISPLAY::QUIT;
	}
	else {
		std::cout << "\n!Invalid Input!\n\n";
	}
	return rtnValue;
}


/*Input Menus (Keyboard)*/

//siteURL//
std::string Menu::siteInMenu() { 
	
	int i = 0;
	std::string chkValue;

	while (i < 1) {

		std::cout << "Site Address: ";
		std::cin  >> siteIn;
		std::cout << "Re-Enter Site Address: ";
		std::cin  >> chkValue;

		if (chkValue != siteIn) {
			std::cout << "\nAdresses Entered Do Not Match!\n"
					  << "\nPlease Enter site Again.\n\n";
			i = 0;
		}
		else {
			i = 1;
		}
	}
	
	return toLower(formatURL(siteIn));
}

std::string Menu::getSite() {

	std::string siteIn;

	std::cout << "Site Address: ";
	std::cin >> siteIn;

	return toLower(formatURL(siteIn));
}

std::string Menu::getUser() {
	std::string username;
	std::cout << "Username: ";
	std::cin >> username;
	return toLower(username);
}

std::string Menu::getName() {
	std::string filename;
	std::cout << "Filename: ";
	std::cin >> filename;
	return toLower(filename);
}

//Username//
std::string Menu::userInMenu() { 
	
	int i = 0;
	std::string chkValue;

	while (i < 1) {

		std::cout << "Username: ";
		std::cin >> userIn;
		std::cout << "Re-Enter Username: ";
		std::cin >> chkValue;

		if (chkValue != userIn) {
			std::cout << "\nUsernames Entered Do Not Match!\n"
				<< "\nPlease Enter Username Again.\n\n";
			i = 0;
		}
		else {
			i = 1;
		}
	}
	return toLower(userIn); 
}

//password//
std::string Menu::passInMenu() {

	int i = 0;
	std::string chkValue;

	i = 0;
	while (i < 1) {

		std::cout << "Password: ";
		std::cin >> passIn;
		std::cout << "Re-Enter Password: ";
		std::cin >> chkValue;
		if (chkValue != passIn) {
			std::cout << "\nPasswords Entered Do Not Match!\n"
				      << "\nPlease Enter Password Again.\n\n";
			i = 0;
		}
		else {
			i = 1;
		}
	}
	return passIn;
}

/*Yes | N | Quit Menus/Functions*/

//Get Yes or No
YNQuit Menu::yesNoGet() {
	YNQuit ynQuit;
	char keyIn;

	for (int i = 0; i < 1; ++i) {

		std::cin >> keyIn;

		if (keyIn == 'Y' || keyIn == 'y' || keyIn == '1') {
			ynQuit = Y;
		}
		else if (keyIn == 'N' || keyIn == 'n' || keyIn == '0') {
			ynQuit = N;
		}
		else {
			std::cout << "\n!Invalid Input!\n y = Yes | n = No" << std::endl;
			i = i-1;
		}	
	}
	return ynQuit;
	
}

//Get Yes, No or Quit
YNQuit Menu::yesNoQuitGet() {
	YNQuit ynQuit;
	char keyIn;
	int i = 0;

	while (i < 1) {
		
		std::cin >> keyIn;

		if (keyIn == 'Y' || keyIn == 'y' || keyIn == '1') {
			ynQuit = Y;
		}
		else if (keyIn == 'N' || keyIn == 'n' || keyIn == '0') {
			ynQuit = N;
		}
		else if (keyIn == keyIn == 'Q' || keyIn == 'q' || keyIn == '3') {
			ynQuit = Q;
		}
		else {
			std::cout << "\n!Invalid Input!\n y = Yes | n = No | q = Quit" << std::endl;	
			i = 0;
		}
	}
	return ynQuit;
}

YNQuit Menu::contPromtSite() {
	return yesNoQuitGet();
}

YNQuit Menu::contPromtUser() {
	
	std::cout << "Add Another Account?\n(y/n): ";
	return yesNoGet();
}

std::string Menu::getPass() {

	std::cout << "Password: ";
	std::cin >> passIn;
	return passIn;
}
std::string Menu::toLower(std::string stringToLower) {

	std::transform(stringToLower.begin(), stringToLower.end(), stringToLower.begin(), ::tolower);
	return stringToLower;
}

std::string Menu::formatURL(std::string URL) {

	const std::regex filter("(http|ftp|https)://|(www.)");
	std::string formattedURL;

	std::regex_replace(back_inserter(formattedURL), URL.begin(), URL.end(), filter, "");
	return formattedURL;
}











