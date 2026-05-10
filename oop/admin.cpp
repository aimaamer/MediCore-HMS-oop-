#include"admin.h"
#include<iostream>
using namespace std;

bool Admin::login(int ID, const char* passw)
{
	if (id != ID)
		return 0;
	for (int i = 0; password[i] != '\0' || passw[i] != '\0'; i++)
	{
		if (password[i] != passw[i])
			return 0;
	}
	return 1;
}
void Admin::display() const
{
	cout << "Admin Details : " << endl;
	cout << "Name : " << name << endl;
	cout << "ID : " << id << endl;
}
void Admin::viewSecLog() const
{
	// txt
}
void Admin::dailyRep()
{
	//txt shi
}