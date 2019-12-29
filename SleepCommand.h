//
// Created by katie on 28/12/2019.
//

#ifndef PROJECT__SLEEPCOMMAND_H_
#define PROJECT__SLEEPCOMMAND_H_

#include <unordered_map>
#include "Command.h"
#include "Var.h"
#include "SymboleTable.h"

class SleepCommand: public Command {
 private:
  unordered_map<string, Var*> * name_to_var;

 public:
  explicit SleepCommand(SymboleTable symbol_table) {
    this->name_to_var = symbol_table.get_NameVar_ToVar();
  }
  int execute(vector <string> tokens, int index) override;
};

#endif //PROJECT__SLEEPCOMMAND_H_
