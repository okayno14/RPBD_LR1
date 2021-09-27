#include "View\View.h"
#include "Controller\Controller.h"
#include "Model\Model.h"

int main() 
{
	ConsoleApp con;
	try { DataBase* dbc = DataBase::getInstance(); }
	catch (const char* msg) { cout << msg;  return -1; }
	
	
	con.run();

	//Person* person = Person::getInstance();
	//Person* person2 = Person::getInstance();
	//delete person;

	return 0;
	
}