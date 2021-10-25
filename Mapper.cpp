#pragma once
#include "Model.h"

void AbstractMapper::checkErr()

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
		cerr << info << std::endl;

		SQLGetDiagFieldW(
			SQL_HANDLE_STMT,
			hstmt,
			1,
			SQL_DIAG_SQLSTATE,
			info,
			SQL_MAX_MESSAGE_LENGTH,
			&infoL);
		cerr << info << std::endl;
		std::wcout << cerr.str() << std::endl;
		throw cerr.str();
	}
}

void AbstractMapper::commitTransaction()
{
	retcode = SQLEndTran(SQL_HANDLE_DBC, *(db->getHDBC()), SQL_COMMIT);
	checkErr();
}

void AbstractMapper::rollbackTransaction()
{
	retcode = SQLEndTran(SQL_HANDLE_DBC, *(db->getHDBC()), SQL_ROLLBACK);
	checkErr();
}

void PersonMapper::bindNamePar()

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
}
void PersonMapper::getIdPhone()
{
	SQLLEN a;
	SQLINTEGER phoneId;

	statementText =
		(SQLWCHAR*)L"SELECT idphone FROM persone_number WHERE idperson = ?";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
	checkErr();

	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &phoneId, 0, &(buf->idLen));
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLRowCount(hstmt, &a);
	checkErr();

	//buf->phoneCount = a;
	if (a > 0)
	{
		while (retcode = SQLFetch(hstmt) != SQL_NO_DATA)
		{
			buf->idPhones.push_back(phoneId);
		}
	}
	retcode = SQLCloseCursor(hstmt);
	checkErr();
}
PersonMapper::PersonMapper(Person* buf)
{
	try
	{
		this->buf = buf;
		db = DataBaseConnection::getInstance();
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, *(db->getHDBC()), &hstmt);
	}
	catch (int err) {}
}
void PersonMapper::findObj(int id)

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

	getIdPhone();
}
//ФИО
int PersonMapper::findObjj()

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

	bindNamePar();

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

	getIdPhone();

	commitTransaction();
	//Не забудь поправить
	return a;
}
//ФИО+ТЕЛЕФОН
int PersonMapper::findObj(PhoneNumber* phone)
{
	/*if (!buf->containPhoneNumber(phone)) 
		return 0;*/
	SQLLEN a;
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
		" 	phoneNumber.number"
		" FROM"
		" 	person INNER JOIN persone_number"
		" 	ON"
		" 		person.id = persone_number.idPerson"
		" 	INNER JOIN phonenumber"
		" 	ON "
		" 		persone_number.idPhone = phoneNumber.id"
		" WHERE "
		" lastname = ? and"
		" firstname = ? and"
		" fathername = ? and"
		" number = ?";
	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	bindNamePar();

	retcode = SQLBindParameter(
		hstmt,
		4,
		SQL_PARAM_INPUT,
		SQL_C_WCHAR,
		SQL_WCHAR,
		sizeof(SQLWCHAR) * strSZ,
		0,
		&(phone->number),
		sizeof(SQLWCHAR) * strSZ,
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

	if (a != 1)
	{
		retcode = SQLCloseCursor(hstmt);
		checkErr();
	}
	else
	{
		retcode = SQLFetch(hstmt);
		checkErr();

		retcode = SQLCloseCursor(hstmt);
		checkErr();

		getIdPhone();
	}
	commitTransaction();
	return a;
}
//ФИО+АДРЕС
int PersonMapper::findObj(Address* address)

{
	if (address != buf->address) return false;
	SQLLEN a;
	bool res = false;
	statementText =
		(SQLWCHAR*)L" SELECT "
		" 	person.id AS id,"
		" 	person.idaddress AS idaddress,"
		" 	person.lastname AS lastname,"
		" 	person.firstname AS firstname,"
		" 	person.fathername AS fathername,"
		" 	address.idstreet AS idstreet,"
		" 	address.home AS home,"
		" 	address.appartement AS appartement,"
		" 	street.streetname AS streetname"
		" FROM"
		" 	person INNER JOIN address"
		" 	ON"
		" 		person.idAddress = address.id"
		" 	INNER JOIN street"
		" 	ON"
		" 		address.idstreet = street.id"
		" 	WHERE"
		" 		lastname = ? and"
		" 		firstname = ? and"
		" 		fathername = ? and"
		" 		home = ? and"
		" 		appartement = ? and"
		" 		streetname = ?;";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	bindNamePar();

	retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(address->home), 0, NULL);
	checkErr();
	retcode = SQLBindParameter(
		hstmt,
		5,
		SQL_PARAM_INPUT,
		SQL_C_SLONG,
		SQL_INTEGER,
		4,
		0,
		&(address->appartement),
		0,
		NULL);
	checkErr();
	retcode = SQLBindParameter(
		hstmt,
		6,
		SQL_PARAM_INPUT,
		SQL_C_WCHAR,
		SQL_WCHAR,
		sizeof(SQLWCHAR) * strSZ,
		0,
		&(address->streetName),
		sizeof(SQLWCHAR) * strSZ,
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

	if (a != 1)
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

		getIdPhone();
	}

	commitTransaction();
	//Не забудь поправить
	return a;
}
//ФИО+ТЕЛЕФОН+АДРЕС
int PersonMapper::findObj(PhoneNumber* phone, Address* address)

{
	SQLLEN a;
	bool res = false;
	statementText =
		(SQLWCHAR*)L" SELECT "
		" 	person.id AS id,"
		" 	person.idaddress AS idaddress,"
		" 	person.lastname AS lastname,"
		" 	person.firstname AS firstname,"
		" 	person.fathername AS fathername,"
		" 	persone_number.idPhone AS idPhone,"
		" 	phoneNumber.idtype AS idtype,"
		" 	phoneNumber.number AS number,"
		" 	address.idstreet AS idstreet,"
		" 	address.home AS home,"
		" 	address.appartement AS appartement,"
		" 	street.streetname AS streetname"
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
		" 	WHERE"
		" 		lastname = ? and"
		" 		firstname = ? and"
		" 		fathername = ? and"
		" 		home = ? and"
		" 		appartement = ? and"
		" 		streetname = ? and"
		" 		number = ?";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	bindNamePar();
	retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(address->home), 0, NULL);
	checkErr();
	retcode = SQLBindParameter(
		hstmt,
		5,
		SQL_PARAM_INPUT,
		SQL_C_SLONG,
		SQL_INTEGER,
		4,
		0,
		&(address->appartement),
		0,
		NULL);
	checkErr();
	retcode = SQLBindParameter(
		hstmt,
		6,
		SQL_PARAM_INPUT,
		SQL_C_WCHAR,
		SQL_WCHAR,
		sizeof(SQLWCHAR) * strSZ,
		0,
		&(address->streetName),
		sizeof(SQLWCHAR) * strSZ,
		NULL);
	checkErr();
	retcode = SQLBindParameter(
		hstmt,
		7,
		SQL_PARAM_INPUT,
		SQL_C_WCHAR,
		SQL_WCHAR,
		sizeof(SQLWCHAR) * strSZ,
		0,
		&(phone->number),
		sizeof(SQLWCHAR) * strSZ,
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

	if (a != 1)
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

		getIdPhone();
	}
	commitTransaction();
	return a;
}
void PersonMapper::insertObj()

{
	SQLLEN a;

	//Добавляем обьект в таблицу Person
	if (buf->idAddress != -1)
	{
		statementText =
			(SQLWCHAR*)L"INSERT INTO person (lastname, firstname, fathername, idaddress) VALUES (?, ?, ?, ?)";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		bindNamePar();
		retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->idAddress), 0, NULL);
		checkErr();
	}
	else
	{
		statementText =
			(SQLWCHAR*)L"INSERT INTO person (lastname, firstname, fathername) VALUES (?, ?, ?)";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		bindNamePar();
	}
	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLRowCount(hstmt, &a);
	checkErr();
	//Добавляем обьект в таблицу Person

	//считываем id нового обьекта
	statementText = (SQLWCHAR*)L"SELECT * FROM sec_p";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLFetch(hstmt);
	checkErr();

	retcode = SQLCloseCursor(hstmt);
	checkErr();
	//считываем id нового обьекта

	//Добавляем объекты в таблицу-связку телефонов и контактов, если они есть
	if (buf->idPhones.size() > 0)
	{
		statementText =
			(SQLWCHAR*)L"INSERT INTO persone_number (idPerson, idPhone) VALUES (?, ?)";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
		checkErr();

		for (int i = 0; i < buf->idPhones.size(); i++)
		{
			retcode = SQLBindParameter(
				hstmt,
				2,
				SQL_PARAM_INPUT,
				SQL_C_SLONG,
				SQL_INTEGER,
				4,
				0,
				&(buf->idPhones[i]),
				0,
				NULL);
			checkErr();

			retcode = SQLExecute(hstmt);
			checkErr();

			retcode = SQLRowCount(hstmt, &a);
			checkErr();
		}
	}
	//Добавляем объекты в таблицу-связку телефонов и контактов, если они есть
	commitTransaction();
}
void PersonMapper::deleteObj()

{
	SQLLEN a;
	//почистить persone_number
	if (!buf->idPhones.empty())
	{
		statementText = (SQLWCHAR*)L"DELETE from persone_number WHERE idPerson = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLRowCount(hstmt, &a);
		checkErr();
	}

	//почистить person

	statementText = (SQLWCHAR*)L"DELETE FROM person WHERE id = ?";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLRowCount(hstmt, &a);
	checkErr();

	//обьект адреса не трогаем внутри данного класса
	commitTransaction();
}
void PersonMapper::updateObj()

{
	SQLLEN a;

	//<обновить persone_number>
		statementText = (SQLWCHAR*)L"DELETE FROM persone_number WHERE idPerson = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter
		(hstmt,
			1,
			SQL_PARAM_INPUT,
			SQL_C_SLONG,
			SQL_INTEGER,
			4, 0,
			&(buf->id), 0, NULL);
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLRowCount(hstmt, &a);
		checkErr();

		if (!buf->idPhones.empty())
		{
			statementText = (SQLWCHAR*)L"INSERT INTO persone_number (idPerson, idPhone) VALUES (?,?)";

			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();

			retcode = SQLBindParameter
			(hstmt,
				1,
				SQL_PARAM_INPUT,
				SQL_C_SLONG,
				SQL_INTEGER,
				4, 0,
				&(buf->id), 0, NULL);
			checkErr();

			for (int i = 0; i < buf->idPhones.size(); i++)
			{
				retcode = SQLBindParameter(
					hstmt,
					2,
					SQL_PARAM_INPUT,
					SQL_C_SLONG,
					SQL_INTEGER,
					4,
					0,
					&(buf->idPhones[i]),
					0,
					NULL);
				checkErr();

				retcode = SQLExecute(hstmt);
				checkErr();

				retcode = SQLRowCount(hstmt, &a);
				checkErr();
			}

		}
	//</обновить persone_number>

	//<обновить person>
		if (buf->idAddress != -1)
		{
			statementText =
				(SQLWCHAR*)L"UPDATE person SET lastname = ?, firstname = ?, fathername = ?, idaddress = ? WHERE id = ?";

			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();

			bindNamePar();
			retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->idAddress), 0, NULL);
			checkErr();
			retcode = SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
			checkErr();

			retcode = SQLExecute(hstmt);
			checkErr();

			retcode = SQLRowCount(hstmt, &a);
			checkErr();
		}
		else
		{
			statementText =
				(SQLWCHAR*)L"UPDATE person SET lastname = ?, firstname = ?, fathername = ? WHERE id = ?";

			retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
			checkErr();

			bindNamePar();
			retcode = SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
			checkErr();

			retcode = SQLExecute(hstmt);
			checkErr();

			retcode = SQLRowCount(hstmt, &a);
			checkErr();
		}
	//</обновить person>
	commitTransaction();
}
void PersonMapper::createDB()
{
	std::wstringstream command;
	std::wstring buf;
	std::wifstream file("rpbd_databaseNULL.txt", std::ios::binary);
	while (std::getline(file,buf)) 
	{ 
		if (!buf.empty())
			command << buf;
	};
	buf = command.str();
	statementText = (SQLWCHAR*) buf.c_str();	
	file.close();

	retcode = SQLExecDirect(hstmt, statementText, SQL_NTS);
	checkErr();

	commitTransaction();
}
int PersonMapper::findObj(bool q)
{
	SQLLEN a;
	bool res = false;
	statementText =
		(SQLWCHAR*)L"SELECT person.id FROM person, persone_number"
		" WHERE"
		" person.lastname = ? AND"
		" person.firstname = ? AND"
		" person.fathername = ? AND"
		" person.id = persone_number.idPerson";


	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	bindNamePar();

	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLRowCount(hstmt, &a);
	checkErr();


	retcode = SQLCloseCursor(hstmt);
	checkErr();

	if (a == 0)
	{
		statementText =
			(SQLWCHAR*)L"SELECT id"
			" FROM person as p"
			" WHERE"
			" p.lastname = ? AND"
			" p.firstname = ? AND"
			" p.fathername = ? AND"
			" p.idAddress is NULL";


		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		bindNamePar();

		retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLRowCount(hstmt, &a);
		checkErr();


		if (a == 1) 
		{
			retcode = SQLFetch(hstmt);
			checkErr();
			
			retcode = SQLCloseCursor(hstmt);
			checkErr();

		}
		else 
		{
			retcode = SQLCloseCursor(hstmt);
			checkErr();
		}
	}

	commitTransaction();
	//Не забудь поправить
	return a;
};

AddressMapper::AddressMapper(Address* buf)
{
	try 
	{
		this->buf = buf;
		db = DataBaseConnection::getInstance();
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, *(db->getHDBC()), &hstmt);
	}
	catch (int err) {}
}
void AddressMapper::insertObj()

{
	SQLLEN a;
	//<Если нет улицы - вставка. Чтение idStreet>
	if (!findStreet()) { insertStreet(); }
	//</Если нет улицы - вставка. Чтение idStreet>

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

	//<Поиск id нового объекта>
	statementText = (SQLWCHAR*)L"SELECT * FROM sec_a";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLFetch(hstmt);
	checkErr();

	retcode = SQLCloseCursor(hstmt);
	checkErr();
	//</Поиск id нового объекта>
	commitTransaction();
}
void AddressMapper::updateObj()

{
	SQLLEN a;
	//проверяем количество адресов, связанных со старой улицей
	//если оно равно 0, то удалить улицу
	SQLINTEGER oldIdStreet = buf->idStreet;

	//<Если нет улицы - вставка. Чтение idStreet>
	if (!findStreet()) { insertStreet(); }
	/*if(buf->idStreet == -1) 
		insertStreet();*/
	//</Если нет улицы - вставка. Чтение idStreet>

	/*делаем апдейт дома, квартиры, идУлицы*/
	statementText = (SQLWCHAR*)L"UPDATE address SET idstreet = ?, home = ?, appartement = ? WHERE id = ?";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->idStreet), 0, NULL);
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

	//Если старая улица не связана с какими-то адресами, то 
	//удаляем улицу
	delStreet(oldIdStreet);

	commitTransaction();
}
void AddressMapper::deleteObj()

{
	statementText = (SQLWCHAR*)L"DELETE FROM address WHERE id = ?";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->id), 0, NULL);
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	SQLLEN a;
	retcode = SQLRowCount(hstmt, &a);
	checkErr();

	//проверяем количество адресов, связанных со старой улицей
	//если оно равно 0, то удалить улицу
	delStreet(buf->idStreet);

	commitTransaction();
}
void AddressMapper::findObj(int id)

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
	commitTransaction();
}
int AddressMapper::findObj()

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
	commitTransaction();

	return finded;
}
void AddressMapper::insertStreet()

{
	SQLLEN a;

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

	//<Поиск id>
	statementText = (SQLWCHAR*)L"SELECT * FROM sec_s";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->idStreet), 0, &(buf->idLen));
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLFetch(hstmt);
	checkErr();

	retcode = SQLCloseCursor(hstmt);
	checkErr();
	//</Поиск id>

	commitTransaction();
}
void AddressMapper::delStreet(SQLINTEGER idStreet)

{
	//<Поиск связей улицы и адреса>
	SQLLEN a;

	statementText =
		(SQLWCHAR*)L" SELECT"
		" street.id as id,"
		" street.streetname as streetname,"
		" address.id as idaddress"
		" FROM"
		" street INNER JOIN address"
		" ON"
		" street.id = address.idstreet"
		" WHERE street.id = ?";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &idStreet, 0, NULL);
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLRowCount(hstmt, &a);
	checkErr();

	/*retcode = SQLFetch(hstmt);
	checkErr();*/

	retcode = SQLCloseCursor(hstmt);
	checkErr();
	//</Поиск связей улицы и адреса>

	if (a == 0)
	{
		statementText = (SQLWCHAR*)L"DELETE FROM street WHERE id = ?";

		retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
		checkErr();

		retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &idStreet, 0, NULL);
		checkErr();

		retcode = SQLExecute(hstmt);
		checkErr();

		retcode = SQLRowCount(hstmt, &a);
		checkErr();
	}
}
void AddressMapper::updateStreet()

{
	SQLLEN a;

	statementText = (SQLWCHAR*)L"UPDATE street set streetName = ? WHERE id = ?";

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
	retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 4, 0, &(buf->idStreet), 0, NULL);
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLRowCount(hstmt, &a);
	checkErr();
}
bool AddressMapper::findStreet()

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

}
int AddressMapper::findReferences()
{
	statementText = (SQLWCHAR*)L" SELECT * FROM person WHERE person.idaddress = ?";
	
	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
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
	commitTransaction();

	return finded;
};


PhoneMapper::PhoneMapper(PhoneNumber* buf)
{
	try
	{
		this->buf = buf;
		db = DataBaseConnection::getInstance();
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, *(db->getHDBC()), &hstmt);
	}
	catch (int err) {}
}
void PhoneMapper::findObj(int id)

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

	commitTransaction();
}
int PhoneMapper::findObj()

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
	
	commitTransaction();

	return finded;
	
}
void PhoneMapper::insertObj()

{
	//id idType номер телефона
	statementText = (SQLWCHAR*)L"INSERT INTO phoneNumber (idtype, number) VALUES (?,?)";

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

	/*statementText = (SQLWCHAR*)L"SELECT id FROM phoneNumber where number = ?";

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
	checkErr();*/
	//id idType номер телефона

	//<Получение id обьекта>
	statementText = (SQLWCHAR*)L"SELECT * FROM sec_pn";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
	checkErr();

	retcode = SQLExecute(hstmt);
	checkErr();

	retcode = SQLFetch(hstmt);
	checkErr();

	retcode = SQLCloseCursor(hstmt);
	checkErr();
	//</Получение id обьекта>

	commitTransaction();
}
void PhoneMapper::deleteObj()

{
	//Удаляем из phoneNumber
	statementText = (SQLWCHAR*)L"DELETE FROM phoneNumber WHERE id = ?";

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
	commitTransaction();
}
void PhoneMapper::updateObj()

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
	commitTransaction();
}
int PhoneMapper::findReferences()
{
	statementText = (SQLWCHAR*)L" SELECT * FROM persone_number WHERE idphone = ?";

	retcode = SQLPrepare(hstmt, statementText, SQL_NTS);
	checkErr();

	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &(buf->id), 0, &(buf->idLen));
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
	commitTransaction();

	return finded;
};
