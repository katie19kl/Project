//
// Created by katie on 10/11/2019.
//

#include <stack>
#include <queue>
#include <map>
#include <regex>
#include "Ex1.h"
#include <list>
#include <utility>
#include <vector>
using namespace std;


Interpreter::Interpreter() {
  this->variablesSetter = new unordered_map<string, Var *>(); //creates an empty map
}

Interpreter::~Interpreter() {
  this->variablesSetter->clear();
}

Expression *Interpreter::interpret(string exp) {

  stack<string> operatorStack; //includes the operators symbols, including parenthesis.
  queue<string> outputQueue;   //the numbers
  list<string> tokens = fromStringToTokens(std::move(exp));
  string currOperator;
  list<string> ::iterator it;
  stack<Expression*> reversePolishNot;
  Expression *expLeft, *expRight;

  //The shunting yard algorithm:
  for (it = tokens.begin(); it != tokens.end() ; it++) { //a number or a variable
    if((regex_match(*it, regex("[0-9]+\\.[0-9]+"))) || (regex_match(*it, regex("[0-9]+")))
    || (regex_match(*it, regex("^-[0-9]+"))) || (regex_match(*it, regex("^-[0-9]+\\.[0-9]+")))
    || (regex_match(*it, regex("^[_a-zA-Z]\\w*")))) {
      outputQueue.push(*it);
    } else if((*it == "+") || (*it == "-") || (*it == "*") || (*it == "/")) {
      if((*it == "+") || (*it == "-")) {
        if(!operatorStack.empty()) {
          while((operatorStack.top() == "/") || (operatorStack.top() == "*")) {
            currOperator = operatorStack.top();
            operatorStack.pop();
            outputQueue.push(currOperator);
            if (operatorStack.empty()) {
              break;
            }
          }
          operatorStack.push(*it);
        } else { //The stack is empty
          operatorStack.push(*it);
        }
      } else { //multiplication or division
        operatorStack.push(*it);
      }
    } else if(*it == "(") {
      operatorStack.push(*it);
    } else if(*it == ")") {
      if(!operatorStack.empty()) {
        while(operatorStack.top() != "(") {
          currOperator = operatorStack.top();
          operatorStack.pop();
          outputQueue.push(currOperator);
          if(operatorStack.empty()) {
            break;
          }
        }
        if (!operatorStack.empty()) {
          while((operatorStack.top() == "(") && (!operatorStack.empty())) {
            operatorStack.pop(); //pop and get rid of the '(' ////////////////////
            if (operatorStack.empty()) {
              break;
            }
          }
        }
      } else {
        break;
      }
    }
  }
  while(!operatorStack.empty()) { //moving the rest of the operators to the output queue
    currOperator = operatorStack.top();
    operatorStack.pop();
    outputQueue.push(currOperator);
  }
  //building the calculation tree:
  while(!outputQueue.empty()) {
    if((regex_match(outputQueue.front(), regex("[0-9]+\\.[0-9]+")))
    || (regex_match(outputQueue.front(), regex("[0-9]+")))
    || (regex_match(outputQueue.front(), regex("[-][0-9]+")))
    || (regex_match(outputQueue.front(), regex("[-][0-9]+\\.[0-9]+")))) { //a number
      reversePolishNot.push(new Value(stod(outputQueue.front())));
      outputQueue.pop(); //remove the number
    } else if(regex_match(outputQueue.front(), regex("^[_a-zA-Z]\\w*"))) { //a variable
      reversePolishNot.push(new Value(this->variablesSetter->find(outputQueue.front())->second->getValue()));
      outputQueue.pop(); //remove the variable string
    } else { //an operator
      if(outputQueue.front() == "+") {
        expRight = reversePolishNot.top();
        reversePolishNot.pop();
        expLeft = reversePolishNot.top();
        reversePolishNot.pop();
        reversePolishNot.push(new Plus(expLeft, expRight));
        outputQueue.pop(); //remove the "+" operator
      } else if(outputQueue.front() == "-") {
        expRight = reversePolishNot.top();
        reversePolishNot.pop();
        expLeft = reversePolishNot.top();
        reversePolishNot.pop();
        reversePolishNot.push(new Minus(expLeft, expRight));
        outputQueue.pop(); //remove the "-" operator
      } else if(outputQueue.front() == "*") {
        expRight = reversePolishNot.top();
        reversePolishNot.pop();
        expLeft = reversePolishNot.top();
        reversePolishNot.pop();
        reversePolishNot.push(new Mul(expLeft, expRight));
        outputQueue.pop(); //remove the "*" operator
      } else if(outputQueue.front() == "/") {
        expRight = reversePolishNot.top();
        reversePolishNot.pop();
        expLeft = reversePolishNot.top();
        reversePolishNot.pop();
        reversePolishNot.push(new Div(expLeft, expRight));
        outputQueue.pop(); //remove the "/" operator
      }
    }
  }
  return reversePolishNot.top();
} //end of method

list<string> Interpreter::fromStringToTokens(string str) {
  list<string> tokens;
  list<string> ::iterator it;
  int counterOpener = 0, counterCloser = 0;
  unsigned long j;

  for (unsigned long i = 0; i < str.length(); i++) {
    if ((i == 0) && (regex_match(string(1, str[i]), regex("^-")))
    && (regex_match(string(1, str[i + 1]), regex("[0-9]")))) {
      j = i + 1;
      while((regex_match(string(1, str[j]), regex("[0-9]")))
          || (regex_match(string(1, str[j]), regex("[.]")))) {
        j++;
      }
      tokens.emplace_back(str.substr(i, j - i));
      i = j - 1;
    } else if ((regex_match(string(1, str[i]), regex("[0-9]")))) { //a number
      j = i + 1;
      while((regex_match(string(1, str[j]), regex("[0-9]")))
          || (regex_match(string(1, str[j]), regex("[.]")))) {
        j++;
      }
      if((j - i) == 1) {
        tokens.emplace_back(string(1, str[i]));
        i = j - 1;
      } else { //a number with more than 1 char
        tokens.emplace_back(str.substr(i, j - i));
        i = j - 1;
      }
    } else if(str[i] == '(') {
      tokens.emplace_back(string(1, str[i]));
    } else if(str[i] == ')') {
      tokens.emplace_back(string(1, str[i]));
    } else if((str[i] == '*') || (str[i] == '/')) {
      if((tokens.back() == "+") || (tokens.back() == "-") || (tokens.back() == "*")
          || (tokens.back() == "/")) { //when the last token inserted was an operator as well
        throw "bad input";
      } else {
        tokens.emplace_back(string(1, str[i]));
      }
    } else if((str[i] == '+') || ((str[i] == '-'))) {
      if(!tokens.empty()) {
        if((tokens.back() == "+") || (tokens.back() == "-") || (tokens.back() == "*")
            || (tokens.back() == "/")) { //when the last token inserted was an operator as well
          throw "bad input";
        } else {
          if((unsigned)str.length() > (i + 1)) {
            if((tokens.back() == "(") || ((str[i + 1] == '(') && (str[i - 1] == '('))) { //unary operator
              if(str[i] == '+') {
                tokens.emplace_back("1");
                tokens.emplace_back("*");
              } else if(str[i] == '-') {
                tokens.emplace_back("-1");
                tokens.emplace_back("*");
              }
            } else { //Binary operator
              tokens.emplace_back(string(1, str[i]));
            }
          } else {
            throw "bad input"; //the last char in the string is an operator - invalid input
          }
        }
      } else { //the unary + or - is the first char in the string
        if((unsigned)str.length() > (i + 1)) {
          if(str[i + 1] == '(') { //unary operator
            if(str[i] == '+') {
              tokens.emplace_back("1");
              tokens.emplace_back("*");
            } else if(str[i] == '-') {
              tokens.emplace_back("-1");
              tokens.emplace_back("*");
            }
          } else { //Binary operator
            tokens.emplace_back(string(1, str[i]));
          }
        } else {
          throw "bad input"; //the last char in the string is an operator - invalid input
        }
      }
    } else if((regex_match(string(1, str[i]), regex("[a-z]")))
        || (regex_match(string(1, str[i]), regex("[_]")))) { //looking for variables
      j = i;
      while((regex_match(string(1, str[j]), regex("[a-zA-z]")))
          || (regex_match(string(1, str[j]), regex("[_]")))
          || (regex_match(string(1, str[j]), regex("\\d")))) {
        j++;
      }
      if((j - i) == 1) {
        tokens.emplace_back(string(1, str[i]));
        i = j - 1;
        if(this->variablesSetter->find(tokens.back()) == this->variablesSetter->end()) {
          throw "bad input"; // the variable has not been set with a value
        }
      } else { //a number with more than 1 char
        tokens.emplace_back(str.substr(i, j - i));
        i = j - 1;
        if(this->variablesSetter->find(tokens.back()) == this->variablesSetter->end()) {
          throw "bad input"; // the variable has not been set with a value
        }
      }
    } else {
      throw "bad input"; //any other char should not be in the expression's string
    }
  } //end of for loop
  for (it = tokens.begin(); it != tokens.end() ; it++) {
    if(*it == "(") {
      counterOpener++;
    } else if(*it == ")") {
      counterCloser++;
    }
  }
  if(counterOpener != counterCloser) {
    throw "bad input"; //the number of each type of parenthesis is different - therefore it's invalid input
  }
  return tokens;
}

void Interpreter::setSymbolTable(unordered_map<std::string, Var *> *simToVar) {
  this->variablesSetter = simToVar;
}