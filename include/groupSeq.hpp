
#ifndef GROUP_SEQ_HEADER_FILE
#define GROUP_SEQ_HEADER_FILE

#include <vector>
#include "group.hpp"
#include "expr.hpp"
#include "stmt.hpp"

// `T` must conform to `Group`.
template <class T>
class GroupSeq {
    public:
    
    std::vector<T *> groups;
    
    GroupSeq(std::vector<T *> groups);
};

class ExprSeq: public GroupSeq<Expr> {
    
};

class PrepExprSeq: public ExprSeq {
    
};

class FlowExprSeq: public ExprSeq {
    
};

// `T` must conform to `Stmt`.
template <class T>
class StmtSeq: public GroupSeq<T> {
    
};

class BhvrStmtSeq: public StmtSeq<BhvrStmt> {
    
};

class AttrStmtSeq: public StmtSeq<AttrStmt> {
    
};

#endif


