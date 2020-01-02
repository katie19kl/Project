//
// Created by katie on 23/12/2019.
//

#ifndef PROJECT__CHANGEVALUE_H_
#define PROJECT__CHANGEVALUE_H_

#include <unordered_map>
#include "Command.h"
#include "Expression.h"
#include "Var.h"
#include "SymboleTable.h"

class ChangeValue : public Command
{
private:
  string varName;
  double value{};
  unordered_map<string, Var *> *name_to_var;
  int *client_socket;
  SymboleTable *symboleTable;

public:
  ChangeValue(SymboleTable* smb)
  {
    this->name_to_var = smb->get_NameVar_ToVar();
    this->client_socket = smb->get_ClientSocket();
    this->symboleTable = smb;
  }

  int execute(vector<string> tokens, int index) override;
};

#endif //PROJECT__CHANGEVALUE_H_
