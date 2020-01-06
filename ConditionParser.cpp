//
// Created by katie on 22/12/2019.
//

#include <regex>
#include <iostream>
#include "ConditionParser.h"
#include "Ex1.h"


bool ConditionParser::parseCondition(vector<string> conditionVec,
    unordered_map<string, Var*> * nameToVar) {
  unsigned long j = 0;
  string leftExp = "", rightExp = "";
  string comparison;
  auto* interpreter = new Interpreter();
  double leftVal = 0, rightVal = 0;

  while((conditionVec[j] != "<") && (conditionVec[j] != ">") && (conditionVec[j] != "<=")
      && (conditionVec[j] != ">=") && (conditionVec[j] != "==") && (conditionVec[j] != "!=")) {
    leftExp += conditionVec[j];
    j++;
  }

  comparison = conditionVec[j]; // would be one of: <,>,<=,>=,==,!=
  j++;

  for (; j < conditionVec.size(); j++) {
    rightExp += conditionVec[j];
  }

  interpreter->setSymbolTable(nameToVar);
  leftVal = interpreter->interpret(leftExp)->calculate();
  rightVal = interpreter->interpret(rightExp)->calculate();

  if (comparison == "<") {
    return leftVal < rightVal;
  } else if (comparison == ">") {
    return leftVal > rightVal;
  } else if (comparison == "<=") {
    return leftVal <= rightVal;
  } else if (comparison == ">=") {
    return leftVal >= rightVal;
  } else if (comparison == "==") {
    return leftVal == rightVal;
  } else if (comparison == "!=") {
    return leftVal != rightVal;
  }
  return false;
}

/* adds each token that has to do with the condition to a vector */
vector<string> ConditionParser::createConditionVec(vector<string> tokens, int i) {
  vector<string> condition;
  int k = i;

  k++; //the recent k was on "if"/"while"
  while (tokens[k] != "{") {
    condition.emplace_back(tokens[k]);
    k++;
  }
  return condition;
}

/* adds tokens that define the commands in the scope to a vector */
vector<string> ConditionParser::createCommandsVector(vector<string> tokens, int start, int end) {
  vector<string> commands;

  //creating vector of the commands in the scope
  for (int i = start; i <= end - 1; i++) {
    commands.emplace_back(tokens[i]);
  }

  return commands;
}
