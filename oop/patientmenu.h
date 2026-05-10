#pragma once
#include "patient.h"
#include "doctor.h"
#include "appt.h"
#include "bill.h"
#include "prescription.h"
#include "Storage.h"
#include"filehandler.h"

class PatientMenu
{
private:
    Patient& patient;
    Storage<Doctor>& doctors;
    Storage<Appointment>& appointments;
    Storage<Bill>& bills;
    Storage<Prescription>& prescriptions;
    void showAvailableSlots(int drID, const char* date) const;
    bool isSlotTaken(int drID, const char* date, const char* slot) const;
    bool strEq(const char* a, const char* b) const;
    int getNextApptID() const;
    int getNextBillID() const;

    int compareDates(const char* d1, const char* d2) const;
    char toLowerChar(char c) const;
    bool strEqCI(const char* a, const char* b) const;
public:
    PatientMenu(Patient& p,Storage<Doctor>& doc,Storage<Appointment>& appt,Storage<Bill>& bill,Storage<Prescription>& pres);
    void run();
    void bookAppointment();
    void cancelAppointment();
    void viewAppointments();
    void viewMedicalRecords();
    void viewBills();
    void payBill();
    void topUpBalance();
};