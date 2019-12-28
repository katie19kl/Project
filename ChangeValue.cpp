//
// Created by katie on 23/12/2019.
//

#include <sstream>
#include "ChangeValue.h"
#include "Ex1.h"
#include <sys/socket.h>
#include <regex>
#include <iostream>

ChangeValue::ChangeValue(unordered_map<std::string, Var *> *nameToVar, int socket_of_client) {
  this->name_to_var = nameToVar;
  this->client_socket = socket_of_client;
}

int ChangeValue::execute(vector<string> tokens, int index) {
  this->varName = tokens[index];
  string expression = tokens[index + 2];
  string intermediate;
  string preUpdated = "", updatedExp = "";


  //checking if there's an expression of the type: var = -var1
  if ((expression[0] == '-') && (regex_match(string(1, expression[1]),regex("^[_a-zA-Z]\\w*")))) {
    int i = 1;
    while (regex_match(string(1, expression[i]),regex("^[_a-zA-Z]\\w*"))) {
      i++;
    }
    i--;
    preUpdated = expression.substr(0, 1) + "(" +
        expression.substr(1, i) + ")" + expression.substr(i + 1, expression.length() - (i + 1));
  } else {
    preUpdated = expression;
  }

  stringstream check1(preUpdated);
  while(getline(check1, intermediate, ' ')) { //tokenizing according to ' '
    updatedExp += intermediate; //creating the exp without spaces
  }

  auto* interpreter = new Interpreter;

  interpreter->setSymbolTable(this->name_to_var);

  //interpret the expression and calculate it.
  this->value = interpreter->interpret(updatedExp)->calculate();

  this->name_to_var->find(this->varName)->second->setValue(this->value); //put the value into the symbol table

  if (this->name_to_var->find(this->varName)->second->bindINServer()) { //to be changed in simulator

    Var* var = this->name_to_var->find(this->varName)->second;
    string msg = "set " + var->getSim() + " " + to_string(this->value) + "\r\n";

    //we block the server, send the data to the simulator,
    //and then unblock the server

    /*// client_socket sends the value to be updated in the simulator
    int is_sent = send(this->client_socket, msg.c_str(), msg.length(), 0);
    if (is_sent == -1) {
      throw "Error - cannot send the message to the simulator";
    }*/
  }

  return 3; //updating the index:
}