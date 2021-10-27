#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>

#include <iostream>
#include <sstream>

#define CONN_DATA_SZ 256

class Model;
class DataBaseConnection
{
	friend class Model;
protected:
	SQLHENV handleEnv;
	SQLRETURN retcode;
	static SQLWCHAR dsn[CONN_DATA_SZ];
	static SQLWCHAR user[CONN_DATA_SZ];
	static SQLWCHAR password[CONN_DATA_SZ];
	//Сделать доступ через get и заприватить
	SQLHDBC hDBC;

	static DataBaseConnection* database_;

	DataBaseConnection();

	void checkErr();

	SQLWCHAR info[SQL_MAX_MESSAGE_LENGTH] = L"default";
	SQLSMALLINT infoL;

	std::wstringstream cerr;
public:

	bool status;
	SQLHDBC* getHDBC() { return &hDBC; }
	DataBaseConnection(DataBaseConnection& other) = delete;
	void operator=(const DataBaseConnection&) = delete;
	static DataBaseConnection* getInstance();
	~DataBaseConnection();
	
};


