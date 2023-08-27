
#ifndef STMT_HEADER_FILE
#define STMT_HEADER_FILE

#include <vector>
#include "component.hpp"
#include "group.hpp"

class Stmt : public Group {
    public:
    
};

class PreStmt : public Stmt {
    public:
    
    std::vector<Component *> components;
    
    PreStmt(std::vector<Component *> components);
};

#endif


