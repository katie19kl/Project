//
// Created by katie on 28/12/2019.
//

#ifndef PROJECT__FUNCCOMMAND_H_
#define PROJECT__FUNCCOMMAND_H_

#include <unordered_map>
#include "Command.h"
#include "Var.h"
#include "FuncParser.h"

class FuncCommand: public Command {
 private:
  unordered_map<string, Var*> * name_to_var;
  unordered_map<string, Command*> * fromTape;
  FuncParser& func_parser;
 public:
  FuncCommand(unordered_map<string, Var *> *nameToVar,
              unordered_map<string, Command *> *from_tape,
              FuncParser &func_parser1) : func_parser(func_parser1) {
    this->name_to_var = nameToVar;
    this->fromTape = from_tape;
    this->func_parser = func_parser1;
  }
  int execute(vector<string> tokens, int index) override;
};

#endif //PROJECT__FUNCCOMMAND_H_
