#include "pch.h"
#include <iostream>
#include "string"
#include "Program.h"
#include "windows.h"
#include <cstdio>

using namespace std;

void ProtectedInput(int* value) //функция для безопасного считывания чисел
{
	cin >> *value;
	while (!cin)
	{
		cout << "Я хочу число! Попробуй еще раз: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> *value;
	}
}

int main()
{
	SetConsoleCP(1251); //настройка русского языка
	SetConsoleOutputCP(1251);

	int number, menu;
	string name = "х";
	cout << "\nВведите название программы: ";
	getline(cin, name, '\n');
	cout << "\n";


	Program *program = new Program(name);

	do
	{
		cout << "Вы находитесь в меню программы " << program->GetName() << "\nВам доступно следующее:\n\n";
		cout << "1 - Посмотреть модули и их подпрограммы в прямом порядке" << endl;
		cout << "2 - Посмотреть модули и их подпрограммы в обратном порядке" << endl;
		cout << "3 - Добавить модуль" << endl;
		cout << "4 - Удалить выбранный модуль" << endl;
		cout << "5 - Перейти к конкретному модулю" << endl;
		cout << "6 - Сохранить базу данных в файл" << endl;
		cout << "7 - Загрузить базу данных из файла" << endl;
		cout << "0 - Завершить работу программы" << endl;

		ProtectedInput(&menu); //ввод
		system("cls");

		switch (menu)
		{
		case 0: {delete program; //здесь вызывается деструктор главной композиции
			return 0; }
		case 1:
			program->ShowStraight();
			break;
		case 2:
			program->ShowBack();
			break;
		case 3: //добавление
		{
			int newNumber;
			cout << "Введите номер нового модуля: ";
			ProtectedInput(&newNumber);
			program->Add(newNumber);
			break;
		}
		case 4:
		{
			int delNumber;
			cout << "Введите номер модуля, который хотите удалить: ";
			ProtectedInput(&delNumber);
			program->Delete(delNumber);
			break;
		}
		case 5:
		{
			cout << "Введите номер модуля, к которому хотите перейти: ";
			ProtectedInput(&number);

			Module *temp = program->Search(number);

			if (temp == program->GetModule()) { cout << "Такого модуля нет!" << endl; break; }
			else
			{
				system("cls");
				int number = -1;
				string description = "";

				do
				{
					cout << "\n\nВы находитесь в меню модуля " << temp->GetNumber()
						<< "\nВы можете совершить следующие действия:\n" << endl;
					
					cout << "1 - Посмотреть список подпрограмм в прямом порядке" << endl;
					cout << "2 - Посмотреть список подпрограмм в обратном порядке" << endl;
					cout << "3 - Добавить новую подпрограмму" << endl;
					cout << "4 - Удалить выбранную подпрограмму" << endl;
					cout << "5 - Найти выбранную подпрограмму" << endl;
					cout << "0 - Вернуться к меню программы" << endl;

					ProtectedInput(&menu);
					system("cls");

					switch (menu)
					{
					case 0: { break; }
					case 1: //показ
					{
						temp->ShowStraight();
						break;
					}
					case 2:
					{
						temp->ShowBack();
						break;
					}
					case 3: //добавление 
					{
						cout << "Введите номер подпрограммы: ";
						ProtectedInput(&number);

						cout << "Введите описание: ";
						cin.ignore();
						cin.clear();
						getline(cin, description, '\n');
							
						temp->Add(number, description);
						break;
					}
					case 4: //удаление 
					{
						cout << "Введите номер подпрограммы: ";
						ProtectedInput(&number);
							
						temp->Delete(number);
						break;
					}
					case 5:
					{
						cout << "Введите имя подпрограммы: ";
						ProtectedInput(&number);
							
						temp->Search(number);

						Podprogram* podprogram = temp->Search(number);

						if (podprogram == temp->GetPodprogram()) { cout << "Такой подпрограммы нет!" << endl; break; }
						else
						{
							cout << "\nПодпрограмма " << podprogram->GetNumber() << ":";
							cout << "\n" << podprogram->GetNumber() << ", " << podprogram->GetDiscription();
						}
							
						break;
					}
					default: { break; }
					}


				} while (menu != 0);
			}
			break;
		}

		case 6:
		{
			char way[] = "C:\\SAOD\\database.txt";
			if (program->Save_File(way)) cout << "Данные сохранены." << endl;
			else cout << "Композиция пуста, сохранять нечего" << endl;
			break;
		}
		case 7:
		{
			char way[] = "C:\\SAOD\\database.txt";
			if (program->Download(way)) cout << "Данные загружены." << endl;
			else cout << "Произошел конфликт при чтении файла.\nПроверте правильность оформления файла и повторите попытку.";

			break;
		}
		default: {cout << "Команды, соответсвующей введенному числу, нет." << endl; }
		}
		cout << endl;
	} while (true);
	return 0;
}

