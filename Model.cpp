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

Person Model::findPerson(Person p, bool isEmpty, int& ctr) 
{
	Person res;
	
	ctr = 0;
	int i = 0;
	int sz = personTable.size();
	
	int sd = 0;
	int bd = 0;
	int common = 0;

	//���� � �� ���������� �� ���
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
	
	//���� ���� ���������� � ����
	if (dbc != nullptr) 
	{
		if (isEmpty)
			bd = pMap.findObj(isEmpty);
		else		
			bd = pMap.findObjj();
	
		//���� ��������� ������� ���� ������ � ��
		//, �� ��������� ��� � ������ ����������
		if (bd == 1 && !res.isEqual(&p)) 
		{
			personTable.push_back(p);
			personTable.back().isSynced = 1;
			res = personTable.back();
		}		
	}

	//��������� ����������� �������� � ����� ����������
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