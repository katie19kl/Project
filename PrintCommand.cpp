//
// Created by katie on 28/12/2019.
//

#include <iostream>
#include "PrintCommand.h"
#include "Ex1.h"

int PrintCommand::execute(vector<string> tokens, int index) {
  auto* interpreter = new Interpreter();
  interpreter->setSymbolTable(this->name_to_var);
  double value;

  try {
    value = interpreter->interpret(tokens[index + 1])->calculate();
    cout << value << endl;
  } catch (const char * e) {
    cout << tokens[index + 1] << endl;
  }

  return 2;
}
