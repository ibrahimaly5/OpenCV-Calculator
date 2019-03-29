#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>

using namespace std;

enum class Token{
    LEFT_PAREN,
    RIGHT_PAREN,
    EQUAL_SIGN,
    NEGATIVE_SIGN,
    POSITIVE_SIGN,
    MULTIPLY_SIGN,
    DIVIDE_SIGN,
    DOT_SIGN,

    NUM_ZERO,
    NUM_ONE,
    NUM_TWO,
    NUM_THREE,
    NUM_FOUR,
    NUM_FIVE,
    NUM_SIX,
    NUM_SEVEN,
    NUM_EIGHT,
    NUM_NINE,


    TRIG_SIN,
    TRIG_COS,
    TRIG_TAN
};


inline const char* ToString(Token v) {
    switch (v) {
        case Token::LEFT_PAREN: 
            return "LEFT_PAREN";
            break;
        case Token::RIGHT_PAREN:
            return "RIGHT_PAREN";
            break;
        case Token::EQUAL_SIGN: 
            return "EQUAL_SIGN";
            break;
        case Token::NEGATIVE_SIGN: 
            return "NEGATIVE_SIGN";
            break;
        case Token::POSITIVE_SIGN: 
            return "POSITIVE_SIGN";
            break;
        case Token::MULTIPLY_SIGN: 
            return "MULTIPLY_SIGN";
            break;
        case Token::DIVIDE_SIGN: 
            return "DIVIDE_SIGN";
            break;
        case Token::DOT_SIGN: 
            return "DOT_SIGN";
            break;
        
        case Token::NUM_ZERO: 
            return "NUM_ZERO";
            break;
        case Token::NUM_ONE: 
            return "NUM_ONE";
            break;
        case Token::NUM_TWO: 
            return "NUM_TWO";
            break;
        case Token::NUM_THREE: 
            return "NUM_THREE";
            break;
        case Token::NUM_FOUR: 
            return "NUM_FOUR";
            break;
        case Token::NUM_FIVE: 
            return "NUM_FIVE";
            break;
        case Token::NUM_SIX: 
            return "NUM_SIX";
            break;
        case Token::NUM_SEVEN: 
            return "NUM_SEVEN";
            break;
        case Token::NUM_EIGHT: 
            return "NUM_EIGHT";
            break;
        case Token::NUM_NINE: 
            return "NUM_NINE";
            break;
        
        case Token::TRIG_SIN:
            return "TRIG_SIN";
            break;
        case Token::TRIG_COS:
            return "TRIG_COS";
            break;
        case Token::TRIG_TAN:
            return "TRIG_TAN";
            break;

        default:
            return "Unknown Token";
    }
}


#endif