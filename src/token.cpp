
#include <vector>
#include <iostream>
#include <algorithm>
#include "token.hpp"

Token Token::empty(TokenType::Empty, 0);

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

std::vector<TokenText> TokenText::tokenTextList;

bool compareLength(TokenText tokenText1, TokenText tokenText2) {
    return (tokenText1.text.length() > tokenText2.text.length());
}

void TokenText::init() {
    TokenText::add(" ", TokenType::Separator);
    TokenText::add("\n", TokenType::Separator);
    std::sort(
        TokenText::tokenTextList.begin(),
        TokenText::tokenTextList.end(),
        compareLength
    );
}

void TokenText::add(std::string text, TokenType type) {
    TokenText::tokenTextList.push_back(TokenText(text, type));
}

TokenText::TokenText(std::string text, TokenType type) {
    this->text = text;
    this->type = type;
}

TokenParser::TokenParser(std::string *content) {
    this->content = content;
    this->index = 0;
    this->lineNum = 1;
}

char TokenParser::peekChar(int offset = 0) {
    int index = this->index + offset;
    if (index < this->content->length()) {
        return this->content->at(index);
    } else {
        return 0;
    }
}

void TokenParser::advanceIndex(int amount = 1) {
    for (int count = 0; count < amount; count++) {
        char character = this->peekChar();
        if (character == '\n') {
            this->lineNum += 1;
        }
        this->index += 1;
    }
}

bool TokenParser::matchText(std::string text) {
    if (this->index + text.length() <= this->content->length()) {
        std::string subText = this->content->substr(index, text.length());
        if (subText == text) {
            this->advanceIndex(text.length());
            return true;
        }
    }
    return false;
}

Token TokenParser::parseToken() {
    char firstChar = this->peekChar();
    if (firstChar == ' ') {
        this->advanceIndex();
        return Token::empty;
    }
    int lineNum = this->lineNum;
    for (auto &tokenText : TokenText::tokenTextList) {
        if (this->matchText(tokenText.text)) {
            return TextToken(tokenText.type, lineNum, tokenText.text);
        }
    }
    throw std::runtime_error("Unexpected character '" + std::string(1, firstChar) + "'.");
}

std::vector<Token> TokenParser::parseTokens() {
    std::vector<Token> output;
    while (this->index < this->content->length()) {
        Token token = this->parseToken();
        if (token.type != TokenType::Empty) {
            output.push_back(token);
        }
    }
    return output;
}


