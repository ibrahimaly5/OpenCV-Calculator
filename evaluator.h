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
  
  //postfix expression vector
  vector<string> postfix_expr;
  
  //doubles and complex numbers for handling evaluations
  double num1, num2;
  complex<double> complex1, complex2;
  
  //stack to handle the evaluation of the postfix expression
  stack<string> expression;

public:
  //get the postfix expression and clear the other variables
  void start_evaluator(vector<string> input_expr);

  //evaluate the postfix expression
  void EvaluateExpr();

  //perform an operation on two real numbers and 
  //and save the result again in the expression stack
  void perform_operation(string operation);

  //print the output of the expression
  void print_output();

  //perform an operation on two numbers, one is imaginary.
  //save the result again in the expression stack
  void evaluate_imaginary(string s1, string s2, string operation);

  //parse the string and save the value in the input complex number
  void put_imaginary(string s, complex<double> &number);

  //check if the string is an operator
  bool is_operator(string t);

  //check if the string is an imaginary number
  bool is_imag(string t);
  
  //return the result of evaluating the expression
  string send_result();

};

//get the postfix expression and clear the other variables
void evaluator::start_evaluator(vector<string> input_expr) {
  num1 = 0;
  num2 = 0;
  postfix_expr = input_expr;
  while (!expression.empty()){
    expression.pop();
  }
}

//check if the string is an operator
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

//check if the string is an imaginary number
bool evaluator::is_imag(string t){
  if (!t.substr(t.size()-1,1).compare("i")){
    return true;
  }
  return false;
}

//perform an operation on two real numbers and 
//and save the result again in the expression stack
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

//parse the string and save the value in the input complex number
void evaluator::put_imaginary(string s, complex<double> &number){
  string num_string;
  for (int i=0; i<s.size(); i++){
    //if a + or - sign is found, convert the num_string string
    //to a double and save it in the real component of the complex number
    if ( s[i] == '+' || s[i] == '-'){
      number.real( stod( num_string ) );
      num_string = s[i];
    } else if (s[i] == 'i'){
      //if an "i" is found, save the num_string in the 
      //complex component of the complex number 
      number.imag( stod( num_string ) );
    } else {
      //Otherwise, concatenate the num_string with the element
      num_string += s[i];
    }
  }
}

//perform an operation on two numbers, one is imaginary.
//save the result again in the expression stack
void evaluator::evaluate_imaginary(string s1, string s2, string operation){
  complex1 = (0,0);
  complex2 = (0,0);
  string sign;
  //if the first string is an imaginary number, add the complex component
  //to complex1
  if (is_imag(s1)){
    put_imaginary(s1, complex1);
  } else{
    //Otherwise, add the real component to complex1, with a complex component of 0
    complex1.real ( stod(s1) );
  }


  //Do the former operations on the second string and complex2
  if (is_imag(s2)){
    put_imaginary(s2, complex2);  
  } else{
    complex2.real ( stod(s2) );
  }

  //Compute the operation
  if (!operation.compare("*")){
    complex1 *= complex2;
  } else if (!operation.compare("+")){
    complex1 += complex2;
  } else if (!operation.compare("-")){
    complex1 = complex2 - complex1;
  } else if (!operation.compare("/")){
    complex1 = complex2 / complex1;
  }
  
  //Only push the non-zero part.
  //Otherwise, push the complex number as a "x+yi" string 
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
  }
  
}

//evaluate the postfix expression
void evaluator::EvaluateExpr(){
  string element1, element2, operation;
  
  //loop through the postfix vector
  for (int i=0; i<postfix_expr.size(); i++){
    //if the element is not an operator, push it to
    //the expression stack
    if ( !is_operator(postfix_expr[i]) ){
      expression.push(postfix_expr[i]);
    }else{
      //Otherwise, pop the topmost 2 elements from
      //the expression stack
      element1 = expression.top();
      expression.pop();
      
      element2 = expression.top();
      expression.pop();

      //get the operation
      operation = postfix_expr[i];

      //if either of the two elements is an imaginary, use 
      //the evaluate_imaginary method.
      if(is_imag(element1) || is_imag(element2)){
        evaluate_imaginary(element1, element2, operation);
      } else{
        //Otherwise, convert the two numbers and perform
        //the operation on them
        num1 = stod(element2);
        num2 = stod(element1);
        
        perform_operation(operation);
      }
    }
  }
}

//print the output of the expression
void evaluator::print_output(){
  cout << expression.top() << endl;
  expression.pop();
}

//return the result of evaluating the expression
string evaluator::send_result() {
  return expression.top();
}

#endif
