
#include "groupSeq.hpp"

template <class T>
GroupSeq<T>::GroupSeq(GroupSeqType type, std::vector<T *> groups) {
    this->type = type;
    this->groups = groups;
}

ExprSeq::ExprSeq(GroupSeqType type, std::vector<Expr *> exprs): GroupSeq<Expr>(type, exprs) {
    
}

PrepExprSeq::PrepExprSeq(std::vector<Expr *> exprs): ExprSeq(GroupSeqType::PrepExpr, exprs) {
    
}

FlowExprSeq::FlowExprSeq(std::vector<Expr *> exprs): ExprSeq(GroupSeqType::FlowExpr, exprs) {
    
}

template <class T>
StmtSeq<T>::StmtSeq(GroupSeqType type, std::vector<T *> stmts): GroupSeq<T>(type, stmts) {
    
}

BhvrStmtSeq::BhvrStmtSeq(std::vector<BhvrStmt *> stmts): StmtSeq<BhvrStmt>(GroupSeqType::BhvrStmt, stmts) {
    
}

AttrStmtSeq::AttrStmtSeq(std::vector<AttrStmt *> stmts): StmtSeq<AttrStmt>(GroupSeqType::AttrStmt, stmts) {
    
}

GroupSeqBuilder *GroupSeqBuilder::create(std::string openBrackText) {
    // TODO: Implement.
    return NULL;
}

GroupSeqBuilder::GroupSeqBuilder(PreGroupBuilder<> *preGroupBuilder, std::string closeBracketText) {
    this->preGroupBuilder = preGroupBuilder;
    this->closeBracketText = closeBracketText;
}


