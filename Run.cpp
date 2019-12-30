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

using namespace std;
unique_lock<mutex> ul(SymboleTable::mut); // mutex.lock

bool *firstConnection;
bool *serverWantsToSend;

bool boolFoo;

void parser(vector<string> tokens, unordered_map<string, Command *> *fromTape,
            unordered_map<string, Var *> *name_to_var, FuncParser &func_parser, SymboleTable *symboleTable)
{

    cout << this_thread::get_id() << " main thread  " << endl;
    int numIter = 0;
    int i = 0; //change - since we are not using the first 3 commands(server, client, var creation)
    while (true /*i < tokens.size()*/)
    {
        numIter++;
        //    cout << i << " number tokens" << endl;
        //    cout << tokens[i] << "================================= zaebalo " << endl;

        Command *c;

        //A specific command that is in the fromTape map(<string, Command*>)
        if (fromTape->find(tokens[i]) != fromTape->end())
        ///////////////////////// Loop/var/cond/func/server/client/
        {

            c = fromTape->find(tokens[i])->second;

            i += c->execute(tokens, i);

            cout << this_thread::get_id() << " is --------------------- wainting main 1  " << endl;
            cout << "condtion in condition variable" << symboleTable->check_ServerRead() << endl;
            SymboleTable::cv.wait(ul, [symboleTable] { return !(symboleTable->check_ServerRead()); });

            //SymboleTable::cv.wait(ul, [symboleTable] { return (symboleTable->check_FirstGiven() && !symboleTable->check_ServerRead()) && !symboleTable->check_ClientTryConnect(); });

            cout << this_thread::get_id() << " running main  1" << endl;
            cout << " already in main working" << endl;

            cout << "Making work after wait. Try number of token -----" << numIter << endl;
            cout<< "main finished ----------------------------"<<endl;
        }
        /*    
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

                cout << this_thread::get_id() << " wainting main  2" << endl;
                //SymboleTable::cv.wait(ul, [symboleTable] { return (symboleTable->check_FirstGiven() && !symboleTable->check_ServerRead()) && !symboleTable->check_ClientTryConnect(); });

                SymboleTable::cv.wait(ul, [symboleTable] { return (symboleTable->check_FirstGiven()); });
                cout << this_thread::get_id() << " running main  2";
                cout << " already in main  2" << endl;
                //definition of a function
            }
            else if (tokens[i + 1].substr(0, 3) == "var") // ziiny she ze defition function
            {
                c = fromTape->find("funcParser")->second;
                i += c->execute(tokens, i);

                cout << this_thread::get_id() << " wainting main  3" << endl;
                SymboleTable::cv.wait(ul, [symboleTable] { return (symboleTable->check_FirstGiven() && !symboleTable->check_ServerRead()) && !symboleTable->check_ClientTryConnect(); });
                cout << this_thread::get_id() << " running main 3";
                cout << " already in main  3" << endl;
                //a name of a function that has been defined before - run the function
            }
            else if (func_parser.getFunctions().find(tokens[i]) != func_parser.getFunctions().end()) //running of function
            {
                c = fromTape->find("funcCommand")->second;
                i += c->execute(tokens, i);

                cout << this_thread::get_id() << " wainting main  4" << endl;
                SymboleTable::cv.wait(ul, [symboleTable] { return (symboleTable->check_FirstGiven() && !symboleTable->check_ServerRead()) && !symboleTable->check_ClientTryConnect(); });
                cout << this_thread::get_id() << " running main  4";
                cout << " already in main  4" << endl;
            }
            else
            {
                throw "No such command exists!";
            }
        }
    */
    }
}

int main()
{

    int currIndex = 0;
    vector<string> simFromSimXML = parseXML();              // for server constructor
    vector<string> tokensKeti = lexer("fly_with_func.txt"); // CHANGE TO ARGV!!!!!!!!!!!!!!

    ///parser run programm

    string connectControlClient = "connectControlClient";
    string openDataServer = "openDataServer";
    string var = "var";

    unordered_map<string, Command *> *fromTape = new unordered_map<string, Command *>();

    unordered_map<string, Var *> *nameVar_ToVar = new unordered_map<string, Var *>();
    unordered_map<string, Var *> *SIM_ToVar = new unordered_map<string, Var *>();
    unordered_map<string, double> *bindValue = new std::unordered_map<std::string, double>();

    SymboleTable *symboleTable = new SymboleTable(bindValue, nameVar_ToVar, SIM_ToVar);

    OpenServerCommand server(symboleTable, simFromSimXML);
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

    FuncParser func_parser;
    fromTape->insert({"funcParser", &func_parser});

    IfCommand if_command(fromTape, symboleTable, func_parser);
    fromTape->insert({"if", &if_command});

    LoopCommand loop_command(fromTape, symboleTable, func_parser);
    fromTape->insert({"while", &loop_command});

    FuncCommand func_command(symboleTable, fromTape, func_parser);
    fromTape->insert({"funcCommand", &func_command});

    parser(tokensKeti, fromTape, symboleTable->get_NameVar_ToVar(), func_parser, symboleTable);

    cout << server.getTable_XML_VAR()->begin()->first << endl;

    return 0;
}