#include "DefineVarCommand.h"
#include <vector>
#include <string>
#include "Var.h"
#include "SymboleTable.h"
#include <iostream>


using namespace std;

int DefineVarCommand::execute(vector<string> vectOfParam, int indexCurr)
{
    string nameVar = vectOfParam.at(indexCurr + 1);
    bool bind_IN_sim = false;
    bool bind_FROM_sim = false;
    bool is_binding = true;


    //cout<<"Checking define------------------------------"<<endl;

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
        //double value = -10000;
        double value ;
        
        unordered_map<std::string, double>::iterator itToCheck = this->bindXMLValueFromServer->find(sim);
        if (itToCheck != bindXMLValueFromServer->end())
        {
            if (nameVar == "rpm"){
                int x = 6;
                x++;
            }
            value = this->bindXMLValueFromServer->find(sim)->second;
        }
        Var *varToAdd = new Var(value, sim, nameVar, bind_FROM_sim, bind_IN_sim, is_binding);
        
        this->nameVar_ToVar->insert({nameVar, varToAdd});
        this->SIM_ToVar->insert({sim,varToAdd});

        this->DILUG = 5;
    }
    else
    { // not binding rather there is var __ = smt or var __ = number;
        string sim = "";
        int flagFound = 0;
        double numToAdd;

        if (this->nameVar_ToVar->find(vectOfParam.at(indexCurr + 3)) == this->nameVar_ToVar->end())
        {
            // no var name => the is a number
            if (vectOfParam.at(indexCurr + 3) == "-")
            {
                numToAdd = (-1) * (stold(vectOfParam.at(indexCurr + 4))); // if there is minus before
                this->DILUG = 5;
            }
            else
            {
                numToAdd = stod(vectOfParam.at(indexCurr + 3)); // if num withput minus
                this->DILUG = 4;
            }
        }
        else
        { //  var name  exist

            numToAdd =  this->nameVar_ToVar->find(vectOfParam.at(indexCurr + 3))->second->getValue();
            this->DILUG = 4;
        }

        Var *toAdd = new Var(numToAdd, sim, nameVar, bind_FROM_sim, bind_IN_sim, is_binding);

        this->nameVar_ToVar->insert({nameVar, toAdd});
        
    }

    return this->DILUG;
}