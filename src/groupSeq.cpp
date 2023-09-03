
#include "utils.hpp"
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

template <class T1, class T2>
GroupSeqBuilder<T1, T2>::GroupSeqBuilder(CreatePreGroup<T2> createPreGroup, std::string closeBracketText) {
    this->createPreGroup = createPreGroup;
    this->closeBracketText = closeBracketText;
}

GroupSeqBuilder<> *createGroupSeqBuilder(std::string openBrackText) {
    // TODO: Implement.
    return NULL;
}

PrepExprSeqBuilder::PrepExprSeqBuilder(): GroupSeqBuilder<PrepExprSeq, PreExpr>(PreExpr::create, ">") {
    
}

PrepExprSeq *PrepExprSeqBuilder::createGroupSeq(std::vector<PreExpr *> preExprs) {
    return new PrepExprSeq(castPtrVector<PreExpr, Expr>(preExprs));
}

FlowExprSeqBuilder::FlowExprSeqBuilder(): GroupSeqBuilder<FlowExprSeq, PreExpr>(PreExpr::create, ")") {
    
}

FlowExprSeq *FlowExprSeqBuilder::createGroupSeq(std::vector<PreExpr *> preExprs) {
    return new FlowExprSeq(castPtrVector<PreExpr, Expr>(preExprs));
}

BhvrStmtSeqBuilder::BhvrStmtSeqBuilder(): GroupSeqBuilder<BhvrStmtSeq, BhvrPreStmt>(BhvrPreStmt::create, "}") {
    
}

BhvrStmtSeq *BhvrStmtSeqBuilder::createGroupSeq(std::vector<BhvrPreStmt *> preStmts) {
    return new BhvrStmtSeq(castPtrVector<BhvrPreStmt, BhvrStmt>(preStmts));
}

AttrStmtSeqBuilder::AttrStmtSeqBuilder(): GroupSeqBuilder<AttrStmtSeq, AttrPreStmt>(AttrPreStmt::create, "]") {
    
}

AttrStmtSeq *AttrStmtSeqBuilder::createGroupSeq(std::vector<AttrPreStmt *> preStmts) {
    return new AttrStmtSeq(castPtrVector<AttrPreStmt, AttrStmt>(preStmts));
}


