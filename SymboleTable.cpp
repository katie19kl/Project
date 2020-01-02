#include "SymboleTable.h"
#include <condition_variable>
#include <mutex>
#include <string>
#include <unordered_map>
#include <iostream>
#include <iterator>

//std::condition_variable SymboleTable ::cv;

std::mutex SymboleTable ::mut;

using namespace std;

void SymboleTable ::server_UpdateSymbleTable(char buffer[])
{
    /// 142 -157 --> updating table XML->VALUE
    int i = 0, numOfValue = 0;
    string data;
    unordered_map<string, double>::iterator it;

    //cout << "--------------" << endl;
    //  cout << buffer << "<--"        << "gonna change" << endl;
    int count_coma = 0;
    int size_doubl;
    while (buffer[i] != '\n')
    {

        if (buffer[i] == ',' || buffer[i + 1] == '\n') /// ONly XML
        {

            if (buffer[i + 1] == '\n')
            {
                data.push_back(buffer[i]);

                cout << "------------" << endl;
                cout << this->orderedXML->at(numOfValue) << " is " << stold(data) << endl;
                cout << "------------" << endl;
            }

            this->bindXMLValueFromServer->insert({this->orderedXML->at(numOfValue), stod(data)});

            // changing in maps

            auto it = SIM_ToVar->find(this->orderedXML->at(numOfValue));
            if (it != SIM_ToVar->end())
            {
                it->second->setValue(stod(data));
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

    /*   unordered_map<string, double> *bindValue_CHECK = this->get_BindXMLValueFromServer();
    cout << "in symbole changing table" << endl;

    cout << bindValue_CHECK->empty();

    for (auto elem : *bindValue_CHECK)
    {
        cout << "update smb" << endl;
        std::cout << elem.first << " " << elem.first << " " << elem.second << "\n";
    }
*/

    return;
}
/**
 * All will change via this func
 * 
 *  
 * Now just decedi who is changing and put mutex
 * 
 * 
 * 
*/
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

void SymboleTable::changeValue_UpdateSymbolTable(double valToPut, string varName)
{
    this->nameVar_ToVar->find(varName)->second->setValue(valToPut); //put the value into the symbol table
}