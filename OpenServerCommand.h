#ifndef OpenServerCommand_H
#define OpenServerCommand_H

#include "Command.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <thread>
#include "Var.h"
using namespace std;

class OpenServerCommand : public Command
{
private:
    std::vector<std::string> orderedXML;
    std::unordered_map<std::string, double> *bindValue;
    std::list<Var *> *listOfProgVar;
    std::unordered_map<std::string, Var *> *SIM_ToVar;

    std::thread *threadServer;

public:
    OpenServerCommand(std::vector<std::string> XML, std::list<Var *> *listOf, std::unordered_map<std::string, Var *> *SIM_ToVar1)
    {
        this->orderedXML = XML;
        this->listOfProgVar = listOf;
        this->bindValue = new std::unordered_map<std::string, double>();
        this->SIM_ToVar = SIM_ToVar1;
    }
    const int DILUG = 1;
    virtual int execute(std::vector<std::string>, int);
    std::unordered_map<std::string, double> *getTable_XML_VAR();
    char check[1024] = {"fooo"};
    void getDataFromSim(int);
    void updateSymbleTable(char[]);
    void makeThreadConnect(int );
    void setThreadServer(int socket);


    std::thread *getServerThread()
    {

        return this->threadServer;
    }
};

#endif