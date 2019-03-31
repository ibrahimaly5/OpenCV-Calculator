#ifndef _PARSER_H
#define _PARSER_H

#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include "token.h"
#include "lexer.h"

using namespace std;

/*
Design plan:
*/
unordered_map<string,int> precedence(
  {
    {"*",3},
    {"/",3},
    {"+",2},
    {"-",2}
  }
);

class parser {
private:
  /* data */
  stack<string> operations;
  vector<string> postfix;
  vector<string> tokens;
public:
  parser(vector<string> input_tokens);
  void update_tokens(vector<string> input_tokens);
  void parse_tokens();
  vector<string> get_postfix();
  bool is_unary_neg(int index);
  bool is_operator(string t);
  bool is_int(string t);
  bool check_imag(int index);

};

parser::parser(vector<string> input_tokens) {
  tokens = input_tokens;
}
void parser::update_tokens(vector<string> input_tokens){
  postfix.clear();
  while (!operations.empty()){
    operations.pop();
  }
  tokens = input_tokens;
}


#endif