#pragma once
#include <iostream>
#include <conio.h>
#include <cstdlib>
using namespace std;

class ConsoleApp 
{
private:
	int MainMenu;
	int UntMenu;
	int ch;
//��������� �� ���������� �� ������

public:
	ConsoleApp() 
	{
		MainMenu = 0;
		UntMenu = 0;
		ch = 0;
		setlocale(LC_ALL, "Russian");
		//system("chcp 1251 > nul");
		system("color 0F");
	}

	void Main_menu_output()
	{
		cout << "1 - ��������� ������ � ���������� �����" << endl;
		cout << "2 - �������� ������ � ���������� �����" << endl;
		cout << "3 - �������� ������ � ���������� �����" << endl;
		cout << "4 - �������� ������" << endl;
		cout << "������� 9 ��� ������" << endl;
	}

	void clear()
	{
		MainMenu = 0;
		UntMenu = 0;
		ch = 0;

		Main_menu_output();
	}

	void run()
	{
		Main_menu_output();
		

		while (MainMenu != 9)
		{
			cin >> MainMenu;
			system("cls");
			switch (MainMenu)
			{
				default:
				{
					cout << "��������\n";
					_getch();
					system("cls");
					clear();
					break;
				}
				case 1:
				{
					_getch();
					system("cls");
					clear();
					break;
				};
				case 2:
				{
					_getch();
					system("cls");
					clear();
					break;
				}
				case 3:
				{
					_getch();
					system("cls");
					clear();
					break;
				}
				case 4:
				{
					_getch();
					system("cls");
					clear();
					break;
				}
				case 9: break;
			}
		}
		system("pause");
	}
};