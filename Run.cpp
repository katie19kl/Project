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

using namespace std;


int main()
{   /*
    double num;
    string da;
    da.push_back('-');
    da.push_back('9');
    da.push_back('.');
    da.push_back('4');
    da.push_back('1');
    da.push_back('1');
    da.push_back('9');
    da.push_back('6');
    da.push_back('8');
    num = stold(da);
    double gr = num;
    double gr1 = num*10 + 2;
    cout<<num<<endl;*/
    vector <string> simFromSimXML = parseXML();

    OpenServerCommand server(simFromSimXML);
    ConnectCommand client;
    
    list <string> tokens = lexer("fly_with_func.txt");

    vector <string> tokensKeti(tokens.begin(), tokens.end());

    server.execute(tokensKeti);


    return 0;
}