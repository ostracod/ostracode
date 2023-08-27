
#include "component.hpp"

Component::Component(ComponentType type) {
    this->type = type;
}

TokenComponent::TokenComponent(Token *token) : Component(ComponentType::Token) {
    this->token = token;
}

StmtComponent::StmtComponent(Stmt *stmt) : Component(ComponentType::Stmt) {
    this->stmt = stmt;
}

ExprComponent::ExprComponent(Expr *expr) : Component(ComponentType::Expr) {
    this->expr = expr;
}


