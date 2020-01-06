#ifndef _RUN_H
#define _RUN_H

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

void parser(vector<string>, unordered_map<string, Command *>,
            unordered_map<string, Var *>, FuncParser);

void run(string);

#endif