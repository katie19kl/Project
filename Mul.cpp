//
// Created by katie on 09/11/2019.
//

#include "Ex1.h"
using namespace std;


Mul::Mul(Expression *leftExp, Expression *rightExp) : BinaryOperator(leftExp, rightExp) {
  this->left = leftExp;
  this->right = rightExp;
}

double Mul::calculate() {
  return this->left->calculate() * this->right->calculate();
}
