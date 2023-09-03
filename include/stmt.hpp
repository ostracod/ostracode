
#ifndef STMT_HEADER_FILE
#define STMT_HEADER_FILE

#include <vector>
#include "component.hpp"
#include "group.hpp"

class Stmt: virtual public Group {
    
};

class PreStmt: virtual public Stmt, public PreGroup {
    public:
    
    PreStmt(std::vector<Component *> components);
};

class BhvrStmt: virtual public Stmt {
    
};

class BhvrPreStmt: public BhvrStmt, public PreStmt {
    public:
    
    static BhvrPreStmt *create(std::vector<Component *> components);
    
    BhvrPreStmt(std::vector<Component *> components);
};

class AttrStmt: virtual public Stmt {
    
};

class AttrPreStmt: public AttrStmt, public PreStmt {
    public:
    
    static AttrPreStmt *create(std::vector<Component *> components);
    
    AttrPreStmt(std::vector<Component *> components);
};

#endif


