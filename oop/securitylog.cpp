#include "securitylog.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void SecurityLog::unauthAccess(int id, const char* reason)
{
    ofstream file("security_log.txt", ios::app);
    if (!file)
        return; 

    file << "Unauthorized access. ID :" << id << endl;
}

void SecurityLog::viewLogs()
{
    std::ifstream file("security_log.txt");
    if (!file)
        return;

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}