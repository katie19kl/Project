#include "DefineVarCommand.h"
#include <vector>
#include <string>
#include "Var.h"
using namespace std;

int DefineVarCommand::execute(vector<string> vectOfParam, int indexCurr)
{
    string nameVar = vectOfParam.at(indexCurr + 1);
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
        double value = -1000;
        if (this->bindXMLValueFromServer->size() > 0)
        {
            value = this->bindXMLValueFromServer->find(sim)->second;
        }
        Var *varToAdd = new Var(value, sim, nameVar, bind_FROM_sim, bind_IN_sim, is_binding);
        this->listOfProgVar->push_back(varToAdd);
        this->DILUG = 5;
    }
    else
    { // not binding rather there is var __ = smt or var __ = number;
        string sim = NULL;
        int flagFound = 0;
        double numToAdd;

        list<Var *>::iterator it = this->listOfProgVar->begin();

        while ( it  != listOfProgVar->end() )
        {
            if ((*it)->getVarName() == vectOfParam.at(indexCurr + 3))
            {
                break;
            }

            *(it)++;
        }
        if ((*it)->getVarName() == vectOfParam.at(indexCurr + 3))
        {
            flagFound = 1;
            numToAdd = (*it)->getValue();
        }
        else
        { // there is a number
            if (vectOfParam.at(indexCurr + 3) == "-")
            {
                numToAdd = stold(vectOfParam.at(indexCurr + 4));// if there is minus before
                numToAdd *= -1;
                this->DILUG = 5;
            }
            else
            {
                numToAdd = stod(vectOfParam.at(indexCurr + 3)); // if num withput minus
                this->DILUG = 4;
            }
        }
        Var *toAdd = new Var(numToAdd, sim, nameVar, bind_FROM_sim, bind_IN_sim, is_binding);
        this->listOfProgVar->push_back(toAdd);
    }

    return this->DILUG;
}