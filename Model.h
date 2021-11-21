#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <fstream>
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
		if(
			wcscmp(streetNameOrig, streetNameOther) == 0 &&
			home == ad->home &&
			appartement == ad->appartement)
			return true;
		else
			return false;
	};
	int getId() {return id;}
	SQLWCHAR* getStreet() { return streetName; }
	int getHome() { return this->home; }
	int getAppartement() { return this->appartement; }
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

	bool isContain(std::vector<int>* nums);

	SQLINTEGER getId() { return id; }

	SQLWCHAR* getNumber(){return number;}

	int getType() {return idType;}
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

	std::vector<PhoneNumber*> phoneNumbers;
	
	SQLINTEGER id = -1;
	SQLLEN idLen;

	SQLINTEGER idAddress = -1;
	SQLLEN idAddressLen;

	std::vector<SQLINTEGER> idPhones;

	SQLLEN idPhone;

	bool isSynced = false;

public:
	Person(SQLWCHAR* lastName, SQLWCHAR* firstName, SQLWCHAR* fatherName);	

	Person() {};
	
	bool isEqual(const Person* b);	

	bool containPhoneNumber(PhoneNumber* pn);	

	bool containAddress(Address* ad);	

	void addPhoneNumber(PhoneNumber* pn);	

	void setPhoneNumber(int pos, PhoneNumber* pn);	

	SQLWCHAR* getLastName();

	SQLWCHAR* getFirstName();

	SQLWCHAR* getFatherName();	

	void setAddress(Address* add);

	Address* getAddress() { return this->address; }

	void editFIO(SQLWCHAR* lastName, SQLWCHAR* firstName, SQLWCHAR* fatherName);

	std::vector<PhoneNumber*> getNumbers();	
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

	void setDBC(DataBaseConnection* dbc) 
	{ 
		this->db = dbc; 
		if (db == nullptr) 
			throw - 2;
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, *(db->getHDBC()), &hstmt);
		if (retcode < 0) 
			throw - 2;
	}

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

	void createDB();

	std::vector<Person> findby4(std::vector<int>* args);
	std::vector<Person> findListFIO();
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
	Model();
	void tryDB();

	/*insert
	update
	delete
	find*/

	//<Person>
		Person& insertPerson(Person p);
		void updatePerson(Person* pOld, Person pNew);
		void deletePerson(Person* p);
		//ФИО
		Person& findPerson(Person p, bool isEmpty, int& ctr);
		//ФИО ТЕЛЕФОН
		Person& findPerson(Person p, PhoneNumber pn, int& ctr);
		//ФИО ТЕЛЕФОН АДРЕС
		Person& findPerson(Person p, PhoneNumber pn, Address add, int& ctr);
		std::vector<Person*> findBy4(std::vector<int> nums);
		std::vector<Person*> find_List_FIO(Person p);

private:
		bool checkConnect();
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