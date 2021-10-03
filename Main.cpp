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
		//<�������>
			//������ ����� � ������
			PhoneNumber pn;
			PhoneMapper pnMap(&pn);

			//��������� ��� ��������������
			pn.idType = 2;
			wcscpy_s(pn.number, L"123456");

			pnMap.insertObj();

			//��������� ��������
			wcscpy_s(pn.number, L"1488");

			pnMap.updateObj();

			pnMap.deleteObj();
		//</�������>

		//<�����>
			//������ ����� � ������
			Address ad;
			AddressMapper adMap(&ad);

			//��������� ��� ��������������
			wcscpy_s(ad.streetName,L"Maksa");
			ad.home = 16;
			ad.appartement = 1337;		

			//adMap.insertObj();

			//��������� ��������
			adMap.findObj();
			
			ad.home = 16;

			adMap.updateObj();

			adMap.deleteObj();
		//</�����>

	
		//<�������>
			//������ ����� � ������
			Person p;
			PersonMapper pMap(&p);

			//��������� ��� ��������������
			wcscpy_s(p.lastName, L"a");
			wcscpy_s(p.firstName, L"b");
			wcscpy_s(p.fatherName, L"c");
			p.idAddress = 4;
			p.idPhones.push_back(6);

			pMap.insertObj();

			//��������� ��������
			wcscpy_s(p.firstName, L"Vasya");
			p.idAddress = 8;
			p.idPhones.push_back(4);


			pMap.updateObj();

			pMap.deleteObj();
		//</�������>
	
	}
	catch (wstring msg) { wcout << msg; }
	
	
	return 0;	
}