#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#define strSZ 20

class Model;
class PhoneNumber;

class StatePhoneNumber
{
public:
	virtual void find(PhoneNumber* pn) = 0;
	virtual void add(PhoneNumber* pn) = 0;
	virtual void update(PhoneNumber* pn) = 0;
	virtual void delObj(PhoneNumber* pn) = 0;
	virtual void sync(PhoneNumber* pn) = 0;
protected:

	Model* model;
};

class StatePhoneNumber_1 : public StatePhoneNumber
{
public:
	StatePhoneNumber_1(Model* model) { this->model = model; }
	void find(PhoneNumber* pn) {};
	void add(PhoneNumber* pn);
	void update(PhoneNumber* pn) {};
	void delObj(PhoneNumber* pn) {};
	void sync(PhoneNumber* pn) {};
};

class DataBaseConnection;

class Address
{
public:
	SQLWCHAR streetName[strSZ];	
	SQLINTEGER home;
	SQLINTEGER appartement;

private:
	DataBaseConnection* dbc;
	
	SQLINTEGER id;
	SQLINTEGER idStreet;

	SQLLEN idLen;
	SQLLEN idStreetLen;	
	SQLLEN streetNameLen;
	SQLLEN homeLen;
	SQLLEN appartementLen;

public:

	Address(int id = -1, int idStreet = -1)
	{
		this->id = id;
		this->idStreet = idStreet;
	}
	friend class AddressMapper;
	friend class Model;
};

class PhoneNumber
{
private:
	StatePhoneNumber* currentState;
	
	SQLWCHAR number[strSZ];
	SQLWCHAR typeName[strSZ];
	
	DataBaseConnection* dbc;
	
	SQLINTEGER id;
	SQLLEN idLen;
	SQLINTEGER idType;
	SQLLEN idTypeLen;
	SQLLEN numberLen;
	SQLLEN typeNameLen;

	void add() { currentState->add(this); };

public:
	
	PhoneNumber(int id =-1, int idType=-1)
	{
		this->id = id;
		this->idType = idType;
	}

	void changeState(StatePhoneNumber* newState) { currentState = newState; }
	
	friend class PhoneMapper;
	friend class PersonMapper;
	friend class Model;
	friend class StatePhoneNumber;
};

class Person
{
public:
	SQLWCHAR firstName[strSZ];	
	SQLWCHAR lastName[strSZ];
	SQLWCHAR fatherName[strSZ];
	Address* address;
	vector<PhoneNumber*> phoneNumbers;	

private:
	DataBaseConnection* dbc;

	SQLINTEGER id;
	SQLINTEGER idAddress;
	SQLINTEGER phoneCount;

	vector<SQLINTEGER> idPhones;
	
	SQLLEN nameLen;
	SQLLEN lastNameLen;
	SQLLEN fatherNameLen;
	SQLLEN idLen;
	SQLLEN idAddressLen;
	SQLLEN idPhone;

public:

	Person(int id=-1,int idAddress=-1)
	{
		phoneCount = 0;
		this->id = id;
		this->idAddress = idAddress;		
	}
	
	bool containPhoneNumber(PhoneNumber* pn) 
	{
		for (int i = 0; i < phoneNumbers.size(); i++) 
		{
			if (pn == phoneNumbers[i]) return true;
		}
		return false;
	}

	friend class PersonMapper;
	friend class Model;

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

		//Ставим ручной режим траназакций
		retcode = SQLSetConnectAttr(hDBC, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)FALSE, 0);
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
public:
	vector<Address> addressList;
	//AddressMapper
	vector<PhoneNumber> phoneNumberList;
	//PhoneNumberMapper
	vector<Person> personList;
	//PersonMapper
	ConsoleApp* conApp;


	bool findPerson(Person p) {};
	bool findPerson(PhoneNumber pn) {};
	bool findPerson(Address ad) {};
	void removePerson(Person p) {};
	void updatePerson(Person p) {};
	void addPerson(Person p) {};

	void addPhone(PhoneNumber pn);

private:
	Person& findByAllAtributes() {};
	Person& findBy4() {};
	Person& findById() {};

	//PhoneNumber
		void findPhoneNumber();
		void addPhoneNumber();
		void updatePhoneNumber();
		void delObjPhoneNumber();
		void syncPhoneNumber();
	//PhoneNumber

	//Address
		
	//Address
};


void Model::addPhone(PhoneNumber pn)
{
	pn.changeState(new StatePhoneNumber_1(this));
	pn.add();
}

void StatePhoneNumber_1::add(PhoneNumber* pn) 
{
	model->phoneNumberList.push_back(*pn);
	cout << "add";
}


