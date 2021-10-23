#pragma once

#include <iostream>
#include <string>
#include "Module.h"

using namespace std;
class Program //динамический упорядоченный двунаправленный список
{
private:
	string name;
	Module *module;

public:
	Program(string name)
	{
		this->name = name;
		module = new Module();
	}
	~Program()
	{
		Module  *temp = module->GetNext();
		while (temp != module)
		{
			temp = temp->GetNext();
			delete temp->GetPrev();
		};
		delete module;
	}

	string GetName() { return name; }

	Module *GetModule() { return module; }

	bool ShowStraight()
	{
		Module *temp = module->GetNext();
		if (temp == module)
		{
			cout << "\nВ программе " << name << " нет модулей.\n";
			return false;
		}

		while (temp != module)
		{
			cout << "\nМодуль " << temp->GetNumber() << ": ";
			temp->ShowStraight();
			temp = temp->GetNext();
		}
		cout << endl;
		return true;
	}

	bool ShowBack()
	{
		Module *temp = module->GetPrev();
		if (temp == module)
		{
			cout << "\nВ программе " << name << " нет модулей.\n";
			return false;
		}

		while (temp != module)
		{
			cout << "\nМодуль " << temp->GetNumber() << ": ";
			temp->ShowBack();
			temp = temp->GetPrev();
		}
		cout << endl;
		return true;
	}

	void Add(int number)
	{
		Module *temp = module->GetNext();
		Module *newModule = new Module(number);

		if (temp == module)
		{
			newModule->SetNext(temp);
			newModule->SetPrev(temp);
			temp->SetNext(newModule);
			temp->SetPrev(newModule);
		}
		else
		{
			while (temp->GetNumber() < number && temp != module)
			{
				temp = temp->GetNext();
			}
			newModule->SetNext(temp);
			newModule->SetPrev(temp->GetPrev());
			temp->GetPrev()->SetNext(newModule);
			temp->SetPrev(newModule);
		}

		cout << "Модуль был успешно добавлен\n";
	}

	void Delete(int number)
	{
		Module *temp = Search(number);

		if (temp == module)
			cout << "Такого модуля в программе нет.\n";
		else
		{
			temp->SetNext(temp->GetNext());
			temp->GetNext()->SetPrev(temp->GetPrev());
			temp->GetPrev()->SetNext(temp->GetNext());
			delete temp;
			cout << "Модуль был успешно удален.\n";
		}
	}

	Module *Search(int number)
	{
		Module *temp = module->GetNext();

		while (temp->GetNumber() != number && temp != module)
			temp = temp->GetNext();

		return temp;
	}

	bool Save_File(char *way)
	{
		if (module->GetNext() == module) return false;
		ofstream file(way);

		Module *moduleTemp = module->GetNext();
		
		while (moduleTemp != module)
		{
			file << moduleTemp->GetNumber();

			Podprogram* podprogram = moduleTemp->GetPodprogram();
			Podprogram* podprogramTemp = moduleTemp->GetPodprogram()->GetNext();
			if (podprogramTemp != podprogram)
			{
				file << ":" << endl;
				while (podprogramTemp != podprogram)
				{
					file << podprogramTemp->GetNumber() << "|" << podprogramTemp->GetDiscription();
					podprogramTemp = podprogramTemp->GetNext();
					if (podprogramTemp == podprogram)
					{
						file << ";" << endl;
					}
					else file << endl;
				}
			}
			else file << endl;

			moduleTemp = moduleTemp->GetNext();
		}

		file.close();
		return true;
	}

	bool Protect_File(char *way)
	{
		ifstream file(way);
		char *buf = new char[100];
		bool nr = true;
		while (file.getline(buf, 100))
		{
			int i = 0;
			if (buf[i] == '\0') { cout << "a"; file.close(); return false; }
			if (nr)
			{
				while (buf[i] != '\0')
				{
					if ((buf[i] == ':' && (i == 0 || buf[i + 1] != '\0')))
					{
						cout << "e";
						cout << buf[i];
						file.close(); return false;
					}
					if (((int)buf[i] < 48 || (int)buf[i] > 57) && buf[i] != ':')
					{
						cout << "w";
						cout << buf[i];
						file.close(); return false;
					}
					i++;
				}
				if (buf[i - 1] == ':') nr = false;
			}

			else
			{
				int pr = 0;
				while (buf[i] != '\0')
				{

					if (buf[i] == '|')
					{
						pr++;
						if ((buf[i + 1] == '\0' || buf[i + 1] == ';')) 
						{ 
							cout << "q" << buf[i]; 
							file.close(); 
							return false; }
					}

					i++;
				}
				if (pr == 0 || pr > 1) { cout << buf[i]; file.close(); return false; }
				if (buf[i - 1] == ';') nr = true;
			}
		}
		file.close();
		return true;
	}

	bool Download(char *way)
	{
		if (!Protect_File(way)) return false;

		Module *temp = module->GetNext();

		while (temp != module)
		{
			temp = temp->GetNext();
			delete temp->GetPrev();
		}
		module->SetNext(module);

		ifstream file(way);

		char *buf = new char[100];
		bool nr = true;
		string moduleNumber, number = "", stringCount = "";
		while (file.getline(buf, 100))
		{
			int i = 0;
			if (nr)
			{
				moduleNumber = "";

				while (buf[i] != '\0' && buf[i] != ':' && (int)buf[i] >= 48 && (int)buf[i] <= 57)
				{
					moduleNumber += buf[i];
					i++;
				}

				Add(atoi(moduleNumber.c_str()));
				if (buf[i] == ':') nr = false;
			}
			else
			{
				temp = Search(atoi(moduleNumber.c_str()));
				number = "";
				stringCount = "";
				while (buf[i] != '|')
				{
					number += buf[i];
					i++;
				}
				i++;
				while (buf[i] != '\0')
				{
					if (buf[i] != ';') stringCount += buf[i];
					i++;
				}

				temp->Add(atoi(number.c_str()), stringCount);
				if (buf[i - 1] == ';') nr = true;
			}
		}
		file.close();
		return true;
	}
};

