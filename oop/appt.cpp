#include "appt.h"
#include <iostream>
using namespace std;

static int myStrLen(const char* s) //helpers
{
	int i = 0; while (s[i]) i++; return i;
}
static void myCopy(char* dst, const char* src, int maxLen)
{
	int i = 0;
	for (; src[i] != '\0' && i < maxLen - 1; i++) 
		dst[i] = src[i];
	dst[i] = '\0';
}
static bool myStrEq(const char* a, const char* b)
{
	int i = 0;
	while (a[i] != '\0' || b[i] != '\0')
	{
		if (a[i] != b[i]) return false;
		i++;
	}
	return true;
}
Appointment::Appointment()
{
	apptID = 0; patientID = 0; drID = 0;
	date[0] = '\0'; timeSlot[0] = '\0'; status[0] = '\0';
}

Appointment::Appointment(int aID, int pID, int dID, const char* d, const char* ts, const char* st)
{
	apptID = aID; patientID = pID; drID = dID;
	myCopy(date, d, 11);
	myCopy(timeSlot, ts, 6);
	myCopy(status, st, 20);
}

bool Appointment::operator==(const Appointment& a) const
{
	if (drID == a.drID)
	{
		if (myStrEq(status, "cancelled") || myStrEq(a.status, "cancelled"))
			return 0;

		return myStrEq(date, a.date) && myStrEq(timeSlot, a.timeSlot);
	}
	return 0;
}
ostream& operator<<(ostream& out, const Appointment& a)
{
	out << "Appointment ID : " << a.apptID << endl;
	out << "Doctor ID : " << a.drID << endl;
	out << "Patient ID : " << a.patientID << endl;
	out << "Date of Appointment : " << a.date << endl;
	out << "Time Slot : " << a.timeSlot << endl;
	out << "Status : " << a.status << endl;
	return out;

}
int Appointment::getID() const
{
	return apptID;
}
int Appointment::getPatientID()const
{ return patientID; }
int Appointment::getDrID() const
{ return drID; }
const char* Appointment::getDate()  const
{ return date; }
const char* Appointment::getTimeSlot() const 
{ return timeSlot; }
const char* Appointment::getStatus()const 
{ return status; }
void Appointment::setStatus(const char* s)
{
	myCopy(status, s, 20);
}
