#ifndef SymboleTable_H
#define SymboleTable_H

#include <unordered_map>
#include <string>
#include <list>
#include "Var.h"
#include <condition_variable>
#include <mutex>

class SymboleTable
{

private:
    std::unordered_map<std::string, Var *> *nameVar_ToVar;
    std::unordered_map<std::string, Var *> *SIM_ToVar;
    std::unordered_map<std::string, double> *bindXMLValueFromServer;

    bool firstGivenRecieved = false;
    //bool serverRead = true;
    bool serverRead = false;
    bool clientWantsToSend = false;
    bool clientTryConnect = true;

public:
    static std::condition_variable cv;
    static std::mutex mut;
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

    bool check_FirstGiven()
    {
        return this->firstGivenRecieved;
    }

    void set_FirstGiven(bool outside)
    {
        this->firstGivenRecieved = outside;
    }

    bool check_ClientSend()
    {
        return this->clientWantsToSend;
    }
    void set_ClientWantsToCheck(bool outside)
    {
        this->clientWantsToSend = outside;
    }

    void set_ServerRead(bool outside)
    {
        this->serverRead = outside;
    }
    bool check_ServerRead(){
        return this->serverRead;
    }

    void set_ClientTryConnect(bool outside){
        this->clientTryConnect = outside;
    }
    bool check_ClientTryConnect(){
        return this->clientTryConnect;
    }






};
#endif