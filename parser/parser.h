#ifndef _PARSER_H
#define _PARSER_H

#include <stack>
#include <string>
#include <vector>
#include "token.h"

using namespace std;

/*
Design plan:
*/

class parser {
private:
  /* data */
  stack<Token> operations;
  stack<Token> postfix;
  vector<Token> tokens;
public:
  parser(vector<Token> input_tokens);
  void parse_tokens();
};

parser::parser(vector<Token> input_tokens) {
  tokens = input_tokens;
}

#endif