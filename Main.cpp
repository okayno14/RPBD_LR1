#include "Model.h"
#include "View.h"
using namespace std;

int main() 
{
	ConsoleApp app;		
	Controller controller(&app);
	app.setController(&controller);	
	app.run();	
	return 0;	
}