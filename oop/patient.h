#pragma once
#include "person.h"
#include<iostream>

class Patient :public Person
{
private:
	int age;
	char gender;
	char contact[12];
	double balance;
public:
	Patient();
	Patient(int ID, char* n, char* p, int a, char g, char* c, double b);
	void display() const override;
	bool login(int ID, const char* passw) override;
	double operator-=(double amount);                      
	double operator+=(double amount);
	bool operator==(const Patient& obj) const;
	friend std::ostream& operator<<(std::ostream& out, const Patient& p);
	double getBalance() const;
	int getAge() const;
	char getGender() const;
	const char* getContact() const;
	void setBalance(double b);

};