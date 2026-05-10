#pragma once
class Person
{
protected:
	int id;
	char name[50];
	char password[50];
public:
	virtual void display() const = 0;
	virtual bool login(int id, const char* passw) = 0;
	Person(int ID, char* n, char* p);
	int getId();
	char* getName();
	char* getPwd();
	void setName(const char* n);
	void setPwd(const char* p);
	void setId(int i);
};
