//
// Created by katie on 09/11/2019.
//

#include "Ex1.h"
using namespace std;

UMinus::UMinus(Expression *exp) : UnaryOperator(exp) {
  this->expression = exp;
}

double UMinus::calculate() {
  return this->expression->calculate() * (-1);
}