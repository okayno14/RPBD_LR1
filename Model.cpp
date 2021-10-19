#pragma once
#include "Model.h"
#include "math.h"

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

	pMap.setBuf(&p);

	//Если БД доступна - записать объект
	if (dbc != nullptr) 
	{ 
		pMap.insertObj(); 
		personTable.back().isSynced = 1;
	}
};

Person Model::findPerson(Person p, bool isEmpty, int& ctr) 
{
	//ПОКА ЧТО НЕ УЧИТЫВАЕТ isEmpty
	
	Person res;
	
	ctr = 0;
	int i = 0;
	int sz = personTable.size();
	
	int sd = 0;
	int bd = 0;

	//Ищем в СД совпадение по ФИО
	while (i < sz) 
	{
		if (p.isEqual(&personTable[i])) 
		{ 
			res = personTable[i];
			sd++;
		}
		i++;
	}
	pMap.setBuf(&p);
	
	//Если есть совпадения в базе
	if (dbc != nullptr) 
	{
		bd = pMap.findObjj();
		//ctr = ctr + q;
		
		if (bd == 1) 
		{
			personTable.push_back(p);
			res = p;
		}		
		//return res;
	}

	ctr = abs(bd - sd);

	return res;

}