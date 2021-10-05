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
	cout << "1 - поиск контакта" << endl;
	cout << "2 - Добавить контакт в тк" << endl;
	cout << "3 - Редактирование контакта в тк" << endl;
	cout << "4 - Удаление контакта" << endl;
	cout << "Нажмите 9 для выхода" << endl;
	cout << "------------------------------------------------" << endl;
	cout << ">>";
}
void ConsoleApp::Find_menu()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------- поиск информации -------------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "1 - Искать адрес по ФИО" << endl;
	cout << "2 - Искать номер(а) по ФИО" << endl;
	cout << "3 - Поиск контакта по 4-м символам номера" << endl;
	cout << "9 - Выход из меню поиска информации" << endl;
	cout << "------------------------------------------------" << endl;
	cout << ">>";
}
void ConsoleApp::Update_menu()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------- Обновление информации --------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "1 - Обновить ФИО контакта" << endl;
	cout << "2 - Добавить адрес контакту" << endl;
	cout << "3 - изменить улицу контакту" << endl;
	cout << "4 - изменить номер квартиры контакьта" << endl;
	cout << "5 - изменить номер дома контакту" << endl;
	cout << "6 - Добавить номер телефона контакта" << endl;
	cout << "7 - Изменить номер контакта" << endl;
	cout << "8 - Изменить тип номера контакту" << endl;
	cout << "9 - Удалить номер контакту" << endl;
	cout << "10 - Удалить адрес проживания контакта" << endl;
	cout << "0 - Выход из меню обновление информации" << endl;
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
			cout << "Очепятка\n";
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
			cout << "Очепятка\n";
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
			cout << "Очепятка\n";
			_getwch();
			system("cls");
			break;
		}
	}
}

void ConsoleApp::addContact()
{
	cout << "------------------------------------------------" << endl;
	cout << "-----------------Добавление контакта -----------" << endl;
	cout << "------------------------------------------------" << endl;
	//cout << ">>";
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	con->addСontact(lastnamecontact, firstnamecontact, fathernamecontact);
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::deleteContact()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------------- Удаление контакта ------------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	con->deleteContact(lastnamecontact, firstnamecontact, fathernamecontact);
	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::findAddresstoFIO()
{
	cout << "------------------------------------------------" << endl;
	cout << "----------------- Поиск адреса по ФИО ----------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;

	con->findAddressByFIO(lastnamecontact, firstnamecontact, fathernamecontact);

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::findPhoneNumbertoFIO()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- Поиск телефонного номера по ФИО --------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;

	con->findPhoneByFIO(lastnamecontact, firstnamecontact, fathernamecontact);

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}

void ConsoleApp::findto4()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- Поиск контакта по 4-м символам  --------" << endl;
	cout << "-------------- телефонного номера --------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Введите 4-е символа телефонного номера контакта : ";
	wchar_t* four_phonenumber = new wchar_t[5];
	wcin >> four_phonenumber;
	con->findContactBy4NumberPhone(four_phonenumber);
	delete[] four_phonenumber;
}

void ConsoleApp::updateFIOcontacte()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------- Изменить ФИО контакту ------------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* oldlastnamecontact = new wchar_t[20];
	wchar_t* oldfirstnamecontact = new wchar_t[20];
	wchar_t* oldfathernamecontact = new wchar_t[20];
	wchar_t* newlastnamecontact = new wchar_t[20];
	wchar_t* newfirstnamecontact = new wchar_t[20];
	wchar_t* newfathernamecontact = new wchar_t[20];
	cout << "Заменяемое ФИО контакта" << endl;
	cout << "Введите имя контакта : ";
	wcin >> oldlastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> oldfirstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> oldfathernamecontact;
	cout << "Новое ФИО контакта" << endl;
	cout << "Введите имя контакта : ";
	wcin >> newlastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> newfirstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> newfathernamecontact;

	con->toСhangeContact(
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
	cout << "------------ Добавить адрес контакту -----------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;

	wchar_t* nameStreet = new wchar_t[20];
	int numberHome, numberAppotarment;
	cout << "Введите название улицы проживания контакта : ";
	wcin >> nameStreet;
	cout << "Введите номер дома проживания контакта : ";
	cin >> numberHome;
	cout << "Введите номер квартиры проживания контакта : ";
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
	cout << "------- Обновить название улицы контакту -------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	wchar_t* nameStreet = new wchar_t[20];
	cout << "Введите новое название улицы проживания контакта : ";
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
	cout << "---------- Обновить номер дома контакту --------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	int numberHome;
	cout << "Введите новый номер дома проживания контакта : ";
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
	cout << "------ Обновить номер квартиры контакту --------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	int numberAppotarment;
	cout << "Введите новый номер дома проживания контакта : ";
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
	cout << "------ Добавить телефонный номер контакту ------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Пример ввода -[ +7(999)462-12-42 ]" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	wchar_t* phoneNumber = new wchar_t[20];
	cout << "Введите телефонный номер : ";
	wcin >> phoneNumber;
	int type;
	cout << "Введите тип телефонного номера : ";
	cin >> type;
	if (type < 0 || type > 3)
	{
		cout << "Ошибка! неизвестный тип телефонного номера" << endl;
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
	cout << "------ Изменить телефонный номер контакту ------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Пример ввода -[ +7(999)462-12-42 ]" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	wchar_t* oldphoneNumber = new wchar_t[20];
	cout << "Введите старый телефонный номер : ";
	wcin >> oldphoneNumber;
	wchar_t* newphoneNumber = new wchar_t[20];
	cout << "Введите новый телефонный номер : ";
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
	cout << "------------ Изменить тип телефонного ----------" << endl;
	cout << "-----------------номера контакту----------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Пример ввода -[ +7(999)462-12-42 ]" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	wchar_t* phoneNumber = new wchar_t[20];
	cout << "Введите телефонный номер : ";
	wcin >> phoneNumber;
	int type;
	cout << "Введите тип телефонного номера контакту : ";
	cin >> type;
	if (type < 0 || type > 3)
	{
		cout << "Ошибка! неизвестный тип телефонного номера" << endl;
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
	cout << "------- Удалить телефонный номер контакту ------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Пример ввода -[ +7(999)462-12-42 ]" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	wchar_t* phoneNumber = new wchar_t[20];
	cout << "Введите телефонный номер : ";
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
	cout << "------------ Удалить адрес контакту -----------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите имя контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;

	con->deleteAddress(
		lastnamecontact,
		firstnamecontact,
		fathernamecontact);

	delete[] lastnamecontact;
	delete[] firstnamecontact;
	delete[] fathernamecontact;
}


