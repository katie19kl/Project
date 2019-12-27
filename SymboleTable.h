#ifndef SymboleTable_H
#define SymboleTable_H

#include <unordered_map>
#include <string>
#include <list>
#include "Var.h"
#include <condition_variable>
#include <mutex>
/*
static std::condition_variable cv;
static std::mutex mut;*/

class SymboleTable
{
private:
    std::unordered_map<std::string, Var *> *nameVar_ToVar;
    std::unordered_map<std::string, Var *> *SIM_ToVar;
    std::unordered_map<std::string, double> *bindXMLValueFromServer;

    std::condition_variable cv;
    std::mutex mut;

public:
    SymboleTable(
        std::unordered_map<std::string, double> *bindValueFromServer1, std::unordered_map<std::string, Var *> *nameVar_ToVar1, std::unordered_map<std::string, Var *> *SIM_ToVar1)
    {
        this->bindXMLValueFromServer = bindValueFromServer1;
        this->nameVar_ToVar = nameVar_ToVar1;
        this->SIM_ToVar = SIM_ToVar1;
    }
    std::unordered_map<std::string, Var *> *get_NameVar_ToVar()
    {
        return this->nameVar_ToVar;
    }
    std::unordered_map<std::string, Var *> *get_SIM_ToVar()
    {
        return this->SIM_ToVar;
    }
    std::unordered_map<std::string, double> *get_BindXMLValueFromServer()
    {
        return this->bindXMLValueFromServer;
    }

    std::mutex getMutex(){
        return std::mutex m;
    }
};
#endif