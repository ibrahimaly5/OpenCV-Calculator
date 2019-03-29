#include <vector>
#include <string>
#include <iostream>
#include "lexer.h"
#include "token.h"

using namespace std;

void lexer::LexInput(string s){
  tokens.clear();
  for (int i=0; i<s.size(); i++){
    // cout << s[i] << " ";
    StringToToken( string(1,s[i]) );
  }
}

void lexer::StringToToken(string s){

  if ( !s.compare("(") ){
    tokens.push_back( Token::LEFT_PAREN );
  }else if ( !s.compare(")") ){
    tokens.push_back( Token::RIGHT_PAREN );
  }else if ( !s.compare("=") ){
    tokens.push_back( Token::EQUAL_SIGN );
  }else if ( !s.compare("-") ){
    tokens.push_back( Token::NEGATIVE_SIGN );
  }else if ( !s.compare("+") ){
    tokens.push_back( Token::POSITIVE_SIGN );
  }else if ( !s.compare("*") ){
    tokens.push_back( Token::MULTIPLY_SIGN );
  }else if ( !s.compare("/") ){
    tokens.push_back( Token::DIVIDE_SIGN );
  }else if ( !s.compare(".") ){
    tokens.push_back( Token::DOT_SIGN );
  }
  
  else if ( !s.compare("0") ){
    tokens.push_back( Token::NUM_ZERO );
  } else if ( !s.compare("1") ){
    tokens.push_back( Token::NUM_ONE );
  } else if ( !s.compare("2") ){
    tokens.push_back( Token::NUM_TWO );
  } else if ( !s.compare("3") ){
    tokens.push_back( Token::NUM_THREE );
  } else if ( !s.compare("4") ){
    tokens.push_back( Token::NUM_FOUR );
  } else if ( !s.compare("5") ){
    tokens.push_back( Token::NUM_FIVE );
  } else if ( !s.compare("6") ){
    tokens.push_back( Token::NUM_SIX );
  } else if ( !s.compare("7") ){
    tokens.push_back( Token::NUM_SEVEN );
  } else if ( !s.compare("8") ){
    tokens.push_back( Token::NUM_EIGHT );
  } else if ( !s.compare("9") ){
    tokens.push_back( Token::NUM_NINE );
  }
      
  // else if ( !s.compare("s") ){
  //     string second, third;
  // }
}

vector<Token> lexer::getTokens(){
  return tokens;
}
