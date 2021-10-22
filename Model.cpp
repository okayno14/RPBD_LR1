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
Person& Model::insertPerson(Person p)
{
	personTable.push_back(p);	

	//Если БД доступна - записать объект
	if (dbc != nullptr) 
	{ 
		sync(&personTable.back());
	}

	return personTable.back();
};

void Model::download(Person* p)
{
	//адреса
	int count = 0;

	std::list<Address>::iterator it = addressTable.begin();
	while (it != addressTable.end()) 
	{
				
		//Если нашёлся адрес по id в СД
		if ((*it).id == p->idAddress)
		{
			p->address = &(*it);
			count++;
			break;
		}
		it++;
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
		count = 0;
		int id = p->idPhones[i];

		std::list<PhoneNumber>::iterator jt = phoneNumberTable.begin();
		
		while (jt != phoneNumberTable.end())
		{
			//Если нашёлся телефон по id в СД
			if ((*jt).id == id)
			{
				p->phoneNumbers.push_back(&(*jt));
				count++;
				break;
			}
			jt++;
		}
		//Телефона в памяти нет
		if (count == 0)
		{
			PhoneNumber pn;
			pn.id = id;
			pnMap.setBuf(&pn);
			pnMap.findObj(id);
			phoneNumberTable.push_back(pn);
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

PhoneNumber& Model::findPhone(PhoneNumber pn, int& ctr)
{
	PhoneNumber* res = &pn;
	for (std::list<PhoneNumber>::iterator i = phoneNumberTable.begin(); i != phoneNumberTable.end(); ++i)
	{
		if ((*i).isEqual(&pn))
		{
			ctr++;
			res = &(*i);
		}
	}
	return *res;
}

Address& Model::findAddress(Address add, int& ctr)
{
	Address* res = &add;
	for (std::list<Address>::iterator i = addressTable.begin(); i != addressTable.end(); ++i) 
	{
		if ((*i).isEqual(&add))
		{
			ctr++;
			res = &(*i);
		}
	}
	return *res;
}

void Model::syncAll()
{
	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end();++i) 
	{
		sync(&(*i));
	}
};

void Model::sync( Person* p)
{
	if (!p->isSynced)
	{
		pMap.setBuf(p);

		//Подготовка вторичных сущностей к загрузке
		upload(p);

		//состояние 01
		if (p->id == -1)
		{
			pMap.insertObj();
		}
		//состояние 12
		else
		{
			pMap.updateObj();
		}
		p->isSynced = 1;
	}	
};

void Model::updatePerson(Person* pOld, Person pNew)
{
	pOld->isSynced = 0;

	//Если обновляли ФИО
	if (!pOld->isEqual(&pNew)) 
	{
		wcscpy_s(pOld->lastName, pNew.lastName);
		wcscpy_s(pOld->firstName, pNew.firstName);
		wcscpy_s(pOld->fatherName, pNew.fatherName);
	}
	
	//работа с адресами
	int q = 0;
	
	//Инициализируем указатель на случай, если
	//у контакта не было адреса до этого 
	Address empty;
	if (pOld->address == nullptr)
		pOld->address = &empty;

	if (!pOld->address->isEqual(pNew.address))
	{
		Address* finded = &findAddress(*(pNew.address), q);
		//Если адреса в справочнике нет
		//Тогда мы производим замену старого элемента коллекции
		if (q == 0 && pOld->address != &empty)
			*(pOld->address) = *(pNew.address);
		//Добавляем в коллекцию новый элемент
		else if (pOld->address == &empty)
		{
			addressTable.push_back(*pNew.address);
			pOld->address = &addressTable.back();
		}		
		//переприсваивание указателей. Был вставлен существующий адрес
		else 
			pOld->address = finded;
	}

	//работа с телефонами
	PhoneNumber* findedd = nullptr;

	PhoneNumber emptyy;
	//сначала осмотр элементов вектора, присутствующих в обоих
	//контактах
	for (int i = 0; i < pNew.phoneNumbers.size(); i++)
	{
		//расширяем коллекции оригинала 
		//если в новом объекте больше элементов
		if (i >= pOld->phoneNumbers.size())
		{
			pOld->phoneNumbers.push_back(&emptyy);
			pOld->idPhones.push_back(-1);
		}
		
		//Если телефоны не совпали
		if (!pOld->phoneNumbers[i]->isEqual(pNew.phoneNumbers[i])) 
		{
			findedd = &findPhone(*(pNew.phoneNumbers[i]), q);
			//Если телефона в справочнике нет
			if (q == 0 && pOld->phoneNumbers[i] != &emptyy)
				*(pOld->phoneNumbers[i]) = *(pNew.phoneNumbers[i]);
			else if (pOld->phoneNumbers[i] == &emptyy) 
			{
				phoneNumberTable.push_back(*pNew.phoneNumbers[i]);
				pOld->phoneNumbers[i] = &phoneNumberTable.back();
			}
			//переприсваивание указателей
			else
				pOld->phoneNumbers[i] = findedd;

			pOld->idPhones[i] = pOld->phoneNumbers[i]->id;
		}		
	}
	
	if (dbc != nullptr)
		sync(pOld);
}

//Метод делает атомарную операцию поиска 1 контакта.
//Возвращается копия найденного объекта и изменяется значение поступившего счётчика
//Если поиск успешный, то счётчик = 1
//Если счётчик > 0 значит недостаточно вторичных атрибутов
//Если счётчик == 0 значит ничего не нашлось

Person& Model::findPerson(Person p, bool isEmpty, int& ctr)
{
	//Общая часть
	Person* res = &p;
	
	ctr = 0;
	int i = 0;
	int sz = personTable.size();
	
	int sd = 0;
	int bd = 0;

	//Ищем в СД совпадение по ФИО
	
	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i) 
	{
		if (p.isEqual(&(*i))) 
		{
			res = &(*i);
			sd++;
		}
	}
	
	//Онлайн-часть
	//Поиск совпадений в базе
	if (dbc != nullptr) 
	{
		//вызов синхронизации
		syncAll();
		
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


Person& Model::findPerson(Person p, PhoneNumber pn, int& ctr) 
{
	//Общая часть
	Person* res = &p;

	ctr = 0;
	int i = 0;
	int sz = personTable.size();

	int sd = 0;
	int bd = 0;

	//Ищем в СД совпадение по ФИО и ТЕЛЕФОНУ

	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i)
	{
		if (p.isEqual(&(*i)) && (*i).containPhoneNumber(&pn))
		{
			res = &(*i);
			sd++;
		}
	}

	//Онлайн-часть
	//Поиск совпадений в базе
	if (dbc != nullptr)
	{
		//вызов синхронизации
		syncAll();

		pMap.setBuf(&p);
		/*bd = pMap.findObjj();*/
		bd = pMap.findObj(&pn);

		//Если найденный элемент есть только в БД
		//, то добавляем его в память приложения
		if (bd == 1 && sd == 0)
		{
			//сделать вспомогательный метод загрузки
			//контакта из БД
			personTable.push_back(p);
			//работа со второстепенными атрибутами
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

//НЕ ЮЗАТЬ ОН КРИВОЙ
Person& Model::findPerson(Person p, PhoneNumber pn, Address add, int& ctr)
{
	//Общая часть
	Person* res = &p;

	ctr = 0;
	int i = 0;
	int sz = personTable.size();

	int sd = 0;
	int bd = 0;

	//Ищем в СД совпадение по ФИО и ТЕЛЕФОНУ

	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i)
	{
		if (p.isEqual(&(*i)) && (*i).containPhoneNumber(&pn) && (*i).containAddress(&add))
		{
			res = &(*i);
			sd++;
		}
	}

	//Онлайн-часть
	//Поиск совпадений в базе
	if (dbc != nullptr)
	{
		//вызов синхронизации
		syncAll();

		pMap.setBuf(&p);
		//bd = pMap.findObj(&pn);
		bd = pMap.findObj(&pn, &add);

		//Если найденный элемент есть только в БД
		//, то добавляем его в память приложения
		if (bd == 1 && sd == 0)
		{
			//сделать вспомогательный метод загрузки
			//контакта из БД
			personTable.push_back(p);
			//работа со второстепенными атрибутами
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
