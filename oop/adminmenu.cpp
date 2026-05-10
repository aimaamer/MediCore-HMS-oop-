#include "adminmenu.h"
#include "validator.h"
#include "hospitalexception.h"
#include"filehandler.h"
#include <iostream>
#include <fstream> 
#include <ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;

AdminMenu::AdminMenu(Admin& a,Storage<Patient>& pat,Storage<Doctor>& doc, Storage<Appointment>& appt,Storage<Bill>& bill,Storage<Prescription>& pres) : admin(a), patients(pat), doctors(doc),appointments(appt), bills(bill), prescriptions(pres)
{}
bool AdminMenu::strEq(const char* a, const char* b) const
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
void AdminMenu::getTodayDate(char* buf) const
{
    time_t t = time(nullptr);
    tm* localt = localtime(&t);
    strftime(buf, 11, "%d-%m-%Y", localt);
}
void AdminMenu::myCopy(char* dst, const char* src, int maxLen) const
{
    int i = 0;
    for (; src[i] != '\0' && i < maxLen - 1; i++)
        dst[i] = src[i];
    dst[i] = '\0';
}
int AdminMenu::compareDates(const char* d1, const char* d2) const
{
    for (int i = 6; i <= 9; i++)
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
void AdminMenu::sortApptByDateDesc(Appointment* arr, int n) const
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (compareDates(arr[j].getDate(), arr[j + 1].getDate()) < 0)
            {
                Appointment tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
int AdminMenu::getNextDoctorID() const
{
    int maxID = 0;
    for (int i = 0; i < doctors.size(); i++)
    {
        if (doctors.get(i).getId() > maxID)
            maxID = doctors.get(i).getId();
    }
    return maxID + 1;
}
int AdminMenu::daysBw(const char* oldDate, const char* today) const
{
    int d1, m1, y1;
    int d2, m2, y2;
    // Use secure version to avoid MSVC deprecation warning C4996
    sscanf_s(oldDate, "%2d-%2d-%4d", &d1, &m1, &y1);
    sscanf_s(today, "%2d-%2d-%4d", &d2, &m2, &y2);
    tm date1 = {};
    date1.tm_mday = d1;
    date1.tm_mon = m1 - 1;
    date1.tm_year = y1 - 1900;
    tm date2 = {};
    date2.tm_mday = d2;
    date2.tm_mon = m2 - 1;
    date2.tm_year = y2 - 1900;
    time_t t1 = mktime(&date1);
    time_t t2 = mktime(&date2);
    double seconds = difftime(t2, t1);

    return seconds / (60 * 60 * 24);

}
void AdminMenu::run()
{
    int choice = 0;
    do
    {
        cout << "Admin Panel - MediCore" << endl;
        cout << "1.  Add Doctor" << endl;
        cout << "2.  Remove Doctor" << endl;
        cout << "3.  Add Patient" << endl;
        cout << "4.  Remove Patient" << endl;
        cout << "5.  View All Patients" << endl;
        cout << "6.  View All Doctors" << endl;
        cout << "7.  View All Appointments" << endl;
        cout << "8.  View Unpaid Bills" << endl;
        cout << "9.  Discharge Patient" << endl;
        cout << "10.  View Security Log" << endl;
        cout << "11.  Generate Daily Report" << endl;
        cout << "12. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            addDoctor();
        }
        else if (choice == 2)
        {
            removeDoctor();
        }
        else if (choice == 3)
        {
            addPatient();
        }
        else if (choice == 4)
        {
            removePatient();
        }
        else if (choice == 5)
        {
            viewAllPatients();
        }
        else if (choice == 6)
        {
            viewAllDoctors();
        }
        else if (choice == 7)
        {
            viewAllAppointments();
        }
        else if (choice == 8)
        {
            viewUnpaidBills();
        }
        else if (choice == 9)
        {
            dischargePatient();
        }
        else if (choice == 10)
        {
            viewSecurityLog();
        }
        else if (choice == 11)
        {
            generateDailyReport();
        }
        else if (choice == 12)
        {
            cout << "Logging out..." << endl;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 12);
}

void AdminMenu::addDoctor()
{
    char name[50], spec[50], contact[12], password[50];
    double fee;
    cout << "Enter doctor name (max 50 chars) : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter specialization (max 50 chars) : ";
    cin.getline(spec, 50);
    int attempts = 0;
    bool valid = 0;
    while (attempts < 3 && !valid)
    {
        cout << "Enter contact (11 digits) : ";
        cin >> contact;
        if (!Validator::validContact(contact))
        {
            cout << "Invalid contact. Must be exactly 11 numeric digits." << endl;
            attempts++;
        }
        else 
            valid = 1;
    }
    if (!valid)
    {
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }

    attempts = 0; 
    valid = 0;
    while (attempts < 3 && !valid)
    {
        cout << "Enter password (min 6 chars): ";
        cin >> password;
        if (!Validator::validPassw(password))
        {
            cout << "Invalid password. Must be at least 6 characters." << endl;
            attempts++;
        }
        else 
            valid = 1;
    }
    if (!valid)
    {
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }
    attempts = 0; 
    valid = 0;
    while (attempts < 3 && !valid)
    {
        cout << "Enter consultation fee (PKR) : ";
        cin >> fee;
        if (!Validator::validPFloat((float)fee))
        {
            cout << "Invalid fee. Must be a positive number." << endl;
            attempts++;
        }
        else
            valid = 1;
    }
    if (!valid) 
    {
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }
    int newID = getNextDoctorID();
    Doctor newDoc(newID, name, password, spec, contact, fee);
    doctors.add(newDoc);
    FileHandler::writeDoctor(newDoc);
    cout << "Doctor added successfully. ID : " << newID << endl;
}
void AdminMenu::removeDoctor()
{
    viewAllDoctors();
    int drID;
    cout << "Enter Doctor ID to remove : ";
    cin >> drID;
    Doctor* dr = doctors.findByID(drID);
    if (dr == nullptr)
    {
        cout << "Doctor not found." << endl;
        return;
    }
    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (a.getDrID() == drID && strEq(a.getStatus(), "pending"))
        {
            cout << "Cannot remove doctor with pending appointments. Cancel or reassign them first." << endl;
            return;
        }
    }

    doctors.removeByID(drID);
    FileHandler::deleteDoctor(drID);
    cout << "Doctor removed." << endl;
}
void AdminMenu::addPatient()
{
    char name[50], contact[11], passw[6];
    char gender;
    int age;
    float balance;
    cout << "Enter patient name (max 50 chars) : ";
    cin.ignore();
    cin.getline(name, 50);
   
    int attempts = 0;
    bool valid = 0;
    while (attempts < 3 && !valid)
    {
        cout << "Enter age : ";
        cin >> age;
        if (!Validator::validPFloat((float)age))
        {
            cout << "Invalid age. Must be a positive number." << endl;
            attempts++;
        }
        else
            valid = 1;
    }
    if (!valid)
    {
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }
    cout << "Enter gender (M/F) : ";
    cin >> gender;

    attempts = 0; valid = 0;
    while (attempts < 3 && !valid)
    {
        cout << "Enter contact (11 digits) : ";
        cin >> contact;
        if (!Validator::validContact(contact))
        {
            cout << "Invalid contact. Must be exactly 11 numeric digits." << endl;
            attempts++;
        }
        else
            valid = 1;
    }
    if (!valid)
    {
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }
    attempts = 0;
    valid = 0;
    while (attempts < 3 && !valid)
    {
        cout << "Enter password (min 6 chars): ";
        cin >> passw;
        if (!Validator::validPassw(passw))
        {
            cout << "Invalid password. Must be at least 6 characters." << endl;
            attempts++;
        }
        else
            valid = 1;
    }
    if (!valid)
    {
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }
    attempts = 0;
    valid = 0;
    while (attempts < 3 && !valid)
    {
        cout << "Enter initial balance : ";
        cin >> balance;
        if (!Validator::validPFloat(balance))
        {
            cout << "Invalid balance. Must be a positive number." << endl;
            attempts++;
        }
        else
            valid = 1;
    }
    if (!valid)
    {
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }
    int newID = 1;
    for (int i = 0; i < patients.size(); i++)
    {
        if (patients.get(i).getId() >= newID)
            newID = patients.get(i).getId() + 1;
    }
    Patient newPat(newID, name, passw, age, gender, contact, balance);
    patients.add(newPat);
    FileHandler::writePatient(newPat);
    cout << "New patient added successfully. ID : " << newID << endl;

}
void AdminMenu::removePatient()
{
    viewAllPatients();

    int pid;
    cout << "Enter patient ID to remove : ";
    cin >> pid;
    Patient* pt = patients.findByID(pid);
    if (pt == nullptr)
    {
        cout << "Patient not found." << endl;
        return;
    }
    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (a.getPatientID() == pid && strEq(a.getStatus(), "pending"))
        {
            cout << "Cannot remove patient with pending appointments" << endl;
            return;
        }
    }
    for (int i = 0; i < bills.size(); i++)
    {
        if (bills.get(i).getPID() == pid && strEq(bills.get(i).getStatus(), "unpaid"))
        {
            cout << "Cannot remove patient with unpaid bills." << endl;
            return;
        }
    }  
    patients.removeByID(pid);
    FileHandler::deletePatient(pid);
    cout << "Patient removed." << endl;
}
void AdminMenu::viewAllPatients()
{
    if (patients.size() == 0)
    {
        cout << "No patients registered." << endl;
        return;
    }

    cout << endl << "--- All Patients ---" << endl;
    cout << setw(5) << "ID" << setw(22) << "Name" << setw(6) << "Age" << setw(8) << "Gender" << setw(15) << "Contact" << setw(15) << "Balance" << setw(15) << "Unpaid Bills" << endl;
    for (int i = 0; i < patients.size(); i++)
    {
        Patient& p = patients.get(i);
        int unpaidCount = 0;
        for (int j = 0; j < bills.size(); j++)
        {
            if (bills.get(j).getPID() == p.getId() && strEq(bills.get(j).getStatus(), "unpaid"))
            {
                unpaidCount++;
            }
        }
        cout << setw(5) << p.getId() << setw(22) << p.getName() << setw(6) << p.getAge() << setw(8) << p.getGender() << setw(15) << p.getContact() << setw(15) << p.getBalance() << setw(15) << unpaidCount << endl;

    }

}
void AdminMenu::viewAllDoctors()
{
    if (doctors.size() == 0)
    {
        cout << "No doctors registered." << endl;
        return;
    }

    cout << endl << "--- All Doctors ---" <<endl;
    cout << setw(5) << "ID" << setw(25) << "Name" << setw(25) << "Specialization" << setw(15) << "Contact" << setw(12) << "Fee" << endl;
    for (int i = 0; i < doctors.size(); i++)
    {
        Doctor& d = doctors.get(i);
        cout << setw(5) << d.getId() << setw(25) << d.getName() << setw(25) << d.getSpec() << setw(15) << d.getContact() << setw(12) << d.getFee() << endl;
    }
}
void AdminMenu::viewAllAppointments()
{
    if (appointments.size() == 0)
    {
        cout << "No appointments found." << endl;
        return;
    }
    Appointment all[100];
    int count = 0;
    for (int i = 0; i < appointments.size(); i++)
        all[count++] = appointments.get(i);           //takay we can sort
    sortApptByDateDesc(all, count); 
    cout << endl << "--- All Appointments ---" << endl;
    cout << setw(5) << "ID" << setw(22) << "Patient" << setw(22) << "Doctor" << setw(14) << "Date" << setw(10) << "Slot" << setw(15) << "Status" << endl;
    for (int i = 0; i < count; i++)
    {
        Patient* p = patients.findByID(all[i].getPatientID());
        Doctor* d = doctors.findByID(all[i].getDrID());
        const char* patName = p ? p->getName() : "Unknown";
        const char* drName = d ? d->getName() : "Unknown";

        cout << setw(5) << all[i].getID() << setw(22) << patName << setw(22) << drName << setw(14) << all[i].getDate() << setw(10) << all[i].getTimeSlot() << setw(15) << all[i].getStatus() << endl;

    }

}
void AdminMenu::viewUnpaidBills()
{
    char today[11];
    getTodayDate(today);
    bool flag = 0;
    cout << endl << "--- Unpaid Bills ---" << endl;
    cout << setw(10) << "Bill ID" << setw(25) << "Patient" << setw(18) << "Amount(PKR)" << setw(15) << "Date" << endl;

    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.get(i);
        if (!strEq(b.getStatus(), "unpaid")) 
            continue;
        flag = true;

        int days = daysBw(b.getDate(), today);
        bool overdue = (days > 7);
        Patient* p = patients.findByID(b.getPID());
        const char* patName = p ? p->getName() : "Unknown";
        cout << setw(10) << b.getBillID() << setw(25) << patName << setw(18) << b.getAmount() << setw(15) << b.getDate();
        if (overdue)
            cout << "  [OVERDUE]";
        cout << endl;
    }

    if (!flag)
        cout << "No unpaid bills found." << endl;
}
void AdminMenu::dischargePatient()
{
    int patID;
    cout << "Enter Patient ID : ";
    cin >> patID;
    Patient* pat = patients.findByID(patID);
    if (pat == nullptr)
    {
        cout << "Patient not found." <<endl;
        return;
    }
    for (int i = 0; i < bills.size(); i++)
    {
        if (bills.get(i).getPID() == patID && strEq(bills.get(i).getStatus(), "unpaid"))
        {
            cout << "Cannot discharge patient with unpaid bills." << endl;
            return;
        }
    }
    for (int i = 0; i < appointments.size(); i++)
    {
        if (appointments.get(i).getPatientID() == patID && strEq(appointments.get(i).getStatus(), "pending"))
        {
            cout << "Cannot discharge patient with pending appointments." << endl;
            return;
        }
    }
    FileHandler::archivePatient(patID, patients, appointments, bills, prescriptions);
    FileHandler::deletePatient(patID);

    patients.removeByID(patID);
    for (int i = 0; i < appointments.size(); i++)
    {
        if (appointments.get(i).getPatientID() == patID)
            appointments.removeByID(appointments.get(i).getID());
    }
    for (int i = 0; i < bills.size(); i++)
    {
        if (bills.get(i).getPID() == patID)
            bills.removeByID(bills.get(i).getBillID());
    }
    for (int i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptions.get(i).getPatientID() == patID)
            prescriptions.removeByID(prescriptions.get(i).getPresID());
    }
    cout << "Patient discharged and archived successfully." << endl;
}
void AdminMenu::viewSecurityLog()
{
    ifstream file("security_log.txt");
    if (!file.is_open())
    {
        cout << "No security events logged." << endl;
        return;
    }
    char line[300];
    bool flag = 0;

    cout << endl << "--- Security Log ---" << endl;
    while (file.getline(line, 300))
    {
        cout << line << endl;
        flag = 1;
    }
    file.close();
    if (!flag)
        cout << "No security events logged." << endl;
}
void AdminMenu::generateDailyReport()
{
    char today[11];
    getTodayDate(today);
    cout << endl << "---- Daily Report: " << today << " ----" << endl;
    int totalToday = 0, pendingN = 0, completedN = 0,noshowN = 0, cancelledN = 0;
    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (!strEq(a.getDate(), today)) 
            continue;
        totalToday++;
        if (strEq(a.getStatus(), "pending"))  
            pendingN++;
        else if (strEq(a.getStatus(), "completed")) 
            completedN++;
        else if (strEq(a.getStatus(), "noshow"))   
            noshowN++;
        else if (strEq(a.getStatus(), "cancelled")) 
            cancelledN++;
    }

    cout << "Total appointments today: " << totalToday << " ( Pending: " << pendingN << " | Completed: " << completedN << " | No-show: " << noshowN << " | Cancelled: " << cancelledN << ")" << endl;
    
    double revenue = 0;
    for (int i = 0; i < bills.size(); i++)
    {
        const Bill& b = bills.get(i);
        if (strEq(b.getDate(), today) && strEq(b.getStatus(), "paid"))
            revenue += b.getAmount();
    }
    cout << "Revenue collected today (paid bills) : PKR " << revenue << endl;
    cout << "Patients with outstanding unpaid bills :" << endl;
    cout << "Patient Name               Total Owed" <<endl;
    cout << "------------------------  ----------" <<endl;

    bool unpaid = 0;
    for (int i = 0; i < patients.size(); i++)
    {
        Patient& p = patients.get(i);
        double owed = 0;
        for (int j = 0; j < bills.size(); j++)
        {
            if (bills.get(j).getPID() == p.getId() && strEq(bills.get(j).getStatus(), "unpaid"))
                owed += bills.get(j).getAmount();
        }
        if (owed > 0.0)
        {
            cout << p.getName() << "             PKR " << owed <<endl;
            unpaid = 1;
        }
    }
    if (!unpaid)
        cout << "None" << endl;

    cout << endl << "Doctor-wise summary for today :" << endl;
    cout << "Doctor Name               Completed  Pending  No-show" << endl;
    cout << "------------------------  ---------  -------  -------" << endl;

    for (int i = 0; i < doctors.size(); i++)
    {
        Doctor& d = doctors.get(i);
        int comp = 0, pend = 0, nos = 0;
        for (int j = 0; j < appointments.size(); j++)
        {
            const Appointment& a = appointments.get(j);
            if (a.getDrID() != d.getId()) 
                continue;
            if (!strEq(a.getDate(), today)) 
                continue;
            if (strEq(a.getStatus(), "completed"))
                comp++;
            else if (strEq(a.getStatus(), "pending"))  
                pend++;
            else if (strEq(a.getStatus(), "noshow"))   
                nos++;
        }
        if (comp + pend + nos > 0)  //jin drs ki aj appts thi
        {
            cout << d.getName() << "     " << comp << "          " << pend << "        " << nos << endl;
        }
    }

}