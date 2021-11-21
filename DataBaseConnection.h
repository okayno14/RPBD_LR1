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
	static SQLWCHAR dsn[CONN_DATA_SZ];
	static SQLWCHAR user[CONN_DATA_SZ];
	static SQLWCHAR password[CONN_DATA_SZ];
	static DataBaseConnection* database_;

	SQLHENV handleEnv;
	SQLRETURN retcode;
	SQLHDBC hDBC;
	SQLWCHAR info[SQL_MAX_MESSAGE_LENGTH] = L"default";
	SQLSMALLINT infoL;
	std::wstringstream cerr;

	DataBaseConnection();
	void checkErr();
public:
	bool status;
	
	static DataBaseConnection* getInstance();
	
	DataBaseConnection(DataBaseConnection& other) = delete;
	~DataBaseConnection();
	
	bool checkConnection();
	void operator=(const DataBaseConnection&) = delete;
	
	SQLHDBC* getHDBC() { return &hDBC; }
};


