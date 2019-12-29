//
// Created by katie on 28/12/2019.
//

#include <thread>
#include <iostream>
#include "SleepCommand.h"
#include "Ex1.h"

int SleepCommand::execute(vector<string> tokens, int index) {
  auto* interpreter = new Interpreter;
  interpreter->setSymbolTable(this->name_to_var);
  double value = interpreter->interpret(tokens[index + 1])->calculate();
  int val = (int) value;

  this_thread::sleep_for(chrono::milliseconds((chrono::duration<int64_t, milli>) val));

  return 2;
}
