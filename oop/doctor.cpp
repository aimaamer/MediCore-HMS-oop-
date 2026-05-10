#include"doctor.h"
#include<iostream>
using namespace std;
static void drCopy(char* dst, const char* src, int maxLen)
{
    int i = 0;
    for (; src[i] != '\0' && i < maxLen - 1; i++) dst[i] = src[i];
    dst[i] = '\0';
}
Doctor::Doctor() : Person(0, (char*)"", (char*)"")
{
    spec[0] = '\0'; contact[0] = '\0'; fee = 0.0;
}
Doctor::Doctor(int ID, char* n, char* p, char* s, char* c, double f) : Person(ID, n, p)
{
    drCopy(spec, s, 70);
    drCopy(contact, c, 12);
    fee = f;
}

void Doctor :: display() const
{
	cout << "Doctor Details : " << endl;
	cout << "Name : " << name << endl;
	cout << "ID : " << id << endl;
	cout << "Contact : " << contact << endl;
	cout << "Specialization : " << spec << endl;
	cout << "Fee : " << fee << endl;
}
bool Doctor::login(int ID, const char* passw)
{
    if (id != ID)
        return 0;
    int i = 0;
    while (password[i] != '\0' || passw[i] != '\0')
    {
        if (password[i] != passw[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}
bool Doctor ::operator==(const Doctor& obj) const
{
    return (id == obj.id);
}
ostream& operator<<(ostream& out, const Doctor& d) 
{
    d.display();
    return out;
}

const char* Doctor::getSpec() const
{
    return spec;
}
const char* Doctor::getContact() const 
{ 
    return contact;
}
double Doctor::getFee()const
{
    return fee;
}