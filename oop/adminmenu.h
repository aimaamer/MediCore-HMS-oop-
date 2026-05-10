#pragma once
#include "admin.h"
#include "patient.h"
#include "doctor.h"
#include "appt.h"
#include "bill.h"
#include "prescription.h"
#include "storage.h"
#include <ctime>

class AdminMenu
{
private:
    Admin& admin;
    Storage<Patient>& patients;
    Storage<Doctor>& doctors;
    Storage<Appointment>& appointments;
    Storage<Bill>& bills;
    Storage<Prescription>& prescriptions;
    bool strEq(const char* a, const char* b) const;
    void getTodayDate(char* buf) const;
    int  compareDates(const char* d1, const char* d2) const;
    int daysBw(const char* oldDate, const char* today) const;
    int getNextDoctorID() const;
    void myCopy(char* dst, const char* src, int maxLen) const;
    void sortApptByDateDesc(Appointment* arr, int n) const;
public:
    AdminMenu(Admin& a, Storage<Patient>& pat, Storage<Doctor>& doc, Storage<Appointment>& appt, Storage<Bill>& bill, Storage<Prescription>& pres);
    void run();
    void addDoctor();
    void removeDoctor();
    void addPatient();
    void removePatient();
    void viewAllPatients();
    void viewAllDoctors();
    void viewAllAppointments();
    void viewUnpaidBills();
    void dischargePatient();
    void viewSecurityLog();
    void generateDailyReport();


};