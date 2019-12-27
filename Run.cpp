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

using namespace std;

//extern condition_variable cond_var;
//extern mutex mut;
bool* firstConnection;
bool* serverWantsToSend;

bool boolFoo;

int main()
{

    int currIndex = 0;
    vector<string> simFromSimXML = parseXML();              // for server constructor
    vector<string> tokensKeti = lexer("fly_with_func.txt"); //

    string connectControlClient = "ConnectCommand";
    string openDataServer = "openDataServer";
    string var = "var";

    map<string, Command *> fromTape;
    //list<Var *> *tableOfProgVar = new list<Var *>();

    unordered_map<string, Var *> *nameVar_ToVar = new unordered_map<string, Var *>();
    unordered_map<string, Var *> *SIM_ToVar = new unordered_map<string, Var *>();
    unordered_map<string, double> *bindValue = new std::unordered_map<std::string, double>();

    SymboleTable *symboleTable = new SymboleTable(bindValue, nameVar_ToVar, SIM_ToVar);

    OpenServerCommand server(symboleTable, simFromSimXML);
    ConnectCommand clientOnlyConnect(symboleTable);

    //DefineVarCommand defVar(symboleTable);

    unique_lock<mutex> ul(SymboleTable::mut);  // mutex.lock


    server.execute(tokensKeti, 0);
    cout<<"wait for server"<<endl;
    SymboleTable::cv.wait(ul, [symboleTable] { return  !symboleTable->check_ServerRead();});
    cout<<"server got first data = > lets activate client"<<endl;
    clientOnlyConnect.execute(tokensKeti, 2);
    SymboleTable::cv.wait(ul, [symboleTable] { return  !symboleTable->check_ClientTryConnect();  } );
    cout<<"client is connected lets continue our main"<<endl;

 /*   SymboleTable::cv.wait(ul, [symboleTable] {return  symboleTable->check_FirstGiven();  } ); // shtok to main!!!
    symboleTable->set_FirstGiven(false); // maybe client uses the same!!!
    printf("after server\n");

    ul.unlock(); //mutex.unlock()
*/

    
    /* defVar.execute(tokensKeti,2);
    defVar.execute(tokensKeti,7);
    defVar.execute(tokensKeti,11);
    defVar.execute(tokensKeti,16);
    */
    //fromTape.insert({openDataServer, &server});
    //fromTape.insert({connectControlClient, &client});
    //fromTape.insert({var, &defVar});
    /* while (currIndex < tokensKeti.size())
    {
        //Command* command = fromTape.at(tokensKeti[currIndex]);
        Command* command = (fromTape.find(tokensKeti[currIndex])->second);
        
        if command == client has to send 
        server.shtok
        client.execute

        if (command != NULL){
            currIndex += command->execute(tokensKeti,currIndex);
        }
        client shtok
        server keep receiving
    }    
*/
    //ul.lock();
    int x = 0;

        //this_thread::sleep_for(chrono::milliseconds(2000));
    cout<<"getting bool of client   "<<symboleTable->check_ClientTryConnect()<<endl;

    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(2));
        cout << this_thread::get_id() << " wainting main  "<<endl;

        SymboleTable::cv.wait(ul, [symboleTable] { return  !symboleTable->check_ServerRead() && !symboleTable->check_ClientTryConnect();  } );
/*
        cout<<"1"<<endl;
        SymboleTable::cv.wait(ul, [symboleTable] { return  !symboleTable->check_ServerRead();  } ); // shtok to main!!!
        cout<<"2"<<endl;
        SymboleTable::cv.wait(ul, [symboleTable] { return  !symboleTable->check_ClientTryConnect();  } );
        cout<<"3"<<endl;
*/
        cout << this_thread::get_id() << " running main  ";
        cout << " already in main " << endl;
        x++;
        if (x == 50)
        {
            break;
        }
    }
    cout << server.getTable_XML_VAR()->begin()->first << endl;

    return 0;
}