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

	bool add—ontact(
		SQLWCHAR* lastNameContact, 
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);
	bool deleteContact(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);
	bool to—hangeContact(
		SQLWCHAR* oldlastNameContact,
		SQLWCHAR* oldfirstNameContact,
		SQLWCHAR* oldfatherNameContact,
		SQLWCHAR* newlastNameContact,
		SQLWCHAR* newfirstNameContact,
		SQLWCHAR* newfatherNameContact);
	bool addPhoneNumberContact(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact,
		SQLWCHAR* number,
		int type);
	bool deletePhoneNumberContact(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact,
		SQLWCHAR* number);
	bool toChangePhoneNumberContact(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact,
		SQLWCHAR* oldnumber,
		SQLWCHAR* newnumber);
	bool toChangeTypePhoneNumber(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact,
		SQLWCHAR* number,
		int type);
	bool findPhoneByFIO(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);
	bool toChangeStreetContacn(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact,
		SQLWCHAR* nameStret);
	bool toChangeNumberHome(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact,
		int numberHome);
	bool toChangeNumberApartment(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact,
		int numemberApartment);
	bool findAddressByFIO(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);
	bool findContactBy4NumberPhone(SQLWCHAR* number4);
	bool addAddress(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact,
		SQLWCHAR* nameStreet,
		int numberHome,
		int numberApartment);
	bool deleteAddress(
		SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact);


	void experiment();
	void testFindFIO();
	void testFindPhone01();
	void testFindPhone01(bool isOnline);
	void testFindPhone10();
	void testFindPhoneNameErr();
	void testFindPhoneAddress01(bool isOnline);
	void testFindPhoneAddress10();
	void testUpdateAddrOffline();
	void testUpdateAddrPhoneOffline();
	void testUpdateAddrPhoneOnline();
	void testUpdateAddrOnline();
	void testUpdatePhoneOnline();
};