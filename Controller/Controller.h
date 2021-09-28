#include "Model\Model.h"
#include "View\View.h"
#pragma once
class ControllerInterface
{
public:
	ControllerInterface(Person* person) 
	{
		this->person = person;
		//добавить код присвоения указателю адреса view
		//добавить код присвоения указателю адреса person
		//добавить код генерации мапперов
		//добавить код распределения указателей по мапперам
	}
	//записал в буфер строку, вывел и так по кругу
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