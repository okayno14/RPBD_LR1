#pragma once
#include "Model.h"
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <sstream>

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

	wstringstream cerr;
	void checkErr()
	{
		if (retcode < 0)
		{
			SQLGetDiagFieldW(
				SQL_HANDLE_STMT,
				hstmt,
				1,
				SQL_DIAG_MESSAGE_TEXT,
				info,
				SQL_MAX_MESSAGE_LENGTH,
				&infoL);
			cerr << info << endl;

			SQLGetDiagFieldW(
				SQL_HANDLE_STMT,
				hstmt,
				1,
				SQL_DIAG_SQLSTATE,
				info,
				SQL_MAX_MESSAGE_LENGTH,
				&infoL);
			cerr << info << endl;
			throw cerr.str();
		}
	}
};

class PersonMapper : public AbstractMapper 
{
private:
	Person* buf;
	void bindName() 
	{
		retcode = SQLBindParameter(
			hstmt,
			1,
			SQL_PARAM_INPUT,
			SQL_C_WCHAR,
			SQL_WCHAR,
			sizeof(SQLWCHAR) * strSZ,
			0,
			&(buf->lastName),
			sizeof(SQLWCHAR) * strSZ, NULL);
		checkErr();
		retcode = SQLBindParameter(
			hstmt,
			2,
			SQL_PARAM_INPUT,
			SQL_C_WCHAR,
			SQL_WCHAR,
			sizeof(SQLWCHAR) * strSZ,
			0,
			&(buf->firstName),
			sizeof(SQLWCHAR) * strSZ, NULL);
		checkErr();
		retcode = SQLBindParameter(
			hstmt,
			3,
			SQL_PARAM_INPUT,
			SQL_C_WCHAR,
			SQL_WCHAR,
			sizeof(SQLWCHAR) * strSZ,
			0,
			&(buf->fatherName),
			sizeof(SQLWCHAR) * strSZ, NULL);
		checkErr();
	};
public:
	PersonMapper(Person* buf = nullptr)
	{
		this->buf = buf;
		db = DataBaseConnection::getInstance();
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, *(db->getHDBC()), &hstmt);
	}
	~PersonMapper() { SQLFreeHandle(SQL_HANDLE_STMT, hstmt); }
	void setBuf(Person* buf) { this->buf = buf; }

	void findObj(int id) override
	{
		SQLINTEGER idT = (SQLINTEGER)id;
		buf->id = idT;

		statementText = (SQLWCHAR*)L"SELECT * FROM person WHERE id = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
		checkErr();

		retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &(buf->idAddress), 0, &(buf->idAddressLen));
		checkErr();
		retcode = SQLBindCol(hstmt, 3, SQL_C_WCHAR, &(buf->lastName), sizeof(SQLWCHAR) * strSZ, &(buf->lastNameLen));
		checkErr();
		retcode = SQLBindCol(hstmt, 4, SQL_C_WCHAR, &(buf->firstName), sizeof(SQLWCHAR) * strSZ, &(buf->nameLen));
		checkErr();
		retcode = SQLBindCol(hstmt, 5, SQL_C_WCHAR, &(buf->fatherName), sizeof(SQLWCHAR) * strSZ, &(buf->fatherNameLen));
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLFetch(hstmt);
		checkErr();

		retcode = SQLCloseCursor(hstmt);
		checkErr();
	};

	//ФИО
	bool findObj(SQLWCHAR* lastName, SQLWCHAR* name, SQLWCHAR* fatherName) 
	{ 
		SQLLEN a;
		bool res = false;
		statementText =
			(SQLWCHAR*)L"SELECT * FROM person WHERE"
			" lastname = ? and"
			" firstname = ? and"
			" fathername = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		bindName();
		
		retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
		checkErr();
		
		retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &(buf->idAddress), 0, &(buf->idAddressLen));
		checkErr();		

		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLRowCount(hstmt, &a);
		checkErr();

		if (a > 1 || a == 0)
		{
			res = false;
			
			retcode = SQLCloseCursor(hstmt);
			checkErr();
		}
		else 
		{
			res = true;
			retcode = SQLFetch(hstmt);
			checkErr();

			retcode = SQLCloseCursor(hstmt);
			checkErr();
		}		

		//Не забудь поправить
		return res;		
	}

	//ФИО ТЕЛЕФОН
	bool findObj(PhoneNumber* phone) 
	{ 
		SQLLEN a;
		bool res = false;
		statementText =
			(SQLWCHAR*)
			L" SELECT "
			" 	person.id,"
			" 	person.idaddress,"
			" 	person.lastname AS lastname,"
			" 	person.firstname AS firstname,"
			" 	person.fathername AS fathername,"
			" 	persone_number.idPhone AS number,"
			" 	phoneNumber.idtype,"
			" 	phoneNumber.number,"
			" 	address.idstreet,"
			" 	address.home,"
			" 	address.appartement,"
			" 	street.streetname"
			" FROM"
			" 	person INNER JOIN persone_number"
			" 	ON"
			" 		person.id = persone_number.idPerson"
			" 	INNER JOIN phonenumber"
			" 	ON "
			" 		persone_number.idPhone = phoneNumber.id"
			" 	INNER JOIN address"
			" 	ON"
			" 		person.idAddress = address.id"
			" 	INNER JOIN street"
			" 	ON"
			" 		address.idstreet = street.id"
			" WHERE "
			" lastname = ? and"
			" firstname = ? and"
			" fathername = ? and"
			" number = ?";
		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		bindName();

		retcode = SQLBindParameter(
			hstmt,
			4,
			SQL_PARAM_INPUT,
			SQL_C_WCHAR,
			SQL_WCHAR,
			sizeof(SQLWCHAR) * strSZ,
			0,
			&(phone->number),
			sizeof(SQLWCHAR)*strSZ,
			NULL);
		checkErr();

		retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
		checkErr();

		retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &(buf->idAddress), 0, &(buf->idAddressLen));
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLRowCount(hstmt, &a);
		checkErr();

		if (a!=1)
		{
			res = false;

			retcode = SQLCloseCursor(hstmt);
			checkErr();
		}
		else
		{
			retcode = SQLFetch(hstmt);
			checkErr();

			retcode = SQLCloseCursor(hstmt);
			checkErr();
			res = true;
		}

		//Не забудь поправить
		return res;
	};

	// ФИО АДРЕС
	bool findObj(Address* address) { return false; };

	// ФИО ТЕЛЕФОН АДРЕС
	bool findObj()  override
	{
		bool res = false;
		statementText =
			(SQLWCHAR*)L"SELECT * FROM person WHERE"
			" idaddress = ? and "
			" lastname = ? and "
			" firstname = ? and"
			" fathername = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		//retcode = SQLBindParameter(hstmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,4,0,&(buf->id),0,NULL);
		//checkErr();

		//retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &(buf->idAddress), 0, &(buf->idAddressLen));
		//checkErr();


		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLFetch(hstmt);
		checkErr();

		retcode = SQLCloseCursor(hstmt);
		checkErr();

		//Не забудь поправить
		return res;
	};

	//bool finObj(Address* address, PhoneNumber* phone) { return false; }

};


class AddressMapper : public AbstractMapper 
{
private:
	Address* buf;
public:
	AddressMapper(Address* buf = nullptr) 
	{
		this->buf = buf;
		db = DataBaseConnection::getInstance();
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, *(db->getHDBC()), &hstmt);
	}
	~AddressMapper() { SQLFreeHandle(SQL_HANDLE_STMT, hstmt); }
	void setBuf(Address* buf) { this->buf = buf; }
	
	bool findStreet()
	{
		statementText = (SQLWCHAR*)L"SELECT id FROM street WHERE streetname = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(
			hstmt,
			1,
			SQL_PARAM_INPUT,
			SQL_C_WCHAR,
			SQL_WCHAR,
			sizeof(SQLWCHAR) * strSZ,
			0,
			buf->streetName,
			sizeof(SQLWCHAR) * strSZ,
			NULL
		);
		checkErr();

		retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->idStreet), 0, &(buf->idStreetLen));
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		SQLLEN finded;
		retcode = SQLRowCount(hstmt, &finded);
		checkErr();

		retcode = SQLFetch(hstmt);
		checkErr();

		retcode = SQLCloseCursor(hstmt);
		checkErr();
		
		if (finded == 1) 
		{
			return true;
		}
		else 
		{
			return false;
		}

	};
	void checkStreet() 
	{
		SQLLEN a;
		if (findStreet() == false)
		{
			statementText = (SQLWCHAR*)L"INSERT INTO street (streetname) VALUES (?)";

			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();

			retcode = SQLBindParameter
			(
				hstmt,
				1,
				SQL_PARAM_INPUT,
				SQL_C_WCHAR,
				SQL_WCHAR,
				sizeof(SQLWCHAR) * strSZ,
				0,
				buf->streetName,
				sizeof(SQLWCHAR) * strSZ,
				NULL
			);
			checkErr();

			retcode = SQLExecute(hstmt);
			checkErr();

			retcode = SQLRowCount(hstmt, &a);
			checkErr();

			findStreet();
		}
	}
	
	void insertObj() override 
	{
		SQLLEN a;
		//Проверка и вставка улицы
		checkStreet();
		
		//Проверка и вставка улицы

		//Вставка квартиры и дома
			statementText = (SQLWCHAR*)L"INSERT INTO address (home, appartement, idStreet) VALUES (?,?,?)";

			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();
			
			retcode = SQLBindParameter(
				hstmt,
				1,
				SQL_PARAM_INPUT,
				SQL_INTEGER,
				SQL_C_SLONG,
				4,
				0,
				&(buf->home),
				0,
				NULL);
			checkErr();
			retcode = SQLBindParameter(
				hstmt,
				2,
				SQL_PARAM_INPUT,
				SQL_INTEGER,
				SQL_C_SLONG,
				4,
				0,
				&(buf->appartement),
				0,
				NULL);
			checkErr();
			retcode = SQLBindParameter(
				hstmt,
				3,
				SQL_PARAM_INPUT,
				SQL_INTEGER,
				SQL_C_SLONG,
				4,
				0,
				&(buf->idStreet),
				0,
				NULL);
			checkErr();

			retcode = SQLExecute(hstmt);
			checkErr();	
			
			retcode = SQLRowCount(hstmt, &a);
			checkErr();
	
		//Вставка квартиры и дома

		findObj(); //записывает в обьект его id

	};
	virtual void updateObj() override 
	{
		SQLLEN a;
		
		/*Если пользователь переписал название улицы, то
		нужно сгенерировать новый обьект улицы и записать его ид в буфер, иначе ничего не делать*/
		checkStreet();

		/*делаем апдейт дома, квартиры, идУлицы*/
		statementText = (SQLWCHAR*)L"UPDATE address SET idstreet = ?, home = ?, appartement = ? WHERE id = ?";
		
		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(	hstmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,4,0,&(buf->idStreet),0,NULL);
		checkErr();
		retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->home), 0, NULL);
		checkErr();
		retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->appartement), 0, NULL);
		checkErr();
		retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();
				
		retcode = SQLRowCount(hstmt, &a);
		checkErr();
	};
	virtual void deleteObj()  override 
	{
		statementText = (SQLWCHAR*)L"DELETE FROM address WHERE id = ?";
		
		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(hstmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,4,0,&(buf->id),0,NULL);
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		SQLLEN a;
		retcode = SQLRowCount(hstmt,&a);
		checkErr();

	};
	virtual void findObj(int id) override 
	{
		SQLINTEGER idT = (SQLINTEGER)id;
					
		statementText = (SQLWCHAR*)
		L"SELECT "
		" *"
		" FROM"
		" address INNER JOIN street"
		" ON"
		" address.idStreet = street.id"
		" WHERE address.id = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter
		(
			hstmt,
			1,
			SQL_PARAM_INPUT,
			SQL_C_SLONG,
			SQL_INTEGER,
			4,
			0,
			&idT,
			0,
			NULL
		);
		checkErr();

		retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
		checkErr();
		retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &(buf->idStreet), 0, &(buf->idStreetLen));
		checkErr();
		retcode = SQLBindCol(hstmt, 3, SQL_C_SLONG, &(buf->home), 0, &(buf->homeLen));
		checkErr();
		retcode = SQLBindCol(hstmt, 4, SQL_C_SLONG, &(buf->appartement), 0, &(buf->appartementLen));
		checkErr();
		retcode = SQLBindCol(
			hstmt,
			6,
			SQL_C_WCHAR,
			&(buf->streetName),
			sizeof(SQLWCHAR) * strSZ,
			&(buf->streetNameLen));
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLFetch(hstmt);
		checkErr();
		retcode = SQLCloseCursor(hstmt);
		checkErr();
	};
	virtual bool findObj() override 
	{
		statementText =
			(SQLWCHAR*)L"SELECT"
			" address.id,"
			" address.idStreet"
			" FROM"
			" address INNER JOIN street"
			" ON"
			" address.idstreet = street.id"
			" WHERE"
			" address.home = ? and"
			" address.appartement = ? and"
			" street.streetname = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(
			hstmt,
			1,
			SQL_PARAM_INPUT,
			SQL_C_SLONG,
			SQL_INTEGER,
			4,
			0,
			&(buf->home),
			0,
			NULL);
		checkErr();
		retcode = SQLBindParameter(
			hstmt,
			2,
			SQL_PARAM_INPUT,
			SQL_C_SLONG,
			SQL_INTEGER,
			4,
			0,
			&(buf->appartement),
			0,
			NULL);
		checkErr();
		retcode = SQLBindParameter
		(
			hstmt,
			3,
			SQL_PARAM_INPUT,
			SQL_C_WCHAR,
			SQL_WCHAR,
			sizeof(SQLWCHAR) * strSZ,
			0,
			buf->streetName,
			sizeof(SQLWCHAR) * strSZ,
			NULL
		);
		checkErr();

		retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), sizeof(SQLWCHAR) * strSZ, &(buf->idLen));
		checkErr();
		retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &(buf->idStreet), sizeof(SQLWCHAR) * strSZ, &(buf->idStreetLen));
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		SQLLEN finded;
		retcode = SQLRowCount(hstmt, &finded);
		checkErr();
		
		retcode = SQLFetch(hstmt);
		checkErr();
		retcode = SQLCloseCursor(hstmt);
		checkErr();

		if (finded > 1) return false;
		else return true;
	};
};

class PhoneMapper: public AbstractMapper
{
private:
	PhoneNumber* buf;
public:
	PhoneMapper(PhoneNumber* buf = nullptr)
	{
		this->buf = buf;
		db = DataBaseConnection::getInstance();
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, *(db->getHDBC()), &hstmt);
		checkErr();
	}
	
	~PhoneMapper() { SQLFreeHandle(SQL_HANDLE_STMT, hstmt); }
	
	void setBuf(PhoneNumber* buf) { this->buf = buf; }
	
	void findObj(int id) override
	{
		
		SQLINTEGER idT = (SQLINTEGER)id;
		buf->id = idT;

		statementText =
			(SQLWCHAR*)L"SELECT"
			" phoneNumber.number, type_of_phone.id, type_of_phone.typename "
			" FROM"
			" phoneNumber INNER JOIN type_of_phone"
			" ON"
			" phonenumber.idtype = type_of_phone.id "
			" WHERE phoneNumber.id = ?";
		
		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();
			
		retcode = SQLBindParameter(
			hstmt,
			1,
			SQL_PARAM_INPUT,
			SQL_C_SLONG,
			SQL_INTEGER,
			4,
			0,
			&idT,
			0,
			NULL);
		checkErr();
		
		retcode = SQLBindCol(
			hstmt,
			1,
			SQL_C_WCHAR,
			&(buf->number),
			sizeof(SQLWCHAR) * strSZ,
			&(buf->numberLen));
		checkErr();
		retcode = SQLBindCol(
			hstmt,
			2,
			SQL_C_SLONG,
			&(buf->idType),
			0,
			&(buf->idTypeLen));
		checkErr();
		retcode = SQLBindCol(
			hstmt,
			3,
			SQL_C_WCHAR,
			&(buf->typeName),
			sizeof(SQLWCHAR) * strSZ,
			&(buf->typeNameLen));
		checkErr();
		
		retcode = SQLExecute(hstmt);
		checkErr();
		
		retcode = SQLFetch(hstmt);
		checkErr();
		retcode = SQLCloseCursor(hstmt);
		checkErr();		
	}

	bool findObj() override 
	{
		//Поиск обьекта в таблице по номеру телефона
		
		statementText =
			(SQLWCHAR*)L"SELECT"
			" phoneNumber.id, type_of_phone.id, type_of_phone.typename "
			" FROM"
			" phoneNumber INNER JOIN type_of_phone"
			" ON"
			" phonenumber.idtype = type_of_phone.id "
			" WHERE phoneNumber.number = ?";

			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();

			retcode = SQLBindParameter
			(
				hstmt,
				1,
				SQL_PARAM_INPUT,
				SQL_C_WCHAR,
				SQL_WCHAR,
				sizeof(SQLWCHAR) * strSZ,
				0,
				buf->number,
				sizeof(SQLWCHAR) * strSZ,
				NULL
			);
			checkErr();

			retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
			checkErr();
			retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &(buf->idType), 0, &(buf->idTypeLen));
			checkErr();
			retcode = SQLBindCol(
				hstmt,
				3,
				SQL_C_WCHAR,
				&(buf->typeName),
				sizeof(SQLWCHAR) * strSZ,
				&(buf->typeNameLen));
			checkErr();
			
			
			retcode = SQLExecute(hstmt);
			checkErr();

			SQLLEN finded;
			retcode = SQLRowCount(hstmt, &finded);
			checkErr();
			

			retcode = SQLFetch(hstmt);
			checkErr();
			retcode = SQLCloseCursor(hstmt);
			checkErr();


			if (finded > 1) return false;
			else return true;
		//Поиск обьекта в таблице по номеру телефона
	};
	
	void insertObj() override
	{
		//id idType номер телефона
			statementText = (SQLWCHAR*) L"INSERT INTO phoneNumber (idtype, number) VALUES (?,?)";

			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();

			retcode = SQLBindParameter(
				hstmt,
				1,
				SQL_PARAM_INPUT,
				SQL_C_SLONG,
				SQL_INTEGER,
				4,
				0,
				&(buf->idType),
				0,
				NULL);
			checkErr();
			retcode = SQLBindParameter
			(
				hstmt,
				2,
				SQL_PARAM_INPUT,
				SQL_C_WCHAR,
				SQL_WCHAR,
				sizeof(SQLWCHAR) * strSZ,
				0,
				buf->number,
				sizeof(SQLWCHAR) * strSZ,
				NULL
			);
			checkErr();

			retcode = SQLExecute(hstmt);
			checkErr();

			SQLLEN rc;
			retcode = SQLRowCount(hstmt, &rc);
			checkErr();

			statementText = (SQLWCHAR*)L"SELECT id FROM phoneNumber where number = ?";
			
			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();

			retcode = SQLBindParameter
			(
				hstmt,
				1,
				SQL_PARAM_INPUT,
				SQL_C_WCHAR,
				SQL_WCHAR,
				sizeof(SQLWCHAR) * strSZ,
				0,
				buf->number,
				sizeof(SQLWCHAR) * strSZ,
				NULL
			);
			checkErr();

			retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
			checkErr();

			retcode = SQLExecute(hstmt);
			checkErr();

			retcode = SQLFetch(hstmt);
			checkErr();
			retcode = SQLCloseCursor(hstmt);
			checkErr();
		//id idType номер телефона
	}

	void deleteObj() override 
	{
		//Удаляем из phoneNumber
			statementText = (SQLWCHAR*) L"DELETE FROM phoneNumber WHERE id = ?";

			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();

			retcode = SQLBindParameter(
				hstmt,
				1,
				SQL_PARAM_INPUT,
				SQL_C_SLONG,
				SQL_INTEGER,
				4,
				0,
				&(buf->id),
				0,
				NULL);
			checkErr();

			retcode = SQLExecute(hstmt);
			checkErr();

			SQLLEN rc;
			retcode = SQLRowCount(hstmt, &rc);
			checkErr();
		//Удаляем из phoneNumber
	};

	void updateObj() override 
	{
		statementText = (SQLWCHAR*)L"UPDATE phoneNumber SET idtype = ?, number = ? WHERE id = ?";
		
		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(
			hstmt,
			1,
			SQL_PARAM_INPUT,
			SQL_C_SLONG,
			SQL_INTEGER,
			4,
			0,
			&(buf->idType),
			0,
			NULL);
		checkErr();
		
		retcode = SQLBindParameter
		(
			hstmt,
			2,
			SQL_PARAM_INPUT,
			SQL_C_WCHAR,
			SQL_WCHAR,
			sizeof(SQLWCHAR) * strSZ,
			0,
			buf->number,
			sizeof(SQLWCHAR) * strSZ,
			NULL
		);
		checkErr();

		retcode = SQLBindParameter(
			hstmt,
			3,
			SQL_PARAM_INPUT,
			SQL_C_SLONG,
			SQL_INTEGER,
			4,
			0,
			&(buf->id),
			0,
			NULL);
		checkErr();
		
		retcode = SQLExecute(hstmt);
		checkErr();

		SQLLEN rc;
		retcode = SQLRowCount(hstmt, &rc);
		checkErr();
	}
};
