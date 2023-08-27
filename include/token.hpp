
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
    virtual std::string toStr() = 0;
};

class TextToken: public Token {
    public:
    
    std::string text;
    
    TextToken(TokenType type, int lineNum, std::string text);
    std::string toStr();
};

class IntToken: public Token {
    public:
    
    int value;
    
    IntToken(int lineNum, int value);
    std::string toStr();
};

class FloatToken: public Token {
    public:
    
    double value;
    
    FloatToken(int lineNum, double value);
    std::string toStr();
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
    char peekChar(int offset = 0);
    void advanceIndex(int amount = 1);
    char readChar();
    char readCharWithEscape();
    bool matchText(std::string text);
    void seekChar(char targetChar);
    std::string parseTokenHelper(bool (*charMatches)(char));
    TextToken *parseWordToken();
    IntToken *parseHexIntToken();
    Token *parseDecNumToken();
    IntToken *parseCharToken();
    TextToken *parseStrToken();
    Token *parseToken();
    std::vector<Token *> parseTokens();
};

#endif


