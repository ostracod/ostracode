
#include "component.hpp"

Component::Component(ComponentType type) {
    this->type = type;
}

TokenComponent::TokenComponent(Token *token): Component(ComponentType::Token) {
    this->token = token;
}

GroupSeqComponent::GroupSeqComponent(GroupSeq<> *groupSeq): Component(ComponentType::GroupSeq) {
    this->groupSeq = groupSeq;
}


