
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

// `T1` must conform to `GroupSeq`, and `T2` must conform to `PreGroup`.
template <class T1 = GroupSeq<>, class T2 = PreGroup>
class GroupSeqBuilder {
    public:
    
    CreatePreGroup<T2> createPreGroup;
    std::string closeBracketText;
    
    GroupSeqBuilder(CreatePreGroup<T2> createPreGroup, std::string closeBracketText);
    virtual T1 *createGroupSeq(std::vector<T2 *> preGroups) = 0;
};

GroupSeqBuilder<> *createGroupSeqBuilder(std::string openBrackText);

class PrepExprSeqBuilder: public GroupSeqBuilder<PrepExprSeq, PreExpr> {
    public:
    
    PrepExprSeqBuilder();
    PrepExprSeq *createGroupSeq(std::vector<PreExpr *> preExprs);
};

class FlowExprSeqBuilder: public GroupSeqBuilder<FlowExprSeq, PreExpr> {
    public:
    
    FlowExprSeqBuilder();
    FlowExprSeq *createGroupSeq(std::vector<PreExpr *> preExprs);
};

class BhvrStmtSeqBuilder: public GroupSeqBuilder<BhvrStmtSeq, BhvrPreStmt> {
    public:
    
    BhvrStmtSeqBuilder();
    BhvrStmtSeq *createGroupSeq(std::vector<BhvrPreStmt *> preStmts);
};

class AttrStmtSeqBuilder: public GroupSeqBuilder<AttrStmtSeq, AttrPreStmt> {
    public:
    
    AttrStmtSeqBuilder();
    AttrStmtSeq *createGroupSeq(std::vector<AttrPreStmt *> preStmts);
};

#endif


