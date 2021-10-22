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

	//���� �� �������� - �������� ������
	if (dbc != nullptr) 
	{ 
		sync(&personTable.back());
	}

	return personTable.back();
};

void Model::download(Person* p)
{
	//������
	int count = 0;

	std::list<Address>::iterator it = addressTable.begin();
	while (it != addressTable.end()) 
	{
				
		//���� ������� ����� �� id � ��
		if ((*it).id == p->idAddress)
		{
			p->address = &(*it);
			count++;
			break;
		}
		it++;
	}
	//������ � ������ ���
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

	//��������
	//���� ������ id ���������
	for (int i = 0; i < p->idPhones.size(); i++) 
	{
		count = 0;
		int id = p->idPhones[i];

		std::list<PhoneNumber>::iterator jt = phoneNumberTable.begin();
		
		while (jt != phoneNumberTable.end())
		{
			//���� ������� ������� �� id � ��
			if ((*jt).id == id)
			{
				p->phoneNumbers.push_back(&(*jt));
				count++;
				break;
			}
			jt++;
		}
		//�������� � ������ ���
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
	//������ � ����������
	for (int i = 0; i < p->phoneNumbers.size(); i++) 
	{
		PhoneNumber* pn = p->phoneNumbers[i];
		//��������� ������� 01
		if (pn->id < 0) 
		{
			pnMap.setBuf(pn);
			pnMap.insertObj();
			p->idPhones[i] = pn->id;
		}
		//��������� ������� 12
		else if (pn->id > 0 && !pn->isSynced)
		{
			pnMap.setBuf(pn);
			pnMap.updateObj();
		}
	}

	//������ � ��������
	//��������� ������� 01

	if (p->address == nullptr) return;
	if (p->idAddress < 0)
	{
		adMap.setBuf(p->address);
		adMap.insertObj();
		p->idAddress = p->address->id;
	}
	//��������� ������� 12
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

		//���������� ��������� ��������� � ��������
		upload(p);

		//��������� 01
		if (p->id == -1)
		{
			pMap.insertObj();
		}
		//��������� 12
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

	//���� ��������� ���
	if (!pOld->isEqual(&pNew)) 
	{
		wcscpy_s(pOld->lastName, pNew.lastName);
		wcscpy_s(pOld->firstName, pNew.firstName);
		wcscpy_s(pOld->fatherName, pNew.fatherName);
	}
	
	//������ � ��������
	int q = 0;
	
	//�������������� ��������� �� ������, ����
	//� �������� �� ���� ������ �� ����� 
	Address empty;
	if (pOld->address == nullptr)
		pOld->address = &empty;

	if (!pOld->address->isEqual(pNew.address))
	{
		Address* finded = &findAddress(*(pNew.address), q);
		//���� ������ � ����������� ���
		//����� �� ���������� ������ ������� �������� ���������
		if (q == 0 && pOld->address != &empty)
			*(pOld->address) = *(pNew.address);
		//��������� � ��������� ����� �������
		else if (pOld->address == &empty)
		{
			addressTable.push_back(*pNew.address);
			pOld->address = &addressTable.back();
		}		
		//���������������� ����������. ��� �������� ������������ �����
		else 
			pOld->address = finded;
	}

	//������ � ����������
	PhoneNumber* findedd = nullptr;

	PhoneNumber emptyy;
	//������� ������ ��������� �������, �������������� � �����
	//���������
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
			findedd = &findPhone(*(pNew.phoneNumbers[i]), q);
			//���� �������� � ����������� ���
			if (q == 0 && pOld->phoneNumbers[i] != &emptyy)
				*(pOld->phoneNumbers[i]) = *(pNew.phoneNumbers[i]);
			else if (pOld->phoneNumbers[i] == &emptyy) 
			{
				phoneNumberTable.push_back(*pNew.phoneNumbers[i]);
				pOld->phoneNumbers[i] = &phoneNumberTable.back();
			}
			//���������������� ����������
			else
				pOld->phoneNumbers[i] = findedd;

			pOld->idPhones[i] = pOld->phoneNumbers[i]->id;
		}		
	}
	
	if (dbc != nullptr)
		sync(pOld);
}

//����� ������ ��������� �������� ������ 1 ��������.
//������������ ����� ���������� ������� � ���������� �������� ������������ ��������
//���� ����� ��������, �� ������� = 1
//���� ������� > 0 ������ ������������ ��������� ���������
//���� ������� == 0 ������ ������ �� �������

Person& Model::findPerson(Person p, bool isEmpty, int& ctr)
{
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
	
	//������-�����
	//����� ���������� � ����
	if (dbc != nullptr) 
	{
		//����� �������������
		syncAll();
		
		pMap.setBuf(&p);
		if (isEmpty)
			bd = pMap.findObj(isEmpty);
		else		
			bd = pMap.findObjj();
	
		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && sd == 0) 
		{
			//������� ��������������� ����� ��������
			//�������� �� ��
			personTable.push_back(p);
			//������ �� ��������������� ����������, ���� ������� ��������������
			if(!isEmpty)
				download(&personTable.back());			
			personTable.back().isSynced = 1;
			res = &personTable.back();
		}

		//���� ��������� ������ ��������� � �� � ��
		if (bd == sd && bd == 1)
			ctr = 1;
		else 
			ctr = bd - sd;
		return *res;
	}
	else 
	{
		//������ �����
		ctr = sd;
		return *res;
	}
}


Person& Model::findPerson(Person p, PhoneNumber pn, int& ctr) 
{
	//����� �����
	Person* res = &p;

	ctr = 0;
	int i = 0;
	int sz = personTable.size();

	int sd = 0;
	int bd = 0;

	//���� � �� ���������� �� ��� � ��������

	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i)
	{
		if (p.isEqual(&(*i)) && (*i).containPhoneNumber(&pn))
		{
			res = &(*i);
			sd++;
		}
	}

	//������-�����
	//����� ���������� � ����
	if (dbc != nullptr)
	{
		//����� �������������
		syncAll();

		pMap.setBuf(&p);
		/*bd = pMap.findObjj();*/
		bd = pMap.findObj(&pn);

		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && sd == 0)
		{
			//������� ��������������� ����� ��������
			//�������� �� ��
			personTable.push_back(p);
			//������ �� ��������������� ����������
			download(&personTable.back());
			personTable.back().isSynced = 1;
			res = &personTable.back();
		}

		//���� ��������� ������ ��������� � �� � ��
		if (bd == sd && bd == 1)
			ctr = 1;
		else
			ctr = bd - sd;
		return *res;
	}
	else
	{
		//������ �����
		ctr = sd;
		return *res;
	}
}

//�� ����� �� ������
Person& Model::findPerson(Person p, PhoneNumber pn, Address add, int& ctr)
{
	//����� �����
	Person* res = &p;

	ctr = 0;
	int i = 0;
	int sz = personTable.size();

	int sd = 0;
	int bd = 0;

	//���� � �� ���������� �� ��� � ��������

	for (std::list<Person>::iterator i = personTable.begin(); i != personTable.end(); ++i)
	{
		if (p.isEqual(&(*i)) && (*i).containPhoneNumber(&pn) && (*i).containAddress(&add))
		{
			res = &(*i);
			sd++;
		}
	}

	//������-�����
	//����� ���������� � ����
	if (dbc != nullptr)
	{
		//����� �������������
		syncAll();

		pMap.setBuf(&p);
		//bd = pMap.findObj(&pn);
		bd = pMap.findObj(&pn, &add);

		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && sd == 0)
		{
			//������� ��������������� ����� ��������
			//�������� �� ��
			personTable.push_back(p);
			//������ �� ��������������� ����������
			download(&personTable.back());
			personTable.back().isSynced = 1;
			res = &personTable.back();
		}

		//���� ��������� ������ ��������� � �� � ��
		if (bd == sd && bd == 1)
			ctr = 1;
		else
			ctr = bd - sd;
		return *res;
	}
	else
	{
		//������ �����
		ctr = sd;
		return *res;
	}
}
