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
	~Controller() { delete model; }
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
		SQLWCHAR* number,
		int type);
	bool deletePhoneNumberContact(
		Person* p,
		SQLWCHAR* number);
	
	std::vector<Person*> findContactBy4NumberPhone(std::vector<int> number4);
	bool addAddress(
		Person* p,
		SQLWCHAR* nameStreet,
		int numberHome,
		int numberApartment);
	bool deleteAddress(
		Person* p);
	Person* findPerson(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);

};