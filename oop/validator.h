#pragma once

class Validator
{
public:
	static bool validID(const int i);
	static bool validDate(const char* d);
	static bool validTime(const char* t);
	static bool validContact(const char* c);
	static bool validAge(const int a);
	static bool validGender(const char g);
	static bool validPassw(const char* p);
	static bool validPFloat(float x);
};