#include <string>
#include "Command.h"
#include <unordered_map>
#include <list>
#include "Var.h"

class DefineVarCommand : public Command
{
private:
    //std::unordered_map <std::string,Var> symbolTable;
    std::list<Var *> *listOfProgVar;
    std::unordered_map<std::string, double> *bindXMLValueFromServer;
    int DILUG;
    std::unordered_map<std::string, Var *> *nameVar_ToVar;
    std::unordered_map<std::string, Var *> *SIM_ToVar;

public:
    DefineVarCommand(std::list<Var *> *list, std::unordered_map<std::string, double> *bindValueFromServer1, std::unordered_map<std::string, Var *> *nameVar_ToVar1,std::unordered_map<std::string, Var *> *SIM_ToVar1)
    {
        this->listOfProgVar = list;
        this->bindXMLValueFromServer = bindValueFromServer1;
        this->nameVar_ToVar = nameVar_ToVar1;
        this->SIM_ToVar = SIM_ToVar1;
    }
    virtual int execute(std::vector<std::string>, int);

    std::unordered_map<std::string, Var *>* getSymbolTable(){
        return this->nameVar_ToVar;
    }

};
/*
1- It just define value and return it in table
2- It creates table in it.
3- sim is not clear// sim is function
*/
