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
		//âûâåñòè íà ýêðàí èíôó
	};
	
}

void Controller::setView(ConsoleApp* consoleApp)
{
	this->consoleApp = consoleApp;
}

Person* Controller::addÑontact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
		throw - 1;
		
	Person p(lastNameContact, firstNameContact, fatherNameContact);
	Person* temp;
	temp = &model->insertPerson(p);

	consoleApp->success();
	return temp;
}

bool Controller::deleteContact(
	Person* p)
{
	if (p == NULL)
		return false;

	model->deletePerson(p);
	return true;
}

bool Controller::toÑhangeContact(
	Person* p, 
	SQLWCHAR* newlastNameContact, 
	SQLWCHAR* newfirstNameContact, 
	SQLWCHAR* newfatherNameContact)
{
	if (newlastNameContact == NULL || newfirstNameContact == NULL || newfatherNameContact == NULL || p == NULL)
	{
		return false;
	}
	Person newp(newlastNameContact, newfirstNameContact, newfatherNameContact);
	model->updatePerson(p, newp);
	return true;
}

bool Controller::addPhoneNumberContact(Person* p, PhoneNumber* pn)
{
	if (p == NULL || pn == NULL)
		return false;
	Person newPer = *p;
	newPer.addPhoneNumber(pn);

	model->updatePerson(p, newPer);
	return true;
}

bool Controller::deletePhoneNumberContact(Person* p, SQLWCHAR* number)
{
	if (p == NULL || number == NULL)
		return false;
	//?????
	return true;
}

void Controller::findContactBy4NumberPhone(std::vector<int> number4)
{
	std::vector<Person*> tmp = model->findBy4(number4);
	for (int i = 0; i < tmp.size(); i++)
	{
		Person* p = tmp[i];
		this->consoleApp->drawPerson(p);
	}
}

bool Controller::addAddress(Person* p, Address* ad)
{
	if (p == NULL || ad == NULL)
		return false;

	Person newPer = *p;
	newPer.setAddress(ad);

	model->updatePerson(p, newPer);
	return true;
}

bool Controller::deleteAddress(Person* p)
{
	return false;////????????????
}

Person* Controller::findPerson(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact, 
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
	{
		cout << "íå âñå äàííûå!" << endl;
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
					throw - 1;
				}
				if (count3 == 1)
				{
					return tmp;
				}
				if (count > 1)
				{
					cout << "Àòàêà êëîíîâ" << endl;
					throw - 2;
				}
			}
		}
	}
}

bool Controller::updateAddress(Person* p, Address* ad)
{
	if (p == NULL || ad == NULL)
		return false;

	Person newPer = *p;
	newPer.setAddress(ad);

	model->updatePerson(p, newPer);
	return true;
}

bool Controller::updatePhoneNumber(Person* p, PhoneNumber* ph)
{
	if (p == NULL || ph == NULL)
		return false;

	Person newPer = *p;
	newPer.addPhoneNumber(ph);

	model->updatePerson(p, newPer);
	return true;
}
