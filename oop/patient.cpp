#include"patient.h"
using namespace std;

Patient::Patient() : Person(0, (char*)"", (char*)"")
{
    age = 0;
    gender = 'x';
    contact[0] = '\0';
    balance = 0.0;
}
Patient::Patient(int ID, char* n, char* p, int a, char g, char* c, double b) : Person(ID, n, p)
{
    age = a;
    gender = g;
    int i = 0;
    for (; c[i] != '\0' && i < 11; i++) 
        contact[i] = c[i];
    contact[i] = '\0';
    balance = b;
}
void Patient :: display() const 
{
	cout << "Patient Details : " << endl;
	cout << "Name : " << name << endl;
	cout << "ID : " << id << endl;
	cout << "Age : " << age << endl;
	cout << "Gender : " << gender << endl;
	cout << "Contact : " << contact << endl;
	cout << "Balance : PKR. " << balance << endl;
}
bool Patient::login(int ID, const char* passw) 
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
double Patient :: operator-=(double amount)
{
    if ( (balance -= amount) > 0)
        return balance -= amount;
    else
        return 0;
}
double Patient :: operator+=(double amount)
{
    return balance += amount;
}
bool Patient :: operator==(const Patient& obj) const
{
    return (obj.id == id);
}
ostream& operator<<(ostream& out, const Patient& p)
{
    p.display();
    return out;
}
double Patient::getBalance() const 
{
    return balance;
}
int Patient::getAge() const 
{
    return age; 
}
char Patient::getGender() const
{
    return gender;
}
const char* Patient::getContact() const 
{
    return contact;
}
void Patient::setBalance(double b) 
{
    balance = b;
}