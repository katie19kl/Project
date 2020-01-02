//
// Created by katie on 09/11/2019.
//

#include "Ex1.h"
using namespace std;

UPlus::UPlus(Expression *exp) : UnaryOperator(exp) {
  this->expression = exp;
}

double UPlus::calculate() {
  return this->expression->calculate();
}

