#pragma once

class SecurityLog
{
public:
    static void unauthAccess(int id, const char* reason);
    static void viewLogs(); 
};