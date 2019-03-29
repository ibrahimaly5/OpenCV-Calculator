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
    {ToString(Token::MULTIPLY_SIGN),3},
    {ToString(Token::DIVIDE_SIGN),3},
    {ToString(Token::POSITIVE_SIGN),2},
    {ToString(Token::NEGATIVE_SIGN),2},
  }
);

class parser {
private:
  /* data */
  stack<Token> operations;
  stack<Token> postfix;
  vector<Token> tokens;
public:
  parser(vector<Token> input_tokens);
  void parse_tokens();
  stack<Token> get_postfix();
};

parser::parser(vector<Token> input_tokens) {
  tokens = input_tokens;
}

#endif