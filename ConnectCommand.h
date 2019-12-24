#ifndef ConnectCommand_H
#define ConnectCommand_H

#include "Command.h"
#include <string>
#include <vector>
#include <list>
#include "Var.h"
#include <unordered_map>

class ConnectCommand : public Command
{
private:
    int clientSocket;
    bool isConnected = false;
    std::list<Var *> *listOfProgVar;
    std::unordered_map<std::string, double> *bindValueXMLFromServer;
    std::unordered_map<std::string, Var *> *nameVar_ToVar;
    std::unordered_map<std::string, Var *> *SIM_ToVar;


public:
    ConnectCommand(std::list<Var *> *listOf, std::unordered_map<std::string, double> *bindValueFromServer1, std::unordered_map<std::string, Var *> *nameVar_ToVar1,std::unordered_map<std::string, Var *> *SIM_ToVar1)
    {
        this->listOfProgVar = listOf;
        this->bindValueXMLFromServer = bindValueFromServer1;
        this->nameVar_ToVar = nameVar_ToVar1;
        this->SIM_ToVar = SIM_ToVar1;

    }
    const int DILUG = 2;
    virtual int execute(std::vector<std::string>, int);
    int connectControlClient();
    int sendToSimul();
};

#endif
