//
// Created by katie on 08/11/2019.
//

#ifndef EX1__EX1_H_
#define EX1__EX1_H_

#include <string>
#include <map>
#include <list>
#include "Expression.h"
using namespace std;

class Value: public Expression {

 private:
  double val;

 public:
  explicit Value(double value);
  double calculate() override;
};

class Variable: public Expression {

 private:
  string name;
  double value;

 public:
  Variable(string nameVar, double num);
  double calculate() override;
  Variable& operator++();
  Variable& operator--();
  Variable& operator+=(double num);
  Variable& operator-=(double num);
  Variable& operator++(int);
  Variable& operator--(int);

  string getName() {
    return this->name;
  }

  double getValue() {
    return this->value;
  }
  Variable(Variable *p_variable);
};

class BinaryOperator: public Expression {

 protected:
  Expression* left;
  Expression* right;

 public:
  BinaryOperator(Expression* leftExp, Expression* rightExp);
  ~BinaryOperator() override;
  virtual double calculate() = 0;

};

class UnaryOperator: public Expression {

 protected:
  Expression* expression;

 public:
  explicit UnaryOperator(Expression* exp);
  ~UnaryOperator() override;
  virtual double calculate() = 0;
};

class Plus: public BinaryOperator {

 public:
  Plus(Expression* leftExp, Expression* rightExp);
  double calculate() override;
};

class Minus: public BinaryOperator {

 public:
  Minus(Expression* leftExp, Expression* rightExp);
  double calculate() override;
};

class Mul: public BinaryOperator {

 public:
  Mul(Expression* leftExp, Expression* rightExp);
  double calculate() override;
};

class Div: public BinaryOperator {

 public:
  Div(Expression* leftExp, Expression* rightExp);
  double calculate() override;
};

class UPlus: public UnaryOperator {

 public:
  UPlus(Expression* exp);
  double calculate() override;
};

class UMinus: public UnaryOperator {

 public:
  UMinus(Expression* exp);
  double calculate() override;
};

class Interpreter {
 private:
  map<string, double> variablesSetter;

 public:
  Interpreter();
  ~Interpreter();
  Expression* interpret(string exp);
  void setVariables(const string& exp);
  list<Variable> fromStringToVariables(const string& str);
  list<string> fromStringToTokens(string str);
};
#endif //EX1__EX1_H_