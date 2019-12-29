//
// Created by katie on 28/12/2019.
//

#ifndef PROJECT__SLEEPCOMMAND_H_
#define PROJECT__SLEEPCOMMAND_H_

#include <unordered_map>
#include "Command.h"
#include "Var.h"

class SleepCommand: public Command {
 private:
  unordered_map<string, Var*> * name_to_var;

 public:
  explicit SleepCommand(unordered_map<string, Var*> * nameToVar) {
    this->name_to_var = nameToVar;
  }
  int execute(vector <string> tokens, int index) override;
};

#endif //PROJECT__SLEEPCOMMAND_H_
