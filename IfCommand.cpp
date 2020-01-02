//
// Created by katie on 22/12/2019.
//

#include <iostream>
#include "IfCommand.h"
using namespace std;


int IfCommand::execute(vector<string> tokens, int index) {
  int k = index, j;
  vector<string> conditionVec, commandsVec;
  bool isTrue;

  k++; //was on "if"
  while (tokens[k] != "{") {
    k++;
  }
  //k is on "{"

  ConditionParser condition_parser;

  conditionVec = condition_parser.createConditionVec(tokens , index);
  isTrue = condition_parser.parseCondition(conditionVec, this->name_to_var);

  j = k;
  while (tokens[j] != "}") {
    j++;
  }
  // j is on "}"

  if (!isTrue) {
    return j - index + 1; //check
  } else {
    k++; //k is now on the first token of the first command in the if-scope

    commandsVec = condition_parser.createCommandsVector(tokens, k, j);

    int i = 0;
    while (i < commandsVec.size()) {
      Command* c;

      if (this->fromTape->find(commandsVec[i]) != this->fromTape->end()) {
        c = this->fromTape->find(commandsVec[i])->second;
        i += c->execute(commandsVec, i);

      } else {

        //check if it's of the type changeValue -
        //meaning, the current token is a name of a var from the map name_to_var
        if ((this->name_to_var->find(commandsVec[i]) != this->name_to_var->end()) && (commandsVec[i + 1] == "=")) {
          c = this->fromTape->find("changeValue")->second;
          i += c->execute(commandsVec, i);

          //func call - execution
        } else if (this->func_parser.getFunctions().find(commandsVec[i]) != this->func_parser.getFunctions().end()) {
          c = this->fromTape->find("funcCommand")->second;
          i += c->execute(commandsVec, i);

        } else {
          throw "no such command exists!";
        }
      }
    }
    return j - index + 1; //check
  }
}