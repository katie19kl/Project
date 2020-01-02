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
    std::vector<std::string> *orderedXML;

    std::unordered_map<std::string, double> *bindValue;
    std::unordered_map<std::string, Var *> *SIM_ToVar;
   
public:
    OpenServerCommand(SymboleTable *smb)
    {
        this->symboleTable = smb;
        this->orderedXML = smb->get_orderedXML();
        this->SIM_ToVar = smb->get_SIM_ToVar();
        this->bindValue = smb->get_BindXMLValueFromServer();
    }
    const int DILUG = 2;
    virtual int execute(std::vector<std::string>, int);
    std::unordered_map<std::string, double> *getTable_XML_VAR();


    void updateXML(char buffer[]);
    int createThread(int);

};

#endif