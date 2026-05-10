#include "patientmenu.h"
#include "hospitalexception.h"
#include"filehandler.h"
#include "validator.h"
#include <iostream>
using namespace std;

PatientMenu::PatientMenu(Patient& p,Storage<Doctor>& doc,Storage<Appointment>& appt,Storage<Bill>& bill,Storage<Prescription>& pres) : patient(p), doctors(doc), appointments(appt),bills(bill), prescriptions(pres)
{}
char PatientMenu::toLowerChar(char c) const
{
    if (c >= 'A' && c <= 'Z') 
        return c + ('a' - 'A');
    return c;
}
bool PatientMenu::strEqCI(const char* a, const char* b) const
{
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0')
    {
        if (toLowerChar(a[i]) != toLowerChar(b[i]))
            return 0;
        i++;
    }
    return 1;
}
int PatientMenu::compareDates(const char* d1, const char* d2) const
{
    for (int i = 6; i <= 9; i++)  // DD-MM-YYYY format
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
bool PatientMenu::strEq(const char* a, const char* b) const
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
bool PatientMenu::isSlotTaken(int drID, const char* date, const char* slot) const
{
    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (a.getDrID() == drID && strEqCI(a.getDate(), date) && strEq(a.getTimeSlot(), slot) && !strEqCI(a.getStatus(), "cancelled"))
        {
            return 1;
        }
    }

    return 0;
}
void PatientMenu::showAvailableSlots(int drID, const char* date) const
{
    const char* slots[8] = { "09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00" };
    cout << endl << "Available time slots for " << date << " : " << endl;
    bool free = 0;
    for (int i = 0; i < 8; i++)
    {
        if (!isSlotTaken(drID, date, slots[i]))
        {
            cout << "  " << slots[i] << endl;
            free = 1;
        }
    }
    if (!free)
        cout << "  No slots available on this date." << endl;
}
int PatientMenu::getNextApptID() const
{
    int maxID = 0;
    for (int i = 0; i < appointments.size(); i++)
    {
        if (appointments.get(i).getID() > maxID)
            maxID = appointments.get(i).getID();
    }
    return maxID + 1;
}
int PatientMenu::getNextBillID() const
{
    int maxID = 0;
    for (int i = 0; i < bills.size(); i++)
    {
        if (bills.get(i).getBillID() > maxID)
            maxID = bills.get(i).getBillID();
    }
    return maxID + 1;
}


void PatientMenu::run()
{
    int choice = 0;
    do
    {
        cout << "Welcome, " << patient.getName() << endl;
        cout << "Balance: PKR " << patient.getBalance() << endl << endl;
        cout << "1. Book Appointment" << endl;
        cout << "2. Cancel Appointment" << endl;
        cout << "3. View My Appointments" << endl;
        cout << "4. View My Medical Records" << endl;
        cout << "5. View My Bills" << endl;
        cout << "6. Pay Bill" << endl;
        cout << "7. Top Up Balance" << endl;
        cout << "8. Logout" << endl;
        cout << "Enter choice : ";
        cin >> choice;

        if (choice == 1)
        {
            bookAppointment();
        }
        else if (choice == 2)
        {
            cancelAppointment();
        }
        else if (choice == 3)
        {
            viewAppointments();
        }
        else if (choice == 4)
        {
            viewMedicalRecords();
        }
        else if (choice == 5)
        {
            viewBills();
        }
        else if (choice == 6)
        {
            payBill();
        }
        else if (choice == 7)
        {
            topUpBalance();
        }
        else if (choice == 8)
        {
            cout << "Logging out..." << endl;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 8);


}

void PatientMenu::bookAppointment()
{
    char spec[70];
    cout << "Enter specialization to search : " ;
    cin.ignore();
    cin.getline(spec, 70);

    Doctor matched[100];
    int matchCount = 0;
    for (int i = 0; i < doctors.size(); i++)
    {
        if (strEqCI(doctors.get(i).getSpec(), spec)) //jin bhi drs ki spec matches req. spec
            matched[matchCount++] = doctors.get(i);
    }

    if (matchCount == 0)
    {
        cout << "No doctors available for required specialization" << endl;
        return;
    }

    cout << endl << "Doctors in " << spec << endl;
    cout << "ID    Name                      Fee (PKR)" << endl;
    cout << "----  -----------------------  ----------" << endl;
    for (int i = 0; i < matchCount; i++)
    {
        cout << matched[i].getId() << "     " << matched[i].getName() << "     PKR " << matched[i].getFee() << endl;
    }

    int drID;
    cout << "Enter required Doctor ID : ";
    cin >> drID;

    Doctor* selectedDr = nullptr;
    for (int i = 0; i < matchCount; i++)
    {
        if (matched[i].getId() == drID)
        {
            selectedDr = &matched[i];
            break;
        }
    }
    if (selectedDr == nullptr)
    {
        cout << "Doctor not found against given ID." << endl;
        return;
    }

    char date[11];
    int dateAttempts = 0;
    bool validDate = 0;

    while (dateAttempts < 3 && !validDate)
    {
        cout << "Enter date (DD-MM-YYYY) : ";
        cin >> date;
        if (!Validator::validDate(date))
        {
            cout << "Invalid date format" << endl;
            dateAttempts++;
        }
        else
        {
            validDate = 1;
        }
    }
    if (!validDate)
        return;

    showAvailableSlots(drID, date);

    char slot[6];
    const char* validSlots[8] = {"09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00"};

    while (true)
    {
        cout << "Enter time slot : ";
        cin >> slot;
       if (Validator::validTime(slot))
       {
           cout << "Invalid time slot." << endl;
            showAvailableSlots(drID, date);
            continue;
       }

       try
       {
           if (isSlotTaken(drID, date, slot))
               throw SlotUnavailableException();
           break;
       }
        catch (const SlotUnavailableException& e)
        {
            cout << e.what() <<endl;
            showAvailableSlots(drID, date);
        }
    }

    try
    {
        if (patient.getBalance() < selectedDr->getFee())
            throw InsufficientFundsException();
    }
    catch (const InsufficientFundsException& e)
    {
        cout << e.what() << endl;
        return;
    }

    int newApptID = getNextApptID();
    int newBillID = getNextBillID();
    patient -= selectedDr->getFee();  

    Appointment newAppt(newApptID, patient.getId(), drID, date, slot, "pending");
    Bill newBill(newBillID, newApptID, patient.getId(), selectedDr->getFee(), "unpaid", date);
    appointments.add(newAppt);
    bills.add(newBill);
    FileHandler::writeAppointment(newAppt);
    FileHandler::writeBill(newBill);
    FileHandler::updatePatientBalance(patient.getId(), patient.getBalance());

    cout << "Appointment booked successfully. Appointment ID : " << newApptID <<endl;
}
void PatientMenu::cancelAppointment()
{
    Appointment pending[100];
    int pendCount = 0;
    for (int i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments.get(i);
        if (a.getPatientID() != patient.getId())
            continue;

        const char* st = a.getStatus();
        bool isPending = 1;
        const char* word = "pending";
        for (int j = 0; word[j] != '\0' || st[j] != '\0'; j++)
            if (st[j] != word[j]) 
            {
                isPending = 0; break; 
            }

        if (isPending)
            pending[pendCount++] = a;
    }

    if (pendCount == 0)
    {
        cout << "You have no pending appointments." << endl;
        return;
    }
   
    cout << endl << "Your Pending Appointments" << endl ;
    cout << "Appt ID   Doctor Name              Date         Slot"<<endl;
    for (int i = 0; i < pendCount; i++)
    {
        Doctor* dr = doctors.findByID(pending[i].getDrID());
        const char* drName = dr ? dr->getName() : "Unknown";
        cout << pending[i].getID() << "       " << drName << "              " << pending[i].getDate() << "       " << pending[i].getTimeSlot() << endl;
    }

    int cancelID;
    cout << "Enter Appointment ID to cancel : ";
    cin >> cancelID;

    Appointment* target = nullptr;
    for (int i = 0; i < pendCount; i++)
    {
        if (pending[i].getID() == cancelID)
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
    Doctor* dr = doctors.findByID(target->getDrID());
    double refund = dr ? dr->getFee() : 0.0;
    Appointment* stored = appointments.findByID(cancelID);
    if (stored) stored->setStatus("cancelled");
    int bID;
    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.get(i);
        if (b.getApptID() == cancelID && b.getPID() == patient.getId())
        {
            bID = b.getBillID();
            b.setStatus("canceled");  
            break;
        }
    }
    patient += refund;
    FileHandler::updateAppointmentStatus(cancelID, "cancelled");
    FileHandler::updateBillStatus(bID, "cancelled");  
    FileHandler::updatePatientBalance(patient.getId(), patient.getBalance());

    cout << "Appointment cancelled. PKR " << refund << " refunded to your balance."<<endl;
}
void PatientMenu::viewAppointments()
{
    Appointment myAppts[100];
    int count = 0;
    for (int i = 0; i < appointments.size(); i++)
    {
        if (appointments.get(i).getPatientID() == patient.getId()) //count num of appts of a patient
            myAppts[count++] = appointments.get(i);
    }

    if (count == 0)
    {
        cout << "No appointments found."<<endl;
        return;
    }
    cout << endl << "Your Appointments" << endl;
    cout << "ID   Doctor               Specialization      Date         Slot     Status" << endl;

    for (int i = 0; i < count; i++)
    {
        Doctor* dr = doctors.findByID(myAppts[i].getDrID());
        const char* drName = dr ? dr->getName() : "Unknown";
        const char* drSpec = dr ? dr->getSpec() : "Unknown";
        cout << myAppts[i].getID() << "       " << drName << "              " << drSpec << "           " << myAppts[i].getDate() << "       " << myAppts[i].getTimeSlot() << "     " << myAppts[i].getStatus() << endl;
    }
}
void PatientMenu::viewMedicalRecords()
{
    Prescription myPres[100];
    int count = 0;

    for (int i = 0; i < prescriptions.size(); i++)
    {
        if (prescriptions.get(i).getPatientID() == patient.getId())
            myPres[count++] = prescriptions.get(i);
    }

    if (count == 0)
    {
        cout << "No medical records found." << endl ;
        return;
    }

    cout << endl << "Your Medical Records" << endl;
    for (int i = 0; i < count; i++)
    {
        Doctor* dr = doctors.findByID(myPres[i].getDrID());
        const char* drName = dr ? dr->getName() : "Unknown";
        cout << endl;
        cout << "Date       : " << myPres[i].getDate() << endl;
        cout << "Doctor     : " << drName << endl;
        cout << "Medicines  : " << myPres[i].getMedicine() << endl;
        cout << "Notes      : " << myPres[i].getNotes() << endl;
    }
}
void PatientMenu::viewBills()
{
    Bill myBills[100];
    int count = 0;
    double totalUnpaid = 0;

    for (int i = 0; i < bills.size(); i++)
    {
        if (bills.get(i).getPID() == patient.getId())
        {
            myBills[count++] = bills.get(i);
            const char* st = bills.get(i).getStatus();
            const char* word = "unpaid";
            bool isUnpaid = 1;
            for (int j = 0; word[j] != '\0' || st[j] != '\0'; j++)
            {
                if (st[j] != word[j])
                {
                    isUnpaid = 0; break; 
                }
            }

            if (isUnpaid)
                totalUnpaid += bills.get(i).getAmount();
        }
    }

    if (count == 0)
    {
        cout << "No bills found." << endl;
        return;
    }

    cout << endl << "Your Bills" << endl;
    cout << "Bill ID  Appt ID     Amount(PKR)   Status     Date" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << myBills[i].getBillID() << "       " << myBills[i].getApptID() << "           " << myBills[i].getAmount() << "        " << myBills[i].getStatus() << "      " << myBills[i].getDate() << endl;
    }
    cout << endl << "Total Outstanding Dues : PKR " << totalUnpaid << endl;
}
void PatientMenu::payBill()
{
    Bill unpaid[100];
    int count = 0;
    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.get(i);
        if (b.getPID() != patient.getId())
            continue;

        const char* st = b.getStatus();
        const char* word = "unpaid";
        bool isUnpaid = 1;
        for (int j = 0; word[j] != '\0' || st[j] != '\0'; j++)
        {
            if (st[j] != word[j]) 
            {
                isUnpaid = 0; 
                break; 
            }
        }

        if (isUnpaid) 
            unpaid[count++] = b;
    }

    if (count == 0)
    {
        cout << "No unpaid bills." << endl;
        return;
    }

    cout << endl << "Unpaid Bills" << endl;
    cout << "Bill ID  Appt ID     Amount(PKR)  Date" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << unpaid[i].getBillID() << "       " << unpaid[i].getApptID() << "           " << unpaid[i].getAmount() << "        " << unpaid[i].getDate() << endl;
    }

    int billID;
    cout << "Enter Bill ID to pay : ";
    cin >> billID;
    Bill* target = nullptr;
    for (int i = 0; i < count; i++)
    {
        if (unpaid[i].getBillID() == billID)
        {
            target = &unpaid[i];
            break;
        }
    }
    if (target == nullptr)
    {
        cout << "Invalid bill ID." << endl;
        return;
    }
    try
    {
        if (patient.getBalance() < target->getAmount())
            throw InsufficientFundsException();
    }
    catch (const InsufficientFundsException& e)
    {
        cout << e.what() << endl;
        return;
    }
    patient -= target->getAmount();  
    Bill* stored = bills.findByID(billID);
    if (stored) stored->setStatus("paid");
    FileHandler::updateBillStatus(billID, "paid");
    FileHandler::updatePatientBalance(patient.getId(), patient.getBalance());
    cout << "Bill paid successfully. Remaining balance : PKR " << patient.getBalance() << endl;
}
void PatientMenu::topUpBalance()
{
    int attempts = 0;
    while (attempts < 3)
    {
        double amount;
        cout << "Enter amount to add (PKR) : ";
        cin >> amount;
        try
        {
            if (amount <= 0)
                throw InvalidInputException("Input Error : Amount must be greater than 0.");
            patient += amount;  
            FileHandler::updatePatientBalance(patient.getId(), patient.getBalance());
            cout << "Balance updated. New balance : PKR " << patient.getBalance() << endl;
            return;
        }
        catch (const InvalidInputException& e)
        {
            cout << e.what() << endl;
            attempts++;
        }
    }
}



