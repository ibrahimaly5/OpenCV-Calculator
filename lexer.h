#ifndef _LEXER_H
#define _LEXER_H

#include <vector>
#include <string>

using namespace std;

/*
Design plan:
  -Create a class called lexer that is a vector of token strings
  -This class will have these functions:
    -vector<token> LexInput(string s) function which will receive a string s,
    and lex the input based on each character in the string, and creates a vector with all the tokens
    -getTokens() function will return the vector of the tokens
*/

class lexer {
private:
  /* a vector of strings for each token */
  vector<string> tokens;
  
public:
  //Lexes the input, and saves the lexed result in the vector tokens
  void LexInput(string s);

  //returns the vector tokens
  vector<string> getTokens();
};

#endif