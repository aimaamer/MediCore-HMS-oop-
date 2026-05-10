#include"filehandler.h"
#include "hospitalexception.h"
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

void FileHandler::getField(const char* line, int& idx ,char* field, int maxLen)
{
    int i = 0;
    while (line[idx] != ',' &&line[idx] != '\0' && line[idx] != '\n')
    {
        if (i < (maxLen - 1) )
            field[i++] = line[idx++];
    }
    field[i] = '\0';
    if (line[idx] == ',')
        idx++;
}
int FileHandler::toInt(const char* s)
{
    int i = 0;
    int res = 0;
    int sign = 1;
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        res= res * 10 + (s[i] - '0');
        i++;
    }

    return res * sign;
}
double FileHandler::toDouble(const char* s)
{
    int i = 0;
    double res = 0.0;
    double sign = 1;
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        res = res* 10 + (s[i] - '0');
        i++;
    }
    if (s[i] == '.')
    {
        i++;
        double place = 0.1;
        while (s[i] >= '0' && s[i] <= '9')
        {
            res += (s[i] - '0') * place;
            place *= 0.1;
            i++;
        }
    }
    return res * sign;
}
void FileHandler::loadPatients(Storage<Patient>& store)
{
    ifstream file("patients.txt");
    if (!file.is_open())
        throw FileNotFoundException();
    char line[300];
    while (file.getline(line, 300))
    {
        int idx = 0;
        char idStr[10], name[50], ageStr[5], genderStr[3],contact[12], password[50], balStr[20];
        getField(line, idx, idStr, 10);
        getField(line, idx, name, 50);
        getField(line, idx, ageStr, 5);
        getField(line, idx, genderStr, 3);
        getField(line, idx, contact, 12);
        getField(line, idx, password, 50);
        getField(line, idx, balStr, 20);
        int id = toInt(idStr);
        int age = toInt(ageStr);
        char gender = genderStr[0];
        double balance = toDouble(balStr);
        Patient p(id, name, password, age, gender, contact, balance);
        store.add(p);
    }
    file.close();
}
void FileHandler::loadDoctors(Storage<Doctor>& store)
{
    ifstream file("doctors.txt");
    if (!file.is_open())
        throw FileNotFoundException();
    char line[300];
    while (file.getline(line, 300))
    {
        int idx = 0;
        char idStr[10], name[50], spec[70], contact[12], password[50], feeStr[20];
        getField(line, idx, idStr, 10);
        getField(line, idx, name, 50);
        getField(line, idx, spec, 70);
        getField(line, idx, contact, 12);
        getField(line, idx, password, 50);
        getField(line, idx, feeStr, 20);
        int id = toInt(idStr);
        double fee = toDouble(feeStr);
        Doctor d(id, name, password, spec, contact, fee);
        store.add(d);
    }
    file.close();
}
void FileHandler::loadAppointments(Storage<Appointment>& store)
{
    ifstream file("appointments.txt");
    if (!file.is_open())
        throw FileNotFoundException();
    char line[300];
    while (file.getline(line, 300))
    {
        int idx = 0;
        char aIDStr[10], pIDStr[10], dIDStr[10], date[11], slot[6], status[20];
        getField(line, idx, aIDStr, 10);
        getField(line, idx, pIDStr, 10);
        getField(line, idx, dIDStr, 10);
        getField(line, idx, date, 11);
        getField(line, idx, slot, 6);
        getField(line, idx, status, 20);
        Appointment a(toInt(aIDStr), toInt(pIDStr), toInt(dIDStr), date, slot, status);
        store.add(a);
    }
    file.close();
}
void FileHandler::loadBills(Storage<Bill>& store)
{
    ifstream file("bills.txt");
    if (!file.is_open())
        throw FileNotFoundException();
    char line[200];
    while (file.getline(line, 200))
    {
        int idx = 0;
        char bIDStr[10], pIDStr[10], aIDStr[10], amtStr[20], status[10], date[11];
        getField(line, idx, bIDStr, 10);
        getField(line, idx, pIDStr, 10);
        getField(line, idx, aIDStr, 10);
        getField(line, idx, amtStr, 20);
        getField(line, idx, status, 10);
        getField(line, idx, date, 11);
        Bill b(toInt(bIDStr), toInt(aIDStr), toInt(pIDStr), toDouble(amtStr), status, date);
        store.add(b);
    }
    file.close();
}
void FileHandler::loadPrescriptions(Storage<Prescription>& store)
{
    ifstream file("prescriptions.txt");
    if (!file.is_open())
        throw FileNotFoundException();
    char line[1100];
    while (file.getline(line, 1100))
    {
        int idx = 0;
        char presIDStr[10], apptIDStr[10], patIDStr[10],drIDStr[10], date[11], medicine[500], notes[300];
        getField(line, idx, presIDStr, 10);
        getField(line, idx, apptIDStr, 10);
        getField(line, idx, patIDStr, 10);
        getField(line, idx, drIDStr, 10);
        getField(line, idx, date, 11);
        getField(line, idx, medicine, 500);
        getField(line, idx, notes, 300);
        Prescription p(toInt(presIDStr), toInt(apptIDStr), toInt(patIDStr), toInt(drIDStr), date, medicine, notes);
        store.add(p);
    }
    file.close();
}
void FileHandler::writePatient(Patient& p)
{
    ofstream file("patients.txt", ios::app);
    if (!file.is_open()) 
        throw FileNotFoundException();
    file << p.getId() << "," << p.getName() << "," << p.getAge() << "," << p.getGender() << "," << p.getContact() << "," << p.getPwd() << "," << p.getBalance() << endl;
    file.close();
}
void FileHandler::writeDoctor(Doctor& d)
{
    ofstream file("doctors.txt", ios::app);
    if (!file.is_open())
        throw FileNotFoundException();
    file << d.getId() << "," << d.getName() << "," << d.getSpec() << "," << d.getContact() << "," << d.getPwd() << "," << d.getFee() << endl;
    file.close();
}
void FileHandler::writeAppointment(Appointment& a)
{
    ofstream file("appointments.txt", ios::app);
    if (!file.is_open()) 
        throw FileNotFoundException();
    file << a.getID() << "," << a.getPatientID() << "," << a.getDrID() << "," << a.getDate() << "," << a.getTimeSlot() << "," << a.getStatus() << endl;
    file.close();
}
void FileHandler::writeBill( Bill& b)
{
    ofstream file("bills.txt", ios::app);
    if (!file.is_open()) 
        throw FileNotFoundException();
    file << b.getBillID() << "," << b.getPID() << "," << b.getApptID() << "," << b.getAmount() << "," << b.getStatus() << "," << b.getDate() << endl;
    file.close();
}
void FileHandler::writePrescription( Prescription& p)
{
    ofstream file("prescriptions.txt", ios::app);
    if (!file.is_open()) 
        throw FileNotFoundException();
    file << p.getPresID() << "," << p.getApptID() << "," << p.getPatientID() << "," << p.getDrID() << "," << p.getDate() << "," << p.getMedicine() << "," << p.getNotes() << endl;
    file.close();
}
void FileHandler::updatePatientBalance(int patientID, double newBalance)
{
    ifstream inFile("patients.txt");
    if (!inFile.is_open())
        throw FileNotFoundException();
    char lines[100][300];
    int lineCount = 0;
    while (inFile.getline(lines[lineCount], 300))
    {
        if (lines[lineCount][0] != '\0')
            lineCount++;
    }
    inFile.close();

    ofstream outFile("patients.txt");  
    if (!outFile.is_open()) 
        throw FileNotFoundException();
    for (int i = 0; i < lineCount; i++)
    {
        int pos = 0;
        char idStr[10];
        getField(lines[i], pos, idStr, 10);
        int id = toInt(idStr);
        if (id == patientID)
        {
            char name[50], ageStr[5], genderStr[3], contact[12], password[50], oldBal[20];
            getField(lines[i], pos, name, 50);
            getField(lines[i], pos, ageStr, 5);
            getField(lines[i], pos, genderStr, 3);
            getField(lines[i], pos, contact, 12);
            getField(lines[i], pos, password, 50);
            getField(lines[i], pos, oldBal, 20);  
            outFile << id << "," << name << "," << ageStr << "," << genderStr << "," << contact << "," << password << "," << newBalance << endl;
        }
        else
        {
            outFile << lines[i] << endl;
        }
    }
    outFile.close();
}
void FileHandler::updateAppointmentStatus(int apptID, const char* newStatus)
{
    ifstream inFile("appointments.txt");
    if (!inFile.is_open()) 
        throw FileNotFoundException();
    char lines[100][200];
    int lineCount = 0;
    while (inFile.getline(lines[lineCount], 200))
    {
        if (lines[lineCount][0] != '\0')
            lineCount++;
    }
    inFile.close();

    ofstream outFile("appointments.txt");
    if (!outFile.is_open()) 
        throw FileNotFoundException();
    for (int i = 0; i < lineCount; i++)
    {
        int pos = 0;
        char idStr[10];
        getField(lines[i], pos, idStr, 10);
        if (toInt(idStr) == apptID)
        {
            char pIDStr[10], dIDStr[10], date[11], slot[6], oldStatus[20];
            getField(lines[i], pos, pIDStr, 10);
            getField(lines[i], pos, dIDStr, 10);
            getField(lines[i], pos, date, 11);
            getField(lines[i], pos, slot, 6);
            getField(lines[i], pos, oldStatus, 20);
            outFile << idStr << "," << pIDStr << "," << dIDStr << "," << date << "," << slot << "," << newStatus << endl;
        }
        else
            outFile << lines[i] << endl;
    }
    outFile.close();
}

void FileHandler::updateBillStatus(int billID, const char* newStatus)
{
    ifstream inFile("bills.txt");
    if (!inFile.is_open()) 
        throw FileNotFoundException();
    char lines[100][200];
    int lineCount = 0;
    while (inFile.getline(lines[lineCount], 200))
    {
        if (lines[lineCount][0] != '\0')
            lineCount++;
    }
    inFile.close();

    ofstream outFile("bills.txt");
    if (!outFile.is_open()) 
        throw FileNotFoundException();
    for (int i = 0; i < lineCount; i++)
    {
        int pos = 0;
        char idStr[10];
        getField(lines[i], pos, idStr, 10);
        if (toInt(idStr) == billID)
        {
            char pIDStr[10], aIDStr[10], amtStr[20], oldStatus[10], date[11];
            getField(lines[i], pos, pIDStr, 10);
            getField(lines[i], pos, aIDStr, 10);
            getField(lines[i], pos, amtStr, 20);
            getField(lines[i], pos, oldStatus, 10);
            getField(lines[i], pos, date, 11);
            outFile << idStr << "," << pIDStr << "," << aIDStr << "," << amtStr << "," << newStatus << "," << date << endl;
        }
        else
            outFile << lines[i] << endl;
    }
    outFile.close();
}
void FileHandler::deleteDoctor(int doctorID)
{
    ifstream inFile("doctors.txt");
    if (!inFile.is_open())
        throw FileNotFoundException();

    char lines[100][300];
    int lineCount = 0;
    while (inFile.getline(lines[lineCount], 300))
    {
        if (lines[lineCount][0] != '\0')
            lineCount++;
    }
    inFile.close();

    ofstream outFile("doctors.txt");
    if (!outFile.is_open())
        throw FileNotFoundException();

    for (int i = 0; i < lineCount; i++)
    {
        int pos = 0;
        char idStr[10];
        getField(lines[i], pos, idStr, 10);
        if (toInt(idStr) != doctorID)   // skip the dltd one
            outFile << lines[i] << endl;
    }
    outFile.close();
}
void FileHandler::deletePatient(int patientID)
{
    ifstream inFile("patients.txt");
    if (!inFile.is_open())
        throw FileNotFoundException();

    char lines[100][300];
    int lineCount = 0;
    while (inFile.getline(lines[lineCount], 300))
    {
        if (lines[lineCount][0] != '\0')
            lineCount++;
    }
    inFile.close();

    ofstream outFile("patients.txt");
    if (!outFile.is_open()) 
        throw FileNotFoundException();
    for (int i = 0; i < lineCount; i++)
    {
        int pos = 0;
        char idStr[10];
        getField(lines[i], pos, idStr, 10);
        if (toInt(idStr) != patientID)
            outFile << lines[i] << endl;
    }
    outFile.close();
}
void FileHandler::archivePatient(int patientID,Storage<Patient>& patients, Storage<Appointment>& appointments, Storage<Bill>& bills,Storage<Prescription>& prescriptions)
{
    ofstream arch("discharged.txt", ios::app);
    if (!arch.is_open()) 
        throw FileNotFoundException();
    Patient* p = patients.findByID(patientID);
    if (p)
    {
        arch << p->getId() << "," << p->getName() << "," << p->getAge() << "," << p->getGender() << "," << p->getContact() << "," << p->getPwd() << "," << p->getBalance() << endl;
    }
    for (int i = 0; i < appointments.size(); i++)
    {
        Appointment& a = appointments.get(i);
        if (a.getPatientID() != patientID) 
            continue;
        arch << a.getID() << "," << a.getPatientID() << "," << a.getDrID() << "," << a.getDate() << "," << a.getTimeSlot() << "," << a.getStatus() << endl;
    }
    for (int i = 0; i < bills.size(); i++)
    {
        Bill& b = bills.get(i);
        if (b.getPID() != patientID)
            continue;
        arch << b.getBillID() << "," << b.getPID() << "," << b.getApptID() << "," << b.getAmount() << "," << b.getStatus() << "," << b.getDate() << endl;
    }
    for (int i = 0; i < prescriptions.size(); i++)
    {
        Prescription& pr = prescriptions.get(i);
        if (pr.getPatientID() != patientID)
            continue;
        arch << pr.getPresID() << "," << pr.getApptID() << "," << pr.getPatientID() << "," << pr.getDrID() << "," << pr.getDate() << "," << pr.getMedicine() << "," << pr.getNotes() << endl;
    }

    arch.close();
}
void FileHandler::logFailedLogin(const char* role, int enteredID)
{
    ofstream file("security_log.txt", ios::app);
    if (!file.is_open())
        return;
    time_t t = time(nullptr);
    tm* localt = localtime(&t);
    char timestamp[25];
    strftime(timestamp, 25, "%d-%m-%Y %H:%M:%S", localt);
    file << timestamp << "," << role << "," << enteredID << "," << "FAILED" << endl;

    file.close();
}