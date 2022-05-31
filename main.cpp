#pragma once
#include "directory.h"
#include <tuple>
#include <iostream>
#include <filesystem>
#include <boost/filesystem.hpp>



std::string masterPass;
std::string folder = "DB\\";
std::string extension = ".db";
std::string fileName;
std::string directoryFile;


int main() {

	bool menuVar;
	Menu menu;
	Directory directoryInMem;
	YNQuit quit = N;
	MENUTOP MENUSELECT;



	
	


	menu.headerMasterPass();
	IO::setMasterPass(IO::passwordPlain());
	directoryInMem.parseExternal("db\\passwordDB.db");

	while (quit == N) {
		
		menu.menuTopPrint();

		MENUSELECT = menu.menuTopReturn();

		if (MENUSELECT == MENUTOP::DISPLAY) {
			menu.menuDisplayPrint();

			switch (menu.menuDisplayReturn()) {

			case MENUDISPLAY::ACCOUNT:
				std::cout << "\n::::::::::::::::::\n"
						  << ":: ACCOUNT INFO ::\n"
						  << "::::::::::::::::::\n\n";
				directoryInMem.displayPWSingle(menu.getUser(), menu.getSite());
				break;
			case MENUDISPLAY::URLMASKED:
				std::cout << "\n::::::::::::::::::\n"
						  << ":: ALL ACCOUNTS ::\n"
						  << "::::::::::::::::::\n\n";
				directoryInMem.displayPWSiteMasked(menu.getSite());
				break;
			case MENUDISPLAY::URLUNMASKED:
				std::cout << "\n::::::::::::::::::\n"
						  << ":: ALL ACCOUNTS ::\n"
						  << "::::::::::::::::::\n\n";
				directoryInMem.displayPWSiteUnmasked(menu.getSite());
				break;
			case MENUDISPLAY::ALLMASKED:
				std::cout << "\n::::::::::::::::::::::::::\n"
						  << ":: ALL SITES & ACCOUNTS ::\n"
						  << "::::::::::::::::::::::::::\n\n";
				directoryInMem.displayPWAllSiteMasked();
				break;
			case MENUDISPLAY::ALLUNMASKED:
				std::cout << "\n::::::::::::::::::::::::::\n"
						  << ":: ALL SITES & ACCOUNTS ::\n"
						  << "::::::::::::::::::::::::::\n\n";
				directoryInMem.displayPWAllSiteUnmaked();
				break;
			case MENUDISPLAY::QUIT:
				break;

				break;
			default:
				std::cout << "\nInvalidInput.\n";
				break;
			}
			
		}


		else if (MENUSELECT == MENUTOP::EDIT) {
			menu.menuEditPrint();

			switch (menu.menuEditReturn()) {

			case MENUEDIT::ADDSITE:
				std::cout << "\n::::::::::::::\n"
					      << ":: ADD SITE ::\n"
					      << "::::::::::::::\n\n";
				directoryInMem.add(menu.siteInMenu());
				break;
			case MENUEDIT::ADDACCOUNT:
				std::cout << "\n:::::::::::::::::\n"
					      << ":: ADD ACCOUNT ::\n"
					      << ":::::::::::::::::\n\n";
				directoryInMem.addExist(menu.getSite());
				break;
			case MENUEDIT::CHANGEPASS:
				std::cout << "\n:::::::::::::::::::::\n"
					      << ":: CHANGE PASSWORD ::\n"
					      << ":::::::::::::::::::::\n\n";
				directoryInMem.changePassword(menu.getSite());
				break;
			case MENUEDIT::REMOVEACCOUNT:
				std::cout << "\n::::::::::::::::::::\n"
					      << ":: REMOVE ACCOUNT ::\n"
					      << "::::::::::::::::::::\n\n";
				directoryInMem.removeAccount(menu.getUser(),
					                         menu.getSite());
				break;
			case MENUEDIT::REMOVESITE:
				std::cout << "\n:::::::::::::::::\n"
					      << ":: REMOVE SITE ::\n"
					      << ":::::::::::::::::\n\n";
				directoryInMem.removeSite(menu.getSite());
				break;
			case MENUEDIT::QUIT:

				break;
			default:
				std::cout << "\nInvalidInput.\n";
				break;
			}
			directoryInMem.saveDirectory("DB\\passwordDb.db");
		}
		else if (MENUSELECT == MENUTOP::QUIT) {
			quit = Y;
			return 0;
		}
		
	}
	return 0;
}