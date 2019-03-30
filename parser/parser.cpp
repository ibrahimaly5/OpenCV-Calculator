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
      postfix.push_back(tokens[i]);
    } 
    // else if (tokens[i] == Token::DOT_SIGN){
    //   // do sth
    // } 
    else if (tokens[i] == "("){
      operations.push(tokens[i]);
    } else if (tokens[i] == ")"){
      // t = operations.top();
      while (true){
        t = operations.top();
        operations.pop();
        if (t == "("){
          break;
        }
        postfix.push_back(t);
      }
    } 
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
          postfix.push_back(t);
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
    postfix.push_back(t);
  }

  for (int i=0; i<postfix.size(); i++){
    cout << postfix[i] << " ";
  }
  cout << endl;
}

vector<string> parser::get_postfix(){
  return postfix;
}


int main(){
  lexer trial1;

  string statement = "2*(3+4*5)+6";
  trial1.LexInput(statement);

  parser trial2(trial1.getTokens());
  trial2.parse_tokens();

  return 0;
}