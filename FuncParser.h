//
// Created by katie on 28/12/2019.
//

#ifndef PROJECT__FUNCPARSER_H_
#define PROJECT__FUNCPARSER_H_

#include <unordered_map>
#include "Command.h"


class FuncParser: public Command {
 private:
  unordered_map<string, vector<string>> functions;
 public:
  FuncParser() {
    this->functions = unordered_map<string, vector<string>>();
  }
  int execute(vector <string> tokens, int index) override;

  unordered_map<string, vector<string>> getFunctions() {
    return this->functions;
  }
};

#endif //PROJECT__FUNCPARSER_H_
