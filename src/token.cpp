
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "token.hpp"

Token::Token(TokenType type, int lineNum) {
    this->type = type;
    this->lineNum = lineNum;
}

std::string Token::toString() {
    return "(Empty)";
}

TextToken::TextToken(TokenType type, int lineNum, std::string text) : Token(type, lineNum) {
    this->text = text;
}

std::string TextToken::toString() {
    return this->text;
}

IntToken::IntToken(int lineNum, int value) : Token(TokenType::Int, lineNum) {
    this->value = value;
}

std::string IntToken::toString() {
    return std::to_string(this->value);
}

FloatToken::FloatToken(int lineNum, double value) : Token(TokenType::Float, lineNum) {
    this->value = value;
}

std::string FloatToken::toString() {
    return std::to_string(this->value);
}

std::vector<TokenText> TokenText::tokenTextList;

bool compareLength(TokenText tokenText1, TokenText tokenText2) {
    return (tokenText1.text.length() > tokenText2.text.length());
}

bool isDecDigit(char character) {
    return (character >= '0' && character <= '9');
}

bool isHexDigit(char character) {
    return (isDecDigit(character)
        || (character >= 'A' && character <= 'F')
        || (character >= 'a' && character <= 'f'));
}

bool isFirstWordChar(char character) {
    return ((character >= 'A' && character <= 'Z')
        || (character >= 'a' && character <= 'z')
        || character == '_' || character == '$');
}

bool isWordChar(char character) {
    return isFirstWordChar(character) || isDecDigit(character);
}

void TokenText::init() {
    TokenText::add("(", TokenType::OpenBracket);
    TokenText::add("(*", TokenType::OpenBracket);
    TokenText::add("<", TokenType::OpenBracket);
    TokenText::add("<?", TokenType::OpenBracket);
    TokenText::add("<*", TokenType::OpenBracket);
    TokenText::add("<*?", TokenType::OpenBracket);
    TokenText::add("{", TokenType::OpenBracket);
    TokenText::add("[", TokenType::OpenBracket);
    TokenText::add(")", TokenType::CloseBracket);
    TokenText::add(">", TokenType::CloseBracket);
    TokenText::add("}", TokenType::CloseBracket);
    TokenText::add("]", TokenType::CloseBracket);
    TokenText::add(" ", TokenType::Separator);
    TokenText::add("\n", TokenType::Separator);
    TokenText::add("+", TokenType::Operator);
    TokenText::add("-", TokenType::Operator);
    TokenText::add("*", TokenType::Operator);
    TokenText::add("/", TokenType::Operator);
    TokenText::add("//", TokenType::Operator);
    TokenText::add("%", TokenType::Operator);
    TokenText::add("**", TokenType::Operator);
    TokenText::add("~", TokenType::Operator);
    TokenText::add("|", TokenType::Operator);
    TokenText::add("&", TokenType::Operator);
    TokenText::add("^", TokenType::Operator);
    TokenText::add("!", TokenType::Operator);
    TokenText::add("||", TokenType::Operator);
    TokenText::add("&&", TokenType::Operator);
    TokenText::add("^^", TokenType::Operator);
    TokenText::add("#sl", TokenType::Operator);
    TokenText::add("#sr", TokenType::Operator);
    TokenText::add("#srz", TokenType::Operator);
    TokenText::add("#lt", TokenType::Operator);
    TokenText::add("#lte", TokenType::Operator);
    TokenText::add("#gt", TokenType::Operator);
    TokenText::add("#gte", TokenType::Operator);
    TokenText::add("#eq", TokenType::Operator);
    TokenText::add("#neq", TokenType::Operator);
    TokenText::add(";", TokenType::Operator);
    TokenText::add(".", TokenType::Operator);
    TokenText::add("@", TokenType::Operator);
    TokenText::add(":", TokenType::Operator);
    TokenText::add("::", TokenType::Operator);
    TokenText::add("+:", TokenType::Operator);
    TokenText::add("=", TokenType::Operator);
    TokenText::add("+=", TokenType::Operator);
    TokenText::add("-=", TokenType::Operator);
    TokenText::add("*=", TokenType::Operator);
    TokenText::add("/=", TokenType::Operator);
    TokenText::add("%=", TokenType::Operator);
    TokenText::add("**=", TokenType::Operator);
    TokenText::add("|=", TokenType::Operator);
    TokenText::add("&=", TokenType::Operator);
    TokenText::add("^=", TokenType::Operator);
    TokenText::add("||=", TokenType::Operator);
    TokenText::add("&&=", TokenType::Operator);
    TokenText::add("^^=", TokenType::Operator);
    TokenText::add("#sl=", TokenType::Operator);
    TokenText::add("#sr=", TokenType::Operator);
    TokenText::add("#srz=", TokenType::Operator);
    TokenText::add(";=", TokenType::Operator);
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

void TokenParser::seekChar(char targetChar) {
    while (this->index < this->content->length()) {
        char character = this->peekChar();
        if (character == targetChar) {
            break;
        }
        this->advanceIndex();
    }
}

std::string TokenParser::parseTokenHelper(bool (*charMatches)(char)) {
    int startIndex = this->index;
    while (this->index < this->content->length()) {
        char character = this->peekChar();
        if (!charMatches(character)) {
            break;
        }
        this->advanceIndex();
    }
    return this->content->substr(startIndex, this->index - startIndex);
}

Token *TokenParser::parseWordToken() {
    int lineNum = this->lineNum;
    std::string text = this->parseTokenHelper(isWordChar);
    return new TextToken(TokenType::Word, lineNum, text);
}

Token *TokenParser::parseHexIntToken() {
    int lineNum = this->lineNum;
    std::string text = this->parseTokenHelper(isHexDigit);
    int value;
    std::stringstream strStream;
    strStream << std::hex << text;
    strStream >> value;
    return new IntToken(lineNum, value);
}

Token *TokenParser::parseDecNumToken() {
    int lineNum = this->lineNum;
    int startIndex = this->index;
    int decPointCount = 0;
    while (this->index < this->content->length()) {
        char character = this->peekChar();
        if (character == '.') {
            // Do not confuse decimal point with member access operator.
            char nextChar = this->peekChar(1);
            if (isFirstWordChar(nextChar) || nextChar == ' ') {
                break;
            }
            decPointCount += 1;
            if (decPointCount > 1) {
                throw std::runtime_error("Number contains too many decimal points.");
            }
        } else if (!isDecDigit(character)) {
            break;
        }
        this->advanceIndex();
    }
    if (this->index == startIndex) {
        return NULL;
    }
    std::string text = this->content->substr(startIndex, this->index - startIndex);
    std::stringstream strStream;
    if (decPointCount > 0) {
        return new FloatToken(lineNum, std::stod(text));
    } else {
        return new IntToken(lineNum, std::stoi(text));
    }
}

Token *TokenParser::parseToken() {
    char firstChar = this->peekChar();
    if (firstChar == ' ') {
        this->advanceIndex();
        return NULL;
    }
    if (isFirstWordChar(firstChar)) {
        return this->parseWordToken();
    }
    bool isComment = this->matchText("--");
    if (isComment) {
        this->seekChar(10);
        return NULL;
    }
    bool isHexInt = this->matchText("0x");
    if (isHexInt) {
        return this->parseHexIntToken();
    }
    if (isDecDigit(firstChar) || firstChar == '.') {
        Token *token = this->parseDecNumToken();
        if (token != NULL) {
            return token;
        }
    }
    int lineNum = this->lineNum;
    for (auto &tokenText : TokenText::tokenTextList) {
        if (this->matchText(tokenText.text)) {
            return new TextToken(tokenText.type, lineNum, tokenText.text);
        }
    }
    throw std::runtime_error("Unexpected character '" + std::string(1, firstChar) + "'.");
}

std::vector<Token *> TokenParser::parseTokens() {
    std::vector<Token *> output;
    while (this->index < this->content->length()) {
        Token *token = this->parseToken();
        if (token != NULL) {
            output.push_back(token);
        }
    }
    return output;
}


