#ifndef _PARSER_H
#define _PARSER_H

#include <stack>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class parser {
private:
  //stack for the operations to convert the infix expression
  //to a postfix expression using the shunting yard algorithm
  stack<string> operations;

  //new vector with the postfix expression
  vector<string> postfix;

  //old tokens vector that will be received from the lexer class
  vector<string> tokens;
  
public:
  //get the tokens from the lexer
  void get_tokens(vector<string> input_tokens);
  
  //parse the infix expression to a postfix expression
  void parse_tokens();
  
  //return the postfix expression vector
  vector<string> get_postfix();
  
  //check if string element with the index is a unary negative
  bool is_unary_neg(int index);
  
  //check if the input string is an operation
  bool is_operator(string t);
  
  //check if the input string can be converted to an integer
  bool is_int(string t);
};

#endif