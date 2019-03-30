#include <vector>
#include <string>
#include <iostream>
#include "lexer.h"
#include "token.h"

using namespace std;

void lexer::LexInput(string s){
  tokens.clear();

  tokens.push_back( string(1,s[0]) );
  for (int i=1; i<s.size(); i++){
    // cout << s[i] << " ";
    StringToToken( string(1,s[i]) );
  }
  // cout << endl;
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
  }else if ( !s.compare("*") ){
    tokens.push_back( "*" );
  }else if ( !s.compare("/") ){
    tokens.push_back( "/" );
  }
  
  //do this later

  // else if ( !s.compare(".") ){
  //   tokens.push_back( "." );
  // }
  
  else {
    try {
      stoi(s);
      try {
        stoi(tokens.back());
        tokens.back() = tokens.back() + s;
      } catch(...) {
        tokens.push_back(s);
      }

    } catch(...) {}
    
  }
    
  // do this later too

  // else if ( !s.compare("s") ){
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