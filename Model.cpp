#pragma once
#include "Model.h"

void Model::addRecord()
{
}
void Model::addPhone(PhoneNumber pn)
{
	/*this->phoneNumberTable.push_back(pn);

	this->pnMap.setBuf(&phoneNumberTable.back());

	pnMap.insertObj();
	pnMap.deleteObj();*/
}
void Model::insertPerson(Person p)
{
	personTable.push_back(p);
	pMap.setBuf(&personTable.back());

	//Если БД доступна - записать объект
	if (DataBaseConnection::getInstance()->status != -2) 
	{ 
		pMap.insertObj(); 
		personTable.back().isSynced = 1;
	}

	pMap.deleteObj();
};