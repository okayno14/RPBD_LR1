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
	virtual void findObj() {};

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

//class PersonMapper : public AbstractMapper 
//{
//
//};
//

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
	void insertObj() override 
	{
		statementText = (SQLWCHAR*)L"";

		//Проверить, есть ои улица из буфера в БД
		//Если нет, то вставить в бд и вернуть в буфер idStreet
		//Если есть, то вернуть в буфер idStreet

	};
	virtual void updateObj() override {};
	virtual void deleteObj()  override {};
	virtual void findObj(int id) override 
	{
		SQLINTEGER idT = (SQLINTEGER)id;
		//запись id дома и квартиры
			statementText = (SQLWCHAR*)L"SELECT * FROM address WHERE id = ?";

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

			retcode = SQLExecute(hstmt);
			checkErr();

			retcode = SQLFetch(hstmt);
			checkErr();
			retcode = SQLCloseCursor(hstmt);
			checkErr();

		//запись id дома и квартиры
		
		//запись улицы и idStreet
			statementText = (SQLWCHAR*)L"SELECT * FROM street WHERE id = ?";

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
				&(buf->idStreet),
				0,
				NULL
			);
			checkErr();

			retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->idStreet), 0, &(buf->idStreetLen));
			checkErr();
			retcode = SQLBindCol(
				hstmt,
				2,
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
		//запись улицы и idStreet
	};
	virtual void findObj() override {};
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
		//Всё кроме типа телефона
			SQLINTEGER idT = (SQLINTEGER)id;
			statementText = (SQLWCHAR*)L"SELECT * FROM phoneNumber WHERE id = ?";
		
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
		
			retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
			checkErr();
			retcode = SQLBindCol(hstmt, 2, SQL_C_SLONG, &(buf->idType), 0, &(buf->idTypeLen));
			checkErr();
			retcode = SQLBindCol(
				hstmt,
				3,
				SQL_C_WCHAR,
				&(buf->number),
				sizeof(SQLWCHAR) * strSZ,
				&(buf->numberLen));
			checkErr();
		
			retcode = SQLExecute(hstmt);
			checkErr();
		
			retcode = SQLFetch(hstmt);
			checkErr();
			retcode = SQLCloseCursor(hstmt);
			checkErr();
		//Всё кроме типа телефона

		//Запись типа телефона
			statementText = (SQLWCHAR*)L"SELECT * FROM type_of_phone WHERE id = ?";
		
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
		
			retcode = SQLBindCol(
				hstmt,
				2,
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
		//Запись типа телефона
	}

	void findObj() override 
	{
		//Поиск обьекта в таблице по номеру телефона
			statementText = (SQLWCHAR*)L"SELECT id, idtype FROM phoneNumber WHERE number = ?";

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

			retcode = SQLExecute(hstmt);
			checkErr();

			retcode = SQLFetch(hstmt);
			checkErr();
			retcode = SQLCloseCursor(hstmt);
			checkErr();
		//Поиск обьекта в таблице по номеру телефона

		//Запись типа телефона
			statementText = (SQLWCHAR*)L"SELECT typename FROM type_of_phone WHERE id = ?";

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

			retcode = SQLBindCol(
				hstmt,
				1,
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
		//Запись типа телефона
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
