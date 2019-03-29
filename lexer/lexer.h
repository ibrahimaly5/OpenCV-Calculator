#ifndef _LEXER_H
#define _LEXER_H

#include <vector>
#include <string>
#include "token.h"

using namespace std;

/*
Design plan:
    -Build a state machine called "token" with all the different token value (ex: left_paren, right_paren, etc)
    -Create a class called lexer that is a vector of tokens
    -This class will have these functions:
        -vector<token> LexInput(string s) function which will receive a string s,
        and lex the input based on each character in the string, and return a vector with all the tokens
        -StringToLex function which will read 1 string character, and return its token type
*/

class lexer {
private:
    /* data */
    vector<Token> tokens;
public:
    void LexInput(string s);
    void StringToToken(string s);
};

#endif