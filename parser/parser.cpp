#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "token.h"
#include "parser.h"
#include "lexer.h"

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

void parser::parse_tokens(){
  string t;

  for (int i=0; i<tokens.size(); i++){
    cout << tokens[i] << endl;
    if ( is_int(tokens[i]) ){
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

        if ( precedence[t] >= precedence[tokens[i]] ){
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
    cout << t << " ";
  }
  cout << endl;
}

stack<string> parser::get_postfix(){
  return postfix;
}


int main(){
  lexer trial1;

  string statement = "22+3*4";
  trial1.LexInput(statement);

  parser trial2(trial1.getTokens());
  trial2.parse_tokens();

  return 0;
}