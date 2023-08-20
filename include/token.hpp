
#ifndef TOKEN_HEADER_FILE
#define TOKEN_HEADER_FILE

#include <string>
#include <vector>

enum class TokenType {
    Word, Int, Float, Str, OpenBracket, CloseBracket, Separator, Operator
};

class Token {
    public:
    
    TokenType type;
    int lineNum;
    
    Token(TokenType type, int lineNum);
};

class TextToken: public Token {
    public:
    
    std::string text;
    
    TextToken(TokenType type, int lineNum, std::string text);
};

class IntToken: public Token {
    public:
    
    int value;
    
    IntToken(int lineNum, int value);
};

class FloatToken: public Token {
    public:
    
    double value;
    
    FloatToken(int lineNum, double value);
};

class TokenParser {
    public:
    
    std::string *content;
    int index;
    int lineNum;
    
    TokenParser(std::string *content);
    std::vector<Token> parseTokens();
};

#endif


