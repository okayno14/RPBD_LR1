#include "View.h"

ConsoleApp::ConsoleApp()
{
	MainMenu = 0;//proverit etih rebayt
	//UntMenu = 0;
	ch = 0;
	this->runTimeProgram = true;
	setlocale(LC_ALL, "Russian");
	system("color 0F");

};

void ConsoleApp::Menu()
{
	cout << "------------------------------------------------" << endl
		<< "--------------| ���������� ����� |--------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - ����� ��������" << endl
		<< "[2] - �������� ������� � ��" << endl
		<< "------------------------------------------------" << endl
		<< "[3] - ����� �������� �� 4-� �������� ������" << endl
		<< "------------------------------------------------" << endl
		<< "[0] - ����� �� ��������� " << endl << endl << endl << ">>>";
}

void ConsoleApp::MenuPC()
{
	cout << ""/*������ �� �������*/ << endl;
	cout << "------------------------------------------------" << endl
		<< "--------------|  �������� �������� |------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - �������� ��� ��������" << endl
		<< "[2] - �������� ����� ��������" << endl
		<< "[3] - ������� ����� ���������� ��������" << endl
		<< "[4] - �������� ����� �������� ��������" << endl
		<< "[5] - ������� ����� ��������" << endl
		<< "[6] - �������� ��������" << endl
		<< "[0] - ����� �� �������" << endl << endl << ">>>";
}





void ConsoleApp::setController(Controller* con)
{
	this->con = con;
}

void ConsoleApp::run()
{
	
	while (this->runTimeProgram)
	{
		Menu();
		cin >> MainMenu;
		system("cls");
		switch (MainMenu)
		{

		case 1: {

		}
		case 2: {

		}
		case 3: {

		}
		case 0: {
			this->runTimeProgram = false;
			break;
		}
		default:
			Sleep(2000);
			cout << "��������!" << endl;
			_getwch();
			system("cls");
			break;
		}
	}

	system("pause");
}

void ConsoleApp::runPC()
{
	bool exitWhileLocal = true;
	while (exitWhileLocal)
	{
		cin >> MainMenu;
		switch (MainMenu)
		{
		case 1: {

		}
		case 2: {

		}
		case 3: {

		}
		case 4: {

		}
		case 5: {

		}
		case 6: {

		}
		case 0: {
			exitWhileLocal = false;
			break;
		}
		default:
			cout << "��������!" << endl;
			break;
		}

	}

}

void ConsoleApp::findPerson()
{
	
}





void ConsoleApp::addContact()
{
	cout << "------------------------------------------------" << endl;
	cout << "-----------------���������� �������� -----------" << endl;
	cout << "------------------------------------------------" << endl;
	//cout << ">>";
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "������� ������� �������� : ";
	wcin >> lastnamecontact;
	cout << "������� ��� �������� : ";
	wcin >> firstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> fathernamecontact;
	con->add�ontact(lastnamecontact, firstnamecontact, fathernamecontact);
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::deleteContact()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------------- �������� �������� ------------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "������� ��� �������� : ";
	wcin >> lastnamecontact;
	cout << "������� ������� �������� : ";
	wcin >> firstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> fathernamecontact;
	con->deleteContact(lastnamecontact, firstnamecontact, fathernamecontact);
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}


/*����� �� ���� ��������� � ���� ������� int*/
void ConsoleApp::findto4()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- ����� �������� �� 4-� ��������  --------" << endl;
	cout << "-------------- ����������� ������ --------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "������� 4-� ������� ����������� ������ �������� : ";
	wchar_t* four_phonenumber = new wchar_t[5];
	wcin >> four_phonenumber;
	con->findContactBy4NumberPhone(four_phonenumber);
	delete[] four_phonenumber;
}

void ConsoleApp::updateFIOcontacte()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------- �������� ��� �������� ------------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* oldlastnamecontact = new wchar_t[20];
	wchar_t* oldfirstnamecontact = new wchar_t[20];
	wchar_t* oldfathernamecontact = new wchar_t[20];
	wchar_t* newlastnamecontact = new wchar_t[20];
	wchar_t* newfirstnamecontact = new wchar_t[20];
	wchar_t* newfathernamecontact = new wchar_t[20];
	cout << "���������� ��� ��������" << endl;
	cout << "������� ��� �������� : ";
	wcin >> oldlastnamecontact;
	cout << "������� ������� �������� : ";
	wcin >> oldfirstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> oldfathernamecontact;
	cout << "����� ��� ��������" << endl;
	cout << "������� ��� �������� : ";
	wcin >> newlastnamecontact;
	cout << "������� ������� �������� : ";
	wcin >> newfirstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> newfathernamecontact;

	con->to�hangeContact(
		oldlastnamecontact,
		oldfirstnamecontact,
		oldfathernamecontact,
		newlastnamecontact,
		newfirstnamecontact,
		newfathernamecontact);

	delete[] oldlastnamecontact;
	delete[] oldfirstnamecontact;
	delete[] oldfathernamecontact;
	delete[] newlastnamecontact;
	delete[] newfirstnamecontact;
	delete[] newfathernamecontact;
}

void ConsoleApp::addAddress()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------ �������� ����� �������� -----------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "������� ��� �������� : ";
	wcin >> lastnamecontact;
	cout << "������� ������� �������� : ";
	wcin >> firstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> fathernamecontact;

	wchar_t* nameStreet = new wchar_t[20];
	int numberHome, numberAppotarment;
	cout << "������� �������� ����� ���������� �������� : ";
	wcin >> nameStreet;
	cout << "������� ����� ���� ���������� �������� : ";
	cin >> numberHome;
	cout << "������� ����� �������� ���������� �������� : ";
	cin >> numberAppotarment;

	con->addAddress(lastnamecontact,
		firstnamecontact,
		fathernamecontact,
		nameStreet,
		numberHome,
		numberAppotarment);

	delete[] nameStreet;
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}


void ConsoleApp::deletePhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- ������� ���������� ����� �������� ------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "������ ����� -[ +7(999)462-12-42 ]" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "������� ��� �������� : ";
	wcin >> lastnamecontact;
	cout << "������� ������� �������� : ";
	wcin >> firstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> fathernamecontact;
	wchar_t* phoneNumber = new wchar_t[20];
	cout << "������� ���������� ����� : ";
	wcin >> phoneNumber;

	con->deletePhoneNumberContact(
		lastnamecontact,
		firstnamecontact,
		fathernamecontact,
		phoneNumber);

	delete[] phoneNumber;
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::deleteAddress()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------ ������� ����� �������� -----------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "������� ��� �������� : ";
	wcin >> lastnamecontact;
	cout << "������� ������� �������� : ";
	wcin >> firstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> fathernamecontact;

	con->deleteAddress(
		lastnamecontact,
		firstnamecontact,
		fathernamecontact);

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::success()
{
	cout << "Success!!!!))" << endl;
}

void ConsoleApp::fail()
{
	cout << "Fail" << endl;
}

wchar_t* ConsoleApp::get_a_number()
{
	wchar_t* numder = new wchar_t[20];
	cout <<  "������� ����� �������� ��� ����������� ������ ��������" << endl;
 	wcin >> numder;
	return numder;
}

wchar_t* ConsoleApp::get_a_address()
{
	wchar_t* numder = new wchar_t[20];
	cout << "������� ����� �������� ��� ����������� ������ ��������" << endl;
	wcin >> numder;
	return numder;
}

void ConsoleApp::offlineStatus()
{
	cout << "������ ����������� � ��. ���������� �������� � ������� ������.\n";
	_getwch();
	system("cls");
}



