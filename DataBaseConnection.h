#pragma once
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>

#include <iostream>
#include <sstream>

class DataBaseConnection
{
protected:
	SQLHENV handleEnv;
	SQLRETURN retcode;
	SQLWCHAR* dsn;
	SQLWCHAR* user;
	SQLWCHAR* password;
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


