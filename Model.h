#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

#include "DataBaseConnection.h"

#define strSZ 20




class Address
{
public:
	SQLWCHAR streetName[strSZ];
	SQLLEN streetNameLen;

	SQLINTEGER home;
	SQLLEN homeLen;

	SQLINTEGER appartement;
	SQLLEN appartementLen;

	Address(int id = -1, int idStreet = -1);
	
	friend class AddressMapper;
	friend class Model;
private:
	SQLINTEGER id;
	SQLLEN idLen;

	SQLINTEGER idStreet;
	SQLLEN idStreetLen;
};

class PhoneNumber
{
public:
	SQLWCHAR number[strSZ];
	SQLWCHAR typeName[strSZ];


	PhoneNumber(int id = -1, int idType = -1);
	SQLINTEGER* getId() { return &id; }
	friend class PhoneMapper;
	friend class Model;
	//private:
	SQLINTEGER id;
	SQLLEN idLen;
	SQLINTEGER idType;
	SQLLEN idTypeLen;
	SQLLEN numberLen;
	SQLLEN typeNameLen;
};

class Person
{
public:
	SQLWCHAR firstName[strSZ];
	SQLLEN nameLen;

	SQLWCHAR lastName[strSZ];
	SQLLEN lastNameLen;

	SQLWCHAR fatherName[strSZ];
	SQLLEN fatherNameLen;

	Address* address;

	SQLINTEGER phoneCount;

	std::vector<PhoneNumber*> phoneNumbers;

	Person(int id = -1, int idAddress = -1);
	
	friend class PersonMapper;
	friend class Model;

	SQLINTEGER id;
	SQLLEN idLen;

	SQLINTEGER idAddress;
	SQLLEN idAddressLen;

public:
	std::vector<SQLINTEGER> idPhones;
	//Если не прокатит, то сделать вектор SQLLEN
	SQLLEN idPhone;

	bool containPhoneNumber(PhoneNumber* pn);
	

};

class AbstractMapper
{
public:
	virtual void insertObj() {};
	virtual void updateObj() {};
	virtual void deleteObj() {};
	virtual void findObj(int id) {};
	virtual bool findObj() = 0;

protected:
	SQLRETURN retcode;
	SQLHSTMT hstmt;

	SQLWCHAR info[SQL_MAX_MESSAGE_LENGTH] = L"default";
	SQLSMALLINT infoL;

	DataBaseConnection* db;
	SQLWCHAR* statementText;

	std::wstringstream cerr;
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

	void findObj(int id) override;

	//ФИО
	bool findObj() override;

	//ФИО ТЕЛЕФОН
	bool findObj(PhoneNumber* phone);

	// ФИО АДРЕС
	bool findObj(Address* address);

	// ФИО ТЕЛЕФОН АДРЕС
	bool findObj(PhoneNumber* phone, Address* address);

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
	bool findObj() override;
	void insertStreet();
	//Если объект улицы не связан с контактами, то удалить его из базы
	void delStreet(SQLINTEGER idStreet);
	//Поиск улицы по имени в БД.
	void updateStreet();
	bool findStreet();
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

	bool findObj() override;

	void insertObj() override;

	void deleteObj() override;

	void updateObj() override;
};


class Model 
{
private:
	std::vector<Address> addressTable;
	AddressMapper adMap;
	std::vector<PhoneNumber> phoneNumberTable;
	PhoneMapper pnMap;
	std::vector<Person> personTable;
	PersonMapper pMap;
public:	
	Person* findPerson() {};
	void removeRecord() {};
	void editRecord() {};
	void addRecord();
	void addPhone(PhoneNumber pn);

	/*insert
	update
	delete
	find*/

	//<Phone>
		void insertPhone(Person* p, PhoneNumber pn);
	//</Phone>

private:
	Person& findByAllAtributes() {};
	Person& findBy4() {};
	Person& findById() {};
};
