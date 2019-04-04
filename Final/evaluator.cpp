#include "evaluator.h"
#include "lexer.h"
#include "parser.h"
#include <vector>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main(){
  lexer Lexer;
  parser Parser;
  evaluator Evaluator;
  string statement;

  while(true){
    cout << "enter expression to evaluate:\n";
    cin >> statement;
    // cout << "entered statement: " << statement << endl;
    
    Lexer.LexInput(statement);
    Parser.get_tokens(Lexer.getTokens());
    Parser.parse_tokens();

    Evaluator.start_evaluator( Parser.get_postfix() );
    Evaluator.EvaluateExpr();
    Evaluator.print_output();
  }

  return 0;
}