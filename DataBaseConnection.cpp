#include "DataBaseConnection.h"

SQLWCHAR DataBaseConnection::dsn[CONN_DATA_SZ];
SQLWCHAR DataBaseConnection::user[CONN_DATA_SZ];
SQLWCHAR DataBaseConnection::password[CONN_DATA_SZ];

DataBaseConnection::DataBaseConnection() : status{ 0 }
{
	//dsn = (SQLWCHAR*)L"Pfdfdfffd";
	//dsn = (SQLWCHAR*)L"Phonebook";
	//dsn = (SQLWCHAR*)L"test";
	//user = (SQLWCHAR*)L"postgres";
	//password = (SQLWCHAR*)L"123";

		

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
		//std::wcout << msg << std::endl;
		int err = -2;
		throw err;
	}
}
