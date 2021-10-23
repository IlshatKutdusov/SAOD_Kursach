#pragma once

#include <iostream>
#include <string>
#include "Podprogram.h"
#include "fstream"

using namespace std;
class Module //динамический упорядоченный двунаправленный список
{
private:
	int number;

	Podprogram *podprogram;

	Module *next, *prev;

public:
	Module(int number) {
		this->number = number;
		podprogram = new Podprogram();
	}
	Module() {
		podprogram = new Podprogram();
		next = prev = this;
	}
	~Module() {
		Podprogram* temp = podprogram->GetNext();
		while (temp != podprogram)
		{
			temp = temp->GetNext();
			delete temp->GetPrev();
		};
		delete podprogram;
	}

	int GetNumber() { return number; }

	Podprogram *GetPodprogram() { return podprogram; }

	Module *GetNext() { return next; }
	void SetNext(Module *next) { this->next = next; }

	Module* GetPrev() { return prev; }
	void SetPrev(Module *prev) { this->prev = prev; }

	bool ShowStraight()
	{
		Podprogram* temp = podprogram->GetNext();
		if (temp == podprogram)
		{
			cout << "\nВ модуле " << number << " нет подпрограмм.";
			return false;
		}

		while (temp != podprogram)
		{
			cout << "\nПодпрограмма " << temp->GetNumber() << ":";
			cout << "\n" << temp->GetNumber() << ", " << temp->GetDiscription();
			temp = temp->GetNext();
		}
		return true;
	}

	bool ShowBack()
	{
		Podprogram* temp = podprogram->GetPrev();
		if (temp == podprogram)
		{
			cout << "\nВ модуле " << number << " нет подпрограмм.";
			return false;
		}

		while (temp != podprogram)
		{
			cout << "\nПодпрограмма " << temp->GetNumber() << ":";
			cout << "\n" << temp->GetNumber() << ", " << temp->GetDiscription();
			temp = temp->GetPrev();
		}
		return true;
	}

	void Add(int number, string description)
	{
		Podprogram* temp = podprogram->GetNext();
		Podprogram* newPodprogram = new Podprogram(number, description);

		if (temp == podprogram)
		{
			newPodprogram->SetNext(temp);
			newPodprogram->SetPrev(temp);
			temp->SetNext(newPodprogram);
			temp->SetPrev(newPodprogram);
		}
		else
		{
			while (temp->GetNumber() < number && temp != podprogram)
			{
				temp = temp->GetNext();
			}
			newPodprogram->SetNext(temp);
			newPodprogram->SetPrev(temp->GetPrev());
			temp->GetPrev()->SetNext(newPodprogram);
			temp->SetPrev(newPodprogram);
		}

		cout << "Подпрограмма была успешно добавлена\n";
	}

	void Delete(int number)
	{
		Podprogram* temp = Search(number);

		if (temp == podprogram)
			cout << "Такой подпрограммы в модуле нет.\n";
		else
		{
			temp->SetNext(temp->GetNext());
			temp->GetNext()->SetPrev(temp->GetPrev());
			temp->GetPrev()->SetNext(temp->GetNext());
			delete temp;
			cout << "Подпрограмма была успешно удалена.\n";
		}
	}

	Podprogram* Search(int number)
	{
		Podprogram* temp = podprogram->GetNext();

		while (temp->GetNumber() != number && temp != podprogram)
			temp = temp->GetNext();

		return temp;
	}
};


