#ifndef OpenServerCommand_H
#define OpenServerCommand_H

#include "Command.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <list> 
#include "Var.h" 


class OpenServerCommand : public Command
{
    private:
        std::vector <std::string> orderedXML;
        std::unordered_map<std::string, double>* bindValue;
        std::list <Var*> *listOfProgVar;

    public:
        OpenServerCommand(std::vector <std::string> XML, std::list <Var*> *listOf){
            this->orderedXML = XML;
            this->listOfProgVar = listOf;
            this->bindValue = new std::unordered_map<std::string,double>();

        }
        const int DILUG = 1;
        virtual  int execute(std::vector <std::string>,int );
        std::unordered_map<std::string, double>* getTable_XML_VAR();
};

#endif