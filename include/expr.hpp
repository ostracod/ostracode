
#ifndef EXPR_HEADER_FILE
#define EXPR_HEADER_FILE

#include <vector>
#include "component.hpp"
#include "group.hpp"

class Expr : public Group {
    public:
    
};

class PreExpr : public Expr {
    public:
    
    std::vector<Component *> components;
    
    PreExpr(std::vector<Component *> components);
};

#endif


