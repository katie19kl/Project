#ifndef ConnectCommand_H
#define ConnectCommand_H

#include "Command.h"
#include <string>
#include <vector>
#include <list>
#include "Var.h"
#include <unordered_map>
#include "SymboleTable.h"

class ConnectCommand : public Command
{
private:
    SymboleTable *symboleTable;
    int clientSocket;
    std::list<Var *> *listOfProgVar;
    std::unordered_map<std::string, double> *bindValueXMLFromServer;
    std::unordered_map<std::string, Var *> *nameVar_ToVar;
    std::unordered_map<std::string, Var *> *SIM_ToVar;
    

public:
    ConnectCommand(SymboleTable *smb)
    {
        this->symboleTable = smb;
        this->bindValueXMLFromServer = smb->get_BindXMLValueFromServer();
        this->nameVar_ToVar = smb->get_NameVar_ToVar();
        this->SIM_ToVar = smb->get_SIM_ToVar();

    }
    const int DILUG = 3;
    virtual int execute(std::vector<std::string>, int);
    int connectControlClient(std::string, int);
};

#endif
