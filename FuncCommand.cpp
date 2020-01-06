//
// Created by katie on 28/12/2019.
//

#include "FuncCommand.h"
#include "Ex1.h"

int FuncCommand::execute(vector<string> tokens, int index)
{
  int i = index;
  double value;

  //commands in func scope
  vector<string> commandsVec = this->func_parser->getFunctions().find(tokens[i])->second;
  string parameterName = commandsVec[0];
  commandsVec.erase(commandsVec.begin());
  auto *interpreter = new Interpreter();
  interpreter->setSymbolTable(this->name_to_var);

  i++;
  value = interpreter->interpret(tokens[i])->calculate();

  //add the name of the parameter to the symbol table with
  //a new Var object that would have the value of the parameter
  Var *varForParam = new Var(value, "", parameterName,
                             false, false, false);
  this->name_to_var->insert({parameterName, varForParam});

  unsigned long j = 0;
  while (j < (commandsVec.size()))
  {
    Command *c;

    if (this->fromTape->find(commandsVec[j]) != this->fromTape->end())
    {
      c = this->fromTape->find(commandsVec[j])->second;
      j += c->execute(commandsVec, j);
    }
    else
    {
      //check if it's of the type changeValue -
      //meaning, the current token is a name of a var from the map name_to_var
      if (this->name_to_var->find(commandsVec[j]) != this->name_to_var->end())
      {
        c = this->fromTape->find("changeValue")->second;
        j += c->execute(commandsVec, j);
      }
      else if ((j == (commandsVec.size() - 1) && (commandsVec[j] == "}")))
      {
        break;
      }
      else
      {
        throw "No such command exists!";
      }
    }
  }

  this->name_to_var->erase(parameterName); // remove the name of the parameter("x")
  return 2;
}
