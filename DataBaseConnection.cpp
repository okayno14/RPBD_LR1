#include "DataBaseConnection.h"

SQLWCHAR DataBaseConnection::dsn[CONN_DATA_SZ];
SQLWCHAR DataBaseConnection::user[CONN_DATA_SZ];
SQLWCHAR DataBaseConnection::password[CONN_DATA_SZ];

DataBaseConnection::DataBaseConnection() : status{ 0 }
{
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

	this->status = true;
}

void DataBaseConnection::checkErr()
{
	if (retcode < 0)
	{
		SQLGetDiagFieldW(
			SQL_HANDLE_DBC,
			hDBC,
			1,
			SQL_DIAG_MESSAGE_TEXT,
			info,
			SQL_MAX_MESSAGE_LENGTH,
			&infoL);
		cerr << info << std::endl;

		SQLGetDiagFieldW(
			SQL_HANDLE_DBC,
			hDBC,
			1,
			SQL_DIAG_SQLSTATE,
			info,
			SQL_MAX_MESSAGE_LENGTH,
			&infoL);
		cerr << info << std::endl;
		throw cerr.str();
	}
};

DataBaseConnection::~DataBaseConnection() 
{
	retcode = SQLDisconnect(hDBC);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, hDBC);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, handleEnv);
}

bool DataBaseConnection::checkConnection()
{
	SQLUINTEGER	uIntVal(321312);		// Unsigned int attribute values
	
	retcode = SQLGetConnectAttr(hDBC,
		SQL_ATTR_CONNECTION_DEAD,
		(SQLPOINTER)&uIntVal,
		(SQLINTEGER)sizeof(uIntVal),
		NULL);
	checkErr();	

	switch (uIntVal)
	{
		case SQL_CD_TRUE:
		{
			return  false;
		}
		case SQL_CD_FALSE:
		{
			return true;
		}
	}
}

DataBaseConnection* DataBaseConnection::database_ = nullptr;
DataBaseConnection* DataBaseConnection::getInstance()
{
	try 
	{
		if (database_ == nullptr) { database_ = new DataBaseConnection(); }
		return database_;
	}
	catch (std::wstring msg) 
	{
		int err = -2;
		throw err;
	}
}
