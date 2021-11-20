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
		<< "--------------| Телефонная книга |--------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - Найти контакт" << endl
		<< "[2] - Добавить контакт в ТК" << endl
		<< "------------------------------------------------" << endl
		<< "[3] - Найти контакты по последним 4-м цифрам номера" << endl
		<< "[4] - Найти контакты по ФИО"<<endl
		<< "------------------------------------------------" << endl
		<< "[0] - Выход из программы " << endl << endl << endl << ">>>";
}

void ConsoleApp::MenuPC()
{
	system("cls");
	drawPerson(this->currentPerson);
	cout << "------------------------------------------------" << endl
		<< "--------------|  Редактор контакта |------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - Обновить ФИО контакта" << endl
		<< "[2] - Обновить адрес контакту" << endl
		<< "[4] - Добавить номер телефона контакту" << endl
		<< "[5] - Переписать номер контакта" << endl
		<< "[6] - Удалить контакт" << endl
		<< "[7] - Посмотреть номера контакта" << endl
		<< "[8] - Просмотреть адрес проживания контакта" << endl
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
			case 1: 
			{
				system("cls");
				try {
					this->currentPerson = findPerson();
					drawPerson(this->currentPerson);// вывод контакта на экран

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
					cout << "Ошибка!" << endl;
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
				cout << "Очепятка!" << endl;
				_getwch();
				break;
		}
	}
}


Person* ConsoleApp::findPerson()
{
	cout << "------------------------------------------------" << endl
		<< "----------------| Поиск контакта |--------------" << endl
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
	cout << "---------------| Добавление контакта |----------" << endl;
	cout << "------------------------------------------------" << endl;
	
	wchar_t* lastnamecontact = nullptr;
	wchar_t* firstnamecontact = nullptr;
	wchar_t* fathernamecontact = nullptr;
	inputContact(lastnamecontact, firstnamecontact, fathernamecontact);
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
	delete pn;
}

/*числа на вход поступают в виде vector int*/
void ConsoleApp::findto4()
{
	cout << "------------------------------------------------" << endl;
	cout << "------- Поиск контакта по 4-м символам  --------" << endl;
	cout << "-------------- телефонного номера --------------" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Введите 4-е символа телефонного номера контакта : ";
	std::vector<int> vec;
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
	cout << "------------- Изменить ФИО контакту ------------" << endl;
	cout << "------------------------------------------------" << endl;
	
	wchar_t* lastnamecontact = nullptr;
	wchar_t* firstnamecontact = nullptr;
	wchar_t* fathernamecontact = nullptr;
	inputContact(lastnamecontact, firstnamecontact, fathernamecontact);

	if (con->toСhangeContact(
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

void ConsoleApp::updatePhoneNumber()
{
	cout << "------------------------------------------------" << endl;
	cout << "-------- Редактировать номер контакту ----------" << endl;
	cout << "------------------------------------------------" << endl;

	if (drawPhoneNumbers(currentPerson->getNumbers())) 
	{
		wcout << L"Введите порядковый номер изменяемого телефона" << endl;
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
	cout << "Желаете редактировать контакт" << endl
		<< "[1] - Да;   [0] - Нет" << endl;
	int tmp;
	while (true)
	{
		cin >> tmp;
		if (tmp == 0)
			return false;		
		else if (tmp == 1)
			return true;
		else
			cout << "Очепятка" << endl;
	}
}

void ConsoleApp::fail()
{
	cout << "Fail" << endl;
}

void ConsoleApp::noRes()
{
	wcout << L"Совпадений не найдено\n";
}

void ConsoleApp::clones()
{
	cout << "Атака клонов" << endl;
}

void ConsoleApp::drawPerson(Person* pt)
{
	wcout << L"контакт : " 
		<< pt->getLastName() << " "
		<< pt->getFirstName() << " "
		<< pt->getFatherName() << endl;
}

void ConsoleApp::drawAddress(Address* add)
{
	if (add != nullptr)
	{
		wcout << L"ул. " << add->getStreet() << " " <<
			L"дом " << add->getHome() << " " <<
			L"кв. " << add->getAppartement() << endl;
	}
	else wcout << L"Ошибка чтения\n";
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
		wcout << L"Ошибка чтения!. Пустой телефон.\n";
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
		wcout << L"Ошибка. Нет номеров.\n";
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

/*ввод номера телефона*/
wchar_t* ConsoleApp::get_a_number()
{
	wchar_t* number = new wchar_t[20];
	cout << "Введите номер телефона" << endl
		<< "X(XXX)XXX-XX-XX" << endl;
	wcin.width(20);
	wcin >> number;
	wcin.ignore(MAXINT, '\n');

	while (!checkFormat(number))
	{
		cout << "Введите заново:" << endl;
		wcin.width(20);
		wcin >> number;
		wcin.ignore(MAXINT, '\n');
	}

	return number;
}

wchar_t* ConsoleApp::get_a_addressName()
{
	wchar_t* street = new wchar_t[20];
	cout << "Введите название улицы проживания" << endl;
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

void ConsoleApp::inputContact(wchar_t* & lastnamecontact, wchar_t*& firstnamecontact, wchar_t*& fathernamecontact)
{
	lastnamecontact = new wchar_t[strSZ];
	firstnamecontact = new wchar_t[strSZ];
	fathernamecontact = new wchar_t[strSZ];
	cout << "Введите фамилию контакта : ";
	wcin.width(20);
	wcin >> lastnamecontact;
	wcin.ignore(MAXINT, '\n');
	
	cout << "Введите имя контакта : ";
	wcin.width(20);
	wcin >> firstnamecontact;
	wcin.ignore(MAXINT, '\n');
	
	cout << "Введите отчество контакта : ";
	wcin.width(20);
	wcin >> fathernamecontact;
	wcin.ignore(MAXINT, '\n');
}

void ConsoleApp::offlineStatus()
{
	wcout << L"Ошибка подключения к бд. Приложение работает в оффлайн режиме.\n";
	_getwch();
	system("cls");
}

void ConsoleApp::noTableConfig()
{
	wcout << L"Нет конфигурационного файла для таблиц бд\n";
	_getwch();
	system("cls");
}

void ConsoleApp::noConnectionConfig()
{
	cout << "Нет конфигурационного файла подключения к БД\n";
	_getwch();
	system("cls");
}
