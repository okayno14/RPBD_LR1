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
	//SQLRETURN retcode;
	//stringstream err;
	//void checkErr() 
	//{
	//	if (retcode != 0) 
	//	{
	//		////Код для отлова ошибки
	//			SQLWCHAR info[SQL_MAX_MESSAGE_LENGTH];
	//			SQLSMALLINT infoL;
	//			SQLGetDiagField(SQL_HANDLE_STMT, hstmt, 1, SQL_DIAG_SQLSTATE, info, sizeof(info), &infoL);
	//			err << info << endl;				
	//			SQLGetDiagField(SQL_HANDLE_STMT, hstmt, 1, SQL_DIAG_MESSAGE_TEXT, info, sizeof(info), &infoL);
	//			err << info << endl;
	//			throw err.str();
	//		////Код для отлова ошибки
	//	}
	//}
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
	DataBaseConnection* db;
	
	SQLHSTMT hstmt;
	SQLLEN idLenOrInd;
	
	SQLWCHAR* statementText;

	SQLRETURN retcode;

public:
	PhoneMapper(PhoneNumber* buf = nullptr) 
	{
		this->buf = buf;
		db = DataBaseConnection::getInstance();
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, *(db->getHDBC()) ,&hstmt);
	}
	~PhoneMapper() {SQLFreeHandle(SQL_HANDLE_STMT, hstmt);}
	void setBuf(PhoneNumber* buf) { this->buf = buf; }
	void findObj(int id) override 
	{
		//Всё кроме типа телефона
			SQLINTEGER idT = (SQLINTEGER) id;
			statementText = (SQLWCHAR*)L"SELECT * FROM phoneNumber WHERE id = ?";
			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
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
			retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
			retcode = SQLBindCol(hstmt,2,SQL_C_SLONG, &(buf->idType),0,&(buf->idTypeLen));
			retcode = SQLBindCol(
				hstmt,
				3, 
				SQL_C_WCHAR,
				&(buf->number),
				sizeof(SQLWCHAR) * strSZ,
				&(buf->numberLen));
			retcode = SQLExecute(hstmt);
			retcode = SQLFetch(hstmt);
			retcode = SQLCloseCursor(hstmt);
		//Всё кроме типа телефона
		
		//Запись типа телефона
			statementText = (SQLWCHAR*) L"SELECT * FROM type_of_phone WHERE id = ?";
			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
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
			retcode = SQLBindCol(
				hstmt,
				2,
				SQL_C_WCHAR,
				&(buf->typeName),
				sizeof(SQLWCHAR) * strSZ,
				&(buf->typeNameLen));
			retcode = SQLExecute(hstmt);
			retcode = SQLFetch(hstmt);
			retcode = SQLCloseCursor(hstmt);
		//Запись типа телефона



		


	}
};
