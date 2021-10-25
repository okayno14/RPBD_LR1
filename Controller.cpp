#include "Controller.h"


Controller::Controller(Model* model)
{
	this->model = model;
}

Controller::Controller(ConsoleApp* view)
{
	try 
	{
		this->consoleApp = view;
		this->model = new Model();
	}
	catch (int) 
	{
		consoleApp->offlineStatus();
		//вывести на экран инфу
	};
	
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
	//testFindPhoneAddress01(false);
	//testFindPhoneAddress10();

	//testUpdateAddrOffline();
	//testUpdateAddrPhoneOffline();

	//testUpdateAddrOnline();

	//testUpdatePhoneOnline();

	/*SQLWCHAR streetName[strSZ];
	wcscpy_s(streetName, L"Voennaya");
	Address add(streetName,40,37);
	
	int q(0);

	Address* f = &model->insertAddress(add);
	model->getState(f);*/
	
	//testUpdateAddrPhoneOffline();

	//testFindFIO();

	//testUpdateAddrOffline();
	//testUpdateAddrOnline();
	//testUpdateAddrPhoneOnline();


	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Ivanov");
	wcscpy_s(firstname, L"Ivan");
	wcscpy_s(fathername, L"Ivanovich");

	Person p(lastname, firstname, fathername);

	Person* f = nullptr;
	int q(0);
	


	
	f = &model->insertPerson(p);

	SQLWCHAR number[strSZ];
	wcscpy_s(number, L"8888888888888");
	PhoneNumber pn(number, 1);

	p.addPhoneNumber(&pn);

	model->updatePerson(f, p);

	model->deletePerson(f);
}

void Controller::testFindFIO() 
{
	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Zaykin");
	wcscpy_s(firstname, L"Igor");
	wcscpy_s(fathername, L"Ivanovich");

	SQLWCHAR phoneNumber[strSZ];

	wcscpy_s(phoneNumber, L"228");

	
	Person p(lastname, firstname, fathername);


	Person* t;

	int q = 0;
	t = &model->findPerson(p, false, q);
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

	p.addPhoneNumber(&pn);

	//вставка объектов в справочники модели, обходя insert()
	//model->personTable.push_back(p);
	//model->phoneNumberTable.push_back(pn);

	//вставленному контакту привязываем указатель вставленного в справочник телефона
	//model->personTable.back().addPhoneNumber(&model->phoneNumberTable.back());	

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

void Controller::testFindPhoneAddress01(bool isOnline) 
{
	if (!isOnline)
		model->dbc = nullptr;

	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Ivanov");
	wcscpy_s(firstname, L"Ivan");
	wcscpy_s(fathername, L"Ivanovich");

	SQLWCHAR phoneNumber[strSZ];

	wcscpy_s(phoneNumber, L"228");
	int type = 1;

	SQLWCHAR streetName[strSZ];
	wcscpy_s(streetName, L"PUshkina");
	int home = 404;
	int apppartement = 502;	
	

	//инициализаця контакта, телефона, адреса
	PhoneNumber pn(phoneNumber, type);
	Person p(lastname, firstname, fathername);
	Address add(streetName, home, apppartement);

	//вставка объектов в справочники модели, обходя insert()
	model->personTable.push_back(p);
	model->phoneNumberTable.push_back(pn);
	model->addressTable.push_back(add);

	//вставленному контакту привязываем указатель вставленного в справочник телефона и адреса
	model->personTable.back().addPhoneNumber(&model->phoneNumberTable.back());
	model->personTable.back().setAddress(&model->addressTable.back());

	Person* t;

	int q = 0;
	t = &model->findPerson(p, pn, add, q);
}

void Controller::testFindPhoneAddress10() 
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

	SQLWCHAR streetName[strSZ];
	wcscpy_s(streetName, L"PUshkina");
	int home = 404;
	int apppartement = 502;


	//инициализаця контакта, телефона, адреса
	PhoneNumber pn(phoneNumber, type);
	Person p(lastname, firstname, fathername);
	Address add(streetName, home, apppartement);

	Person* t;

	int q = 0;
	t = &model->findPerson(p, pn, add, q);
}

void Controller::testUpdateAddrOffline()
{
	model->dbc = nullptr;

	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Ivanov");
	wcscpy_s(firstname, L"Ivan");
	wcscpy_s(fathername, L"Ivanovich");

	Person p(lastname, firstname, fathername);
	
	Person* f = nullptr;
	f = &model->insertPerson(p);

	SQLWCHAR streetName[strSZ];
	wcscpy_s(streetName, L"Ivanova");
	Address add(streetName, 1,2);

	Person copy = p;

	copy.setAddress(&add);

	model->updatePerson(f, copy);


	wcscpy_s(streetName, L"Ivanova");
	Address add1(streetName, 13, 15);
	copy.setAddress(&add1);

	model->updatePerson(f,copy);
};

void Controller::testUpdateAddrPhoneOffline() 
{
	model->dbc = nullptr;

	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Ivanov");
	wcscpy_s(firstname, L"Ivan");
	wcscpy_s(fathername, L"Ivanovich");

	Person p(lastname, firstname, fathername);

	Person* f = nullptr;
	f = &model->insertPerson(p);

	SQLWCHAR streetName[strSZ];
	wcscpy_s(streetName, L"Ivanova");

	Address add(streetName, 1, 2);

	SQLWCHAR number[strSZ];
	wcscpy_s(number, L"334-58-96");
	PhoneNumber pn(number,1);

	SQLWCHAR number1[strSZ];
	wcscpy_s(number, L"44444444");
	PhoneNumber pn1(number, 2);
	
	Person copy = p;

	copy.addPhoneNumber(&pn);
	copy.addPhoneNumber(&pn1);
	copy.setAddress(&add);

	model->updatePerson(f, copy);
}

void Controller::testUpdateAddrPhoneOnline() 
{
	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Ivanov");
	wcscpy_s(firstname, L"Ivan");
	wcscpy_s(fathername, L"Ivanovich");

	Person p(lastname, firstname, fathername);

	Person* f = nullptr;
	f = &model->insertPerson(p);

	SQLWCHAR streetName[strSZ];
	wcscpy_s(streetName, L"Ivanova");

	Address add(streetName, 1, 2);

	SQLWCHAR number[strSZ];
	wcscpy_s(number, L"334-58-96");
	PhoneNumber pn(number, 1);

	SQLWCHAR number1[strSZ];
	wcscpy_s(number, L"44444444");
	PhoneNumber pn1(number, 2);

	Person copy = p;

	copy.addPhoneNumber(&pn);
	copy.addPhoneNumber(&pn1);
	copy.setAddress(&add);

	model->updatePerson(f, copy);
}


void Controller::testUpdateAddrOnline() 
{
	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname,L"Alekseev");
	wcscpy_s(firstname, L"Aleksandr");
	wcscpy_s(fathername, L"Konstantinovich");

	int q = 0;
	
	Person* t = &model->insertPerson(Person(lastname, firstname, fathername));
	//Person* t = & model->findPerson(Person(lastname, firstname, fathername),false, q);

	Person updated = *t;
	
	SQLWCHAR streetname[strSZ];
	wcscpy_s(streetname, L"Lavrentieva");

	Address add(streetname, 51, 81);
	updated.setAddress(&add);

	model->updatePerson(t, updated);
}

void Controller::testUpdatePhoneOnline() 
{
	SQLWCHAR lastname[strSZ];
	SQLWCHAR firstname[strSZ];
	SQLWCHAR fathername[strSZ];

	wcscpy_s(lastname, L"Alekseev");
	wcscpy_s(firstname, L"Aleksandr");
	wcscpy_s(fathername, L"Konstantinovich");

	int q = 0;
	Person* t = &model->findPerson(Person(lastname, firstname, fathername), false, q);

	Person updated = *t;

	SQLWCHAR number[strSZ];
	wcscpy_s(number, L"332-47-73");
	
	PhoneNumber pn(number,3);

	updated.setPhoneNumber(0,&pn);

	model->updatePerson(t, updated);
}