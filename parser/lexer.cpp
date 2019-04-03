#include <vector>
#include <string>
#include <iostream>
#include "lexer.h"

using namespace std;

void lexer::LexInput(string input){
  tokens.clear();
  string s;

  tokens.push_back( string(1,input[0]) );
  for (int i=1; i<input.size(); i++){
    StringToToken(string(1,input[i]));
  }
}

void lexer::StringToToken(string s){
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
    try {
      stoi( tokens.back() );
      tokens.back() = tokens.back() + s;
    } catch(...) {
      tokens.push_back(s);
    }      
  }
  
  else {
    try {
      stoi(s);
      try {
        stoi(tokens.back());
        if (!tokens.back().find("i")){
          tokens.push_back(s);
        }else{
          tokens.back() = tokens.back() + s;
        }
      } catch(...) {
        tokens.push_back(s);
      }

    } catch(...) {}
    
  }
    
  // do this later too

  // else if ( !s.compare("sin") ){
  //     string second, third;
  // }
}

vector<string> lexer::getTokens(){
  return tokens;
}

// int main(){
//   lexer trial1;

//   string statement = "21(3*4)";
//   trial1.LexInput(statement);

//   vector<string> output;
//   output = trial1.getTokens();
//   for (int i=0; i<output.size(); i++){
//     cout << output[i] << " ";
//   }
//   cout << endl;

//   return 0;
// }