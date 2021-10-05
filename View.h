#pragma once
#include <iostream>
#include <sstream>

#include "Controller.h"
using namespace std;

class Controller;

class ConsoleApp
{
private:
	int MainMenu;
	int UntMenu;
	int ch;
	bool findmenu;
	bool updatemenu;
	Controller* con;
//указатель на контроллер не забудь

public:
	ConsoleApp();
	void Main_menu_output();
	void Find_menu();
	void Update_menu();

	void run();
	void runFind(bool findmenu);
	void runUpdate(bool updatemenu);

	void addContact();
	void deleteContact();
	void findAddresstoFIO();
	void findPhoneNumbertoFIO();
	void findto4();
	void updateFIOcontacte();
	void addAddress();
	void updateStreet();
	void updateNumberHome();
	
	void updateNumberAppartment();
	void addPhoneNumber();
	void updatePhoneNumber();
	void updateTypePhoneNumber();
	void deletePhoneNumber();
	void deleteAddress();
};