//
// Created by katie on 23/12/2019.
//

#ifndef PROJECT__CHANGEVALUE_H_
#define PROJECT__CHANGEVALUE_H_

#include <unordered_map>
#include "Command.h"
#include "Expression.h"
#include "Var.h"

class ChangeValue: public Command {
 private:
  string varName;
  double value{};
  unordered_map<string, Var *> *name_to_var;
  int client_socket;

 public:
  ChangeValue(unordered_map<string, Var*>* simToVar, int socket_of_client);
  int execute(vector <string> tokens, int index) override;
};

#endif //PROJECT__CHANGEVALUE_H_
