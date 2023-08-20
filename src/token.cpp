
#include <vector>
#include <iostream>
#include "token.hpp"

Token::Token(TokenType type, int lineNum) {
    this->type = type;
    this->lineNum = lineNum;
}

TextToken::TextToken(TokenType type, int lineNum, std::string text) : Token(type, lineNum) {
    this->text = text;
}

IntToken::IntToken(int lineNum, int value) : Token(TokenType::Int, lineNum) {
    this->value = value;
}

FloatToken::FloatToken(int lineNum, double value) : Token(TokenType::Float, lineNum) {
    this->value = value;
}

TokenParser::TokenParser(std::string *content) {
    this->content = content;
    this->index = 0;
    this->lineNum = 1;
}

std::vector<Token> TokenParser::parseTokens() {
    std::vector<Token> output;
    // TODO: Implement.
    std::cout << "In token parser!" << std::endl;
    
    return output;
}


