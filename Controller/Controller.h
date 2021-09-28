#include "Model\Model.h"
#include "View\View.h"
#pragma once
class ControllerInterface
{
public:
	ControllerInterface(Person* person) 
	{
		this->person = person;
		//�������� ��� ���������� ��������� ������ view
		//�������� ��� ���������� ��������� ������ person
		//�������� ��� ��������� ��������
		//�������� ��� ������������� ���������� �� ��������
	}
	//������� � ����� ������, ����� � ��� �� �����
	void watchRecord() {};
	void removeRecord() {};
	void editRecord() {};
	void addRecord() {};
private:
	ConsoleApp* consoleApp;
	Person* person;
	void findByAllAtributes() {};
	void findBy4() {};
	void findById() {};
};