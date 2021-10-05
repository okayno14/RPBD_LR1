#include "DataBaseConnection.h"

DataBaseConnection::DataBaseConnection() : status{ 1 }
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

	//������ ������ ����� �����������
	retcode = SQLSetConnectAttr(hDBC, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)FALSE, 0);
	checkErr();

	retcode = SQLConnect(hDBC, dsn, SQL_NTS, user, SQL_NTS, password, SQL_NTS);
	checkErr();
	//���������� �������� ��������

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
	}
	catch (std::wstring msg) 
	{
		throw msg;
	}
		
	return database_;
}