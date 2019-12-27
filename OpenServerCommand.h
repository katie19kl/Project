#ifndef OpenServerCommand_H
#define OpenServerCommand_H

#include "Command.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <thread>
#include "Var.h"
#include "SymboleTable.h"


class OpenServerCommand : public Command
{
private:
    SymboleTable *symboleTable;
    std::vector<std::string> orderedXML;

    std::unordered_map<std::string, double> *bindValue;
    std::unordered_map<std::string, Var *> *SIM_ToVar;
    //bool* isConnected = new bool(false);

public:
    OpenServerCommand(SymboleTable *smb, std::vector<std::string> XML)
    {
        this->symboleTable = smb;
        this->orderedXML = XML;
        this->SIM_ToVar = smb->get_SIM_ToVar();
        this->bindValue = smb->get_BindXMLValueFromServer();
    }
    const int DILUG = 1;
    virtual int execute(std::vector<std::string>, int);
    std::unordered_map<std::string, double> *getTable_XML_VAR();

    void updateSymbleTable(char[]);
    int createThread(int);
/*
    bool* get_isConnected(){
        return this->isConnected;
    }*/
};

#endif