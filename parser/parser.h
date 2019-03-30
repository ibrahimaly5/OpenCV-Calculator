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
  stack<string> postfix;
  vector<string> tokens;
public:
  parser(vector<string> input_tokens);
  void parse_tokens();
  stack<string> get_postfix();
};

parser::parser(vector<string> input_tokens) {
  tokens = input_tokens;
}

#endif