#pragma once
#include <iostream>
#include <sstream>
#include <cstring>
#include "Model.h"
#include "Controller.h"
using namespace std;


class Controller;

class ConsoleApp
{
private:
	bool runTimeProgram;// служит в первом цикле программы
	int MainMenu;//используется для ввода пользователем
	Controller* con;
	Person* currentPerson;
public:
	ConsoleApp();

	/*доп методы для отображения меню программы*/
	void Menu();
	void MenuPC();


	void setController(Controller* con);
	
	/*остовные раны для управления приложением*/
	void run();
	void runPC();

	/*солянка для вызова внутри switch*/
	Person* findPerson();
	Person* addContact();
	void deleteContact();
	void findto4();
	void findList_FIO();
	void updateFIOcontacte();
	void addAddress();
	void addPhoneNumber();
	void deletePhoneNumber();
	void deleteAddress();
	void updatePhoneNumber();

	//вывод инфы о состоянии модели
	void offlineStatus();
	void noTableConfig();

	void success();	
	void fail();
	
	/*вспомогательные методы*/
	bool toRunMenuTwo();
	void drawPerson(Person* p);
	void drawAddress(Address* add);
	void drawPhoneNumber(PhoneNumber* pn);
	bool drawPhoneNumbers(std::vector<PhoneNumber*> args);

	/*методы для инпута данных*/
	wchar_t* get_a_number();
	wchar_t* get_a_addressName();
	int get_a_type_number();
	int get_a_apartment();
	int get_a_numberhome();
	void inputContact(wchar_t*& lastnamecontact, wchar_t*& firstnamecontact, wchar_t*& fathernamecontact);
	
};