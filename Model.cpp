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
	Person res;
	
	ctr = 0;
	int i = 0;
	int sz = personTable.size();
	
	int sd = 0;
	int bd = 0;
	int common = 0;

	//Ищем в СД совпадение по ФИО
	while (i < sz) 
	{
		if (p.isEqual(&personTable[i])) 
		{ 
			res = personTable[i];
			if (res.isSynced) common++;
			sd++;
		}
		i++;
	}
	pMap.setBuf(&p);
	
	//Если есть совпадения в базе
	if (dbc != nullptr) 
	{
		if (isEmpty)
			bd = pMap.findObj(isEmpty);
		else		
			bd = pMap.findObjj();
	
		//Если найденный элемент есть только в БД
		//, то добавляем его в память приложения
		if (bd == 1 && !res.isEqual(&p)) 
		{
			personTable.push_back(p);
			personTable.back().isSynced = 1;
			res = personTable.back();
		}		
	}

	//Учитываем дублироание объектов в обоих источниках
	ctr = bd + sd - common;

	return res;
}

Person Model::findPerson(Person p, PhoneNumber pn, int& ctr) 
{
	Person res;

	ctr = 0;
	int sz = personTable.size();

	int sd = 0;
	int bd = 0;
	int common = 0;

	//Ищем в СД совпадение по ФИО
	for (int i = 0;i<sz;i++) 
	{
		//Если совпали ФИО
		if (p.isEqual(&personTable[i])) 
		{
			//Ищем совпадения телефонов
			for (int j = 0; j < personTable[i].phoneNumbers.size(); j++)
			{
				//Совпало имя и телефон
				if (personTable[i].phoneNumbers[j]->isEqual(&pn))
				{
					res = p;
					if (res.isSynced) common++;
					sd++;
				}
			}
		}
	}

	pMap.setBuf(&p);

	//Если есть совпадения в базе
	if (dbc != nullptr)
	{
		bd = pMap.findObj(&pn);

		//Если найденный элемент есть только в БД,
		//то добавляем его в память приложения
		if (bd == 1 && !res.isEqual(&p))
		{
			//имеем контакт и список id его телефонов
			//необходмо запустить поиск телефонов, который
			//ищет по id в СД
			//если не совпал, то обращается к PhoneMapper

			personTable.push_back(p);
			personTable.back().isSynced = 1;
			res = personTable.back();
		}
	}

	//Учитываем дублироание объектов в обоих источниках
	ctr = bd + sd - common;

	return res;
}