#include <vector>
#include <string>
#include <iostream>
#include "lexer.h"

using namespace std;

void lexer::LexInput(string input){
  //clear the vector in case it had data; O(n)
  tokens.clear();

  //push the first element to the vector and start the loop
  //from the second element
  tokens.push_back( string(1,input[0]) );
  string s;
  for (int i=1; i<input.size(); i++){
    s = string(1,input[i]);
    //compare the string with the following operations,
    //if it's equal to one of them, push it back
    if ( !s.compare("(") ){
    tokens.push_back( "(" );
    }else if ( !s.compare(")") ){
      tokens.push_back( ")" );
    }else if ( !s.compare("=") ){
      tokens.push_back( "=" );
    }else if ( !s.compare("-") ){
      tokens.push_back( "-" );
    }else if ( !s.compare("+") ){
      tokens.push_back( "+" );
    }else if ( !s.compare("X") || !s.compare("*") ){
      tokens.push_back( "*" );
    }else if ( !s.compare("÷") || !s.compare("/") ){
      tokens.push_back( "/" );
    }else if ( !s.compare(".") ){
      tokens.back() = tokens.back() + s;
    } else if (!s.compare("i")){
      //If an "i" is detected, check if the element before it
      //can be converted to an integer. If it can be, concatenate
      //the last element in the tokens vector with the i
      try {
        stoi( tokens.back() );
        tokens.back() = tokens.back() + s;
      } catch(...) {
        //Otherwise, push it as a new element in the vector
        tokens.push_back(s);
      }      
    }
    //If it can not be compared to any of those, check if it can be 
    //converted to an integer
    else {
      try {
        stoi(s);
        try {
          //If it can be, check if the last element in the vector can be
          //converted to an integer and there's no i in the end. 
          //If it can be, concatenate the last element with this 
          //string (to support multi-digit numbers).
          stoi(tokens.back());
          if (!tokens.back().find("i")){
            tokens.push_back(s);
          }else{
            tokens.back() = tokens.back() + s;
          }
        } catch(...) {
          //Otherwise, add a new element to the vector with the string
          tokens.push_back(s);
        }

      } catch(...) {}
      
    }
  }
}

//returns the tokens vector
vector<string> lexer::getTokens(){
  return tokens;
}