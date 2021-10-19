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
	//personTable.push_back(p);
	//pMap.setBuf(&personTable.back());

	pMap.setBuf(&p);

	//Если БД доступна - записать объект
	if (dbc != nullptr) 
	{ 
		pMap.insertObj(); 
		//personTable.back().isSynced = 1;
	}

	//pMap.deleteObj();
};

Person Model::findPerson(Person p, bool isEmpty) 
{
	//ПОКА ЧТО НЕ УЧИТЫВАЕТ isEmpty
	
	Person res;
	
	int i = 0;
	int sz = personTable.size();
	//bool flag = 0;

	//Ищем в СД совпадение по ФИО
	//Флаг демонстрирует успешность поиска
	while (i < sz) 
	{
		if (p.isEqual(&personTable[i])) 
		{ 
			//flag = 1; break; 
			res = personTable[i];
			return res;
		}
		i++;
	}
	pMap.setBuf(&p);
	//Если объект был найден в БД и отсутствовал в памяти модели
	if (dbc != nullptr && pMap.findObj()) 
	{
		personTable.push_back(p);
		res = p;
		return res;
	}
	//Если дошли сюда, то нигде такого объекта нет
	throw - 1;

}