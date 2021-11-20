#pragma once
#include "View.h"

ConsoleApp::ConsoleApp()
{
	Person empty;
	this->currentPerson = &empty;
	MainMenu = 0;
	this->runTimeProgram = true;
	setlocale(LC_ALL, "Russian");
	system("color 0F");
};

void ConsoleApp::Menu()
{
	system("cls");
	cout << "------------------------------------------------" << endl
		<< "--------------| ���������� ����� |--------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - ����� �������" << endl
		<< "[2] - �������� ������� � ��" << endl
		<< "------------------------------------------------" << endl
		<< "[3] - ����� �������� �� ��������� 4-� ������ ������" << endl
		<< "[4] - ����� �������� �� ���"<<endl
		<< "------------------------------------------------" << endl
		<< "[0] - ����� �� ��������� " << endl << endl << endl << ">>>";
}

void ConsoleApp::MenuPC()
{
	system("cls");
	drawPerson(this->currentPerson);
	cout << "------------------------------------------------" << endl
		<< "--------------|  �������� �������� |------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - �������� ��� ��������" << endl
		<< "[2] - �������� ����� ��������" << endl
		<< "[4] - �������� ����� �������� ��������" << endl
		<< "[5] - ���������� ����� ��������" << endl
		<< "[6] - ������� �������" << endl
		<< "[7] - ���������� ������ ��������" << endl
		<< "[8] - ����������� ����� ���������� ��������" << endl
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
			case 1: 
			{
				system("cls");
				try {
					this->currentPerson = findPerson();
					drawPerson(this->currentPerson);// ����� �������� �� �����

					if (toRunMenuTwo())
						runPC();
				}
				catch (...) {
			
				}
				_getwch();
				system("cls");
				break;
			}
			case 2:
			{
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
				system("cls");
				break;
			}
			case 3: 
			{
				system("cls");
				findto4();
				_getwch();
				system("cls");			
				break;
			}
			case 4: 
			{
				system("cls");
				this->findList_FIO();
				_getwch();
				system("cls");
				break;
			}
			case 0: {
				this->runTimeProgram = false;
				break;
			}
			default:
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
			case 1: 
			{
				system("cls");
				updateFIOcontacte();
				_getwch();
				system("cls");
				break;
			}
			case 2: 
			{
				system("cls");
				addAddress();
				_getwch();
				system("cls");			
				break;
			}
			case 4: 
			{
				system("cls");
				addPhoneNumber();
				_getwch();
				system("cls");
				break;
			}
			case 5: 
			{
				system("cls");
				updatePhoneNumber();
				_getwch();
				system("cls");
				break;
			}
			case 6: 
			{
				system("cls");
				deleteContact();
				_getwch();
				exitWhileLocal = false;
				system("cls");
				break;
			}
			case 7: 
			{
				drawPhoneNumbers(currentPerson->getNumbers());
				_getwch();
				break;
			}
			case 8: 
			{
				drawAddress(currentPerson->getAddress());
				_getwch();
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
				_getwch();
				break;
		}
	}
}


Person* ConsoleApp::findPerson()
{
	cout << "------------------------------------------------" << endl
		<< "----------------| ����� �������� |--------------" << endl
		<< "------------------------------------------------" << endl;

	wchar_t* lastnamecontact = nullptr;
	wchar_t* firstnamecontact = nullptr;
	wchar_t* fathernamecontact = nullptr;
	inputContact(lastnamecontact,firstnamecontact,fathernamecontact);
	Person* p;
	try 
	{
		p = con->findPerson(lastnamecontact, firstnamecontact, fathernamecontact);
	}
	catch (int errCode)
	{
		p = nullptr;
		delete[] lastnamecontact;
		delete[] firstnamecontact;
		delete[] fathernamecontact;

		if (errCode == -1)
			noRes();
		if (errCode == -2)
			clones();

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
	
	wchar_t* lastnamecontact = nullptr;
	wchar_t* firstnamecontact = nullptr;
	wchar_t* fathernamecontact = nullptr;
	inputContact(lastnamecontact, firstnamecontact, fathernamecontact);
	try
	{
		p = con->add�ontact(lastnamecontact, firstnamecontact, fathernamecontact);
	}
	catch (...)
	{
		p = nullptr;
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
	
	PhoneNumber* pn = new PhoneNumber(phoneNumber, type);

	if (con->addPhoneNumberContact(this->currentPerson, pn))
		success();
	else
		fail();

	delete[] phoneNumber;
	delete pn;
}

/*����� �� ���� ��������� � ���� vector int*/
void ConsoleApp::findto4()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- ����� �������� �� 4-� ��������  --------" << endl;
	cout << "-------------- ����������� ������ --------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "������� 4-� ������� ����������� ������ �������� : ";
	std::vector<int> vec;
	int chetirechisl;
	while (true)
	{
		cin >> chetirechisl;
		if (chetirechisl < 10000 && chetirechisl >= 0)
		{
			break;
		}
		cout << "������� 4 �����" << endl;
	}
	vec.push_back(chetirechisl / 1000);
	vec.push_back((chetirechisl % 1000) / 100);
	vec.push_back((chetirechisl % 100) / 10);
	vec.push_back(chetirechisl % 10);
	
	con->findContactBy4NumberPhone(vec);
}

void ConsoleApp::findList_FIO()
{
	wchar_t* lastnamecontact = nullptr;
	wchar_t* firstnamecontact = nullptr;
	wchar_t* fathernamecontact = nullptr;
	inputContact(lastnamecontact, firstnamecontact, fathernamecontact);

	con->findFIOALL(lastnamecontact, firstnamecontact, fathernamecontact);
	
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::updateFIOcontacte()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------- �������� ��� �������� ------------" << endl;
	cout << "------------------------------------------------" << endl;
	
	wchar_t* lastnamecontact = nullptr;
	wchar_t* firstnamecontact = nullptr;
	wchar_t* fathernamecontact = nullptr;
	inputContact(lastnamecontact, firstnamecontact, fathernamecontact);

	if (con->to�hangeContact(
		this->currentPerson,
		lastnamecontact,
		firstnamecontact,
		fathernamecontact)) success();
	else fail();
		
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::addAddress()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------ �������� ����� �������� -----------" << endl;
	cout << "------------------------------------------------" << endl;
	
	wchar_t* nameStreet = new wchar_t[20];
	int numberHome, numberAppotarment;
	
	nameStreet = get_a_addressName();
	numberHome = get_a_numberhome();
	numberAppotarment = get_a_apartment();

	Address *ad = new Address(nameStreet, numberHome, numberAppotarment);

	if (con->addAddress(
		this->currentPerson,
		ad)) success();
	else fail();

	delete[] nameStreet;
}

void ConsoleApp::updatePhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "-------- ������������� ����� �������� ----------" << endl;
	cout << "------------------------------------------------" << endl;

	if (drawPhoneNumbers(currentPerson->getNumbers())) 
	{
		wcout << L"������� ���������� ����� ����������� ��������" << endl;
		int ch;
		cin >> ch;

		wchar_t* number = get_a_number();
		int type = get_a_type_number();

		PhoneNumber* ph = new PhoneNumber(number, type);

		if (con->updatePhoneNumber(this->currentPerson, ph, ch)) success();
		else fail();

		delete[] number;
	}	
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
			return false;		
		else if (tmp == 1)
			return true;
		else
			cout << "��������" << endl;
	}
}

void ConsoleApp::fail()
{
	cout << "Fail" << endl;
}

void ConsoleApp::noRes()
{
	wcout << L"���������� �� �������\n";
}

void ConsoleApp::clones()
{
	cout << "����� ������" << endl;
}

void ConsoleApp::drawPerson(Person* pt)
{
	wcout << L"������� : " 
		<< pt->getLastName() << " "
		<< pt->getFirstName() << " "
		<< pt->getFatherName() << endl;
}

void ConsoleApp::drawAddress(Address* add)
{
	if (add != nullptr)
	{
		wcout << L"��. " << add->getStreet() << " " <<
			L"��� " << add->getHome() << " " <<
			L"��. " << add->getAppartement() << endl;
	}
	else wcout << L"������ ������\n";
}

void ConsoleApp::drawPhoneNumber(PhoneNumber* pn)
{
	if (pn != nullptr)
	{
		wcout << pn->getNumber() << "\t";
		switch (pn->getType())
		{
			case 1:
			{
				wcout << L"mobile" << endl;
				break;
			}
			case 2:
			{
				wcout << L"work" << endl;
				break;
			}
			case 3:
			{
				wcout << L"home" << endl;
				break;
			}
		}
	}
	else
		wcout << L"������ ������!. ������ �������.\n";
}

bool ConsoleApp::drawPhoneNumbers(std::vector<PhoneNumber*> args)
{
	if (args.size() > 0)
	{
		for (int i = 0; i < args.size(); i++)
		{
			wcout << L"[" << i << L"] ";
			drawPhoneNumber(args[i]);
		}
		return true;
	}
	else
	{
		wcout << L"������. ��� �������.\n";
		return false;
	}
}

bool ConsoleApp::checkFormat(const wchar_t* number)
{	
	if (
		number[1] == L'(' &&
		number[5] == L')' &&
		number[9] == L'-' &&
		number[12] == L'-' &&
		number[15] == L'\0')
		return true;
	
	return false;
}

/*���� ������ ��������*/
wchar_t* ConsoleApp::get_a_number()
{
	wchar_t* number = new wchar_t[20];
	cout << "������� ����� ��������" << endl
		<< "X(XXX)XXX-XX-XX" << endl;
	wcin.width(20);
	wcin >> number;
	wcin.ignore(MAXINT, '\n');

	while (!checkFormat(number))
	{
		cout << "������� ������:" << endl;
		wcin.width(20);
		wcin >> number;
		wcin.ignore(MAXINT, '\n');
	}

	return number;
}

wchar_t* ConsoleApp::get_a_addressName()
{
	wchar_t* street = new wchar_t[20];
	cout << "������� �������� ����� ����������" << endl;
	wcin.width(20);
	wcin >> street;
	wcin.ignore(MAXINT,'\n');
	return street;
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

void ConsoleApp::inputContact(wchar_t* & lastnamecontact, wchar_t*& firstnamecontact, wchar_t*& fathernamecontact)
{
	lastnamecontact = new wchar_t[strSZ];
	firstnamecontact = new wchar_t[strSZ];
	fathernamecontact = new wchar_t[strSZ];
	cout << "������� ������� �������� : ";
	wcin.width(20);
	wcin >> lastnamecontact;
	wcin.ignore(MAXINT, '\n');
	
	cout << "������� ��� �������� : ";
	wcin.width(20);
	wcin >> firstnamecontact;
	wcin.ignore(MAXINT, '\n');
	
	cout << "������� �������� �������� : ";
	wcin.width(20);
	wcin >> fathernamecontact;
	wcin.ignore(MAXINT, '\n');
}

void ConsoleApp::offlineStatus()
{
	wcout << L"������ ����������� � ��. ���������� �������� � ������� ������.\n";
	_getwch();
	system("cls");
}

void ConsoleApp::noTableConfig()
{
	wcout << L"��� ����������������� ����� ��� ������ ��\n";
	_getwch();
	system("cls");
}

void ConsoleApp::noConnectionConfig()
{
	cout << "��� ����������������� ����� ����������� � ��\n";
	_getwch();
	system("cls");
}
