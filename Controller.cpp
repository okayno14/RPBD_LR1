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

Person* Controller::addСontact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
		throw - 1;
		//return false;
	
	Person p(lastNameContact, firstNameContact, fatherNameContact);
	model->insertPerson(p);

	consoleApp->success();
	//return true;
	return &p;
}

bool Controller::deleteContact(
	Person* p)
{
	

	return false;
}

bool Controller::toСhangeContact(
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

bool Controller::deletePhoneNumberContact(Person* p, SQLWCHAR* number)
{
	return false;
}



/*нужно получать int[]*/
bool Controller::findContactBy4NumberPhone(SQLWCHAR* number4)
{
	return false;
}

bool Controller::addAddress(Person* p, SQLWCHAR* nameStreet, int numberHome, int numberApartment)
{
	return false;
}

bool Controller::deleteAddress(Person* p)
{
	return false;
}

Person* Controller::findPerson(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact, 
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
	{
		cout << "не все данные!" << endl;
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
			cout << "Контактов не обнаружено" << endl;
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
				cout << "Контактов не обнаружено" << endl;
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
					cout << "Контактов не обнаружено" << endl;
					throw - 1;
				}
				if (count3 == 1)
				{
					return tmp;
				}
				if (count > 1)
				{
					cout << "Атака клонов" << endl;
					throw - 2;
				}
			}
		}
	}
}
