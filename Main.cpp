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
		

		wcscpy_s(p.lastName,L"Zaykin");
		wcscpy_s(p.firstName, L"Igor");
		wcscpy_s(p.fatherName, L"Ivanovich");
		
		PhoneNumber pn;
		wcscpy_s(pn.number,L"7(383)228-228-228");
		
		PersonMapper pMap(&p);
		
		

		//pMap.findObj(p.lastName,p.firstName,p.fatherName);

		pMap.findObj(&pn);

		pMap.findObj(2);


	}
	catch (wstring msg) { wcout << msg; }
	
	
	return 0;	
}