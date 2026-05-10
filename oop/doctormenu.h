#pragma once
#include "doctor.h"
#include "patient.h"
#include "appt.h"
#include "bill.h"
#include "prescription.h"
#include "storage.h"
#include"filehandler.h"

class DoctorMenu
{
private:
    Doctor& doctor;
    Storage<Patient>& patients;
    Storage<Appointment>& appointments;
    Storage<Bill>& bills;
    Storage<Prescription>& prescriptions;
    void getTodayDate(char* buf) const;   
    bool strEq(const char* a, const char* b) const;
    int  compareDates(const char* d1, const char* d2) const;
    int  getNextPresID() const;
    void sortPressByDateDesc(Prescription* arr, int n) const;

public:
    DoctorMenu(Doctor& d, Storage<Patient>& pat, Storage<Appointment>& appt, Storage<Bill>& bill, Storage<Prescription>& pres);
    void run();
    void viewTodaysAppointments();
    void markComplete();
    void markNoShow();
    void writePrescription();
    void viewPatientHistory();


};
