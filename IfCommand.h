//
// Created by katie on 22/12/2019.
//

#ifndef PROJECT__IFCOMMAND_H_
#define PROJECT__IFCOMMAND_H_

using namespace std;
#include <string>
#include <utility>
#include <vector>
#include "ConditionParser.h"
#include "FuncParser.h"
#include "SymboleTable.h"

class IfCommand: public Command {
 private:
  unordered_map<string, Command*> * fromTape;
  unordered_map<string, Var*> * name_to_var;
  FuncParser * func_parser;

 public:
  IfCommand(unordered_map<string, Command *> *from_tape_map,
            SymboleTable * symbol_table, FuncParser* func_parser1) {
    this->fromTape = from_tape_map;
    this->name_to_var = symbol_table->get_NameVar_ToVar();
    this->func_parser = func_parser1;
  }

  int execute(vector <string> tokens, int index) override;
};

#endif //PROJECT__IFCOMMAND_H_
