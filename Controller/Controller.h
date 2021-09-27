#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>

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

};

class ControllerInterface 
{
public:
	Person& watchRecord(){};
	void removeRecord() {};
	void editRecord() {};
	void addRecord() {};
private:
	Person& findByAllAtributes() {};
	Person& findBy4() {};
	Person& findById() {};
};
