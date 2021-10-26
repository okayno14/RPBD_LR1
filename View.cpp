#include "View.h"

ConsoleApp::ConsoleApp()
{
	MainMenu = 0;
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
	wcout << L"|������� : "
		<< *this->currentPerson->getLastName() << " "
		<< *this->currentPerson->getFirstName() << " "
		<< *this->currentPerson->getFatherName() << L" |" << endl;
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
			system("cls");
			try {
				this->currentPerson = findPerson();
				cout << "������ ������� : ";
				wcout << this->currentPerson->getLastName() << " "
					<< this->currentPerson->getFirstName() << " "
					<< this->currentPerson->getFatherName() << endl << endl;

				if (toRunMenuTwo())
					runPC();
			}
			catch (...) {
				cout << "��������� �� ����������" << endl;
			}
			_getwch();
			break;
		}
		case 2: {
			system("cls");
			try
			{
				this->currentPerson = addContact();

				if (toRunMenuTwo())
					runPC();

			}
			catch (...)
			{
				cout << "������!" << endl;
			}
			
			_getwch();
			break;
		}
		case 3: {
			system("cls");
			findto4();
			break;
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
		MenuPC();
		cin >> MainMenu;
		switch (MainMenu)
		{
		case 1: {
			system("cls");
			updateFIOcontacte();
			break;
		}
		case 2: {
			system("cls");
			addAddress();
			break;
		}
		case 3: {
			system("cls");
			deleteAddress();
			break;
		}
		case 4: {
			system("cls");
			addPhoneNumber();
			break;
		}
		case 5: {
			system("cls");
			deletePhoneNumber();
			break;
		}
		case 6: {
			system("cls");
			deleteContact();
			break;
		}
		case 0: {
			system("cls");
			exitWhileLocal = false;
			break;
		}
		default:
			system("cls");
			cout << "��������!" << endl;
			break;
		}

	}

}


Person* ConsoleApp::findPerson()
{
	cout << "------------------------------------------------" << endl
		<< "----------------| ����� �������� |--------------" << endl
		<< "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "������� ������� �������� : ";
	wcin >> lastnamecontact;
	cout << "������� ��� �������� : ";
	wcin >> firstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> fathernamecontact;
	Person* p;
	try {
		p = con->findPerson(lastnamecontact, firstnamecontact, fathernamecontact);
	}
	catch (...)
	{
		throw - 1;
	}
	

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
	return p;
}

Person* ConsoleApp::addContact()
{
	Person* p;
	cout << "------------------------------------------------" << endl;
	cout << "---------------| ���������� �������� |----------" << endl;
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
	try
	{
		p = con->add�ontact(lastnamecontact, firstnamecontact, fathernamecontact);
	}
	catch (...)
	{
		throw - 1;
	}
	
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
	return p;
}

void ConsoleApp::deleteContact()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------------| �������� �������� |-----------" << endl;
	cout << "------------------------------------------------" << endl;

	if (con->deleteContact(this->currentPerson))
		success();
	else
		fail();
	
}

void ConsoleApp::addPhoneNumber()
{
	cout << "------------------------------------------------" << endl
		<< "---------| ���������� ������ �������� |---------" << endl
		<< "------------------------------------------------" << endl;
	wchar_t* phoneNumber = new wchar_t[20];
	int type;
	
	phoneNumber = get_a_number();
	type = get_a_type_number();
	

	if (con->addPhoneNumberContact(this->currentPerson, phoneNumber, type))
		success();
	else
		fail();

	delete[] phoneNumber;
}

/*redactori*/
/*����� �� ���� ��������� � ���� vector int*/
void ConsoleApp::findto4()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- ����� �������� �� 4-� ��������  --------" << endl;
	cout << "-------------- ����������� ������ --------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "������� 4-� ������� ����������� ������ �������� : ";
	std::vector<int> vec;
	int index;
	for (int i = 0; i < 4; i++)
	{
		cout << "[" << i << "] ";
		cin >> index;
		vec.push_back(index);
	}

	con->findContactBy4NumberPhone(vec);// try ??
}

void ConsoleApp::updateFIOcontacte()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------- �������� ��� �������� ------------" << endl;
	cout << "------------------------------------------------" << endl;
	
	wchar_t* newlastnamecontact = new wchar_t[20];
	wchar_t* newfirstnamecontact = new wchar_t[20];
	wchar_t* newfathernamecontact = new wchar_t[20];
	
	cout << "������� ����� ��� ��������" << endl;
	cout << "������� ��� �������� : ";
	wcin >> newlastnamecontact;
	cout << "������� ������� �������� : ";
	wcin >> newfirstnamecontact;
	cout << "������� �������� �������� : ";
	wcin >> newfathernamecontact;

	if (con->to�hangeContact(
		this->currentPerson,
		newlastnamecontact,
		newfirstnamecontact,
		newfathernamecontact)) success();
	else fail();

	
	delete[] newlastnamecontact;
	delete[] newfirstnamecontact;
	delete[] newfathernamecontact;
}

void ConsoleApp::addAddress()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------ �������� ����� �������� -----------" << endl;
	cout << "------------------------------------------------" << endl;
	
	wchar_t* nameStreet = new wchar_t[20];
	int numberHome, numberAppotarment;
	cout << "������� �������� ����� ���������� �������� : ";
	nameStreet = get_a_addressName();
	cout << "������� ����� ���� ���������� �������� : ";
	numberHome = get_a_numberhome();
	cout << "������� ����� �������� ���������� �������� : ";
	numberAppotarment = get_a_apartment();

	if (con->addAddress(
		this->currentPerson,
		nameStreet,
		numberHome,
		numberAppotarment)) success();
	else fail();

	delete[] nameStreet;
}


void ConsoleApp::deletePhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- ������� ���������� ����� �������� ------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "������ ����� -[ +7(999)462-12-42 ]" << endl;
	
	wchar_t* phoneNumber = new wchar_t[20];
	
	phoneNumber = get_a_number();

	if (con->deletePhoneNumberContact(
		this->currentPerson,
		phoneNumber)) success();
	else fail();

	delete[] phoneNumber;
}

//��������
void ConsoleApp::deleteAddress()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------ ������� ����� �������� -----------" << endl;
	cout << "------------------------------------------------" << endl;

	if (con->deleteAddress(this->currentPerson)) success();
	else fail();
}


void ConsoleApp::success()
{
	cout << "Success!!!!))" << endl;
}

bool ConsoleApp::toRunMenuTwo()
{
	cout << "������� ������������� �������" << endl
		<< "[1] - ��;   [0] - ���" << endl;
	int tmp;
	while (true)
	{
		cin >> tmp;
		if (tmp == 0)
		{
			return false;
		}
		else if (tmp == 1)
		{
			return true;

		}
		else {
			cout << "��������" << endl;
		}
	}
	
	
}

void ConsoleApp::fail()
{
	cout << "Fail" << endl;
}

/*���� ������ ��������*/
wchar_t* ConsoleApp::get_a_number()
{
	wchar_t* numder = new wchar_t[20];
	cout << "������� ����� ��������" << endl
		<< "X(XXX)XXX-XX-XX" << endl;
 	wcin >> numder;
	return numder;
}


wchar_t* ConsoleApp::get_a_addressName()
{
	wchar_t* numder = new wchar_t[20];
	cout << "������� �������� ����� ���������" << endl;
	wcin >> numder;
	return numder;
}

int ConsoleApp::get_a_type_number()
{
	int type;
	while(true)
	{
		cout << "������� ��� ��������" << endl
			<< "[1] - ���������" << endl
			<< "[2] - �������" << endl
			<< "[3] - ��������" << endl;
		cin >> type;
		if (type == 1 || type == 2 || type == 3)
			return type;
	}
}

int ConsoleApp::get_a_apartment()
{
	int num;
	cout << "������� ����� ��������" << endl;
	cin >> num;
	return num;
}

int ConsoleApp::get_a_numberhome()
{
	int num;
	cout << "������� ����� ����" << endl;
	cin >> num;
	return num;
}

void ConsoleApp::offlineStatus()
{
	cout << "������ ����������� � ��. ���������� �������� � ������� ������.\n";
	_getwch();
	system("cls");
}



