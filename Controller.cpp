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
		model->tryDB();
	}
	catch (int err) 
	{
		switch (err)
		{
			case -1:
			{
				//нет конфиг файла для новой таблицы
				consoleApp->noTableConfig();
				break;
			}
			case -2: 
			{
				//вывести на экран инфу
				consoleApp->offlineStatus();
				break;
			}
			case -3: 
			{
				//нет конфига подключения к бд
				break;
			}
		}
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
	Person p(lastNameContact, firstNameContact, fatherNameContact);
	Person* temp = nullptr;

	if (lastNameContact == NULL || firstNameContact == NULL || fatherNameContact == NULL)
		throw - 1;
		
	
	
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

bool Controller::toСhangeContact(
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
		consoleApp->drawPhoneNumbers(p->getNumbers());
	}
}

void Controller::findFIOALL(Person p)
{
	vector<Person*>tmp= model->find_List_FIO(p);

	for (int i = 0; i < tmp.size(); i++)
	{
		Person* p = tmp[i];
		this->consoleApp->drawPerson(p);
		consoleApp->drawPhoneNumbers(p->getNumbers());
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
		tmp = &model->findPerson(p, false, count);
		if (count == 0) {
			throw - 1;
		}

		if (count == 1)
		{
			return tmp;
		}
		if (count > 1) 
		{

			wchar_t* number;
			number = this->consoleApp->get_a_number();
			int type = this->consoleApp->get_a_type_number();
			PhoneNumber ph(number, type);
			tmp = &model->findPerson(p, ph, count);

			if (count == 0) {
				throw - 1;
			}
			if (count == 1) 
			{
				return tmp;
			}
			if (count > 1) {
				wchar_t* address;
				int numHome;
				int numApartment;
				address = this->consoleApp->get_a_addressName();
				numHome = this->consoleApp->get_a_numberhome();
				numApartment = this->consoleApp->get_a_apartment();
				Address ad(address,numHome,numApartment);
				tmp = &model->findPerson(p, ph, ad, count);
				if (count == 0) 
				{
					throw - 1;
				}
				if (count == 1)
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

bool Controller::updateAddress(Person* p, Address* ad)
{
	if (p == NULL || ad == NULL)
		return false;

	Person newPer = *p;
	newPer.setAddress(ad);

	model->updatePerson(p, newPer);
	return true;
}

bool Controller::updatePhoneNumber(Person* p, PhoneNumber* ph, int ch)
{
	if (p == NULL || ph == NULL)
		return false;

	Person newPer = *p;
	newPer.setPhoneNumber(ch-1,ph);

	model->updatePerson(p, newPer);
	return true;
}
