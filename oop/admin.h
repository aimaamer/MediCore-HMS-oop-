#pragma once
#include "person.h"
class Admin : public Person
{
public:
	Admin() : Person(0, (char*)"", (char*)"") {}
	Admin(int ID, char* n, char* p) : Person(ID, n, p) {}
	void display() const override;
	bool login(int ID, const char* pass) override;
	void viewSecLog() const;
	void dailyRep();

};