#include"person.h"
#include<iostream>

Person :: Person(int ID, char* n, char* p)
{
	id = ID;
	int i = 0;
	for (; n[i] != '\0' && i < 49; i++)
		name[i] = n[i];
	name[i] = '\0';
	int j = 0;
	for (; p[j] != '\0' && j < 49; j++)
		password[j] = p[j];
	password[j] = '\0';
}
int Person::getId()
{
	return id;
}
char* Person::getName()
{
	return name;
}
char* Person::getPwd()
{
	return password;
}
void Person::setName(const char* n)
{
	int i = 0;
	for (; n[i] != '\0' && i < 49; i++)
		name[i] = n[i];
	name[i] = '\0';

}
void Person::setPwd(const char* p)
{
	int i = 0;
	for (; p[i] != '\0' && i < 49; i++)
		password[i] = p[i];
	password[i] = '\0';
}
void Person::setId(int i)
{
	id = i;
}
