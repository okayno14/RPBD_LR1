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
};

class PhoneNumber
{
public:
	SQLWCHAR number[strSZ];
	SQLWCHAR typeName[strSZ];
};

class Person
{
public:
	SQLWCHAR name[strSZ];
	SQLWCHAR lastName[strSZ];
	SQLWCHAR fatherName[strSZ];
	Address address;
	SQLINTEGER phoneCount;
	PhoneNumber* phoneNumbers;
	~Person() { delete[] phoneNumbers; }

	static Person* person_;

	Person(Person& other) = delete;
	void operator=(const Person&) = delete;
	static Person* getInstance();

protected:
	Person()
	{
		phoneCount = 1;
		phoneNumbers = new PhoneNumber[phoneCount];
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

class ControllerInterface
{
public:
	Person& watchRecord() {};
	void removeRecord() {};
	void editRecord() {};
	void addRecord() {};
private:
	Person& findByAllAtributes() {};
	Person& findBy4() {};
	Person& findById() {};
};
