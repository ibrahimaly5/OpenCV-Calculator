#ifndef _EVALUATOR_H
#define _EVALUATOR_H

#include <vector>
#include <string>
#include <complex>
#include <stack>
#include "lexer.h"
#include "parser.h"

using namespace std;


bool is_int(string t){
  try {
      stoi(t);
      return true;
    } catch(...) {
      return false;
    }
}

bool is_operator(string t){
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

bool is_float(string t){
  if (t.find(".")){
    return true;
  }
  return false;
}

bool is_imag(string t){
  if (t.find("i")){
    return true;
  }
  return false;
}

class evaluator {
private:
  /* data */
  vector<string> postfix_expr;
  long int1, int2;
  double float1, float2;
  complex<double> complex1, complex2;
public:
  evaluator(string expression);
  void EvaluateExpr();
};

evaluator::evaluator(string expression) {
  lexer Lexer;
  Lexer.LexInput(expression);
  parser Parser(Lexer.getTokens());
  Parser.parse_tokens();

  postfix_expr = Parser.get_postfix();
}

void evaluator::EvaluateExpr(){
  stack<string> expression;
  string element, operation;

  for (int i=0; i<postfix_expr.size(); i++){
    if ( !is_operator(postfix_expr[i]) ){
      expression.push(postfix_expr[i]);
    }else{
      element = expression.top();
      expression.pop();
      if ( is_imag(element) ){
        complex1.real = 
      } else if ( is_float(element) ){
        float1 = stod(element);
        element = expression.top();
        expression.pop();
        if ( is_imag(element) ){

        } else if ( is_float(element) ){
          float2 = stod(element);
          element = to_string(float1 + float2);
        } else{
          int2 = stol(element);
          element = to_string ( float1 + int2 );
        }
      } else {
        int1 = stol(element);
        element = expression.top();
        expression.pop();
        if ( is_imag(element) ){

        } else if ( is_float(element) ){
          float2 = stod(element);
          element = to_string(int1 + float2);
        } else{
          int2 = stol(element);
          element = to_string ( int1 + int2 );
        }
      }
    }
  }

}



#endif