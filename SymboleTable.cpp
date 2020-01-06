#include "SymboleTable.h"
#include <condition_variable>
#include <mutex>
#include <string>
#include <unordered_map>
#include <iostream>
#include <iterator>

std::mutex SymboleTable ::mut;

using namespace std;

void SymboleTable ::server_UpdateSymbleTable(char buffer[])
{
    int i = 0, numOfValue = 0;
    string data;
    unordered_map<string, double>::iterator it;
    // retrieveing data from sim
    while (buffer[i] != '\n')
    {
        if (buffer[i] == ',' || buffer[i + 1] == '\n') /// ONly XML
        {

            if (buffer[i + 1] == '\n')
            {
                data.push_back(buffer[i]);
            }

            this->bindXMLValueFromServer->insert({this->orderedXML->at(numOfValue), stod(data)});
            auto it1 = SIM_ToVar->find(this->orderedXML->at(numOfValue));
            if (it1 != SIM_ToVar->end())
            {
                it1->second->setValue(stod(data));
            }

            numOfValue++;
            data.clear();
        }
        else
        {
            data.push_back(buffer[i]);
        }
        i++;
    }
    return;
}
// actuall changing of values in proccess
void SymboleTable ::change_SymbolTable(char buffer_server[], string key_who_change, double valToPut, string varName)
{
    std::lock_guard<mutex> lck(SymboleTable::mut);

    if (key_who_change == "server")
    {
        server_UpdateSymbleTable(buffer_server);
    }
    else if (key_who_change == "change_value")
    {
        changeValue_UpdateSymbolTable(valToPut, varName);
    }
    return;
}
// programm updates
void SymboleTable::changeValue_UpdateSymbolTable(double valToPut, string varName)
{
    this->nameVar_ToVar->find(varName)->second->setValue(valToPut); //put the value into the symbol table
}