//
// Created by katie on 09/11/2019.
//

#include "Ex1.h"
using namespace std;

BinaryOperator::BinaryOperator(Expression *leftExp, Expression *rightExp) {
  this->left = leftExp;
  this->right = rightExp;
}

BinaryOperator::~BinaryOperator() {
  if(this->left != nullptr) {
    delete(this->left);
  }
  if(this->right != nullptr) {
    delete(this->right);
  }
}
