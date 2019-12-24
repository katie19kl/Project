//
// Created by katie on 21/12/2019.
//

#ifndef PROJECT__LEXER_H_
#define PROJECT__LEXER_H_

#include <vector>
#include <string>
#include <unordered_map>
#include "Command.h"
#include <list>
using namespace std;


vector<string> lexer(const string& file_name);

unordered_map <string, Command> parser(list<string> tokens);


#endif //PROJECT__MAIN_H_
