//
// Created by katie on 22/12/2019.
//

#ifndef PROJECT__CONDITIONPARSER_H_
#define PROJECT__CONDITIONPARSER_H_

#include <list>
#include <unordered_map>
#include <utility>
#include "Command.h"
#include "Var.h"
using namespace std;

class ConditionParser {
 public:
  ConditionParser() = default;
  bool parseCondition(vector<string> conditionVector, unordered_map<string, Var*> * nameToVar);
  vector<string> createConditionVec(vector<string> tokens, int i);
  vector<string> createCommandsVector(vector<string> tokens, int start, int end);
};

#endif //PROJECT__CONDITIONPARSER_H_
