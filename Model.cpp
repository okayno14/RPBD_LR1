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

	//���� �� �������� - �������� ������
	if (dbc != nullptr) 
	{ 
		pMap.insertObj(); 
		personTable.back().isSynced = 1;
	}
};

void Model::download(Person* p)
{
	//������
	int i = 0;
	int count = 0;
	while (i < addressTable.size()) 
	{
		//���� ������� ����� �� id � ��
		if (addressTable[i].id == p->idAddress) 
		{
			p->address = &addressTable[i];
			count++;
			break;
		}
		i++;
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
		int j = 0;
		count = 0;
		int id = p->idPhones[i];
		while (j < phoneNumberTable.size())
		{
			//���� ������� ������� �� id � ��
			if (phoneNumberTable[j].id == id)
			{
				p->phoneNumbers.push_back(&phoneNumberTable[j]);
				count++;
				break;
			}
			j++;
		}
		//�������� � ������ ���
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

void Model::sync() 
{
	for (int i = 0; i < personTable.size(); i++) 
	{
		if (!personTable[i].isSynced) 
		{
			pMap.setBuf(&personTable[i]);
			
			//���������� ��������� ��������� � ��������
			upload(&personTable[i]);
			
			//��������� 01
			if (personTable[i].id == -1) 
			{
				pMap.insertObj();
			}
			//��������� 12
			else 
			{
				pMap.updateObj();
			}
			personTable[i].isSynced = 1;
		}
	}
};

//����� ������ ��������� �������� ������ ��������.
//������������ ����� ���������� ������� � ���������� �������� ������������ ��������
//���� ����� ��������, �� ������� = 1
//���� ������� > 0 ������ ������������ ��������� ���������
//���� ������� == 0 ������ ������ �� �������

Person& Model::findPerson(Person p, bool isEmpty, int& ctr) 
{
	
	//����� �����
	//Person* res = &personTable.front();
	Person* res = &p;
	
	ctr = 0;
	int i = 0;
	int sz = personTable.size();
	
	int sd = 0;
	int bd = 0;

	//���� � �� ���������� �� ���
	while (i < sz) 
	{
		if (p.isEqual(&personTable[i])) 
		{ 
			res = &personTable[i];
			sd++;
		}
		i++;
	}
	
	//������-�����
	//����� ���������� � ����
	if (dbc != nullptr) 
	{
		//����� �������������
		sync();
		
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

//�� �����, �� ������
Person& Model::findPerson(Person p, PhoneNumber pn, int& ctr) 
{
	Person res;

	ctr = 0;
	int sz = personTable.size();

	int sd = 0;
	int bd = 0;
	int common = 0;

	//���� � �� ���������� �� ���
	for (int i = 0;i<sz;i++) 
	{
		//���� ������� ���
		if (p.isEqual(&personTable[i])) 
		{
			//���� ���������� ���������
			for (int j = 0; j < personTable[i].phoneNumbers.size(); j++)
			{
				//������� ��� � �������
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

	//���� ���� ���������� � ����
	if (dbc != nullptr)
	{
		bd = pMap.findObj(&pn);

		//���� ��������� ������� ���� ������ � ��,
		//�� ��������� ��� � ������ ����������
		if (bd == 1 && !res.isEqual(&p))
		{
			//����� ������� � ������ id ��� ���������
			//��������� ��������� ����� ���������, �������
			//���� �� id � ��
			//���� �� ������, �� ���������� � PhoneMapper

			personTable.push_back(p);
			personTable.back().isSynced = 1;
			res = personTable.back();
		}
	}

	//��������� ����������� �������� � ����� ����������
	ctr = bd + sd - common;

	return res;
}