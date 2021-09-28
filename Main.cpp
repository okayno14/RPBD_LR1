#include "View\View.h"
#include "Controller\Controller.h"
#include "Model\Model.h"

int main() 
{
	ConsoleApp con;
	try { DataBase* dbc = DataBase::getInstance(); }
	catch (const char* msg) { cout << msg;  return -1; }
	Person* person = Person::getInstance();
	
	
	
	con.run();
	return 0;	
}