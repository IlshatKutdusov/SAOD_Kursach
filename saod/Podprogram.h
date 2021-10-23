#pragma once

#include <iostream>
#include <string>

using namespace std;
class Podprogram
{
private:
	int number;
	string description;

	Podprogram *next, *prev;
public:
	Podprogram(int number, string description)
	{
		this->number = number;
		this->description = description;
	}
	Podprogram() {
		next = prev = this;
	}
	~Podprogram() {}

	void SetNumber(int value) { number = value; }
	int GetNumber() { return number; }

	void SetDiscription(int value) { description = value; }
	string GetDiscription() { return description; }

	Podprogram* GetNext() { return next; }
	void SetNext(Podprogram* next) { this->next = next; }

	Podprogram* GetPrev() { return prev; }
	void SetPrev(Podprogram* prev) { this->prev = prev; }
};

