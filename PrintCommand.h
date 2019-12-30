//
// Created by katie on 28/12/2019.
//

#ifndef PROJECT__PRINTCOMMAND_H_
#define PROJECT__PRINTCOMMAND_H_

#include <unordered_map>
#include "Command.h"
#include "Var.h"
#include "SymboleTable.h"
#include <string>

using namespace std;

class PrintCommand: public Command {
 private:
  unordered_map<string, Var*> * name_to_var;

 public:
  explicit PrintCommand(SymboleTable* symbol_table) {
    this->name_to_var = symbol_table->get_NameVar_ToVar();
  }
  int execute(vector <string> tokens, int index) override;

};

#endif //PROJECT__PRINTCOMMAND_H_
