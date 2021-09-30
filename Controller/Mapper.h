#pragma once
#include "..\Model\Model.h"
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <sstream>

class AbstractMapper
{
public:
	//virtual void insertObj();
	//virtual void updateObj();
	//virtual void deleteObj();
	virtual void findObj(int id) {};

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
//class AddressMapper : public AbstractMapper 
//{
//
//};

class PhoneMapper :public AbstractMapper
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

		SQLLEN y;
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
			/*NULL*/&y);

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
};
