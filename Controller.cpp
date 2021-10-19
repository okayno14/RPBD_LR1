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

Person* Controller::find_Person()
{
	Person* tmpfree = nullptr;
	try
	{
		/*poisk s null*/
		/*tmpfree = find;*/
	}
	catch (int debag)
	{
		throw - 2;
	}
	return tmpfree;
}

Person* Controller::find_Person(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	Person* tmp = nullptr;
	wchar_t* number;

	try
	{
		/*tmp = find*/
	}catch(int debag)
	{
		number = this->consoleApp->get_a_number();
		try
		{
			/*poisk po fio i telefony*/
			/*tmp = find*/

			
		}
		catch (int debag2)
		{
			tmp = find_Person(
				lastNameContact,
				firstNameContact,
				fatherNameContact,
				number);
		}
	}
	return tmp;
}

Person* Controller::find_Person(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* phonenumber)
{
	Person* tmptwo = nullptr;
	wchar_t* address = this->consoleApp->get_a_address();
	try
	{
		/*poisk po addresu fio i telephonu*/
		/*tmptwo = find*/
		
		
	}
	catch (int debag)
	{
		tmptwo = find_Person();

		////null poisk
		//try
		//{

		//}
		//catch (int debag2)
		//{
		//	//pizdech
		//}
	}
	return tmptwo;
}

