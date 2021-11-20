#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <sstream>
#include <cstring>

#include "Model.h"
#include "View.h"

using namespace std;

class Model;
class ConsoleApp;

class Controller
{
private:
	Model* model;
	ConsoleApp* consoleApp;

public:
	Controller(Model* model);
	Controller(ConsoleApp* view);
	~Controller() { delete model;}
	void setView(ConsoleApp* consoleApp);

	Person* add—ontact(
		SQLWCHAR* lastNameContact, 
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);
	bool deleteContact(
		Person* p);
	bool to—hangeContact(
		Person* p,
		SQLWCHAR* newlastNameContact,
		SQLWCHAR* newfirstNameContact,
		SQLWCHAR* newfatherNameContact);
	bool addPhoneNumberContact(
		Person* p,
		PhoneNumber* pn);
	bool deletePhoneNumberContact(
		Person* p,
		SQLWCHAR* number);
	
	void findContactBy4NumberPhone(std::vector<int> number4);
	void findFIOALL(SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);

	bool addAddress(
		Person* p,
		Address* ad);

	Person* findPerson(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);

	bool updateAddress(
		Person* p,
		Address* ad);
	bool updatePhoneNumber(
		Person* p,
		PhoneNumber* ph, int ch);

};