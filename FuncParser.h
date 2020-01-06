#ifndef FuncParser_H_
#define FuncParser_H_

#include <unordered_map>
#include "Command.h"
#include <string>

using namespace std;

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
