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

	bool isSynced = false;
};

class PhoneNumber
{
public:
	SQLWCHAR number[strSZ];
	SQLWCHAR typeName[strSZ];


	PhoneNumber(int id = -1, int idType = -1);

	bool isEqual(const PhoneNumber* b)
	{
		const SQLWCHAR* a_number = this->number;
		const SQLWCHAR* b_number = b->number;

		if (wcscmp(a_number, b_number) == 0) return true;
		else return false;
	};

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

	bool isSynced = false;
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

	Address* address;

	SQLINTEGER phoneCount;

	std::vector<PhoneNumber*> phoneNumbers;

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

	bool containPhoneNumber(PhoneNumber* pn);
		
	

private:
	SQLINTEGER id = -1;
	SQLLEN idLen;

	SQLINTEGER idAddress = -1;
	SQLLEN idAddressLen;


	std::vector<SQLINTEGER> idPhones;
	//≈ÒÎË ÌÂ ÔÓÍ‡ÚËÚ, ÚÓ Ò‰ÂÎ‡Ú¸ ‚ÂÍÚÓ SQLLEN
	SQLLEN idPhone;

	
	

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

	//ID
	void findObj(int id) override;

	//‘»Œ
	int findObjj();
	
	//œ”—“€ÿ ¿
	bool findObj() { return false; };

	//‘»Œ “≈À≈‘ŒÕ
	int findObj(PhoneNumber* phone);

	// ‘»Œ ¿ƒ–≈—
	int findObj(Address* address);

	// ‘»Œ “≈À≈‘ŒÕ ¿ƒ–≈—
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
	bool findObj() override;
	void insertStreet();
	//≈ÒÎË Ó·˙ÂÍÚ ÛÎËˆ˚ ÌÂ Ò‚ˇÁ‡Ì Ò ÍÓÌÚ‡ÍÚ‡ÏË, ÚÓ Û‰‡ÎËÚ¸ Â„Ó ËÁ ·‡Á˚
	void delStreet(SQLINTEGER idStreet);
	//œÓËÒÍ ÛÎËˆ˚ ÔÓ ËÏÂÌË ‚ ¡ƒ.
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

//”·‡Ú¸
class Controler;

class Model 
{
	//Û·‡Ú¸
	friend class Controller;
private:
	std::vector<Address> addressTable;
	AddressMapper adMap;
	std::vector<PhoneNumber> phoneNumberTable;
	PhoneMapper pnMap;
	std::vector<Person> personTable;
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
	
	
	Person* findPerson() {};
	void removeRecord() {};
	void editRecord() {};
	void addRecord();
	void addPhone(PhoneNumber pn);

	/*insert
	update
	delete
	find*/

	//<Person>
private:
		void sync();
		void upload(Person* p);
		void download(Person* p);

public:
		void insertPerson(Person p);
		
		void updatePerson(Person pOld, Address add);
		void updatePerson(Person pOld, PhoneNumber pn);
		void updatePerson(Person pOld, Person fio);

		void deletePerson(Person p);
		
		//‘»Œ
		Person& findPerson(Person p, bool isEmpty, int& ctr);
		//‘»Œ “≈À≈‘ŒÕ
		Person& findPerson(Person p, PhoneNumber pn, int& ctr);
		//‘»Œ “≈À≈‘ŒÕ ¿ƒ–≈—
		Person& findPerson(Person p, PhoneNumber pn, Address add);
	//</Person>
	
	//<Phone>
		void insertPhone(Person* p, PhoneNumber pn);
		void updatePhone(Person* p, PhoneNumber pnOld, PhoneNumber pnNew);
		void deletePhone(Person* p, PhoneNumber pnOld, PhoneNumber pnNew);
		//void findPhone();
	//</Phone>

private:
	//Person& findByAllAtributes() {};
	//Person& findBy4() {};
	//Person& findById() {};
};
