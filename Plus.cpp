//
// Created by katie on 09/11/2019.
//

#include "Ex1.h"
using namespace std;


Plus::Plus(Expression *leftExp, Expression *rightExp) : BinaryOperator(leftExp, rightExp) {
  this->left = leftExp;
  this->right = rightExp;
}

double Plus::calculate() {
  return this->left->calculate() + this->right->calculate();
}
