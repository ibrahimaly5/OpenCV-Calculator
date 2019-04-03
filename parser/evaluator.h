#ifndef _EVALUATOR_H
#define _EVALUATOR_H

#include <vector>
#include <string>
#include <complex>
#include <stack>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

class evaluator {
private:
  /* data */
  vector<string> postfix_expr;
  double num1, num2;
  complex<double> complex1, complex2;
  stack<string> expression;
public:
  void start_evaluator(vector<string> input_expr);
  void EvaluateExpr();
  void perform_operation(string operation);
  void print_output();
  bool is_operator(string t);
  bool is_imag(string t);
};

void evaluator::start_evaluator(vector<string> input_expr) {
  num1 = 0;
  num2 = 0;
  postfix_expr = input_expr;
  while (!expression.empty()){
    expression.pop();
  }
}

void evaluator::perform_operation(string operation){
  if (!operation.compare("*")){
    expression.push( to_string(num1*num2) );
  } else if (!operation.compare("+")){
    expression.push( to_string(num1+num2) );
  } else if (!operation.compare("-")){
    expression.push( to_string(num1-num2) );
  } else if (!operation.compare("/")){
    expression.push( to_string(num1/num2) );
  }
}

void evaluator::EvaluateExpr(){
  string element, operation;

  for (int i=0; i<postfix_expr.size(); i++){
    if ( !is_operator(postfix_expr[i]) ){
      expression.push(postfix_expr[i]);
    }else{
      element = expression.top();
      expression.pop();
      num1 = stod(element);
      
      element = expression.top();
      expression.pop();
      num2 = stod(element);
      
      operation = postfix_expr[i];
      perform_operation(operation);
    }
  }
}

bool evaluator::is_operator(string t){
  if (
    t == "*" ||
    t == "/" ||
    t == "+" ||
    t == "-" 
    ) {
      return true;
    }
    return false;
}

bool evaluator::is_imag(string t){
  if (t.find("i")){
    return true;
  }
  return false;
}

void evaluator::print_output(){
  cout << expression.top() << endl;
  expression.pop();
}

#endif