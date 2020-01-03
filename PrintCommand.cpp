//
// Created by katie on 28/12/2019.
//

#include <iostream>
#include <sstream>
#include "PrintCommand.h"
#include "Ex1.h"

int PrintCommand::execute(vector<string> tokens, int index) {
  string param = tokens[index + 1];
  if ((param[0] == param[param.length() - 1]) && (param[0] == '"')) { //it's a string
    cout << param.substr(1, param.length() - 2) << endl;

  } else { //an expression
    auto* interpreter = new Interpreter();
    interpreter->setSymbolTable(this->name_to_var);
    double value;
    string intermediate, updatedExp;

    stringstream check1(param);
    while(getline(check1, intermediate, ' ')) { //tokenizing according to ' '
      updatedExp += intermediate; //creating the exp without spaces
    }

    value = interpreter->interpret(updatedExp)->calculate();
    cout << value << endl;
  }

  return 2;
}
