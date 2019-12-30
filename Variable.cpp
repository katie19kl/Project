//
// Created by katie on 09/11/2019.
//

#include <utility>
#include "Ex1.h"
using namespace std;


Variable::Variable(string nameVar, double num) {
  this->name = std::move(nameVar);
  this->value = num;
}

double Variable::calculate() {
  return this->value;
}

Variable &Variable::operator++() {
  this->value = this->value + 1;
  return *this;
}

Variable &Variable::operator--() {
  this->value = this->value - 1;
  return *this;
}

Variable &Variable::operator+=(double num) {
  this->value = this->value + num;
  return *this;
}

Variable &Variable::operator-=(double num) {
  this->value = this->value - num;
  return *this;
}

Variable &Variable::operator++(int) {
  this->value = this->value + 1;
  return *this;
}

Variable &Variable::operator--(int) {
  this->value = this->value - 1;
  return *this;
}
Variable::Variable(Variable *p_variable) {
  this->name = p_variable->name;
  this->value = p_variable->value;
}
