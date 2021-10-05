#include "View.h"

ConsoleApp::ConsoleApp()
{
	MainMenu = 0;
	UntMenu = 0;
	ch = 0;
	findmenu = false;
	updatemenu = false;
	setlocale(LC_ALL, "Russian");
	//system("chcp 1251 > nul");
	system("color 0F");
};

void ConsoleApp::Main_menu_output()
{
	cout << "------------------------------------------------" << endl;
	cout << "-----------------------Menu---------------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "1 - ����� ��������" << endl;
	cout << "2 - �������� ������� � ��" << endl;
	cout << "3 - �������������� �������� � ��" << endl;
	cout << "4 - �������� ��������" << endl;
	cout << "������� 9 ��� ������" << endl;
	cout << "------------------------------------------------" << endl;
	cout << ">>";
}
void ConsoleApp::Find_menu()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------- ����� ���������� -------------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "1 - ������ ����� �� ���" << endl;
	cout << "2 - ������ �����(�) �� ���" << endl;
	cout << "3 - ����� �������� �� 4-� �������� ������" << endl;
	cout << "9 - ����� �� ���� ������ ����������" << endl;
	cout << "------------------------------------------------" << endl;
	cout << ">>";
}
void ConsoleApp::Update_menu()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------- ���������� ���������� --------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "1 - �������� ��� ��������" << endl;
	cout << "2 - �������� ����� ��������" << endl;
	cout << "3 - �������� ����� ��������" << endl;
	cout << "4 - �������� ����� �������� ���������" << endl;
	cout << "5 - �������� ����� ���� ��������" << endl;
	cout << "6 - �������� ����� �������� ��������" << endl;
	cout << "7 - �������� ����� ��������" << endl;
	cout << "8 - �������� ��� ������ ��������" << endl;
	cout << "9 - ������� ����� ��������" << endl;
	cout << "10 - ������� ����� ���������� ��������" << endl;
	cout << "0 - ����� �� ���� ���������� ����������" << endl;
	cout << "------------------------------------------------" << endl;
	cout << ">>";
}
void ConsoleApp::run()
{
	while (MainMenu != 9)
	{
		Main_menu_output();
		cin >> MainMenu;
		system("cls");
		switch (MainMenu)
		{
		default:
		{
			Sleep(2000);
			system("cls");
			cout << "��������\n";
			_getwch();
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			findmenu = true;
			runFind(findmenu);
			_getwch();
			system("cls");
			break;
		};
		case 2:
		{
			system("cls");
			addContact();
			_getwch();
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			updatemenu = true;
			runUpdate(updatemenu);
			_getwch();
			system("cls");
			break;
		}
		case 4:
		{
			system("cls");
			deleteContact();
			_getwch();
			system("cls");
			break;
		}
		case 9: break;
		}
	}
	system("pause");
}
void ConsoleApp::runFind(bool findmenu)
{
	while (findmenu == true)
	{
		int local_menu = 0;
		Find_menu();
		cin >> local_menu;
		switch (local_menu)
		{
		case 1:
			system("cls");
			findAddresstoFIO();
			_getwch();
			system("cls");
			break;
		case 2:
			system("cls");
			findPhoneNumbertoFIO();
			_getwch();
			system("cls");
			break;
		case 3:
			system("cls");
			findto4();
			_getwch();
			system("cls");
			break;
		case 9:
			findmenu = false;
			break;
		default:
			Sleep(2000);
			system("cls");
			cout << "��������\n";
			_getwch();
			system("cls");
			break;
		}
	}
}
void ConsoleApp::runUpdate(bool updatemenu)
{
	while (updatemenu == true)
	{
		int local_menu = 0;
		Update_menu();
		cin >> local_menu;
		switch (local_menu)
		{
		case 1:
			system("cls");
			updateFIOcontacte();
			_getwch();
			system("cls");
			break;
		case 2:
			system("cls");
			addAddress();
			_getwch();
			system("cls");
			break;
		case 3:
			system("cls");
			updateStreet();
			_getwch();
			system("cls");
			break;
		case 4:
			system("cls");
			updateNumberHome();
			_getwch();
			system("cls");
			break;
		case 5:
			system("cls");
			updateNumberAppartment();
			_getwch();
			system("cls");
			break;
		case 6:
			system("cls");
			addPhoneNumber();
			_getwch();
			system("cls");
			break;
		case 7:
			system("cls");
			updatePhoneNumber();
			_getwch();
			system("cls");
			break;
		case 8:
			system("cls");
			updateTypePhoneNumber();
			_getwch();
			system("cls");
			break;
		case 0:
			updatemenu = false;
			break;
		case 9:
			system("cls");
			deletePhoneNumber();
			_getwch();
			system("cls");
			break;
		case 10:
			system("cls");
			deleteAddress();
			_getwch();
			system("cls");
			break;
		default:
			Sleep(2000);
			system("cls");
			cout << "��������\n";
			_getwch();
			system("cls");
			break;
		}
	}
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
	cout << "������� ��� �������� : ";
	wcin >> lastnamecontact;
	cout << "������� ������� �������� : ";
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

void ConsoleApp::findAddresstoFIO()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------------- ����� ������ �� ��� ----------" << endl;
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

	con->findAddressByFIO(lastnamecontact, firstnamecontact, fathernamecontact);

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::findPhoneNumbertoFIO()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- ����� ����������� ������ �� ��� --------" << endl;
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

	con->findPhoneByFIO(lastnamecontact, firstnamecontact, fathernamecontact);

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

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

void ConsoleApp::updateStreet()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- �������� �������� ����� �������� -------" << endl;
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
	cout << "������� ����� �������� ����� ���������� �������� : ";
	wcin >> nameStreet;

	con->toChangeStreetContacn(
		lastnamecontact,
		firstnamecontact,
		fathernamecontact,
		nameStreet);

	delete[] nameStreet;
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::updateNumberHome()
{
	cout << "------------------------------------------------" << endl;
	cout << "---------- �������� ����� ���� �������� --------" << endl;
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
	int numberHome;
	cout << "������� ����� ����� ���� ���������� �������� : ";
	cin >> numberHome;

	con->toChangeNumberHome(
		lastnamecontact,
		firstnamecontact,
		fathernamecontact,
		numberHome);

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::updateNumberAppartment()
{
	cout << "------------------------------------------------" << endl;
	cout << "------ �������� ����� �������� �������� --------" << endl;
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
	int numberAppotarment;
	cout << "������� ����� ����� ���� ���������� �������� : ";
	cin >> numberAppotarment;

	con->toChangeNumberHome(
		lastnamecontact,
		firstnamecontact,
		fathernamecontact,
		numberAppotarment);

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::addPhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "------ �������� ���������� ����� �������� ------" << endl;
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
	int type;
	cout << "������� ��� ����������� ������ : ";
	cin >> type;
	if (type < 0 || type > 3)
	{
		cout << "������! ����������� ��� ����������� ������" << endl;
	}
	else
	{
		con->addPhoneNumberContact(
			lastnamecontact,
			firstnamecontact,
			fathernamecontact,
			phoneNumber,
			type);
	}



	delete[] phoneNumber;
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::updatePhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "------ �������� ���������� ����� �������� ------" << endl;
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
	wchar_t* oldphoneNumber = new wchar_t[20];
	cout << "������� ������ ���������� ����� : ";
	wcin >> oldphoneNumber;
	wchar_t* newphoneNumber = new wchar_t[20];
	cout << "������� ����� ���������� ����� : ";
	wcin >> newphoneNumber;

	con->toChangePhoneNumberContact(
		lastnamecontact,
		firstnamecontact,
		fathernamecontact,
		oldphoneNumber,
		newphoneNumber);

	delete[] newphoneNumber;
	delete[] oldphoneNumber;
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::updateTypePhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------ �������� ��� ����������� ----------" << endl;
	cout << "-----------------������ ��������----------------" << endl;
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
	int type;
	cout << "������� ��� ����������� ������ �������� : ";
	cin >> type;
	if (type < 0 || type > 3)
	{
		cout << "������! ����������� ��� ����������� ������" << endl;
	}
	else
	{
		con->toChangeTypePhoneNumber(
			lastnamecontact,
			firstnamecontact,
			fathernamecontact,
			phoneNumber,
			type);
	}


	delete[] phoneNumber;
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


