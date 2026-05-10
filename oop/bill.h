#pragma once
#include<iostream>

class Bill
{
private:
	int billID;
	int apptID;
	int pID;
	double amount;
	char status[10];
	char date[11];
public:
	Bill();
	Bill(int bID, int aID, int pID, double amt,	const char* st, const char* d);
	friend std::ostream& operator<<(std::ostream& out, const Bill& b);
	int getBillID() const;
	int getApptID() const;
	int getPID() const;
	int getID() const;
	double getAmount() const;
	const char* getStatus() const;
	const char* getDate() const;
	void setStatus(const char* s);
};