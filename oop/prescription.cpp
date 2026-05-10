#include"prescription.h"
using namespace std;

static void presCopy(char* dst, const char* src, int maxLen)
{
    int i = 0;
    for (; src[i] != '\0' && i < maxLen - 1; i++) dst[i] = src[i];
    dst[i] = '\0';
}

Prescription::Prescription()
{
    presID = 0; apptID = 0; patientID = 0; drID = 0;
    date[0] = '\0'; medicine[0] = '\0'; notes[0] = '\0';
}

Prescription::Prescription(int pID, int aID, int patID, int dID, const char* d, const char* med, const char* n)
{
    presID = pID; apptID = aID; patientID = patID; drID = dID;
    presCopy(date, d, 11);
    presCopy(medicine, med, 500);
    presCopy(notes, n, 300);
}
int Prescription::getID() const
{
	return presID;
}
ostream& operator<<(ostream& out, const Prescription& p)
{
	out << "Prescription Details : " << endl;
	out << "Prescription ID : " << p.presID << endl;
	out << "Appointment ID : " << p.apptID << endl;
	out << "Patient ID : " << p.patientID << endl;
	out << "Doctor ID : " << p.drID << endl;
	out << "Date : " << p.date << endl;
	out << "Medicines : " << p.medicine << endl;
	out << "Notes : " << p.notes << endl;
	return out;

}
int Prescription::getPresID()const 
{ return presID; }
int Prescription::getApptID()const
{ return apptID; }
int Prescription::getPatientID()const
{ return patientID; }
int Prescription::getDrID() const 
{ return drID; }
const char* Prescription::getDate() const 
{ return date; }
const char* Prescription::getMedicine() const
{ return medicine; }
const char* Prescription::getNotes() const
{ return notes; }