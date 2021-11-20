#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <sql.h>
#include <iostream>
#include <vector>
#include <cstring>

#include "Model.h"
#include "View.h"
using namespace std;

int main() 
{
	
	ConsoleApp app;
	//Model model;
	
	
	Controller controller(&app);
	app.setController(&controller);

	SQLWCHAR lastname[20];
	SQLWCHAR firstname[20];
	SQLWCHAR fathername[20];

	wcscpy_s(lastname,L"ivanov");
	wcscpy_s(firstname, L"ivan");
	wcscpy_s(fathername, L"ivanovich");
	
	Person p(lastname, firstname, fathername);
	
	app.run();



	
	return 0;	
}