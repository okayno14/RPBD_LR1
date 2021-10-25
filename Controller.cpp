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
		//������� �� ����� ����
	};
	
}

void Controller::setView(ConsoleApp* consoleApp)
{
	this->consoleApp = consoleApp;
}

bool Controller::add�ontact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
		return false;
	
	Person p(lastNameContact, firstNameContact, fatherNameContact);
	model->insertPerson(p);

	consoleApp->success();
	return true;
}

bool Controller::deleteContact(
	Person* p)
{
	

	return false;
}

bool Controller::to�hangeContact(
	Person* p, 
	SQLWCHAR* newlastNameContact, 
	SQLWCHAR* newfirstNameContact, 
	SQLWCHAR* newfatherNameContact)
{
	if (newlastNameContact == NULL || newfirstNameContact == NULL || newfatherNameContact == NULL)
	{
		return false;
	}

	return false;
}

bool Controller::addPhoneNumberContact(Person* p, SQLWCHAR* number, int type)
{
	return false;
}


//bool Controller::addPhoneNumberContact(
//	SQLWCHAR* lastNameContact,
//	SQLWCHAR* firstNameContact,
//	SQLWCHAR* fatherNameContact,
//	SQLWCHAR* number, int type)
//{
//	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
//		return false;
//	if (number == NULL)
//		return false;
//	return false;
//}

//bool Controller::deletePhoneNumberContact(
//	SQLWCHAR* lastNameContact,
//	SQLWCHAR* firstNameContact,
//	SQLWCHAR* fatherNameContact,
//	SQLWCHAR* number)
//{
//	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
//		return false;
//	if (number == NULL)
//		return false;
//
//	return false;
//}






/*����� �������� int[]*/
bool Controller::findContactBy4NumberPhone(SQLWCHAR* number4)
{
	return false;
}

//bool Controller::addAddress(
//	SQLWCHAR* lastNameContact,
//	SQLWCHAR* firstNameContact,
//	SQLWCHAR* fatherNameContact,
//	SQLWCHAR* nameStreet,
//	int numberHome, int numberApartment)
//{
//	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
//		return false;
//	if (nameStreet == NULL)
//		return false;
//	return false;
//}

//bool Controller::deleteAddress(
//	SQLWCHAR* lastNameContact,
//	SQLWCHAR* firstNameContact,
//	SQLWCHAR* fatherNameContact)
//{
//	if(lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
//		return false;
//}
Person* Controller::findPerson(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact, 
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
	{
		cout << "�� ��� ������!" << endl;
		throw - 1;
	}

	Person p(lastNameContact, firstNameContact, fatherNameContact);
	Person* tmp;
	int count;

	tmp = &model->findPerson(p, true, count);
	if (count == 1)
		return tmp;

	if(count == 0 || count > 1)
	{
		int cont;
		tmp = &model->findPerson(p, false, cont);
		if (count == 0) {
			cout << "��������� �� ����������" << endl;
			throw - 1;
		}

		if (cont == 1)
		{
			return tmp;
		}
		if (cont > 1) 
		{
			int count2;
			wchar_t* number;
			number = this->consoleApp->get_a_number();
			int type = this->consoleApp->get_a_type_number();
			PhoneNumber ph(number, type);
			tmp = &model->findPerson(p, ph, count2);

			if (count2 == 0) {
				cout << "��������� �� ����������" << endl;
				throw - 1;
			}
			if (count2 == 1) 
			{
				return tmp;
			}
			if (count2 > 1) {
				int count3;
				wchar_t* address;
				int numHome;
				int numApartment;
				address = this->consoleApp->get_a_addressName();
				numHome = this->consoleApp->get_a_numberhome();
				numApartment = this->consoleApp->get_a_apartment();
				Address ad(address,numHome,numApartment);
				tmp = &model->findPerson(p, ph, ad, count3);
				if (count3 == 0) 
				{
					cout << "��������� �� ����������" << endl;
					throw - 1;
				}
				if (count3 == 1)
				{
					return tmp;
				}
				if (count > 1)
				{
					cout << "����� ������" << endl;
					throw - 2;
				}
			}
		}
	}
	



	

	


}
/* ��������**
����� ����� ���������� ����� ��������  � ������ ������
*/


//Person* Controller::find_Person(
//	SQLWCHAR* lastNameContact,
//	SQLWCHAR* firstNameContact,
//	SQLWCHAR* fatherNameContact)
//{
//	/*Person tmp(lastNameContact,firstNameContact,fatherNameContact);*/
//	wchar_t* number;
//	wchar_t* address;
//	int T = 0; // schetchik
//
//	/*tmp = this->model->findPerson();*/
//
//	if (T > 1)
//	{
//		number = this->consoleApp->get_a_number();
//		/*tmp = this->model->findPerson()*///fio number
//
//		/*????
//		if (???)
//		{
//			addres = this->consoleApp->get_a_address();
//			tmp = this->model->findPerson();
//
//			if(???)
//			{
//				tmp = this->model->findPerson();// poisk pustogo
//				
//				if(voobwe netu)
//				{
//					throw -1;// oblamivaem returny
//				}
//
//				return tmp;
//			}
//
//			return tmp;
//		}
//		*/
//
//		/*return tmp*/
//	}
//
//	/*suda */
//	
//	return nullptr;///<----- poka tut
//}


//void Controller::experiment() 
//{
//	//testFindPhone01(true);
//	//testFindPhone10();
//
//	//testFindPhoneNameErr();
//	//testFindPhoneAddress01(false);
//	//testFindPhoneAddress10();
//
//	//testUpdateAddrOffline();
//	//testUpdateAddrPhoneOffline();
//
//	//testUpdateAddrOnline();
//
//	//testUpdatePhoneOnline();
//
//	/*SQLWCHAR streetName[strSZ];
//	wcscpy_s(streetName, L"Voennaya");
//	Address add(streetName,40,37);
//	
//	int q(0);
//
//	Address* f = &model->insertAddress(add);
//	model->getState(f);*/
//	
//	//testUpdateAddrPhoneOffline();
//
//	//testFindFIO();
//
//	//testUpdateAddrOffline();
//	//testUpdateAddrOnline();
//	//testUpdateAddrPhoneOnline();
//
//
//	SQLWCHAR lastname[strSZ];
//	SQLWCHAR firstname[strSZ];
//	SQLWCHAR fathername[strSZ];
//
//	wcscpy_s(lastname, L"Ivanov");
//	wcscpy_s(firstname, L"Ivan");
//	wcscpy_s(fathername, L"Ivanovich");
//
//	Person p(lastname, firstname, fathername);
//
//	Person* f = nullptr;
//	int q(0);
//	f = &model->findPerson(p,false,q);
//
//	SQLWCHAR number[strSZ];
//	wcscpy_s(number, L"8888888888888");
//	PhoneNumber pn(number, 1);
//
//	p = *f;
//	
//	p.setPhoneNumber(0, &pn);
//
//	model->updatePerson(f, p);
//}

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

//01 - �������� �� ������
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

	//������������ �������� � ��������
	PhoneNumber pn(phoneNumber, type);
	Person p(lastname,firstname,fathername);

	p.addPhoneNumber(&pn);

	//������� �������� � ����������� ������, ������ insert()
	//model->personTable.push_back(p);
	//model->phoneNumberTable.push_back(pn);

	//������������ �������� ����������� ��������� ������������ � ���������� ��������
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

	//������������ �������� � ��������
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

	//������������ �������� � ��������
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
	

	//������������ ��������, ��������, ������
	PhoneNumber pn(phoneNumber, type);
	Person p(lastname, firstname, fathername);
	Address add(streetName, home, apppartement);

	//������� �������� � ����������� ������, ������ insert()
	model->personTable.push_back(p);
	model->phoneNumberTable.push_back(pn);
	model->addressTable.push_back(add);

	//������������ �������� ����������� ��������� ������������ � ���������� �������� � ������
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


	//������������ ��������, ��������, ������
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