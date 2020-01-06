//
// Created by katie on 22/12/2019.
//

#include <iostream>
#include "LoopCommand.h"

int LoopCommand::execute(vector<string> tokens, int index) {
  int k = index, j;
  vector<string> conditionVector, commandsVec;
  bool isTrue;

  k++; //the recent k was on "while"
  while (tokens[k] != "{") {
    k++;
  }
  //k is on "{"

  ConditionParser condition_parser;

  conditionVector = condition_parser.createConditionVec(tokens, index);
  isTrue = condition_parser.parseCondition(conditionVector, this->name_to_var);

  j = k;
  while (tokens[j] != "}") {
    j++;
  }
  // j is on "}"

  if (!isTrue) {
    return j - index + 1;
  } else {
    k++; //k is now on the first token of the first command in the if-scope

    //creating vector of the commands in the scope
    commandsVec = condition_parser.createCommandsVector(tokens, k, j);

    do {
      unsigned long i = 0;
      while (i < commandsVec.size()) {
        Command *c;

        if (this->fromTape->find(commandsVec[i]) != this->fromTape->end()) {
          c = fromTape->find(commandsVec[i])->second;
          i += c->execute(commandsVec, i);
        } else {

          //check if it's of the type changeValue -
          //meaning, the current token is a name of a var from the map name_to_var
          if ((this->name_to_var->find(commandsVec[i]) != this->name_to_var->end()) && (commandsVec[i + 1] == "=")) {
            c = this->fromTape->find("changeValue")->second;
            i += c->execute(commandsVec, i);

            //func call - execution
          } else if (this->func_parser->getFunctions().find(commandsVec[i]) != this->func_parser->getFunctions().end()) {
            c = this->fromTape->find("funcCommand")->second;
            i += c->execute(commandsVec, i);

          } else {
            throw "no such command exists!";
          }
        }
      }
    } while (condition_parser.parseCondition(conditionVector, this->name_to_var));
    return j - index + 1;
  }
}