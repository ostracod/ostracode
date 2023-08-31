
#include "stmt.hpp"

PreStmt::PreStmt(std::vector<Component *> components) : Stmt(), PreGroup(components) {
    
}

BhvrPreStmt::BhvrPreStmt(std::vector<Component *> components) : BhvrStmt(), PreStmt(components) {
    
}

AttrPreStmt::AttrPreStmt(std::vector<Component *> components) : AttrStmt(), PreStmt(components) {
    
}


