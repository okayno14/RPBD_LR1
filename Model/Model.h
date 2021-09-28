#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>

#define strSZ 20

class Address
{
public:
	SQLWCHAR streetName[strSZ];
	SQLINTEGER home;
	SQLINTEGER appartement;

	Address(Address& other) = delete;
	void operator=(const Address&) = delete;
	static Address* getInstance();
private:
	SQLINTEGER id;
	SQLINTEGER idStreet;
	static Address* address_;
protected:
	Address() 
	{
		id = -1;
		idStreet = -1;
	}
};

Address* Address::address_ = nullptr;
Address* Address::getInstance() 
{
	if (address_ == nullptr) address_ = new Address;
	return address_;
}

class PhoneNumber
{
public:
	SQLWCHAR number[strSZ];
	SQLWCHAR typeName[strSZ];
	
	PhoneNumber(PhoneNumber& other) = delete;
	void operator=(const PhoneNumber&) = delete;
	static PhoneNumber* getInstance();
private:
	SQLINTEGER id;
	SQLINTEGER idType;
	static PhoneNumber* phoneNumber_;
protected:
	PhoneNumber() 
	{
		id = -1;
		idType = -1;
	}
};

PhoneNumber* PhoneNumber::phoneNumber_ = nullptr;
PhoneNumber* PhoneNumber::getInstance() 
{
	if (phoneNumber_ == nullptr) phoneNumber_ = new PhoneNumber();
	return phoneNumber_;
}

class Person
{
public:
	SQLWCHAR name[strSZ];
	SQLWCHAR lastName[strSZ];
	SQLWCHAR fatherName[strSZ];
	Address* address;
	SQLINTEGER phoneCount;
	PhoneNumber* phoneNumber;
	static Person* person_;
	
	Person(Person& other) = delete;
	void operator=(const Person&) = delete;
	static Person* getInstance();

private:
	SQLINTEGER id;
	SQLINTEGER idAddress;

protected:

	Person()
	{
		phoneCount = 1;
		phoneNumber = PhoneNumber::getInstance();
		address = Address::getInstance();
		id = -1;
		idAddress = -1;
	}
};

Person* Person::person_ = nullptr;

Person* Person::getInstance()
{
	if (person_ == nullptr) { person_ = new Person(); }
	return person_;
}

class DataBase
{
protected:
	SQLHENV handleEnv;
	SQLHDBC handleDBC;

	SQLRETURN retcode;

	SQLWCHAR* dsn;
	SQLWCHAR* user;
	SQLWCHAR* password;

	static DataBase* database_;
	DataBase(DataBase& other) = delete;
	void operator=(const DataBase&) = delete;

	DataBase()
	{
		dsn = (SQLWCHAR*)L"Phonebook";
		user = (SQLWCHAR*)L"postgres";
		password = (SQLWCHAR*)L"123";

		retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handleEnv);
		checkErr();

		retcode = SQLSetEnvAttr(handleEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
		checkErr();

		retcode = SQLAllocHandle(SQL_HANDLE_DBC, handleEnv, &handleDBC);
		checkErr();

		retcode = SQLConnect(handleDBC, dsn, SQL_NTS, user, SQL_NTS, password, SQL_NTS);
		checkErr();
		//установить атрибуты коннекта
	}

	void checkErr() 
	{
		if (retcode < 0) throw "Ошибка подключения\n";
	}

public:	
	
	static DataBase* getInstance();
	~DataBase() 
	{
		retcode = SQLDisconnect(handleDBC);

		retcode = SQLFreeHandle(SQL_HANDLE_DBC,handleDBC);

		retcode = SQLFreeHandle(SQL_HANDLE_ENV,handleEnv);
	}
};

DataBase* DataBase::database_ = nullptr;
DataBase* DataBase::getInstance() 
{
	if (database_ == nullptr) { database_ = new DataBase(); }
	return database_;
}