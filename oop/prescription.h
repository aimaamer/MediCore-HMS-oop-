#pragma once
#include<iostream>

class Prescription
{
private:
	int presID;
	int apptID;
	int patientID;
	int drID;
	char date[11];
	char medicine[200];
	char notes[500];
public:
	Prescription();
	Prescription(int pID, int aID, int patID, int dID, const char* d, const char* med, const char* n);
	friend std::ostream& operator<<(std::ostream& out, const Prescription& p);
	int getID() const;
	int getPresID() const;
	int getApptID() const;
	int getPatientID() const;
	int getDrID() const;
	const char* getDate() const;
	const char* getMedicine() const;
	const char* getNotes() const;
};