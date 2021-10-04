#include "standart.h"
#include "Model\Model.h"
#include "Model\Mapper.h"
#include "Controller\Controller.h"
#include "View\View.h"

int main() 
{
	
	ConsoleApp con;
	
	Model model;
	PhoneNumber pn;

	model.addPhone(pn);

	return 0;	
}