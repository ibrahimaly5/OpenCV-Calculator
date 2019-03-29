#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "token.h"
#include "parser.h"
#include "lexer.h"

using namespace std;

bool is_digit(Token t){
  string s = ToString(t);
  s = s.substr(0,3);
  if (!s.compare("NUM")){
    // cout << ToString(t) << " is a number" << endl;
    return true;
  }
  return false;
}

bool is_operator(Token t){
  if (
    t == Token::MULTIPLY_SIGN ||
    t == Token::DIVIDE_SIGN ||
    t == Token::POSITIVE_SIGN ||
    t == Token::NEGATIVE_SIGN 
    ) {
      return true;
    }
    return false;
}

// enum paren_state {
//   in_paren,
//   not_paren
// };

void parser::parse_tokens(){
  Token t;

  for (int i=0; i<tokens.size(); i++){
    cout << ToString(tokens[i]) << endl;
    if ( is_digit(tokens[i]) ){
      postfix.push(tokens[i]);
    } 
    // else if (tokens[i] == Token::DOT_SIGN){
    //   // do sth
    // } else if (tokens[i] == Token::LEFT_PAREN){
    //   operations.push(tokens[i]);
    // } else if (tokens[i] == Token::RIGHT_PAREN){
    //   t = operations.top();
    //   while (t != Token::LEFT_PAREN){
    //     operations.pop();
    //     postfix.push(t);
    //     t = operations.top();
    //   }
    // } 
    else if ( is_operator(tokens[i]) ){
      if (operations.empty()){
        operations.push(tokens[i]);
      } else {
        t = operations.top();
        // if (t == Token::LEFT_PAREN){
        //   operations.push(tokens[i]);
        // } else{

        if ( precedence[ToString(t)] >= precedence[ToString(tokens[i])] ){
          operations.pop();
          postfix.push(t);
          operations.push(tokens[i]);
        } else{
          operations.push(tokens[i]);
        }

        // }
      }
    }
  }

  while (!operations.empty()){
    t = operations.top();
    operations.pop();
    postfix.push(t);
  }

  while (!postfix.empty()){
    t = postfix.top();
    postfix.pop();
    cout << ToString(t) << " ";
  }
}

stack<Token> parser::get_postfix(){
  return postfix;
}


int main(){
  lexer trial1;

  string statement = "2+3*4";
  trial1.LexInput(statement);

  parser trial2(trial1.getTokens());
  trial2.parse_tokens();

  return 0;
}