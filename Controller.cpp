#include "Controller.h"


Controller::Controller(Model* model)
{
	this->model = model;
}

void Controller::setView(ConsoleApp* consoleApp)
{
	this->consoleApp = consoleApp;
}

bool Controller::addСontact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
		return false;
	
	Person p(lastNameContact, firstNameContact, fatherNameContact);
	model->insertPerson(p);

	consoleApp->success();
	return true;
}

bool Controller::deleteContact(
	SQLWCHAR* lastNameContact, 
	SQLWCHAR* firstNameContact, 
	SQLWCHAR* fatherNameContact)
{
	return false;
}

bool Controller::toСhangeContact(
	SQLWCHAR* oldlastNameContact,
	SQLWCHAR* oldfirstNameContact,
	SQLWCHAR* oldfatherNameContact,
	SQLWCHAR* newlastNameContact,
	SQLWCHAR* newfirstNameContact,
	SQLWCHAR* newfatherNameContact)
{
	return false;
}

bool Controller::addPhoneNumberContact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* number, int type)
{
	//PhoneNumber pn;
	//wcscpy_s(pn.number,number);
	//pn.idType = type;

	//model->addPhone(pn);

	//this->consoleApp->success();
	
	return false;
}

bool Controller::deletePhoneNumberContact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* number)
{
	return false;
}

bool Controller::toChangePhoneNumberContact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* oldnumber,
	SQLWCHAR* newnumber)
{
	return false;
}

bool Controller::toChangeTypePhoneNumber(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* number, int type)
{
	return false;
}

bool Controller::findPhoneByFIO(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	return false;
}

bool Controller::toChangeStreetContacn(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* nameStret)
{
	return false;
}

bool Controller::toChangeNumberHome(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	int numberHome)
{
	return false;
}

bool Controller::toChangeNumberApartment(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	int numemberApartment)
{
	return false;
}

bool Controller::findAddressByFIO(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	return false;
}

bool Controller::findContactBy4NumberPhone(SQLWCHAR* number4)
{
	return false;
}

bool Controller::addAddress(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* nameStreet,
	int numberHome, int numberApartment)
{
	return false;
}

bool Controller::deleteAddress(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	return false;
}

void Controller::experiment() 
{
	//testFindPhone01(true);
	//testFindPhone10();

	//testFindPhoneNameErr();
}

//01 - загрузка из памяти
void Controller::testFindPhone01(bool isOnline) 
{
	if(!isOnline) 
		model->dbc = nullptr;
	
	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Ivanov");
	wcscpy_s(firstname, L"Ivan");
	wcscpy_s(fathername, L"Ivanovich");

	SQLWCHAR phoneNumber[strSZ];
	
	wcscpy_s(phoneNumber,L"228");
	
	int type = 1;

	//инициализаця контакта и телефона
	PhoneNumber pn(phoneNumber, type);
	Person p(lastname,firstname,fathername);

	//вставка объектов в справочники модели, обходя insert()
	model->personTable.push_back(p);
	model->phoneNumberTable.push_back(pn);

	//вставленному контакту привязываем указатель вставленного в справочник телефона
	model->personTable.back().setPhoneNumber(&model->phoneNumberTable.back());	

	Person* t;

	int q = 0;
	t = &model->findPerson(p, pn, q);
}

void Controller::testFindPhone10() 
{
	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Ivanov");
	wcscpy_s(firstname, L"Ivan");
	wcscpy_s(fathername, L"Ivanovich");

	SQLWCHAR phoneNumber[strSZ];

	wcscpy_s(phoneNumber, L"228");

	int type = 1;

	//инициализаця контакта и телефона
	PhoneNumber pn(phoneNumber, type);
	Person p(lastname, firstname, fathername);

	Person* t;

	int q = 0;
	t = &model->findPerson(p, pn, q);
}

void Controller::testFindPhoneNameErr() 
{
	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Ivfffffeanov");
	wcscpy_s(firstname, L"Ivan");
	wcscpy_s(fathername, L"Ivanovich");

	SQLWCHAR phoneNumber[strSZ];

	wcscpy_s(phoneNumber, L"228");

	int type = 1;

	//инициализаця контакта и телефона
	PhoneNumber pn(phoneNumber, type);
	Person p(lastname, firstname, fathername);

	Person* t;

	int q = 0;
	t = &model->findPerson(p, pn, q);
}