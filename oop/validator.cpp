#include"validator.h"
#include<iostream>
using namespace std;

bool Validator::validID(const int i)
{
	return i > 0;
}
bool Validator::validDate(const char* d)
{
	int i = 0;
	while (d[i] != '\0')
		i++;
	if (i != 10)
		return 0;
	if (d[2] != '-' || d[5] != '-')
		return 0;
	for (int j = 0; j < 10; j++)
	{
		if (j == 2 || j == 5)
			continue;
		if (d[j] < '0' && d[j]>'9')
			return 0;
	}
	return 1;
}
 bool Validator::validTime(const char* t)
{
	 int i = 0;
	 while (t[i] != '\0')
		 i++;
	 if (i != 5)
		 return 0;
	 if (t[2] != ':')
		 return 0;
	 for (int j = 0; j < 5; j++)
	 {
		 if (j == 2)
			 continue;
		 if (t[j] < '0' || t[j]>'9')
			 return 0;
	 }
	 return 1;

}
bool Validator::validContact(const char* c)
{
	int i = 0;
	while (c[i] != '\0')
		i++;
	if (i != 11)
		return 0;
	for (int i = 0; i < 12; i++)
	{
		if (c[i] < '0' || c[i]>'9')
			return 0;
	}
	return 1;
}
bool Validator::validAge(const int a)
{
	return a > 0;
}
bool Validator::validGender(const char g)
{
	return (g == 'f' || g == 'F' || g == 'm' || g == 'M');
}
 bool Validator::validPassw(const char* p)
{
	 if (p == nullptr)
		 return 0;
	 int len = 0;
	 while (p[len] != '\0')
		 len++;
	 return len >= 6;
}
 bool Validator :: validPFloat(float x)
 {
	 return x >= 0;
}