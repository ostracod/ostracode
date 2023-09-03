
#include "expr.hpp"

PreExpr::PreExpr(std::vector<Component *> components): Expr(), PreGroup(components) {
    
}

PreExpr *PreExpr::create(std::vector<Component *> components) {
    return new PreExpr(components);
}


