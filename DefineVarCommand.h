#include <string>
#include "Command.h"
#include "unordered_map"
#include <list>
#include "Var.h"

class DefineVarCommand : public Command
{
private:
    //std::unordered_map <std::string,Var> symbolTable;
    std::list<Var *> *listOfProgVar;
    std::unordered_map<std::string, double> *bindXMLValueFromServer;
    int DILUG;

public:
    DefineVarCommand(std::list<Var *> *list, std::unordered_map<std::string, double> *bindValueFromServer1)
    {
        this->listOfProgVar = list;
        this->bindXMLValueFromServer = bindValueFromServer1;
    }
    virtual int execute(std::vector<std::string>, int);
};
/*
1- It just define value and return it in table
2- It creates table in it.
3- sim is not clear// sim is function
*/
