
#include "utils.hpp"
#include "error.hpp"
#include "groupSeq.hpp"

template <class T>
GroupSeq<T>::GroupSeq(GroupSeqType type, std::vector<T *> groups) {
    this->type = type;
    this->groups = groups;
}

ExprSeq::ExprSeq(GroupSeqType type, bool hasFactorType, std::vector<Expr *> exprs): GroupSeq<Expr>(type, exprs) {
    this->hasFactorType = hasFactorType;
}

PrepExprSeq::PrepExprSeq(bool hasFactorType, bool useConstraintTypes, std::vector<Expr *> exprs): ExprSeq(GroupSeqType::PrepExpr, hasFactorType, exprs) {
    this->useConstraintTypes = useConstraintTypes;
}

FlowExprSeq::FlowExprSeq(bool hasFactorType, std::vector<Expr *> exprs): ExprSeq(GroupSeqType::FlowExpr, hasFactorType, exprs) {
    
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

GroupSeqBuilder<> *createGroupSeqBuilder(std::string openBracketText) {
    char firstChar = openBracketText.at(0);
    bool hasFactorType = (openBracketText.length() > 1 && openBracketText.at(2) == '*');
    int charIndex = hasFactorType ? 2 : 1;
    bool useConstraintTypes = (charIndex < openBracketText.length()
        && openBracketText.at(charIndex) == '?');
    if (firstChar == '{') {
        // This is throwing a compilation error right now...
        // C++ templates are a bit troublesome...
        return static_cast<GroupSeqBuilder<> *>(new BhvrStmtSeqBuilder());
    } else if (firstChar == '[') {
        return new AttrStmtSeqBuilder();
    } else if (firstChar == '<') {
        return new PrepExprSeqBuilder(hasFactorType, useConstraintTypes);
    } else if (firstChar == '(') {
        return new FlowExprSeqBuilder(hasFactorType);
    } else {
        throw Error("Invalid open bracket \"" + openBracketText + "\".");
    }
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

template <class T>
ExprSeqBuilder<T>::ExprSeqBuilder(bool hasFactorType, CreatePreGroup<PreExpr> createPreGroup, std::string closeBracketText): GroupSeqBuilder<T, PreExpr>(createPreGroup, closeBracketText) {
    this->hasFactorType = hasFactorType;
}

PrepExprSeqBuilder::PrepExprSeqBuilder(bool hasFactorType, bool useConstraintTypes): ExprSeqBuilder<PrepExprSeq>(hasFactorType, PreExpr::create, ">") {
    this->useConstraintTypes = useConstraintTypes;
}

PrepExprSeq *PrepExprSeqBuilder::createGroupSeq(std::vector<PreExpr *> preExprs) {
    return new PrepExprSeq(this->hasFactorType, this->useConstraintTypes, castPtrVector<PreExpr, Expr>(preExprs));
}

FlowExprSeqBuilder::FlowExprSeqBuilder(bool hasFactorType): ExprSeqBuilder<FlowExprSeq>(hasFactorType, PreExpr::create, ")") {
    
}

FlowExprSeq *FlowExprSeqBuilder::createGroupSeq(std::vector<PreExpr *> preExprs) {
    return new FlowExprSeq(this->hasFactorType, castPtrVector<PreExpr, Expr>(preExprs));
}


