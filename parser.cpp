#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "parser.h"

using namespace std;

//a map holding the weight of each operation 
unordered_map<string,int> precedence(
  {
    {"*",3},
    {"/",3},
    {"+",2},
    {"-",2}
  }
);

//check if the input string can be converted to an integer
//and return true. Otherwise, return false
bool parser::is_int(string t){
  try {
      stoi(t);
      return true;
    } catch(...) {
      return false;
    }
}

//check if the input string is an operation and return true
//Otherwise, return false
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

//check if string element with the index is a unary negative
//and return true. Otherwise, return false
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

void parser::parse_tokens(){
  string t;
  
  //loop through the tokens vector
  for (int i=0; i<tokens.size(); i++){
    //if the element is an integer, push it down the postfix
    //vector
    if ( this->is_int(tokens[i]) ){
      postfix.push_back(tokens[i]);
    } else if (tokens[i] == "("){
      //if element is a left parantheses
      //push it down the operations stack
      operations.push(tokens[i]);
    } else if (tokens[i] == ")"){

      //if the element is a right parantheses,
      //keep popping the operations on the operation stack
      //and push them in the postfix. When a left parantheses
      //is found, break the loop
      while (true){
        t = operations.top();
        operations.pop();
        if (t == "("){
          break;
        }
        postfix.push_back(t);
      }
    } else if (this->is_unary_neg(i)){
      //If a unary negative is found, push it on the 
      //postfix vector, and add the next element
      //in the tokens vector to it. Increment i
      postfix.push_back(tokens[i]);
      postfix.back() = postfix.back() + tokens[i+1];
      i++;
    } else if ( this->is_operator(tokens[i]) ){
      
      //If an operation is found, and the operations stack is empty,
      //push the operation on the stack. Otherwise, check the weight
      //of the operation and the top of the operations stack
      //and insert the operation accordingly
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

  //Once done looping through the tokens, push everything from the 
  //operations stack to the postfix expression
  while (!operations.empty()){
    t = operations.top();
    operations.pop();
    postfix.push_back(t);
  }

}

//return the postfix vector
vector<string> parser::get_postfix(){
  return postfix;
}

//empty the postfix expression vector and the operations stack,
//and get the tokens from the lexer
void parser::get_tokens(vector<string> input_tokens) {
  postfix.clear();
  while (!operations.empty()){
    operations.pop();
  }
  tokens = input_tokens;
}
