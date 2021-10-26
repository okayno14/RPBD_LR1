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
	Controller* con;
	Person* currentPerson;
public:
	ConsoleApp();

	/*��� ������ ��� ����������� ���� ���������*/
	void Menu();
	void MenuPC();


	void setController(Controller* con);
	
	/*�������� ���� ��� ���������� �����������*/
	void run();
	void runPC();

	/*������� ��� ������ ������ switch*/
	Person* findPerson();
	Person* addContact();
	void deleteContact();
	void findto4();
	void updateFIOcontacte();
	void addAddress();
	void addPhoneNumber();
	void deletePhoneNumber();
	void deleteAddress();

	/*��������������� ������*/
	void success();
	void offlineStatus();
	void fail();
	bool toRunMenuTwo();

	/*������ ��� �������� ����� � ������� ��������*/
	wchar_t* get_a_number();
	wchar_t* get_a_addressName();
	int get_a_type_number();
	int get_a_apartment();
	int get_a_numberhome();
	
};