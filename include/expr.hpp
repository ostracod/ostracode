
#ifndef EXPR_HEADER_FILE
#define EXPR_HEADER_FILE

#include <vector>
#include "component.hpp"
#include "group.hpp"

class Expr : virtual public Group {
    public:
    
};

class PreExpr : public Expr, public PreGroup {
    public:
    
    PreExpr(std::vector<Component *> components);
};

#endif


