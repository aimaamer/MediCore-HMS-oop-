#pragma once
#include "filehandler.h"
#include <iostream>

template <typename T>
class Storage 
{
    T data[100]; 
    int count;
public:
    Storage() : count(0)
    {}
    bool add(const T& item)
    {
        if (count < 100)
        {
            data[count++] = item;
            return 1;
        }
        return 0;
    }
    bool removeByID(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i].getID() == id)
			{
                for (int j = i; j < count - 1; j++)
                {
                    data[j] = data[j + 1];
                }
                count--;
                FileHandler::deleteRecord(id);
                return 1;
            }

        }
        return 0;
    }
    T* findByID(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i].getID() == id)
            {
                return &data[i];
            }
        }
        return nullptr;
    }
    int size() const
    {
        return count;
    }
    T* getAll() 
    {
        return data;
    }
    T& get(int index) 
    {
        return data[index];
    }
    const T& get(int index) const 
    { 
        return data[index];
    }
};