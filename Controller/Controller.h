#include "Model\Model.h"
#pragma once
class ControllerInterface
{
public:
	ControllerInterface(Person* person) 
	{
		this->person = person;
		//�������� ��� ��������� ��������
		//�������� ��� ������������� ���������� �� ��������
	}
	Person& watchRecord() {};
	void removeRecord() {};
	void editRecord() {};
	void addRecord() {};
private:
	Person* person;
	Person& findByAllAtributes() {};
	Person& findBy4() {};
	Person& findById() {};
};