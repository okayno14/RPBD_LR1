#pragma once
#include <iostream>
#include <sstream>
#include <cstring>

#include "Controller.h"
using namespace std;

class Controller;

class ConsoleApp
{
private:
	bool runTimeProgram;// служит в первом цикле программы
	int MainMenu;//используетс€ дл€ ввода пользователем
	//int UntMenu;//?????
	int ch;//???????
	Controller* con;
//указатель на контроллер не забудь

public:
	ConsoleApp();

	/*Ќовое меню приложени€*/
	void Menu();
	void MenuPC();


	void setController(Controller* con);
	
	void run();
	void runPC();

	void findPerson();

	void addContact();
	void deleteContact();

	void findto4();
	void updateFIOcontacte();
	void addAddress();
	void addPhoneNumber();

	void deletePhoneNumber();
	void deleteAddress();

	void success();
	void offlineStatus();
	void fail();
	void What();
	bool toRunMenuTwo();

	wchar_t* get_a_number();/*find fio and phoneNumber*/
	wchar_t* get_a_addressName();/*find fio and phoneNumber and address*/
	int get_a_type_number();
	int get_a_apartment();
	int get_a_numberhome();
	
};