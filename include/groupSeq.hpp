
#ifndef GROUP_SEQ_HEADER_FILE
#define GROUP_SEQ_HEADER_FILE

#include <string>
#include <vector>
#include "group.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "component.hpp"

enum class GroupSeqType {
    PrepExpr, FlowExpr, BhvrStmt, AttrStmt
};

// `T` must conform to `Group`.
template <class T>
class GroupSeq {
    public:
    
    GroupSeqType type;
    std::vector<T *> groups;
    
    GroupSeq(GroupSeqType type, std::vector<T *> groups);
};

class ExprSeq: public GroupSeq<Expr> {
    public:
    
    ExprSeq(GroupSeqType type, std::vector<Expr *> exprs);
};

class PrepExprSeq: public ExprSeq {
    public:
    
    PrepExprSeq(std::vector<Expr *> exprs);
};

class FlowExprSeq: public ExprSeq {
    public:
    
    FlowExprSeq(std::vector<Expr *> exprs);
};

// `T` must conform to `Stmt`.
template <class T>
class StmtSeq: public GroupSeq<T> {
    public:
    
    StmtSeq(GroupSeqType type, std::vector<T *> stmts);
};

class BhvrStmtSeq: public StmtSeq<BhvrStmt> {
    public:
    
    BhvrStmtSeq(std::vector<BhvrStmt *> stmts);
};

class AttrStmtSeq: public StmtSeq<AttrStmt> {
    public:
    
    AttrStmtSeq(std::vector<AttrStmt *> stmts);
};

class GroupSeqBuilder {
    public:
    
    static GroupSeqBuilder *create(std::string openBrackText);
    
    PreGroupBuilder<> *preGroupBuilder;
    std::string closeBracketText;
    
    GroupSeqBuilder(PreGroupBuilder<> *preGroupBuilder, std::string closeBracketText);
    virtual GroupSeq<> *createGroupSeq(std::vector<PreGroup *> preGroups) = 0;
};

#endif


