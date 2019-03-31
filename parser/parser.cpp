#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "parser.h"
#include "lexer.h"

using namespace std;

bool parser::is_int(string t){
  try {
      stoi(t);
      return true;
    } catch(...) {
      return false;
    }
}

// bool is_imag(string t){
// }

bool parser::is_operator(string t){
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

bool parser::is_unary_neg(int index){
  if (!tokens[index].compare("-")){
    if (index == 0){
      return true;
    }
    if ( is_operator(tokens[index-1]) || !tokens[index-1].compare("(") ){
      return true;
    }
  }
  return false;
}

bool parser::check_imag(int index){
  if (index == 0){
    return false;
  } else if (
    tokens[index].find("i") && is_int(tokens[index-1]) 
    ) {
    return true;
  }
  return false;
}


void parser::parse_tokens(){
  string t;
  for (int i=0; i<tokens.size(); i++){
    cout << tokens[i] << " "; 
  }
  cout << endl;

  for (int i=0; i<tokens.size(); i++){
    // if ( this->check_imag(i) ){
    //   postfix.back() = postfix.back() + tokens[i];
    // } else
     if ( this->is_int(tokens[i]) ){
      postfix.push_back(tokens[i]);
    } else if (tokens[i] == "("){
      operations.push(tokens[i]);
    } else if (tokens[i] == ")"){
      while (true){
        t = operations.top();
        operations.pop();
        if (t == "("){
          break;
        }
        postfix.push_back(t);
      }
    } else if (this->is_unary_neg(i)){
      postfix.push_back(tokens[i]);
      postfix.back() = postfix.back() + tokens[i+1];
      i++;
    } else if ( this->is_operator(tokens[i]) ){
      if (operations.empty()){
        operations.push(tokens[i]);
      } else {
        t = operations.top();

        if ( precedence[t] >= precedence[tokens[i]] ){
          operations.pop();
          postfix.push_back(t);
          operations.push(tokens[i]);
        } else{
          operations.push(tokens[i]);
        }

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

  string statement = "-22-4X-3";
  trial1.LexInput(statement);

  parser trial2(trial1.getTokens());
  trial2.parse_tokens();

  return 0;
}