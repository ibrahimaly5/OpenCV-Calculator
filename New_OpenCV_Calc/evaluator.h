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


// template <class T>
// class evaluation_list{

// public:
//   void print_hello();
//   void insert(const T& item);

// private:
//   vector<T> numbers;
// };

// void evaluation_list::insert(const T& item){
//   numbers.push_back(item);
// }

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
  void evaluate_imaginary(string s1, string s2, string operation);
  void put_imaginary(string s, complex<double> &number);
  bool is_operator(string t);
  bool is_imag(string t);
  string send_result();

};

void evaluator::start_evaluator(vector<string> input_expr) {
  num1 = 0;
  num2 = 0;
  postfix_expr = input_expr;
  while (!expression.empty()){
    expression.pop();
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
  if (!t.substr(t.size()-1,1).compare("i")){
    return true;
  }
  return false;
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

void evaluator::put_imaginary(string s, complex<double> &number){
  string num_string;
  for (int i=0; i<s.size(); i++){
    if ( s[i] == '+' || s[i] == '-'){
      number.real( stod( num_string ) );
      // cout << "what is this doing " << num_string << endl;
      num_string = s[i];
    } else if (s[i] == 'i'){
      number.imag( stod( num_string ) );
      // cout << "oh its this " << num_string << endl;
    } else {
      num_string += s[i];
    }
  }
}

void evaluator::evaluate_imaginary(string s1, string s2, string operation){
  complex1 = (0,0);
  complex2 = (0,0);
  // cout << "here " << s1 << " " << s2 << endl;
  string sign;
  if (is_imag(s1)){
    put_imaginary(s1, complex1);
    // complex1.imag( stod( s1.substr(0,s1.size()-1) ) );
  } else{
    complex1.real ( stod(s1) );
  }

  if (is_imag(s2)){
    put_imaginary(s2, complex2);
    // cout << complex2 << endl;  
    // complex2.imag( stod( s2.substr(0,s2.size()-1) ) );
  } else{
    complex2.real ( stod(s2) );
  }
  // cout << "here " << complex1 << " " << complex2 << endl;

  if (!operation.compare("*")){
    complex1 *= complex2;
  } else if (!operation.compare("+")){
    complex1 += complex2;
  } else if (!operation.compare("-")){
    complex1 = complex2 - complex1;
  } else if (!operation.compare("/")){
    complex1 = complex2 / complex1;
  }
  if (complex1.real() == 0){
    expression.push( to_string(complex1.imag()) + "i" );
  } else if (complex1.imag() == 0){
    expression.push( to_string(complex1.real()) );
  } else{
    if (complex1.imag()>0){
      sign = "+";
      expression.push( to_string(complex1.real()) + sign + to_string(complex1.imag()) + "i" );
    } else {
      expression.push( to_string(complex1.real()) + to_string(complex1.imag()) + "i" );
    }
    // cout << "after all: " << expression.top() << endl;
  }
  
}

void evaluator::EvaluateExpr(){
  string element1, element2, operation;

  for (int i=0; i<postfix_expr.size(); i++){
    if ( !is_operator(postfix_expr[i]) ){
      expression.push(postfix_expr[i]);
    }else{
      element1 = expression.top();
      expression.pop();
      
      element2 = expression.top();
      expression.pop();

      operation = postfix_expr[i];

      if(is_imag(element1) || is_imag(element2)){
        evaluate_imaginary(element1, element2, operation);
      } else{

        num1 = stod(element2);
        num2 = stod(element1);
        cout << num1 << " " << num2 << endl;
        
        perform_operation(operation);
      }
    }
  }
}

void evaluator::print_output(){
  cout << expression.top() << endl;
  expression.pop();
}

string evaluator::send_result() {
  return expression.top();
}

#endif
