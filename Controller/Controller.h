#pragma once


class Controller
{
	//Model mod;
public:
	bool add—ontact(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact) {};
	bool deleteContact(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact) {};
	bool to—hangeContact(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact) {};
	
	
	bool addPhoneNumberContact(SQLWCHAR* number) {};
	bool deletePhoneNumberContact(SQLWCHAR* number) {};
	bool toChangePhoneNumberContact(SQLWCHAR* lastNameContact,
		SQLWCHAR* firstNameContact, SQLWCHAR* fatherNameContact,
		SQLWCHAR* oldnumber, SQLWCHAR* newnumber) {};
	
	bool toChangeTypePhoneNumber(int type) {};
	bool findPhoneByFIO(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact,
		SQLWCHAR* fatherNameContact) {};///
	bool changeTheStreet(SQLWCHAR* nameStreet) {};
	bool deleteStreetContacn(SQLWCHAR* nameStret) {};
	bool toChangeNumberHome(int numberHome) {};
	bool toChangeNumberApartment(int numemberApartment) {};
	bool findAddressByFIO(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact, SQLWCHAR* fatherNameContact) {};
	bool findContactBy4NumberPhone(SQLWCHAR* number4) {};
	
};



///*
//bool Controller::add—ontact(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact, SQLWCHAR* fatherNameContact)
//{
//	if(lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
//		return false;
//
//	//poisk
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		AddPerson(lastNameContact, firstNameContact, fatherNameContact);
//	}
//	else
//	{
//		/// Persona nety
//		return false;
//	}
//
//
//	return true;
//}
//
//inline bool Controller::deleteContact(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact, SQLWCHAR* fatherNameContact)
//{
//	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		RemovePerson(lastNameContact, firstNameContact, fatherNameContact);
//	}
//	else
//	{
//		//Persona nebylo i tak
//		return false;
//	}
//	
//
//	return true;
//}				
//				
//inline bool Controller::to—hangeContact(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact, SQLWCHAR* fatherNameContact)
//{				
//	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
//		return false;
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(lastNameContact, firstNameContact, fatherNameContact);//edit dlya izmenenia
//	}
//	else
//	{
//		return false;
//	}
//
//	
//	return true;
//}
//
//inline bool Controller::addPhoneNumberContact(SQLWCHAR* number)
//{
//	if (number == NULL)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(1,/*FIO*/)// peregruzki v classe
//			//3x char peregruz
//	}
//	else
//	{
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::deletePhoneNumberContact(SQLWCHAR* number)
//{
//	if (number == NULL)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(2,/*FIO number*/)// peregruzki v classe
//			//3x char peregruz
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::toChangePhoneNumberContact(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact, SQLWCHAR* fatherNameContact, SQLWCHAR* oldnumber, SQLWCHAR* newnumber)
//{
//	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
//		return false;
//
//	if (newnumber == NULL)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(1,/*FIO*//*phoneNumber*/)// peregruzki v classe
//			//4x char peregruz
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::toChangeTypePhoneNumber(int type)
//{
//	if (type < 0 || type > 3)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(1,/*Type*/)// peregruzki v classe
//			//char peregruz
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//
//	return true;
//}
//
//inline bool Controller::findPhoneByFIO(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact, SQLWCHAR* fatherNameContact)
//{
//	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		//FindPhone();
//		
//		////////////dobavit v shemy
//		FindPhoneNumber(lastNameContact, firstNameContact, fatherNameContact);
//
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::changeTheStreet(SQLWCHAR* nameStreet)
//{
//	if (nameStreet == NULL)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(2,/*Street*/)// peregruzki v classe
//			//char peregruz
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::deleteStreetContacn(SQLWCHAR* nameStret)
//{
//	if (nameStreet == NULL)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(3,/*Street*/)// peregruzki v classe
//			//char peregruz
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::toChangeNumberHome(int numberHome)
//{
//	if (numberHome <= 0)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(1,/*numberHome*/)// peregruzki v classe
//			//int peregruz
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::toChangeNumberApartment(int numberApartment)
//{
//	if (numberApartment <= 0)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		EditPerson(2,/*numberApartment*/)// peregruzki v classe
//			//int peregruz
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::findAddressByFIO(SQLWCHAR* lastNameContact, SQLWCHAR* firstNameContact, SQLWCHAR* fatherNameContact)
//{
//	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
//		return false;
//
//	if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
//	{
//		//vivod adresa na view
//		FindAddress(lastNameContact, firstNameContact, fatherNameContact);
//	}
//	else
//	{
//		//Persona nebylo
//		return false;
//	}
//
//	return true;
//}
//
//inline bool Controller::findContactBy4NumberPhone(SQLWCHAR* number4)
//{
//	if (number4 == NULL)
//		return false;
//
//	findBy4(number4);
//
//	return true;
//}*/
