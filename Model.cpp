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

void Model::download(Person* p)
{
	//адреса
	int i = 0;
	int count = 0;
	while (i < addressTable.size()) 
	{
		//Если нашёлся адрес по id в СД
		if (addressTable[i].id == p->idAddress) 
		{
			p->address = &addressTable[i];
			count++;
			break;
		}
		i++;
	}
	//Адреса в памяти нет
	if (count == 0) 
	{
		Address ad;
		ad.id = p->idAddress;
		adMap.setBuf(&ad);
		adMap.findObj(ad.id);
		addressTable.push_back(ad);
		p->address = &addressTable.back();
	}
	p->address->isSynced = 1;

	//телефоны
	//цикл обхода id телефонов
	for (int i = 0; i < p->idPhones.size(); i++) 
	{
		int j = 0;
		count = 0;
		int id = p->idPhones[i];
		while (j < phoneNumberTable.size())
		{
			//Если нашёлся телефон по id в СД
			if (phoneNumberTable[j].id == id)
			{
				p->phoneNumbers.push_back(&phoneNumberTable[j]);
				count++;
				break;
			}
			j++;
		}
		//Телефона в памяти нет
		if (count == 0)
		{
			PhoneNumber pn;
			pn.id = id;
			pnMap.setBuf(&pn);
			pnMap.findObj(id);
			phoneNumberTable.push_back(pn);
			//PhoneNumber* ptr= &phoneNumberTable.back();
			//p->phoneNumbers.push_back(&phoneNumberTable.back());
			p->phoneNumbers.push_back(&phoneNumberTable.back());
		}
		p->phoneNumbers.back()->isSynced = 1;
	}
};

void Model::upload(Person* p)
{

	//Работа с телефонами
	for (int i = 0; i < p->phoneNumbers.size(); i++) 
	{
		PhoneNumber* pn = p->phoneNumbers[i];
		//состояние объекта 01
		if (pn->id < 0) 
		{
			pnMap.setBuf(pn);
			pnMap.insertObj();
			p->idPhones[i] = pn->id;
		}
		//состояние объекта 12
		else if (pn->id > 0 && !pn->isSynced)
		{
			pnMap.setBuf(pn);
			pnMap.updateObj();
		}
	}

	//Работа с адресами
	//состояние объекта 01

	if (p->address == nullptr) return;
	if (p->idAddress < 0)
	{
		adMap.setBuf(p->address);
		adMap.insertObj();
		p->idAddress = p->address->id;
	}
	//состояние объекта 12
	else if (p->idAddress > 0 && !p->address->isSynced)
	{
		adMap.setBuf(p->address);
		adMap.updateObj();
	}

};

void Model::sync() 
{
	for (int i = 0; i < personTable.size(); i++) 
	{
		if (!personTable[i].isSynced) 
		{
			pMap.setBuf(&personTable[i]);
			
			//Подготовка вторичных сущностей к загрузке
			upload(&personTable[i]);
			
			//состояние 01
			if (personTable[i].id == -1) 
			{
				pMap.insertObj();
			}
			//состояние 12
			else 
			{
				pMap.updateObj();
			}
			personTable[i].isSynced = 1;
		}
	}
};

//Метод делает атомарную операцию поиска контакта.
//Возвращается копия найденного объекта и изменяется значения поступившего счётчика
//Если поиск успешный, то счётчик = 1
//Если счётчик > 0 значит недостаточно вторичных атрибутов
//Если счётчик == 0 значит ничего не нашлось

Person& Model::findPerson(Person p, bool isEmpty, int& ctr) 
{
	
	//Общая часть
	//Person* res = &personTable.front();
	Person* res = &p;
	
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
			res = &personTable[i];
			sd++;
		}
		i++;
	}
	
	//Онлайн-часть
	//Поиск совпадений в базе
	if (dbc != nullptr) 
	{
		//вызов синхронизации
		sync();
		
		pMap.setBuf(&p);
		if (isEmpty)
			bd = pMap.findObj(isEmpty);
		else		
			bd = pMap.findObjj();
	
		//Если найденный элемент есть только в БД
		//, то добавляем его в память приложения
		if (bd == 1 && sd == 0) 
		{
			//сделать вспомогательный метод загрузки
			//контакта из БД
			personTable.push_back(p);
			//работа со второстепенными атрибутами, если таковые присутствовали
			if(!isEmpty)
				download(&personTable.back());			
			personTable.back().isSynced = 1;
			res = &personTable.back();
		}

		//если найденный объект находится в бд и сд
		if (bd == sd && bd == 1)
			ctr = 1;
		else 
			ctr = bd - sd;
		return *res;
	}
	else 
	{
		//Офлайн часть
		ctr = sd;
		return *res;
	}
}

//НЕ ЮЗАТЬ, ОН КРИВОЙ
Person& Model::findPerson(Person p, PhoneNumber pn, int& ctr) 
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