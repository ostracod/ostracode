
#include "stmt.hpp"

PreStmt::PreStmt(std::vector<Component *> components): Stmt(), PreGroup(components) {
    
}

BhvrPreStmt *BhvrPreStmt::create(std::vector<Component *> components) {
    return new BhvrPreStmt(components);
}

BhvrPreStmt::BhvrPreStmt(std::vector<Component *> components): BhvrStmt(), PreStmt(components) {
    
}

AttrPreStmt *AttrPreStmt::create(std::vector<Component *> components) {
    return new AttrPreStmt(components);
}

AttrPreStmt::AttrPreStmt(std::vector<Component *> components): AttrStmt(), PreStmt(components) {
    
}


