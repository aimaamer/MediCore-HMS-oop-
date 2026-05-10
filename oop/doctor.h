#pragma once
#include "person.h"
#include<iostream>
using namespace std;
class Doctor : public Person
{
private:
	char spec[70];
	char contact[12];
	double fee;
public:
	Doctor();
	Doctor(int ID, char* n, char* p, char* s, char* c, double f);
	void display() const override;
	bool login(int id, const char* pass) override;
	bool operator==(const Doctor& obj) const;
	friend std::ostream& operator<<(std::ostream& out, const Doctor& d);
	const char* getSpec() const;
	const char* getContact() const;
	double getFee() const;

};