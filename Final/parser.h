#ifndef _PARSER_H
#define _PARSER_H

#include <stack>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/*
Design plan:
*/

class parser {
private:
  /* data */
  stack<string> operations;
  vector<string> postfix;
  vector<string> tokens;
public:
  void get_tokens(vector<string> input_tokens);
  void parse_tokens();
  vector<string> get_postfix();
  bool is_unary_neg(int index);
  bool is_operator(string t);
  bool is_int(string t);
};

#endif