
#include "component.hpp"
#include "group.hpp"

PreGroup::PreGroup(std::vector<Component *> components) : Group() {
    this->components = components;
}

PreGroupParser::PreGroupParser(std::vector<Token *> *tokens) {
    this->tokens = tokens;
    this->index = 0;
}

Token *PreGroupParser::peekToken() {
    if (this->index < this->tokens->size()) {
        return this->tokens->at(this->index);
    } else {
        return NULL;
    }
}

Token *PreGroupParser::readToken() {
    Token *output = this->peekToken();
    this->index += 1;
    return output;
}

GroupSeq<> *PreGroupParser::parseGroupSeq() {
    // TODO: Implement.
    return NULL;
}

Component *PreGroupParser::parseComponent() {
    Token *token = this->peekToken();
    if (token->type == TokenType::Separator || token->type == TokenType::CloseBracket) {
        return NULL;
    }
    if (token->type == TokenType::OpenBracket) {
        GroupSeq<> *groupSeq = this->parseGroupSeq();
        return new GroupSeqComponent(groupSeq);
    }
    this->index += 1;
    return new TokenComponent(token);
}

template <class T>
T *PreGroupParser::parsePreGroup(T *(*createPreGroup)(std::vector<Component *>)) {
    std::vector<Component *> components;
    while (this->index < this->tokens->size()) {
        Token *token = this->peekToken();
        if (token->type == TokenType::Separator) {
            this->index += 1;
            break;
        }
        Component *component = this->parseComponent();
        if (component == NULL) {
            break;
        }
        components.push_back(component);
    }
    if (components.size() > 0) {
        return createPreGroup(components);
    } else {
        return NULL;
    }
}

template <class T>
std::vector<T *> PreGroupParser::parsePreGroups(T *(*createPreGroup)(std::vector<Component *>)) {
    std::vector<T *> output;
    while (this->index < this->tokens->size()) {
        Token *token = this->peekToken();
        if (token->type == TokenType::CloseBracket) {
            break;
        }
        T *preGroup = this->parsePreGroup(createPreGroup);
        if (preGroup != NULL) {
            output.push_back(preGroup);
        }
    }
    return output;
}


