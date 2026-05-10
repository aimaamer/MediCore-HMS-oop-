#include "authsystem.h"
#include"filehandler.h"

bool AuthSystem::loginPatient(Storage<Patient>& patients, Patient*& p)
{
    int id;
    char pwd[50];
    cout << "Enter Patient ID : ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pwd;
    for (int attempt = 0; attempt < 3; attempt++)
    {
        for (int i = 0; i < patients.size(); i++)
        {
            if (patients.get(i).login(id, pwd))
            {
                p = &patients.get(i);
                return 1;
            }
        }

        FileHandler::logFailedLogin("Patient", id);

        if (attempt < 2)
        {
            cout << "Invalid credentials. Try again." << endl;
            cout << "Enter Patient ID : ";
            cin >> id;
            cout << "Enter Password : ";
            cin >> pwd;
        }
    }
    cout << "Too many unsuccessful attempts" << endl;
    return 0;
}
bool AuthSystem::loginDoctor(Storage<Doctor>& doctors, Doctor*& d)
{
    int id;
    char pwd[50];
    cout << "Enter Doctor ID : ";
    cin >> id;
    cout << "Enter Password : ";
    cin >> pwd;
    for (int attempt = 0; attempt < 3; attempt++)
    {
        for (int i = 0; i < doctors.size(); i++)
        {
            if (doctors.get(i).login(id, pwd))
            {
                d = &doctors.get(i);
                return 1;
            }
        }
        FileHandler::logFailedLogin("Doctor", id);
        if (attempt < 2)
        {
            cout << "Invalid credentials. Try again." << endl;
            cout << "Enter Doctor ID : ";
            cin >> id;
            cout << "Enter Password : ";
            cin >> pwd;
        }
    }

    cout << "Too many unsuccessful attempts" << endl;
    return 0;
}

bool AuthSystem::loginAdmin(Admin& a)
{
    int id;
    char pwd[50];
    cout << "Enter Admin ID : ";
    cin >> id;
    cout << "Enter Password : ";
    cin >> pwd;
    for (int attempt = 0; attempt < 3; attempt++)
    {
        if (a.login(id, pwd))
            return 1;

        FileHandler::logFailedLogin("Admin", id);

        if (attempt < 2)
        {
            cout << "Invalid credentials. Try again." <<endl;
            cout << "Enter Admin ID : ";
            cin >> id;
            cout << "Enter Password : ";
            cin >> pwd;
        }
    }

    cout << "Too many unsuccessful attempts" << endl;
    return 0;
}