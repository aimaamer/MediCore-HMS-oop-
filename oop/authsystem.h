#pragma once
#include <iostream>
#include "patient.h"
#include "doctor.h"
#include "admin.h"
#include "storage.h"

using namespace std;

class AuthSystem
{
public:
    static bool loginPatient(Storage<Patient>& patients, Patient*& p);
    static bool loginDoctor(Storage<Doctor>& doctors, Doctor*& d);
    static bool loginAdmin(Admin& a);
};