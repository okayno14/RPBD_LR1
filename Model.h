#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <cstring>

#include "DataBaseConnection.h"

#define strSZ 20

class Model;
class AddressMapper;
class PhoneMapper;
class PersonMapper;

class Address
{
	friend class AddressMapper;
	friend class PersonMapper;
	friend class Model;
	
private:
	SQLWCHAR streetName[strSZ];
	SQLLEN streetNameLen;

	SQLINTEGER home;
	SQLLEN homeLen;

	SQLINTEGER appartement;
	SQLLEN appartementLen;
	
	SQLINTEGER id = -1;
	SQLLEN idLen;

	SQLINTEGER idStreet = -1;
	SQLLEN idStreetLen;

	bool isSynced = false;

public:
	Address(int id = -1, int idStreet = -1)
	{
		this->id = id;
		this->idStreet = idStreet;
	};
	Address(SQLWCHAR* streetName, int home, int appartement) 
	{
		wcscpy_s(this->streetName, streetName);
		this->home = home;
		this->appartement = appartement;
	}
	bool isEqual(const Address* ad) 
	{
		const SQLWCHAR* streetNameOrig = this->streetName;
		const SQLWCHAR* streetNameOther = ad->streetName;
		if
		(
			wcscmp(streetNameOrig, streetNameOther) == 0 &&
			home == ad->home &&
			appartement == ad->appartement
		)
			return true;
		else
			return false;
	};
};

class PhoneNumber
{
	friend class PhoneMapper;
	friend class Model;
	friend class PersonMapper;
	
private:
	SQLINTEGER id = -1;
	SQLLEN idLen;

	SQLINTEGER idType = -1;
	SQLLEN idTypeLen;

	SQLWCHAR number[strSZ];
	SQLLEN numberLen;

	SQLWCHAR typeName[strSZ];
	SQLLEN typeNameLen;

	bool isSynced = false;

public:

	PhoneNumber(int id = -1, int idType = -1)
	{
		this->id = id;
		this->idType = idType;
	};

	PhoneNumber(SQLWCHAR* number, int type) 
	{
		wcscpy_s(this->number, number);
		this->idType = type;
		switch (type) 
		{
			case 1: 
			{
				wcscpy_s(this->typeName, L"mobile");
				break;
			}
			case 2:
			{
				wcscpy_s(this->typeName, L"work");
				break;
			}
			case 3:
			{
				wcscpy_s(this->typeName, L"home");
				break;
			}
		}
	}

	bool isEqual(const PhoneNumber* b)
	{
		const SQLWCHAR* a_number = this->number;
		const SQLWCHAR* b_number = b->number;

		if (wcscmp(a_number, b_number) == 0 && idType == b->idType) return true;
		else return false;
	};

	SQLINTEGER getId() { return id; }
};

class Person
{
	friend class PersonMapper;
	friend class Model;
private:
	SQLWCHAR firstName[strSZ];
	SQLLEN nameLen;

	SQLWCHAR lastName[strSZ];
	SQLLEN lastNameLen;

	SQLWCHAR fatherName[strSZ];
	SQLLEN fatherNameLen;

	Address* address = nullptr;

	//SQLINTEGER phoneCount;

	std::vector<PhoneNumber*> phoneNumbers;
	
	SQLINTEGER id = -1;
	SQLLEN idLen;

	SQLINTEGER idAddress = -1;
	SQLLEN idAddressLen;

	std::vector<SQLINTEGER> idPhones;
	//Если не прокатит, то сделать вектор SQLLEN
	SQLLEN idPhone;

	bool isSynced = false;

public:
	Person(SQLWCHAR* lastName, SQLWCHAR* firstName, SQLWCHAR* fatherName)
	{
		wcscpy_s(this->lastName, lastName);
		wcscpy_s(this->firstName,firstName);		
		wcscpy_s(this->fatherName, fatherName);
	};

	Person() {};
	
	bool isEqual(const Person* b) 
	{
		const SQLWCHAR* a_lastname = this->lastName;
		const SQLWCHAR* a_firstname = this->firstName;
		const SQLWCHAR* a_fathername = this->fatherName;

		const SQLWCHAR* b_lastname = b->lastName;
		const SQLWCHAR* b_firstname = b->firstName;
		const SQLWCHAR* b_fathername = b->fatherName;

		if
		(
			wcscmp(a_lastname, b_lastname) == 0 &&
			wcscmp(a_firstname, b_firstname) == 0 &&
			wcscmp(a_fathername, b_fathername) == 0
		)
			return true;
		else return false;
	}

	bool containPhoneNumber(PhoneNumber* pn) 
	{
		for (int i = 0; i < phoneNumbers.size(); i++)
		{
			if (phoneNumbers[i]->isEqual(pn)) return true;
		}
		return false;
	}

	bool containAddress(Address* ad) 
	{
		return this->address->isEqual(ad);
	}

	void addPhoneNumber(PhoneNumber* pn) 
	{
		this->phoneNumbers.push_back(pn);
		this->idPhones.push_back( phoneNumbers.back()->getId());
	};

	void setPhoneNumber(int pos, PhoneNumber* pn) 
	{
		if (pos < phoneNumbers.size())
		{
			phoneNumbers[pos] = pn;
			idPhones[pos] = pn->getId();
		}
	}

	void setAddress(Address* add) { this->address = add; };
};

class AbstractMapper
{
protected:
	SQLRETURN retcode;
	SQLHSTMT hstmt;

	SQLWCHAR info[SQL_MAX_MESSAGE_LENGTH] = L"default";
	SQLSMALLINT infoL;

	DataBaseConnection* db;
	SQLWCHAR* statementText;

	std::wstringstream cerr;

public:
	virtual void insertObj() {};
	virtual void updateObj() {};
	virtual void deleteObj() {};
	virtual void findObj(int id) {};
	virtual int findObj() = 0;

protected:
	void checkErr();
	void commitTransaction();
	void rollbackTransaction();
};

class PersonMapper : public AbstractMapper
{
private:
	Person* buf;
	void bindNamePar();
	void getIdPhone();
public:
	PersonMapper(Person* buf = nullptr);
	~PersonMapper() { SQLFreeHandle(SQL_HANDLE_STMT, hstmt); }
	void setBuf(Person* buf) { this->buf = buf; }

	//ID
	void findObj(int id) override;

	//ФИО
	int findObjj();
	
	//ПУСТЫШКА
	int findObj() { return false; };

	//ФИО ТЕЛЕФОН
	int findObj(PhoneNumber* phone);

	// ФИО АДРЕС
	int findObj(Address* address);

	// ФИО ТЕЛЕФОН АДРЕС
	int findObj(PhoneNumber* phone, Address* address);

	//Empty
	int findObj(bool a);

	void insertObj() override;

	void deleteObj()  override;

	void updateObj() override;
};

class AddressMapper : public AbstractMapper
{
private:
	Address* buf;
public:
	AddressMapper(Address* buf = nullptr);
	~AddressMapper() { SQLFreeHandle(SQL_HANDLE_STMT, hstmt); }
	void setBuf(Address* buf) { this->buf = buf; }

	void insertObj() override;
	void updateObj() override;
	void deleteObj()  override;
	void findObj(int id) override;
	int findObj() override;
	void insertStreet();
	//Если объект улицы не связан с контактами, то удалить его из базы
	void delStreet(SQLINTEGER idStreet);
	//Поиск улицы по имени в БД.
	void updateStreet();
	bool findStreet();
	bool findStreet(int personId);
	int findReferences();
};

class PhoneMapper : public AbstractMapper
{
private:
	PhoneNumber* buf;
public:
	PhoneMapper(PhoneNumber* buf = nullptr);

	~PhoneMapper() { SQLFreeHandle(SQL_HANDLE_STMT, hstmt); }

	void setBuf(PhoneNumber* buf) { this->buf = buf; }

	void findObj(int id) override;

	int findObj() override;

	void insertObj() override;

	void deleteObj() override;

	void updateObj() override;

	int findReferences();
};

//Убрать
class Controler;

class Model 
{
	//убрать
	friend class Controller;
private:
	std::list<Address> addressTable;
	AddressMapper adMap;
	
	std::list<PhoneNumber> phoneNumberTable;
	PhoneMapper pnMap;
	
	std::list<Person> personTable;
	PersonMapper pMap;

	DataBaseConnection* dbc = nullptr;
public:	
	Model() 
	{
		try
		{
			dbc = DataBaseConnection::getInstance();
		}
		catch (int err) {}
	}	

	/*insert
	update
	delete
	find*/

	//<Person>
		Person& insertPerson(Person p);
		void updatePerson(Person* pOld, Person pNew);
		void deletePerson(Person p);
		//ФИО
		Person& findPerson(Person p, bool isEmpty, int& ctr);
		//ФИО ТЕЛЕФОН
		Person& findPerson(Person p, PhoneNumber pn, int& ctr);
		//ФИО ТЕЛЕФОН АДРЕС
		Person& findPerson(Person p, PhoneNumber pn, Address add, int& ctr);
		//Person& findByAllAtributes() {};
		//Person& findBy4() {};
		//Person& findById() {};

private:
		void updatePerson(Person* pOld, Address* add);
		void updatePerson(Person* pOld, PhoneNumber* pn);
		void updatePerson(Person* pOld, Person* fio);
		//Получить состояние Контакта из СД
		int getState(Person* p);
		//Синхронизация контакта
		void sync(Person* p);
		void upload(Person* p);
		void download(Person* p);
		void syncAll();
	//</Person>

	//<Phone>
		PhoneNumber& insertPhone(PhoneNumber pn);
		void deletePhone(PhoneNumber* pn);
		PhoneNumber& findPhone(PhoneNumber pn, int& ctr);
		int findReferences(PhoneNumber* pn);
		int getState(PhoneNumber* pn);
		void sync(PhoneNumber* pn);
		void syncAllPhones();		
	//</Phone>

	//<Address>
		Address& insertAddress(Address add);
		void deleteAddress(Address* add);
		Address& findAddress(Address add, int& ctr);
		int findReferences(Address* add);
		int getState(Address* add);
		void sync(Address* add);
		void syncAllAddresses();		
	//</Address>
};
