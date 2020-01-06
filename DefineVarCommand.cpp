#include "DefineVarCommand.h"
#include <vector>
#include <string>
#include "Var.h"
#include "SymboleTable.h"
#include <iostream>
#include "Ex1.h"
#include <sstream>

using namespace std;
// creating new var
int DefineVarCommand::execute(vector<string> vectOfParam, int indexCurr)
{
    string nameVar = vectOfParam.at(indexCurr + 1);
    // checks it state /->/<-/==/
    bool bind_IN_sim = false;
    bool bind_FROM_sim = false;
    bool is_binding = true;
    if (vectOfParam.at(indexCurr + 2) == "->")
    {
        bind_IN_sim = true;
    }
    else if (vectOfParam.at(indexCurr + 2) == "<-")
    {
        bind_FROM_sim = true;
    }
    else if (vectOfParam.at(indexCurr + 2) == "=")
    {
        is_binding = false;
    }
    if (is_binding)
    {
        string sim = vectOfParam.at(indexCurr + 4);
        double value;

        unordered_map<std::string, double>::iterator itToCheck = this->bindXMLValueFromServer->find(sim);// have to bind to smt
        if (itToCheck != bindXMLValueFromServer->end())
        {
            value = this->bindXMLValueFromServer->find(sim)->second;
        }
        Var *varToAdd = new Var(value, sim, nameVar, bind_FROM_sim, bind_IN_sim, is_binding);
        // updates data base
        this->nameVar_ToVar->insert({nameVar, varToAdd});
        this->SIM_ToVar->insert({sim, varToAdd});
        this->DILUG = 5;
    }
    else
    { // not binding rather there is var __ = smt or var __ = number;
        string sim = "";
        double numToAdd;

        if (this->nameVar_ToVar->find(vectOfParam.at(indexCurr + 3)) != this->nameVar_ToVar->end())
        {

            string calc = vectOfParam.at(indexCurr + 3);
            string calcBliSpace, intermediate;
            stringstream check1(calc);

            while (getline(check1, intermediate, ' '))
            {                                 //tokenizing according to ' '
                calcBliSpace += intermediate; //creating the exp without spaces
            }

            auto *interpreter = new Interpreter();
            interpreter->setSymbolTable(nameVar_ToVar);
            numToAdd = interpreter->interpret(calcBliSpace)->calculate();

            this->DILUG = 4;
        }

        Var *toAdd = new Var(numToAdd, sim, nameVar, bind_FROM_sim, bind_IN_sim, is_binding);
        this->nameVar_ToVar->insert({nameVar, toAdd});
    }
    return this->DILUG;
}