//
// Created by katie on 21/12/2019.
//

#ifndef PROJECT__MAIN_H_
#define PROJECT__MAIN_H_

#include <list>
#include <string>
#include <unordered_map>
#include "Command.h"
using namespace std;


list <string> lexer(const string& file_name);

unordered_map <string, Command> parser(list<string> tokens);


#endif //PROJECT__MAIN_H_
