
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

class ExprSeq : GroupSeq<Expr> {
    
};

class StmtSeq : GroupSeq<Stmt> {
    
};

#endif


