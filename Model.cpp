#pragma once
#include "Model.h"
#include "math.h"


Model::Model()
{
	try
	{
		dbc = DataBaseConnection::getInstance();
		//��������� ������� ������ � ��
		Person p;
		Address add;
		PhoneNumber pn;

		pMap.setBuf(&p);
		adMap.setBuf(&add);
		pnMap.setBuf(&pn);

		try 
		{
			pMap.findObj(1);
			adMap.findObj(1);
			pnMap.findObj(1);
		}
		catch (std::wstring msg) 
		{
			pMap.createDB();
		}
	}
	catch (int err) { throw err; }
}

Person& Model::insertPerson(Person p)
{
	personTable.push_back(p);	
	sync(&personTable.back());
	return personTable.back();
}
void Model::updatePerson(Person* pOld, Address* add)
{
}
void Model::updatePerson(Person* pOld, PhoneNumber* pn)
{
}
void Model::updatePerson(Person* pOld, Person* fio)
{
	wcscpy_s(pOld->lastName, fio->lastName);
	wcscpy_s(pOld->firstName, fio->firstName);
	wcscpy_s(pOld->fatherName, fio->fatherName);
}
int Model::getState(Person* p)
{
	bool bd = p->id > -1;
	if (!bd) 
	{
		if (!p->isSynced)
			return 2;
		else
			return 3;
	}
	else 
	{
		if (!p->isSynced)
			return 6;
		else
			return 5;
	}
};

void Model::download(Person* p)
{
	std::list<Address>::iterator it = addressTable.begin();
	//������ �����
	//��������� ��� � ��
	//����������� ��� �� id
	Address ad;
	ad.id = p->idAddress;
	adMap.setBuf(&ad);
	adMap.findObj(ad.id);
	addressTable.push_back(ad);
	p->address = &addressTable.back();
	p->address->isSynced = 1;

	//��������
	//���� ������ id ���������
	for (int i = 0; i < p->idPhones.size(); i++) 
	{
		int id = p->idPhones[i];
		std::list<PhoneNumber>::iterator jt = phoneNumberTable.begin();		
		//������ ������� �� ��� id
		PhoneNumber pn;
		pn.id = id;
		pnMap.setBuf(&pn);
		pnMap.findObj(id);
		phoneNumberTable.push_back(pn);
		p->phoneNumbers.push_back(&phoneNumberTable.back());
		p->phoneNumbers.back()->isSynced = 1;
	}
};

void Model::upload(Person* p)
{
	//������������� ������
	if(p->address!=nullptr) 
		sync(p->address);
	//������������� ���������
	for (
		std::vector<PhoneNumber*>::iterator i = p->phoneNumbers.begin();
		i != p->phoneNumbers.end();
		++i
		)
		sync(*i);
};

PhoneNumber& Model::insertPhone(PhoneNumber pn)
{
	int q(0);
	PhoneNumber* res = &findPhone(pn, q);
	if (q == 1)
		return *res;
	phoneNumberTable.push_back(pn);
	sync(&phoneNumberTable.back());
	return phoneNumberTable.back();
}

PhoneNumber& Model::findPhone(PhoneNumber pn, int& ctr)
{
	//����� �������������
	syncAllPhones();
	int sd(0);
	int bd(0);
	PhoneNumber* res = &pn;
	for (std::list<PhoneNumber>::iterator i = phoneNumberTable.begin(); 
		i != phoneNumberTable.end(); 
		++i)
	{
		if ((*i).isEqual(&pn))
		{
			sd++;
			res = &(*i);
		}
	}

	if (dbc != nullptr)
	{
		//����� ���������� � ����
		pnMap.setBuf(&pn);
		bd = pnMap.findObj();

		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && sd == 0)
		{
			phoneNumberTable.push_back(pn);
			res = &phoneNumberTable.back();
			res->isSynced = 1;
		}
	}
	if (sd == bd)
		ctr = bd;
	else if (bd == 0)
		ctr = sd;
	else
		ctr = bd;
	//ctr = bd;
	return *res;	
}

int Model::getState(PhoneNumber* pn)
{
	bool bd = pn->id > -1;
	if (!bd)
	{
		if (!pn->isSynced)
			return 2;
		else
			return 3;
	}
	else
	{
		if (!pn->isSynced)
			return 6;
		else
			return 5;
	}
}

void Model::sync(PhoneNumber* pn)
{
	int state = getState(pn);
	if ((state == 2 || state == 3 || state == 6) && dbc != nullptr)
	{
		pnMap.setBuf(pn);
		pnMap.insertObj();
		if (state == 6) pn->isSynced = 1;
	}
	if (state == 2)
		pn->isSynced = 1;
}

void Model::syncAllPhones()
{
	for (std::list<PhoneNumber>::iterator i = phoneNumberTable.begin();
		i != phoneNumberTable.end();
		++i)
		sync(&(*i));
}

int Model::findReferences(PhoneNumber* pn)
{
	int state = getState(pn);
	int res(0);
	if (state == 3 || state == 5)
	{
		for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i)
			if ((*i).containPhoneNumber(pn))
				res++;
	};
	if (state == 5)
	{
		pnMap.setBuf(pn);
		res = res + pnMap.findReferences();
	};
	return res;
}

void Model::deletePhone(PhoneNumber* pn)
{
	switch (getState(pn))
	{
		case 5:
		{
			pnMap.setBuf(pn);
			pnMap.deleteObj();
		}
		case 3:
		{
			std::list<PhoneNumber>::iterator i = phoneNumberTable.begin();
			while (i != phoneNumberTable.end() && &(*i) != pn)
				++i;
			phoneNumberTable.erase(i);
			break;
		}
	}
}

Address& Model::findAddress(Address add, int& ctr)
{
	//����� �������������
	syncAllAddresses();
	int sd(0);
	int bd(0);
	Address* res = &add;
	for (std::list<Address>::iterator i = addressTable.begin();
		i != addressTable.end();
		++i)
	{
		if ((*i).isEqual(&add))
		{
			sd++;
			res = &(*i);
		}
	}
	if (dbc != nullptr)
	{
		//����� ���������� � ����
		adMap.setBuf(&add);
		bd = adMap.findObj();

		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && sd == 0)
		{
			addressTable.push_back(add);
			res = &addressTable.back();
			res->isSynced = 1;
		}
	}
	if (sd == bd)
		ctr = bd;
	else if (bd == 0)
		ctr = sd;
	else
		ctr = bd;
	return *res;
}

Address& Model::insertAddress(Address add)
{
	int q(0);
	Address* res = &findAddress(add, q);
	if (q == 1)
		return *res;
	addressTable.push_back(add);
	sync(&addressTable.back());
	return addressTable.back();
}

int Model::getState(Address* add)
{
	bool bd = add->id > -1;
	if (!bd)
	{
		if (!add->isSynced)
			return 2;
		else
			return 3;
	}
	else
	{
		if (!add->isSynced)
			return 6;
		else
			return 5;
	}
}

void Model::sync(Address* add)
{
	int state = getState(add);
	if ((state == 2 || state == 3 || state == 6) && dbc != nullptr)
	{
		adMap.setBuf(add);
		adMap.insertObj();
		if (state == 6) add->isSynced = 1;
	}
	if (state == 2)
		add->isSynced = 1;
}

void Model::syncAllAddresses()
{
	for (std::list<Address>::iterator i = addressTable.begin();
		i != addressTable.end();
		++i)
		sync(&(*i));
}

void Model::deleteAddress(Address* add)
{
	switch (getState(add))
	{
		case 5:
		{
			adMap.setBuf(add);
			adMap.deleteObj();
		}
		case 3: 
		{
			std::list<Address>::iterator i = addressTable.begin();
			while (i != addressTable.end() && &(*i) != add)
				++i;
			addressTable.erase(i);
			break;
		}
	}
}

int Model::findReferences(Address* add)
{
	int state = getState(add);
	int res(0);
	if (state == 3 || state == 5)
	{
		for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i) 
			if ((*i).address == add)
				res++;
	};
	if (state == 5) 
	{
		adMap.setBuf(add);
		res = res + adMap.findReferences();
	};
	return res;
}

void Model::syncAll()
{
	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end();++i) 
		sync(&(*i));	
};

void Model::sync( Person* p)
{
	int state = getState(p);
	if ( (state == 2 || state == 3) && dbc != nullptr ) 
	{
		pMap.setBuf(p);
		upload(p);
		pMap.insertObj();
		if (state == 6) p->isSynced = 1;
	}
	if (state == 2)
		p->isSynced = 1;
	if (state == 6 && dbc != nullptr)
	{
		pMap.setBuf(p);
		upload(p);
		pMap.updateObj();
		p->isSynced = 1;
	}
};

void Model::updatePerson(Person* pOld, Person pNew)
{
	Address* bufA = nullptr;	
	std::vector<PhoneNumber*> bufP;
	pOld->isSynced = 0;
	//���� ��������� ���
	if (!pOld->isEqual(&pNew)) 
		updatePerson(pOld, &pNew);	
	
	//<address>
		//�������������� ��������� �� ������, ����
		//� �������� �� ���� ������ �� ����� 
		Address empty;
		if (pOld->address == nullptr)
			pOld->address = &empty;

		if (!pOld->address->isEqual(pNew.address))
		{
			bufA = pOld->address;
			Address* addN = &insertAddress(*pNew.address);
			pOld->address = addN;
			pOld->idAddress = pOld->address->id;
		}
	//</address>
		
	//<phoneNumber>
		PhoneNumber emptyy;
		for (int i = 0; i < pNew.phoneNumbers.size(); i++)
		{
			//��������� ��������� ��������� 
			//���� � ����� ������� ������ ���������
			if (i >= pOld->phoneNumbers.size())
			{
				pOld->phoneNumbers.push_back(&emptyy);
				pOld->idPhones.push_back(-1);
			}

			//���� �������� �� �������
			if (!pOld->phoneNumbers[i]->isEqual(pNew.phoneNumbers[i]))
			{
				bufP.push_back(pOld->phoneNumbers[i]);
				PhoneNumber* pnN = &insertPhone(*pNew.phoneNumbers[i]);
				pOld->phoneNumbers[i] = pnN;
				pOld->idPhones[i] = pnN->getId();
			}
		}
	//</phoneNumber>

	sync(pOld);

	//����� ��������� �����. ����� ��������� ���������� ������ �� ������ ������. 
	//���� �� �� �����, �� ������� ������.
	if (bufA != nullptr)
	{
		adMap.setBuf(bufA);
		if (findReferences(bufA) == 0)
			deleteAddress(bufA);
	}
	for (int i = 0; i < bufP.size(); i++) 
	{
		if (bufP[i] != nullptr)
		{
			pnMap.setBuf(bufP[i]);
			if (findReferences(bufP[i]) == 0)
				deletePhone(bufP[i]);
		}
	}	
}

//����� ������ ��������� �������� ������ 1 ��������.
//������������ ������ �� ������ � ���������� �������� ������������ ��������
//���� ����� ��������, �� ������� = 1
//���� ������� > 0 ������ ������������ ��������� ���������
//���� ������� == 0 ������ ������ �� �������
Person& Model::findPerson(Person p, bool isEmpty, int& ctr)
{
	//����� �������������
	syncAll();
	
	//����� �����
	Person* res = &p;
	
	ctr = 0;
	int i = 0;
	int sz = personTable.size();
	
	int sd = 0;
	int bd = 0;

	//���� � �� ���������� �� ���
	
	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i) 
	{
		if (p.isEqual(&(*i))) 
		{
			res = &(*i);
			sd++;
		}
	}
	if (dbc != nullptr) 
	{
		//����� ���������� � ����
		pMap.setBuf(&p);
		if (isEmpty)
			bd = pMap.findObj(isEmpty);
		else		
			bd = pMap.findObjj();
	
		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && sd == 0) 
		{
			//������� ��������
			personTable.push_back(p);
			//������ �� ��������������� ����������, ���� ������� ��������������
			if(!isEmpty)
				download(&personTable.back());			
			personTable.back().isSynced = 1;
			res = &personTable.back();
		}
	}	
	
	//ctr = bd;
	if (sd == bd)
		ctr = bd;
	else if (bd == 0)
		ctr = sd;
	else
		ctr = bd;
	return *res;
}

Person& Model::findPerson(Person p, PhoneNumber pn, int& ctr) 
{
	//����� �������������
	syncAll();

	//����� �����
	Person* res = &p;

	ctr = 0;
	int i = 0;
	int sz = personTable.size();

	int sd = 0;
	int bd = 0;

	//���� � �� ���������� �� ���

	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i)
	{
		if (p.isEqual(&(*i)) && (*i).containPhoneNumber(&pn))
		{
			res = &(*i);
			sd++;
		}
	}
	if (dbc != nullptr)
	{
		//����� ���������� � ����
		pMap.setBuf(&p);
		bd = pMap.findObjj();

		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && sd == 0)
		{
			//������� ��������
			personTable.push_back(p);
			//������ �� ��������������� ����������, ���� ������� ��������������
			download(&personTable.back());
			personTable.back().isSynced = 1;
			res = &personTable.back();
		}
	}
	
	
	//ctr = bd;
	if (sd == bd)
		ctr = bd;
	else if (bd == 0)
		ctr = sd;
	else
		ctr = bd;
	return *res;
}

Person& Model::findPerson(Person p, PhoneNumber pn, Address add, int& ctr)
{
	//����� �������������
	syncAll();

	//����� �����
	Person* res = &p;

	ctr = 0;
	int i = 0;
	int sz = personTable.size();

	int sd = 0;
	int bd = 0;

	//���� � �� ���������� �� ���

	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i)
	{
		if (p.isEqual(&(*i)) && (*i).containPhoneNumber(&pn) && (*i).containAddress(&add))
		{
			res = &(*i);
			sd++;
		}
	}

	if (dbc != nullptr)
	{
		//����� ���������� � ����
		pMap.setBuf(&p);
		bd = pMap.findObjj();

		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && sd == 0)
		{
			//������� ��������
			personTable.push_back(p);
			//������ �� ��������������� ����������, ���� ������� ��������������
			download(&personTable.back());
			personTable.back().isSynced = 1;
			res = &personTable.back();
		}
	}

	
	//ctr = bd;
	if (sd == bd)
		ctr = bd;
	else if (bd == 0)
		ctr = sd;
	else
		ctr = bd;
	return *res;
}