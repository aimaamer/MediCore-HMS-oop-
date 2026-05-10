#include "bill.h"
using namespace std;

static void billCopy(char* dst, const char* src, int maxLen)
{
	int i = 0;
	for (; src[i] != '\0' && i < maxLen - 1; i++)
		dst[i] = src[i];
	dst[i] = '\0';
}
int Bill::getID() const
{
	return billID;
}
ostream& operator<<(ostream& out, const Bill& b)
{
	out << "Bill Details : " << endl;
	out << "Bill ID : " << b.billID << endl;
	out << "Patient ID : " << b.pID << endl;
	out << "Appointment ID : " << b.apptID << endl;
	out << "Amount : " << b.amount << endl;
	out << "Status : " << b.status << endl;
	out << "Date : " << b.date << endl;
	return out;

}
Bill::Bill()
{
	billID = 0; apptID = 0; pID = 0; amount = 0.0;
	status[0] = '\0'; date[0] = '\0';
}

Bill::Bill(int bID, int aID, int pid, double amt, const char* st, const char* d)
{
	billID = bID; apptID = aID; pID = pid; amount = amt;
	billCopy(status, st, 10);
	billCopy(date, d, 11);
}
int Bill::getBillID() const
{ return billID; }
int Bill::getApptID()  const
{ return apptID; }
int Bill::getPID() const 
{ return pID; }
double Bill::getAmount() const
{ return amount; }
const char* Bill::getStatus() const 
{ return status; }
const char* Bill::getDate() const
{ return date; }
void Bill::setStatus(const char* s) 
{ billCopy(status, s, 10); }
