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


	app.run();

	
	return 0;	
}