
#ifndef TOKEN_HEADER_FILE
#define TOKEN_HEADER_FILE

#include <string>
#include <vector>

enum class TokenType {
    Empty, Word, Int, Float, Str, OpenBracket, CloseBracket, Separator, Operator
};

class Token {
    public:
    
    static Token empty;
    
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

class TokenText {
    public:
    
    static std::vector<TokenText> tokenTextList;
    
    static void init();
    static void add(std::string text, TokenType type);
    
    std::string text;
    TokenType type;
    
    TokenText(std::string text, TokenType type);
};

class TokenParser {
    public:
    
    std::string *content;
    int index;
    int lineNum;
    
    TokenParser(std::string *content);
    char peekChar(int offset);
    void advanceIndex(int amount);
    bool matchText(std::string text);
    Token parseToken();
    std::vector<Token> parseTokens();
};

#endif


