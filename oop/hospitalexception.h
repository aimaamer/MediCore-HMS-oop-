#pragma once

class HospitalException 
{
protected:
    char message[200];

public:
    HospitalException(const char* msg) 
    {
        int i = 0;
        while (msg[i] != '\0' && i < 199) 
        {
            message[i] = msg[i++];
        }
        message[i] = '\0'; 
    }
    virtual const char* what() const
    {
        return message;
    }
};

class FileNotFoundException : public HospitalException
{
public:
    FileNotFoundException() : HospitalException("File Error : The file containing required data could not be opened.")
    {}
};

class InsufficientFundsException : public HospitalException
{
public:
    InsufficientFundsException() : HospitalException("Financial Error : Insufficient balance to complete transaction.")
    {}
};

class InvalidInputException : public HospitalException
{
public:
    InvalidInputException(const char* msg) : HospitalException(msg) 
    {}
};

class SlotUnavailableException : public HospitalException
{
public:
    SlotUnavailableException() : HospitalException("Booking Error : This time slot is already occupied.")
    {}
};