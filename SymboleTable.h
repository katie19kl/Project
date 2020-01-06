#ifndef SymboleTable_H
#define SymboleTable_H

#include <unordered_map>
#include <string>
#include <list>
#include "Var.h"
#include <condition_variable>
#include <mutex>
#include <vector>

class SymboleTable
{

private:
    std::unordered_map<std::string, Var *> *nameVar_ToVar;
    std::unordered_map<std::string, Var *> *SIM_ToVar;
    std::unordered_map<std::string, double> *bindXMLValueFromServer;
    std::vector<std::string> *orderedXML;

    int *client_socket_to_send = new int();

public:
   // static std::condition_variable cv;
    static std::mutex mut;
    SymboleTable(
        std::unordered_map<std::string, double> *bindValueFromServer1, std::unordered_map<std::string, Var *> *nameVar_ToVar1, std::unordered_map<std::string, Var *> *SIM_ToVar1, std::vector<std::string> *simFromSimXML_OUTSIDE)
    {
        this->bindXMLValueFromServer = bindValueFromServer1;
        this->nameVar_ToVar = nameVar_ToVar1;
        this->SIM_ToVar = SIM_ToVar1;
        this->orderedXML = simFromSimXML_OUTSIDE;
    }
    std::unordered_map<std::string, Var *> *get_NameVar_ToVar()
    {
        return this->nameVar_ToVar;
    }
    std::unordered_map<std::string, Var *> *get_SIM_ToVar()
    {
        return this->SIM_ToVar;
    }
    std::unordered_map<std::string, double> *get_BindXMLValueFromServer()
    {
        return this->bindXMLValueFromServer;
    }
    std::vector<std::string>* get_orderedXML()
    {
        return this->orderedXML;
    }

    void setClientSocket(int cl_socket)
    {
        *(this->client_socket_to_send) = cl_socket;
    }
    int *get_ClientSocket()
    {
        return this->client_socket_to_send;
    }
    
    void changeValue_UpdateSymbolTable(double,std::string);////////////////////////////

    void change_SymbolTable(char [] = NULL , std::string = "", double = 0.0, std::string = "");

    void server_UpdateSymbleTable(char[]);

};
#endif