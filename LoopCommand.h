//
// Created by katie on 22/12/2019.
//

#ifndef PROJECT__LOOPCOMMAND_H_
#define PROJECT__LOOPCOMMAND_H_

using namespace std;
#include <utility>

#include "ConditionParser.h"
#include "FuncParser.h"
#include "SymboleTable.h"

class LoopCommand: public Command {
 private:
  unordered_map<string, Command*> * fromTape;
  unordered_map<string, Var*> * name_to_var;
  FuncParser * func_parser;

 public:
  LoopCommand(unordered_map<string, Command *> *from_tape_map,
              SymboleTable * symbol_table,
              FuncParser * func_parser1) {
    this->fromTape = from_tape_map;
    this->name_to_var = symbol_table->get_NameVar_ToVar();
    this->func_parser = func_parser1;
  }

  int execute(vector <string> tokens, int index) override;
};

#endif //PROJECT__LOOPCOMMAND_H_
