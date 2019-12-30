//
// Created by katie on 23/12/2019.
//

#include <sstream>
#include "ChangeValue.h"
#include "Ex1.h"
#include <sys/socket.h>
#include <regex>
#include <iostream>
#include "SymboleTable.h"

using namespace std;



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

  interpreter->setSymbolTable(this->name_to_var); // not mine

  //interpret the expression and calculate it.
  this->value = interpreter->interpret(updatedExp)->calculate();

  this->name_to_var->find(this->varName)->second->setValue(this->value); //put the value into the symbol table

  if (this->name_to_var->find(this->varName)->second->bindINServer()) { //to be changed in simulator

    Var* var = this->name_to_var->find(this->varName)->second;
    string msg = "set " + var->getSim() + " " + to_string(this->value) + "\r\n";

    //we block the server, send the data to the simulator,
    //and then unblock the server

    this->symboleTable->set_ClientSend(true);
    cout<<msg<<"to send"<<endl;
    int is_send = send(*(this->client_socket), msg.c_str(), msg.length(), 0);  // ++ BLOCKING CALL
    this->symboleTable->set_ClientSend(false);
    SymboleTable::cv.notify_all();


/*    if (is_sent == -1) {
      throw "Error - cannot send the message to the simulator";
    }*/
  }

  return 3; //updating the index:
}