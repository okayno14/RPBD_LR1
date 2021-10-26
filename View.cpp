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
	cout << "------------------------------------------------" << endl
		<< "--------------| Телефонная книга |--------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - Поиск контакта" << endl
		<< "[2] - Добавить контакт в тк" << endl
		<< "------------------------------------------------" << endl
		<< "[3] - Поиск контакта по 4-м символам номера" << endl
		<< "------------------------------------------------" << endl
		<< "[0] - Выход из программы " << endl << endl << endl << ">>>";
}

void ConsoleApp::MenuPC()
{
	drawPerson(this->currentPerson);
	cout << "------------------------------------------------" << endl
		<< "--------------|  Редактор контакта |------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - Обновить ФИО контакта" << endl
		<< "[2] - Добавить адрес контакту" << endl
		<< "[3] - Обновить адрес проживания контакта" << endl
		<< "[4] - Добавить номер телефона контакта" << endl
		<< "[5] - Обновить номер контакту" << endl
		<< "[6] - Удаление контакта" << endl
		<< "[7] - Посмотреть список номеров" << endl
		<< "[8] - Просмотреть список адресов" << endl
		<< "[0] - Выход из подменю" << endl << endl << ">>>";
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
				drawPerson(this->currentPerson);// вывод контакта на экран

				if (toRunMenuTwo())
					runPC();
			}
			catch (...) {
				cout << "Контактов не обнаружено" << endl;
			}
			_getwch();
			system("cls");
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
				cout << "Ошибка!" << endl;
			}
			
			_getwch();
			system("cls");
			break;
		}
		case 3: {
			system("cls");
			findto4();
			system("cls");
			break;
		}
		case 0: {
			this->runTimeProgram = false;
			break;
		}
		default:
			Sleep(2000);
			cout << "Очепятка!" << endl;
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
			_getwch();
			system("cls");
			break;
		}
		case 2: {
			system("cls");
			addAddress();
			_getwch();
			system("cls");
			
			break;
		}
		case 3: {
			system("cls");
			updateAddress();
			_getwch();
			system("cls");
			break;
		}
		case 4: {
			system("cls");
			addPhoneNumber();
			_getwch();
			system("cls");
			break;
		}
		case 5: {
			system("cls");
			updatePhoneNumber();
			_getwch();
			system("cls");
			break;
		}
		case 6: {
			system("cls");
			deleteContact();
			_getwch();
			system("cls");
			break;
		}
		case 7: {
			break;
		}
		case 8: {
			break;
		}
		case 0: {
			system("cls");
			exitWhileLocal = false;
			break;
		}
		default:
			system("cls");
			cout << "Очепятка!" << endl;
			break;
		}

	}

}


Person* ConsoleApp::findPerson()
{
	cout << "------------------------------------------------" << endl
		<< "----------------| Поиск контакта |--------------" << endl
		<< "------------------------------------------------" << endl;
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите фамилию контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите имя контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
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
	cout << "---------------| Добавление контакта |----------" << endl;
	cout << "------------------------------------------------" << endl;
	//cout << ">>";
	wchar_t* lastnamecontact = new wchar_t[20];
	wchar_t* firstnamecontact = new wchar_t[20];
	wchar_t* fathernamecontact = new wchar_t[20];
	cout << "Введите фамилию контакта : ";
	wcin >> lastnamecontact;
	cout << "Введите имя контакта : ";
	wcin >> firstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> fathernamecontact;
	try
	{
		p = con->addСontact(lastnamecontact, firstnamecontact, fathernamecontact);
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
	cout << "----------------| Удаление контакта |-----------" << endl;
	cout << "------------------------------------------------" << endl;

	if (con->deleteContact(this->currentPerson))
		success();
	else
		fail();
	
}

void ConsoleApp::addPhoneNumber()
{
	cout << "------------------------------------------------" << endl
		<< "---------| Добавление номера контакту |---------" << endl
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
}

/*redactori*/
/*числа на вход поступают в виде vector int*/
void ConsoleApp::findto4()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- Поиск контакта по 4-м символам  --------" << endl;
	cout << "-------------- телефонного номера --------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Введите 4-е символа телефонного номера контакта : ";
	std::vector<int> vec;
	//string ch;
	int chetirechisl;
	while (true)
	{
		cin >> chetirechisl;
		if (chetirechisl < 10000 && chetirechisl >= 0)
		{
			break;
		}
		cout << "Введите 4 числа" << endl;
	}
	vec.push_back(chetirechisl / 1000);
	vec.push_back((chetirechisl % 1000) / 100);
	vec.push_back((chetirechisl % 100) / 10);
	vec.push_back(chetirechisl % 10);
	con->findContactBy4NumberPhone(vec);
}

void ConsoleApp::updateFIOcontacte()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------- Изменить ФИО контакту ------------" << endl;
	cout << "------------------------------------------------" << endl;
	
	wchar_t* newlastnamecontact = new wchar_t[20];
	wchar_t* newfirstnamecontact = new wchar_t[20];
	wchar_t* newfathernamecontact = new wchar_t[20];
	
	cout << "Введите новое ФИО контакта" << endl;
	cout << "Введите имя контакта : ";
	wcin >> newlastnamecontact;
	cout << "Введите фамилию контакта : ";
	wcin >> newfirstnamecontact;
	cout << "Введите отчество контакта : ";
	wcin >> newfathernamecontact;

	if (con->toСhangeContact(
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
	cout << "------------ Добавить адрес контакту -----------" << endl;
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


void ConsoleApp::deletePhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- Удалить телефонный номер контакту ------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Пример ввода -[ +7(999)462-12-42 ]" << endl;
	
	wchar_t* phoneNumber = new wchar_t[20];
	
	phoneNumber = get_a_number();

	if (con->deletePhoneNumberContact(
		this->currentPerson,
		phoneNumber)) success();
	else fail();

	delete[] phoneNumber;
}

//изменить
void ConsoleApp::deleteAddress()
{
	cout << "------------------------------------------------" << endl;
	cout << "------------ Удалить адрес контакту -----------" << endl;
	cout << "------------------------------------------------" << endl;

	if (con->deleteAddress(this->currentPerson)) success();
	else fail();
}

void ConsoleApp::updateAddress()
{
	cout << "------------------------------------------------" << endl;
	cout << "-------- Редактировать адрес контакту ----------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* nameStrit = get_a_addressName();
	int numHom = get_a_numberhome();
	int numApart = get_a_apartment();
	Address* ad = new Address(nameStrit, numHom, numApart);
	if (con->updateAddress(this->currentPerson, ad)) success();
	else fail();

	delete[] nameStrit;
}

void ConsoleApp::updatePhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "-------- Редактировать номер контакту ----------" << endl;
	cout << "------------------------------------------------" << endl;
	wchar_t* number = get_a_number();
	int type = get_a_type_number();
	PhoneNumber* ph = new PhoneNumber(number, type);
	
	if (con->updatePhoneNumber(this->currentPerson,  ph)) success();
	else fail();
	delete[] number;

}


void ConsoleApp::success()
{
	cout << "Success!!!!))" << endl;
}

bool ConsoleApp::toRunMenuTwo()
{
	cout << "Желаете редактировать контакт" << endl
		<< "[1] - Да;   [0] - Нет" << endl;
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
			cout << "Очепятка" << endl;
		}
	}
	
	
}

void ConsoleApp::fail()
{
	cout << "Fail" << endl;
}

void ConsoleApp::drawPerson(Person* pt)
{
	wcout << L"контакт : " 
		<< pt->getLastName() << " "
		<< pt->getFirstName() << " "
		<< pt->getFatherName() << endl;
}

/*ввод номера телефона*/
wchar_t* ConsoleApp::get_a_number()
{
	wchar_t* numder = new wchar_t[20];
	cout << "Введите номер телефона" << endl
		<< "X(XXX)XXX-XX-XX" << endl;
 	wcin >> numder;
	return numder;
}

wchar_t* ConsoleApp::get_a_addressName()
{
	wchar_t* numder = new wchar_t[20];
	cout << "Введите название улицы проживаия" << endl;
	wcin >> numder;
	return numder;
}

int ConsoleApp::get_a_type_number()
{
	int type;
	while(true)
	{
		cout << "Введите тип телефона" << endl
			<< "[1] - мобильный" << endl
			<< "[2] - рабочий" << endl
			<< "[3] - домашний" << endl;
		cin >> type;
		if (type == 1 || type == 2 || type == 3)
			return type;
	}
}

int ConsoleApp::get_a_apartment()
{
	int num;
	cout << "Введите номер квартиры" << endl;
	cin >> num;
	return num;
}

int ConsoleApp::get_a_numberhome()
{
	int num;
	cout << "Введите номер дома" << endl;
	cin >> num;
	return num;
}

void ConsoleApp::offlineStatus()
{
	cout << "Ошибка подключения к бд. Приложение работает в оффлайн режиме.\n";
	_getwch();
	system("cls");
}



