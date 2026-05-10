#include "storage.h"
#include "patient.h"
#include "doctor.h"
#include "appt.h"
#include "bill.h"
#include "prescription.h"
#include "admin.h"
#include "filehandler.h"
#include "patientmenu.h"
#include "doctormenu.h"
#include "adminmenu.h"
#include "hospitalexception.h"
#include "validator.h"
#include"authsystem.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    Storage<Patient> patients;
    Storage<Doctor> doctors;
    Storage<Appointment> appointments;
    Storage<Bill> bills;
    Storage<Prescription> prescriptions;
    Storage<Admin> admins;
    try
    {
        FileHandler::loadPatients(patients);
        FileHandler::loadDoctors(doctors);
        FileHandler::loadAppointments(appointments);
        FileHandler::loadBills(bills);
        FileHandler::loadPrescriptions(prescriptions);
    }
    catch (const FileNotFoundException& e)
    {
        cout << e.what() << endl;
    }

    int choice = 0;
    do
    {
        cout << "Welcome to MediCore Hospital Management System" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "Login as :" << endl;
        cout << "1. Patient" << endl << "2. Doctor" << endl << "3. Admin" << endl << "4. Exit" << endl;
        cout << "Enter choice : ";
        cin >> choice;

        if (choice == 1)
        {
            Patient* loggedPat = nullptr;

            if (AuthSystem::loginPatient(patients, loggedPat))
            {
                PatientMenu menu(*loggedPat, doctors, appointments, bills, prescriptions);
                menu.run();
            }
        }
        else if (choice == 2)  
        {
            Doctor* loggedDoc = nullptr;

            if (AuthSystem::loginDoctor(doctors, loggedDoc))
            {
                DoctorMenu menu(*loggedDoc, patients, appointments, bills, prescriptions);
                menu.run();
            }
        }
        else if (choice == 3) 
        {
            ifstream adminFile("admin.txt");
            char line[200];
            adminFile.getline(line, 200);
            adminFile.close();
            int pos = 0;
            char idStr[10], name[50], password[50];
            int i = 0;
            while (line[pos] != ',')
                idStr[i++] = line[pos++];
            idStr[i] = '\0';
            pos++;
            i = 0;
            while (line[pos] != ',')
                name[i++] = line[pos++];
            name[i] = '\0';
            pos++;
            i = 0;
            while (line[pos] != '\0' && line[pos] != '\n')
                password[i++] = line[pos++];
            password[i] = '\0';
            Admin adminObj(FileHandler::toInt(idStr), name, password);
            if (AuthSystem::loginAdmin(adminObj))
            {
                AdminMenu menu(adminObj, patients, doctors,
                    appointments, bills, prescriptions);
                menu.run();
            }
        }
    } while (choice != 4);

    cout << "Logging out..." << endl;
    return 0;
}