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
	bool runTimeProgram;// ������ � ������ ����� ���������
	int MainMenu;//������������ ��� ����� �������������
	//int UntMenu;//?????
	int ch;//???????
	Controller* con;
//��������� �� ���������� �� ������

public:
	ConsoleApp();

	/*����� ���� ����������*/
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

	void deletePhoneNumber();
	void deleteAddress();

	void success();
	void offlineStatus();
	void fail();

	wchar_t* get_a_number();/*find fio and phoneNumber*/
	wchar_t* get_a_address();/*find fio and phoneNumber and address*/
	
};