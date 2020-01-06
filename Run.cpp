#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Command.h"
#include "OpenServerCommand.h"
#include <thread>
#include "ParseXML.h"
#include "Lexer.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include <map>
#include "Var.h"
#include <list>
#include "SymboleTable.h"
#include <condition_variable>
#include <mutex>
#include "ChangeValue.h"
#include "IfCommand.h"
#include "LoopCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "FuncParser.h"
#include "FuncCommand.h"
#include <fstream>
#include <regex>
#include "Run.h"
using namespace std;

void parser(vector<string> tokens, unordered_map<string, Command *> *fromTape,
            unordered_map<string, Var *> *name_to_var, FuncParser *func_parser)
{
    unsigned long i = 0;
    while (i < tokens.size())
    {
        Command *c;
        if (fromTape->find(tokens[i]) != fromTape->end()) // server,define commands
        {
            c = fromTape->find(tokens[i])->second;
            i += c->execute(tokens, i);
        }
        else
        {
            //change value
            if (name_to_var->find(tokens[i]) != name_to_var->end())
            {
                if (tokens[i + 1] == "=")
                { //of the type changeValue
                    c = fromTape->find("changeValue")->second;
                    i += c->execute(tokens, i);
                }
            }
            else if (tokens[i + 1].substr(0, 3) == "var") //defition function
            {

                c = fromTape->find("funcParser")->second;
                i += c->execute(tokens, i);
            }
            else if (func_parser->getFunctions().find(tokens[i]) != func_parser->getFunctions().end()) //running of function
            {
                c = fromTape->find("funcCommand")->second;
                i += c->execute(tokens, i);
            }
            else
            {
                throw "No such command exists!";
            }
        }
    }
}

void run(string fileName)
{
    vector<string> *simFromSimXML = new vector<string>(parseXML()); // for server constructor
    vector<string> tokensKeti = lexer(fileName);

    string connectControlClient = "connectControlClient";
    string openDataServer = "openDataServer";
    string var = "var";

    unordered_map<string, Command *> *fromTape = new unordered_map<string, Command *>();

    unordered_map<string, Var *> *nameVar_ToVar = new unordered_map<string, Var *>();
    unordered_map<string, Var *> *SIM_ToVar = new unordered_map<string, Var *>();
    unordered_map<string, double> *bindValue = new std::unordered_map<std::string, double>();
    // singelton / non static object
    SymboleTable *symboleTable = new SymboleTable(bindValue, nameVar_ToVar, SIM_ToVar, simFromSimXML);
    // creating commands
    OpenServerCommand server(symboleTable);
    fromTape->insert({openDataServer, &server});

    ConnectCommand clientOnlyConnect(symboleTable);
    fromTape->insert({connectControlClient, &clientOnlyConnect});

    DefineVarCommand defVar(symboleTable);
    fromTape->insert({var, &defVar});

    SleepCommand sleep_command(symboleTable);
    fromTape->insert({"Sleep", &sleep_command});

    PrintCommand print_command(symboleTable);
    fromTape->insert({"Print", &print_command});

    ChangeValue change_value(symboleTable);
    fromTape->insert({"changeValue", &change_value});

    FuncParser *func_parser = new FuncParser;
    fromTape->insert({"funcParser", func_parser});

    IfCommand if_command(fromTape, symboleTable, func_parser);
    fromTape->insert({"if", &if_command});

    LoopCommand loop_command(fromTape, symboleTable, func_parser);
    fromTape->insert({"while", &loop_command});

    FuncCommand func_command(symboleTable, fromTape, func_parser);
    fromTape->insert({"funcCommand", &func_command});
    // starting parsing of file
    parser(tokensKeti, fromTape, symboleTable->get_NameVar_ToVar(), func_parser);

    //closing sockets
    server.closeSocket();
    change_value.closeClientSocket();

    return;
}