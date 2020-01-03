//
// Created by katie on 09/11/2019.
//

#include "Ex1.h"
using namespace std;


Div::Div(Expression *leftExp, Expression *rightExp) : BinaryOperator(leftExp, rightExp) {
  this->left = leftExp;
  this->right = rightExp;
}

double Div::calculate() {
  if(this->right->calculate() != 0) {
    return this->left->calculate() / this->right->calculate();
  } else {
    throw "bad input";
  }
}