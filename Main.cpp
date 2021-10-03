#include "View\View.h"
#include "Controller\Controller.h"
#include "Model\Model.h"
#include "Model\Mapper.h"

#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>


int main() 
{
	
	ConsoleApp con;
	/*ConsoleApp con;
	try { DataBaseConnection* dbc = DataBaseConnection::getInstance(); }
	catch (const char* msg) { cout << msg;  return -1; }
	Person* person = Person::getInstance();
	
	
	PhoneMapper pm;
	pm.findObj();
	
	
	unordered_map<int,char> t;*/
	
	
	try 
		{ 
			PhoneNumber pn;
			PhoneMapper pnMap(&pn);
			pnMap.findObj(2); 
		}
	catch (wstring msg) { wcout << msg; }

	try
	{
		//<Телефон>
			//Создаём буфер в памяти
			PhoneNumber pn;
			PhoneMapper pnMap(&pn);

			//Вписываем его хараетеристики
			pn.idType = 2;
			wcscpy_s(pn.number, L"123456");

			pnMap.insertObj();

			//Обновляем значения
			wcscpy_s(pn.number, L"1488");

			pnMap.updateObj();

			pnMap.deleteObj();
		//</Телефон>

		//<Адрес>
			//Создаём буфер в памяти
			Address ad;
			AddressMapper adMap(&ad);

			//Вписываем его характеристики
			wcscpy_s(ad.streetName,L"Maksa");
			ad.home = 16;
			ad.appartement = 1337;		

			//adMap.insertObj();

			//Обновляем значения
			adMap.findObj();
			
			ad.home = 16;

			adMap.updateObj();

			adMap.deleteObj();
		//</Адрес>

	
		//<Контакт>
			//Создаём буфер в памяти
			Person p;
			PersonMapper pMap(&p);

			//Вписываем его хараетеристики
			wcscpy_s(p.lastName, L"a");
			wcscpy_s(p.firstName, L"b");
			wcscpy_s(p.fatherName, L"c");
			p.idAddress = 4;
			p.idPhones.push_back(6);

			pMap.insertObj();

			//Обновляем значения
			wcscpy_s(p.firstName, L"Vasya");
			p.idAddress = 8;
			p.idPhones.push_back(4);


			pMap.updateObj();

			pMap.deleteObj();
		//</Контакт>
	
	}
	catch (wstring msg) { wcout << msg; }
	
	
	return 0;	
}