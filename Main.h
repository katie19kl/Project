//
// Created by katie on 21/12/2019.
//

#ifndef PROJECT__MAIN_H_
#define PROJECT__MAIN_H_

#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include "Command.h"
#include "FuncParser.h"
using namespace std;


vector <string> lexer(const string& file_name);

void parser(vector <string> tokens, unordered_map<string, Command*> * fromTape,
    unordered_map<string, Var*> * name_to_var, FuncParser& func_parser);


#endif //PROJECT__MAIN_H_
