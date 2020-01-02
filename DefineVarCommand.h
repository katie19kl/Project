#ifndef DefineVarCommand_H
#define DefineVarCommand_H

#include <string>
#include "Command.h"
#include <unordered_map>
#include <list>
#include "Var.h"
#include "SymboleTable.h"

class DefineVarCommand : public Command
{
private:
    SymboleTable *symboleTable;

    std::unordered_map<std::string, double> *bindXMLValueFromServer;
    int DILUG;
    std::unordered_map<std::string, Var *> *nameVar_ToVar;
    std::unordered_map<std::string, Var *> *SIM_ToVar;

public:
    DefineVarCommand(SymboleTable *smb)
    {
        this->symboleTable = smb;
        this->bindXMLValueFromServer = smb->get_BindXMLValueFromServer();
        this->nameVar_ToVar = smb->get_NameVar_ToVar();
        this->SIM_ToVar = smb->get_SIM_ToVar();
    }
    virtual int execute(std::vector<std::string>, int);

    SymboleTable* getSymbolTable(){
        return this->symboleTable;
    }

};
#endif