#pragma once
#include<iostream>

class Appointment
{
private:
	int apptID;
	int patientID;
	int drID;
	char date[11];
	char timeSlot[6];
	char status[20];
public:
	Appointment(); 
	Appointment(int aID, int pID, int dID, const char* d, const char* ts, const char* st);
	bool operator==(const Appointment& a) const;
	friend std::ostream& operator<<(std::ostream& out, const Appointment& a);
	int getID() const;
	int getPatientID() const;
	int getDrID() const;
	const char* getDate() const;
	const char* getTimeSlot() const;
	const char* getStatus() const;
	void setStatus(const char* s);
};