#pragma once
#include "Controller.h"

/// <summary>
/// Добавление контакта в ТК
/// </summary>
/// <param name="lastNameContact">Имя</param>
/// <param name="firstNameContact">Фамилия</param>
/// <param name="fatherNameContact">Отчество</param>
/// <returns></returns>
bool Controller::addСontact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
		return false;
	/*wcout << lastNameContact << endl;
	wcout << firstNameContact << endl;
	wcout << fatherNameContact << endl;
	cout << "Это вашше?" << endl;*/
	//system("pause");
	////poisk
	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	AddPerson(lastNameContact, firstNameContact, fatherNameContact);
	//}
	//else
	//{
	//	/// Persona nety
	//	return false;
	//}

	lastNameContact = NULL;
	firstNameContact = NULL;
	fatherNameContact = NULL;
	return true;
}

/// <summary>
/// Удаление контакта из ТК
/// </summary>
/// <param name="lastNameContact">Имя</param>
/// <param name="firstNameContact">Фамилия</param>
/// <param name="fatherNameContact">Отчество</param>
/// <returns></returns>
inline bool Controller::deleteContact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
		return false;
	/*wcout << lastNameContact << endl;
	wcout << firstNameContact << endl;
	wcout << fatherNameContact << endl;
	cout << "Это вашше?" << endl;*/
	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	RemovePerson(lastNameContact, firstNameContact, fatherNameContact);
	//}
	//else
	//{
	//	//Persona nebylo i tak
	//	return false;
	//}

	lastNameContact = NULL;
	firstNameContact = NULL;
	fatherNameContact = NULL;
	return true;
}

/// <summary>
/// Обновление ФИО контакта
/// </summary>
/// <param name="oldlastNameContact"></param>
/// <param name="oldfirstNameContact"></param>
/// <param name="oldfatherNameContact"></param>
/// <param name="newlastNameContact"></param>
/// <param name="newfirstNameContact"></param>
/// <param name="newfatherNameContact"></param>
/// <returns></returns>
inline bool Controller::toСhangeContact(
	SQLWCHAR* oldlastNameContact,
	SQLWCHAR* oldfirstNameContact,
	SQLWCHAR* oldfatherNameContact,
	SQLWCHAR* newlastNameContact,
	SQLWCHAR* newfirstNameContact,
	SQLWCHAR* newfatherNameContact)
{
	if (oldlastNameContact == NULL
		&& oldfirstNameContact == NULL
		&& oldfatherNameContact == NULL
		&& newlastNameContact == NULL
		&& newfirstNameContact == NULL
		&& newfatherNameContact == NULL)
		return false;///chastnii slychai na momen crazi polzovatelya
	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	EditPerson(lastNameContact, firstNameContact, fatherNameContact);//edit dlya izmenenia
	//}
	//else
	//{
	//	return false;
	//}


	return true;
}

/// <summary>
/// Добавить телефонный номер контакту
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <param name="number"></param>
/// <returns></returns>
inline bool Controller::addPhoneNumberContact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* number,
	int type)
{
	if (number == NULL)
		return false;

	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	EditPerson(1,/*FIO*/)// peregruzki v classe
	//		//3x char peregruz
	//}
	//else
	//{
	//	return false;
	//}

	return true;
}

/// <summary>
/// Удалить телефонный номер контакту
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <param name="number"></param>
/// <returns></returns>
inline bool Controller::deletePhoneNumberContact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* number)
{
	if (number == NULL)
		return false;

	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	EditPerson(2,/*FIO number*/)// peregruzki v classe
	//		//3x char peregruz
	//}
	//else
	//{
	//	//Persona nebylo
	//	return false;
	//}

	return true;
}

/// <summary>
/// Изменитьтелефонный номер контакту
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <param name="oldnumber"></param>
/// <param name="newnumber"></param>
/// <returns></returns>
inline bool Controller::toChangePhoneNumberContact(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* oldnumber,
	SQLWCHAR* newnumber)
{
	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
		return false;

	if (newnumber == NULL)
		return false;

	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	EditPerson(1,/*FIO*//*phoneNumber*/)// peregruzki v classe
	//		//4x char peregruz
	//}
	//else
	//{
	//	//Persona nebylo
	//	return false;
	//}

	return true;
}

/// <summary>
/// Изменить тип телефонного номера контакту
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <param name="type"></param>
/// <returns></returns>
inline bool Controller::toChangeTypePhoneNumber(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* number,
	int type)
{
	if (type < 0 || type > 3)
		return false;

	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	EditPerson(1,/*Type*/)// peregruzki v classe
	//		//char peregruz
	//}
	//else
	//{
	//	//Persona nebylo
	//	return false;
	//}


	return true;
}

/// <summary>
/// Поиск телефонного номера по ФИО контакта
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <returns></returns>
inline bool Controller::findPhoneByFIO(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
		return false;

	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	//FindPhone();
	//	
	//	////////////dobavit v shemy
	//	FindPhoneNumber(lastNameContact, firstNameContact, fatherNameContact);

	//}
	//else
	//{
	//	//Persona nebylo
	//	return false;
	//}

	return true;
}

/// <summary>
/// Изменить улицу контакту
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <param name="nameStret"></param>
/// <returns></returns>
inline bool Controller::toChangeStreetContacn(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* nameStret)
{
	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
		return false;

	return true;
}

/// <summary>
/// Изменить номер лома
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <param name="numberHome"></param>
/// <returns></returns>
inline bool Controller::toChangeNumberHome(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	int numberHome)
{
	if (numberHome <= 0)
		return false;

	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	EditPerson(1,/*numberHome*/)// peregruzki v classe
	//		//int peregruz
	//}
	//else
	//{
	//	//Persona nebylo
	//	return false;
	//}

	return true;
}

/// <summary>
/// Изменить номер квартиры
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <param name="numberApartment"></param>
/// <returns></returns>
inline bool Controller::toChangeNumberApartment(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	int numberApartment)
{
	if (numberApartment <= 0)
		return false;

	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	EditPerson(2,/*numberApartment*/)// peregruzki v classe
	//		//int peregruz
	//}
	//else
	//{
	//	//Persona nebylo
	//	return false;
	//}

	return true;
}

/// <summary>
/// Поиск адреса по ФИО
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <returns>vozvrat v consolApp adres (v modeli)</returns>
inline bool Controller::findAddressByFIO(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL && firstNameContact == NULL && fatherNameContact == NULL)
		return false;

	//if (FindByNames(lastNameContact, firstNameContact, fatherNameContact))
	//{
	//	//vivod adresa na view
	//	FindAddress(lastNameContact, firstNameContact, fatherNameContact);
	//}
	//else
	//{
	//	//Persona nebylo
	//	return false;
	//}

	return true;
}



/// <summary>
/// Добавление адреса контакту
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <param name="nameStreet"></param>
/// <param name="numberHome"></param>
/// <param name="numberApartment"></param>
/// <returns></returns>
inline bool Controller::addAddress(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact,
	SQLWCHAR* nameStreet,
	int numberHome,
	int numberApartment)
{
	if (lastNameContact == NULL
		&& firstNameContact == NULL
		&& fatherNameContact == NULL)
		return false;


	return true;
}


/// <summary>
/// Удалить адркес контакту
/// </summary>
/// <param name="lastNameContact"></param>
/// <param name="firstNameContact"></param>
/// <param name="fatherNameContact"></param>
/// <returns></returns>
inline bool Controller::deleteAddress(
	SQLWCHAR* lastNameContact,
	SQLWCHAR* firstNameContact,
	SQLWCHAR* fatherNameContact)
{
	if (lastNameContact == NULL
		&& firstNameContact == NULL
		&& fatherNameContact == NULL)
		return false;

	return false;
}
