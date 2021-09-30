#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#define strSZ 20

class Address
{
public:
	SQLWCHAR streetName[strSZ];
	SQLINTEGER home;
	SQLINTEGER appartement;

	Address(int id = -1, int idStreet = -1)
	{
		this->id = id;
		this->idStreet = idStreet;
	}
	friend class AddressMapper;
private:
	SQLINTEGER id;
	SQLINTEGER idStreet;
};

class PhoneNumber
{
public:
	SQLWCHAR number[strSZ];
	SQLWCHAR typeName[strSZ];
	
	
	PhoneNumber(int id =-1, int idType=-1)
	{
		this->id = id;
		this->idType = idType;
	}
	SQLINTEGER* getId() { return &id; }
	friend class PhoneMapper;
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
	SQLWCHAR name[strSZ];
	SQLWCHAR lastName[strSZ];
	SQLWCHAR fatherName[strSZ];
	Address* address;
	SQLINTEGER phoneCount;
	vector<PhoneNumber*> phoneNumbers;	

	Person(int id=-1,int idAddress=-1)
	{
		phoneCount = 0;
		this->id = id;
		this->idAddress = idAddress;		
	}
	friend class PersonMapper;
private:
	SQLINTEGER id;
	SQLINTEGER idAddress;
};

class DataBaseConnection
{
protected:
	SQLHENV handleEnv;
	SQLRETURN retcode;
	SQLWCHAR* dsn;
	SQLWCHAR* user;
	SQLWCHAR* password;
	//Сделать доступ через get и заприватить
	SQLHDBC hDBC;

	static DataBaseConnection* database_;
	
	DataBaseConnection() : status{1}
	{
		dsn = (SQLWCHAR*)L"Phonebook";
		user = (SQLWCHAR*)L"postgres";
		password = (SQLWCHAR*)L"123";

		retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handleEnv);
		checkErr();

		retcode = SQLSetEnvAttr(handleEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
		checkErr();

		retcode = SQLAllocHandle(SQL_HANDLE_DBC, handleEnv, &hDBC);
		checkErr();

		retcode = SQLConnect(hDBC, dsn, SQL_NTS, user, SQL_NTS, password, SQL_NTS);
		checkErr();
		//установить атрибуты коннекта
	}

	void checkErr() 
	{
		if (retcode < 0) 
		{ 
			status = 0;
			throw "Ошибка подключения к СУБД\n"; 
		}
	}

public:	

	bool status;
	SQLHDBC* getHDBC() { return &hDBC; }
	DataBaseConnection(DataBaseConnection& other) = delete;
	void operator=(const DataBaseConnection&) = delete;
	static DataBaseConnection* getInstance();
	~DataBaseConnection() 
	{
		retcode = SQLDisconnect(hDBC);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC,hDBC);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV,handleEnv);
	}
};

DataBaseConnection* DataBaseConnection::database_ = nullptr;
DataBaseConnection* DataBaseConnection::getInstance() 
{
	if (database_ == nullptr) { database_ = new DataBaseConnection(); }
	return database_;
}

class Model 
{
private:
	unordered_map<int,Address> addressTable;
	//AddressMapper
	unordered_map<int,PhoneNumber> phoneNumberTable;
	//PhoneNumberMapper
	unordered_map<int, Person> personTable;
	//PersonMapper
	ConsoleApp* conApp;
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
