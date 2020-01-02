//
// Created by katie on 28/12/2019.
//

#include <unordered_map>
#include "Command.h"
#include <string>

#include "FuncParser.h"
using namespace std;

int FuncParser::execute(vector<string> tokens, int index) {
  int i = index, indexSpace = 0, counterOpener = 0, counterCloser = 0;
  vector<string> commands;
  string varName;
  string funcName = tokens[i];

  i++;
  indexSpace = tokens[i].find(' ');
  varName = tokens[i].substr(indexSpace + 1, tokens[i].length() - (indexSpace + 1));
  i++;

  //first token in this vector of commands would be the symbol for the parameter-var "x"
  commands.emplace_back(varName);
  if (tokens[i] == "{") {
    counterOpener++;
    i++;
  }

  while (counterCloser < counterOpener) {
    commands.emplace_back(tokens[i]);
    if (tokens[i] == "{") {
      counterOpener++;
    }
    if (tokens[i] == "}") {
      counterCloser++;
    }
    if (counterCloser == counterOpener) {
      break;
    }
    i++;
  }

  this->functions.insert({funcName, commands});
  return i - index + 1;
}