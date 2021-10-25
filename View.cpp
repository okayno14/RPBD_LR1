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
	cout << ""/*данные об персоне*/ << endl;
	cout << "------------------------------------------------" << endl
		<< "--------------|  Редактор контакта |------------" << endl
		<< "------------------------------------------------" << endl
		<< "[1] - Обновить ФИО контакта" << endl
		<< "[2] - Добавить адрес контакту" << endl
		<< "[3] - Удалить адрес проживания контакта" << endl
		<< "[4] - Добавить номер телефона контакта" << endl
		<< "[5] - Удалить номер контакту" << endl
		<< "[6] - Удаление контакта" << endl
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
			findPerson();

			_getwch();
			break;
		}
		case 2: {
			system("cls");
			addContact();
			if (toRunMenuTwo())
				runPC();

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
			cout << "Очепятка!" << endl;
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
	cout << "-----------------Добавление контакта -----------" << endl;
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


void ConsoleApp::addPhoneNumber()
{
}

/*числа на вход поступают в виде vector int*/
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

void ConsoleApp::success()
{
	cout << "Success!!!!))" << endl;
}

bool ConsoleApp::toRunMenuTwo()
{
	cout << "Желаете редактировать контакт" << endl
		<< "[1] - Да;   [0] - Нет" << endl;
	int tmp;
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
		return false;
	}
	
}

void ConsoleApp::fail()
{
	cout << "Fail" << endl;
}

wchar_t* ConsoleApp::get_a_number()
{
	wchar_t* numder = new wchar_t[20];
	cout << "Введите номер телефона для дальнейшего поиска контакта" << endl
		<< "X(XXX)XXX-XX-XX" << endl;
 	wcin >> numder;
	return numder;
}


wchar_t* ConsoleApp::get_a_addressName()
{
	wchar_t* numder = new wchar_t[20];
	cout << "Введите название улицы проживаия для дальнейшего поиска контакта" << endl;
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
	cout << "Введите номер домо" << endl;
	cin >> num;
	return num;
}

void ConsoleApp::offlineStatus()
{
	cout << "Ошибка подключения к бд. Приложение работает в оффлайн режиме.\n";
	_getwch();
	system("cls");
}



