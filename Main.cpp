#include "View\View.h"
#include "Controller\Controller.h"

void main() 
{
	ConsoleApp con;
	con.main();

	Person* person = Person::getInstance();
	Person* person2 = Person::getInstance();
	delete person;
}