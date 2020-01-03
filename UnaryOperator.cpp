//
// Created by katie on 09/11/2019.
//

#include "Ex1.h"
using namespace std;

UnaryOperator::UnaryOperator(Expression* exp) {
  this->expression = exp;
}

UnaryOperator::~UnaryOperator() {
  if(this->expression != nullptr) {
    delete(this->expression);
  }
}
