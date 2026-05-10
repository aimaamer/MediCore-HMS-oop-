#pragma once
#include "patient.h"
#include "doctor.h"
#include "appt.h"
#include "bill.h"
#include "prescription.h"
#include "storage.h"

class FileHandler
{
    static void getField(const char* line, int& idx, char* field, int maxLen);
    static double toDouble(const char* s);
public:
    static void loadPatients(Storage<Patient>& store);
    static void loadDoctors(Storage<Doctor>& store);
    static void loadAppointments(Storage<Appointment>& store);
    static void loadBills(Storage<Bill>& store);
    static void loadPrescriptions(Storage<Prescription>& store);
    static void writePatient( Patient& p);
    static void writeDoctor( Doctor& d);
    static void writeAppointment( Appointment& a);
    static void writeBill( Bill& b);
    static void writePrescription( Prescription& p);
    static void updatePatientBalance(int patientID, double newBalance);
    static void updateAppointmentStatus(int apptID, const char* newStatus);  
    static void updateBillStatus(int billID, const char* newStatus);    
    static void deleteDoctor(int doctorID);
    static void deletePatient(int patientID);
    static void archivePatient(int patientID, Storage<Patient>& patients, Storage<Appointment>& appointments, Storage<Bill>& bills, Storage<Prescription>& prescriptions);
    static void logFailedLogin(const char* role, int enteredID);
    static int  toInt(const char* s);

};