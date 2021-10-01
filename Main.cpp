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
		/*PhoneNumber pn;
		pn.idType = 2;
		wcscpy_s(pn.number,L"8(800)555-35-35");
		PhoneMapper pnMap(&pn);
		pnMap.insertObj();
		
		wcscpy_s(pn.number, L"2281488");
		pnMap.updateObj();

		pnMap.deleteObj();
		cout << pn.id<<endl;

		Address ad;
		AddressMapper adMap(&ad);

		adMap.findObj(1);*/

		PhoneNumber pn;
		PhoneMapper pnMap(&pn);
		wcscpy_s(pn.number, L"7(999)652-97-19");
		pnMap.findObj();
	}
	catch (wstring msg) { wcout << msg; }
	
	
	return 0;	
}