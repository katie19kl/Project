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

using namespace std;

int main()
{   
    
    int currIndex = 0;
    vector <string> simFromSimXML = parseXML();// for server constructor
    list <string> tokens = lexer("fly_with_func.txt");// 
    vector <string> tokensKeti(tokens.begin(), tokens.end());

    string connectControlClient = "ConnectCommand";
    string openDataServer = "openDataServer";
    string var = "var";    

    map <string,Command*> fromTape;
    list <Var*> *tableOfProgVar = new list<Var*>();
    
    OpenServerCommand server(simFromSimXML, tableOfProgVar);
    ConnectCommand client(tableOfProgVar,server.getTable_XML_VAR());    
    DefineVarCommand defVar(tableOfProgVar,server.getTable_XML_VAR());

    server.execute(tokensKeti,0);
    defVar.execute(tokensKeti,2);


    fromTape.insert({openDataServer,&server});
    fromTape.insert({connectControlClient, &client});
    fromTape.insert({var,&defVar});


   /* while (currIndex < tokensKeti.size())
    {
        //Command* command = fromTape.at(tokensKeti[currIndex]);
        Command* command = (fromTape.find(tokensKeti[currIndex])->second);
        
        if (command != NULL){
            currIndex += command->execute(tokensKeti,currIndex);
        }
    }    
*/
    return 0;
}