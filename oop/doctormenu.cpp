#include "doctormenu.h"
#include "hospitalexception.h"
#include"filehandler.h"
#include <iostream>
#include <ctime>
using namespace std;

DoctorMenu::DoctorMenu(Doctor& d, Storage<Patient>& pat,Storage<Appointment>& appt,Storage<Bill>& bill, Storage<Prescription>& pres) : doctor(d), patients(pat), appointments(appt), bills(bill), prescriptions(pres)
{}
void DoctorMenu::getTodayDate(char* buf) const
{
     time_t t = time(0);
     tm* localt = localtime(&t);
     strftime(buf, 11, "%d-%m-%Y", localt);
}
bool DoctorMenu::strEq(const char* a, const char* b) const
{
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0')
    {
        if (a[i] != b[i])
            return 0;
        i++;
    }
    return 1;
}
int DoctorMenu::compareDates(const char* d1, const char* d2) const
{
    for (int i = 6; i <= 9; i++)     //DD-MM-YYYY main compare
    {
        if (d1[i] < d2[i]) 
            return -1;
        if (d1[i] > d2[i])
            return  1;
    }
    for (int i = 3; i <= 4; i++)
    {
        if (d1[i] < d2[i]) 
            return -1;
        if (d1[i] > d2[i])
            return  1;
    }
    for (int i = 0; i <= 1; i++)
    {
        if (d1[i] < d2[i])
            return -1;
        if (d1[i] > d2[i]) 
            return  1;
    }
    return 0;
}
void DoctorMenu::sortPressByDateDesc(Prescription* arr, int n) const
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (compareDates(arr[j].getDate(), arr[j + 1].getDate()) < 0)
            {
                Prescription tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
int DoctorMenu::getNextPresID() const
{
    int maxID = 0;
    for (int i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptions.get(i).getPresID() > maxID)
            maxID = prescriptions.get(i).getPresID();
    }
    return maxID + 1;
}
void DoctorMenu::run()
{
    int choice = 0;
    do
    {
        cout << endl << "Welcome, Dr. " << doctor.getName() << " | Specialization: " << doctor.getSpec() << endl;
        cout << endl;
        cout << "1. View Today's Appointments" << endl;
        cout << "2. Mark Appointment Complete" << endl;
        cout << "3. Mark Appointment No-Show" << endl;
        cout << "4. Write Prescription" << endl;
        cout << "5. View Patient Medical History" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            viewTodaysAppointments();
        }
        else if (choice == 2)
        {
            markComplete();
        }
        else if (choice == 3)
        {
            markNoShow();
        }
        else if (choice == 4)
        {
            writePrescription();
        }
        else if (choice == 5)
        {
            viewPatientHistory();
        }
        else if (choice == 6)
        {
            cout << "Logging out..." << endl;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }
        
    } while (choice != 6);
}
void DoctorMenu::viewTodaysAppointments()
{
    char today[11];
    getTodayDate(today);
    Appointment todays[100];
    int count = 0;
    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (a.getDrID() == doctor.getId() && strEq(a.getDate(), today))
        {
            todays[count++] = a;
        }
    }

    if (count == 0)
    {
        cout << "No appointments scheduled for today." << endl;
        return;
    }
    cout << endl << "Today's Appointments (" << today << ")" <<endl;
    cout << "Appt ID    Patient Name              Slot    Status"<<endl;
    cout << "--------  ------------------------  ------  ----------" << endl;
    for (int i = 0; i < count; i++)
    {
        Patient* p = patients.findByID(todays[i].getPatientID());
        const char* patName = p ? p->getName() : "Unknown";

        cout << todays[i].getID() << "         " << patName << "         " << todays[i].getTimeSlot() << "    " << todays[i].getStatus() << endl;
    }
}
void DoctorMenu::markComplete()
{
    char today[11];
    getTodayDate(today);
    Appointment pending[100];
    int count = 0;

    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (a.getDrID() == doctor.getId() && strEq(a.getDate(), today) && strEq(a.getStatus(), "pending"))
        {
            pending[count++] = a;
        }
    }

    if (count == 0)
    {
        cout << "No pending appointments for today." << endl;
        return;
    }
    cout << endl << " Today's Pending Appointments" << endl;
    for (int i = 0; i < count; i++)
    {
        Patient* p = patients.findByID(pending[i].getPatientID());
        const char* patName = p ? p->getName() : "Unknown";
        cout << "ID: " << pending[i].getID() << " |  Patient: " << patName << " | Slot: " << pending[i].getTimeSlot() << endl;
    }

    int apptID;
    cout << "Enter Appointment ID : ";
    cin >> apptID;
    Appointment* target = nullptr;
    for (int i = 0; i < count; i++)
    {
        if (pending[i].getID() == apptID)
        {
            target = &pending[i];
            break;
        }
    }

    if (target == nullptr)
    {
        cout << "Invalid appointment ID." << endl;
        return;
    }
    Appointment* stored = appointments.findByID(apptID);
    if (stored)
        stored->setStatus("completed");
    FileHandler::updateAppointmentStatus(apptID, "completed");
    cout << "Appointment marked as completed." << endl;
}
void DoctorMenu::markNoShow()
{
    char today[11];
    getTodayDate(today);
    Appointment pending[100];
    int count = 0;

    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (a.getDrID() == doctor.getId() && strEq(a.getDate(), today) && strEq(a.getStatus(), "pending"))
        {
            pending[count++] = a;
        }
    }
    if (count == 0)
    {
        cout << "No pending appointments for today." << endl;
        return;
    }

    cout << endl << " Today's Pending Appointments" << endl;
    for (int i = 0; i < count; i++)
    {
        Patient* p = patients.findByID(pending[i].getPatientID());
        const char* patName = p ? p->getName() : "Unknown";
        cout << "ID : " << pending[i].getID() << " | Patient: " << patName << " | Slot: " << pending[i].getTimeSlot() << endl;
    }
    int apptID;
    cout << "Enter Appointment ID: ";
    cin >> apptID;
    Appointment* target = nullptr;
    for (int i = 0; i < count; i++)
    {
        if (pending[i].getID() == apptID)
        {
            target = &pending[i];
            break;
        }
    }
    if (target == nullptr)
    {
        cout << "Invalid appointment ID." << endl;
        return;
    }
    Appointment* storedAppt = appointments.findByID(apptID);
    if (storedAppt)
        storedAppt->setStatus("noshow");
    int bID = 0;
    for (int i = 0; i < bills.size(); i++) //bill cancel kardo
    {
        Bill& b = bills.get(i);
        if (b.getApptID() == apptID)
        {
            bID = b.getBillID();
            b.setStatus("canceled"); 
            break;
        }
    }
    FileHandler::updateAppointmentStatus(apptID, "noshow");
    if (bID != 0)
        FileHandler::updateBillStatus(bID, "cancelled");
    cout << "Appointment marked as no-show." << endl;
}
void DoctorMenu::writePrescription()
{
    int apptID;
    cout << "Enter Appointment ID : ";
    cin >> apptID;
    Appointment* appt = appointments.findByID(apptID);
    if (appt == nullptr || appt->getDrID() != doctor.getId() ||!strEq(appt->getStatus(), "completed"))
    {
        cout << "Invalid appointment ID." << endl;
        return;
    }
    for (int i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptions.get(i).getApptID() == apptID)
        {
            cout << "Prescription already written for this appointment." << endl;
            return;
        }
    }
    int patientID = appt->getPatientID();
    char medicines[500];
    cout << "Enter medicines (format: MedicineName Dosage; e.g. Paracetamol 500mg;Amoxicillin 250mg) : " << endl;
    cin.ignore();
    cin.getline(medicines, 500);
    char notes[300];
    cout << "Enter notes (< 300 chars) : " << endl;
    cin.getline(notes, 300);
    int newPresID = getNextPresID();
    Prescription newPres(newPresID, apptID, patientID, doctor.getId(), appt->getDate(),medicines, notes);
    prescriptions.add(newPres);
    FileHandler::writePrescription(newPres);
    cout << "Prescription saved." << endl;
}
void DoctorMenu::viewPatientHistory()
{
    int patID;
    cout << "Enter Patient ID : ";
    cin >> patID;
    Patient* pat = patients.findByID(patID);
    if (pat == nullptr)
    {
        cout << "Access denied. You can only view records of your own patients." << endl;
        return;
    }
    bool hasCompleted = 0;
    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (a.getPatientID() == patID && a.getDrID() == doctor.getId() && strEq(a.getStatus(), "completed"))
        {
            hasCompleted = 1;
            break;
        }
    }
    if (!hasCompleted)
    {
        cout << "Access denied. You can only view records of your own patients." << endl;
        return;
    }
    Prescription myPres[100];
    int count = 0;
    for (int i = 0; i < prescriptions.size(); i++)
    {
        const Prescription& pr = prescriptions.get(i);
        if (pr.getPatientID() == patID && pr.getDrID() == doctor.getId())
        {
            myPres[count++] = pr;
        }
    }
    if (count == 0)
    {
        cout << "No medical records found for this patient." << endl;
        return;
    }
    sortPressByDateDesc(myPres, count);
    cout << endl << " Medical History for " << pat->getName() << endl;
    for (int i = 0; i < count; i++)
    {
        cout << "-------------------------------------" << endl;
        cout << "Date       : " << myPres[i].getDate() << endl;
        cout << "Medicines  : " << myPres[i].getMedicine() << endl;
        cout << "Notes      : " << myPres[i].getNotes() << endl;
    }
}
