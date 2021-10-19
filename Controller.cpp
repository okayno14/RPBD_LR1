#include "Controller.h"


Controller::Controller(Model* model)
{
	this->model = model;
}

void Controller::setView(ConsoleApp* consoleApp)
{
	this->consoleApp = consoleApp;
}

bool Controller::addÑontact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
		return false;
	lastNameContact = NULL;
	firstNameContact = NULL;
	fatherNameContact = NULL;
	return true;
}

bool Controller::deleteContact(
	SQLWCHAR* lastNameContact, 
	SQLWCHAR* firstNameContact, 
	SQLWCHAR* fatherNameContact)
{
	return false;
}

bool Controller::toÑhangeContact(
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
	PhoneNumber pn;
	wcscpy_s(pn.number,number);
	pn.idType = type;

	model->addPhone(pn);

	this->consoleApp->success();
	
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
/* èçìåíèòü**
òåïðü íóæíî ïåðåäîâàòü ñûëêó ñ÷åò÷èêà  â ìåäîòû ìîäåëè
*/


Person* Controller::find_Person(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	/*Person tmp(lastNameContact,firstNameContact,fatherNameContact);*/
	wchar_t* number;
	wchar_t* address;
	int T = 0; // schetchik

	/*tmp = this->model->findPerson();*/

	if (T > 1)
	{
		number = this->consoleApp->get_a_number();
		/*tmp = this->model->findPerson()*///fio number

		/*????
		if (???)
		{
			addres = this->consoleApp->get_a_address();
			tmp = this->model->findPerson();

			if(???)
			{
				tmp = this->model->findPerson();// poisk pustogo
				
				if(voobwe netu)
				{
					throw -1;// oblamivaem returny
				}

				return tmp;
			}

			return tmp;
		}
		*/

		/*return tmp*/
	}

	/*suda */
	
	return nullptr;///<----- poka tut
}


