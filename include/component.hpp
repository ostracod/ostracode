
#ifndef COMPONENT_HEADER_FILE
#define COMPONENT_HEADER_FILE

enum class ComponentType {
    Token, Stmt, Expr
};

class Component {
    public:
    
    ComponentType type;
    
    Component(ComponentType type);
};

class TokenComponent: public Component {
    public:
    
    Token *token;
    
    TokenComponent(Token *token);
};

class Stmt;

class StmtComponent: public Component {
    public:
    
    Stmt *stmt;
    
    StmtComponent(Stmt *stmt);
};

class Expr;

class ExprComponent: public Component {
    public:
    
    Expr *expr;
    
    ExprComponent(Expr *expr);
};

#endif


