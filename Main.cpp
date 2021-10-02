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
		/*Address ad;
		AddressMapper adMap(&ad);

		ad.home = 7;
		ad.appartement = 6;
		wcscpy_s(ad.streetName, L"Marksa");

		adMap.insertObj();

		wcscpy_s(ad.streetName, L"Pokryshkina");
		
		adMap.updateObj();

		adMap.deleteObj();*/

		Person p;
		

		wcscpy_s(p.lastName,L"a");
		wcscpy_s(p.firstName, L"b");
		wcscpy_s(p.fatherName, L"c");
		
		PhoneNumber pn;
		wcscpy_s(pn.number,L"7(383)346-11-53");
		

		Address ad;
		wcscpy_s(ad.streetName,L"Utkova");
		ad.home = 9;
		ad.appartement = 9;
		
		PersonMapper pMap(&p);

		//p.idPhones.push_back(1);
		
		

		//pMap.findObj(p.lastName,p.firstName,p.fatherName);

		//pMap.findObj(&pn);

		//pMap.findObj();

		//pMap.findObj(2);
		//pMap.findObj(&ad);
		//pMap.findObj(&pn, &ad);

		//pMap.findObj(&pn);

		//p.phoneNumbers.push_back(&pn);
		
		p.idAddress = 4;

		p.idPhones.push_back(6);

		//pMap.insertObj();

		//p.id = 19;

		p.id = 20;

		pMap.deleteObj();

	}
	catch (wstring msg) { wcout << msg; }
	
	
	return 0;	
}