
#include "error.hpp"
#include "component.hpp"
#include "group.hpp"
#include "groupSeq.hpp"

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
    TextToken *openBracketToken = static_cast<TextToken *>(this->readToken());
    GroupSeqBuilder *groupSeqBuilder = GroupSeqBuilder::create(openBracketToken->text);
    std::vector<PreGroup *> preGroups = this->parsePreGroups<PreGroup>(groupSeqBuilder->preGroupBuilder);
    Token *closeBracketToken = this->readToken();
    if (closeBracketToken->type != TokenType::CloseBracket || static_cast<TextToken *>(closeBracketToken)->text != groupSeqBuilder->closeBracketText) {
        throw Error("Missing " + groupSeqBuilder->closeBracketText + ".");
    }
    return groupSeqBuilder->createGroupSeq(preGroups);
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
T *PreGroupParser::parsePreGroup(PreGroupBuilder<T> *preGroupBuilder) {
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
        return preGroupBuilder->createPreGroup(components);
    } else {
        return NULL;
    }
}

template <class T>
std::vector<T *> PreGroupParser::parsePreGroups(PreGroupBuilder<T> *preGroupBuilder) {
    std::vector<T *> output;
    while (this->index < this->tokens->size()) {
        Token *token = this->peekToken();
        if (token->type == TokenType::CloseBracket) {
            break;
        }
        T *preGroup = this->parsePreGroup(preGroupBuilder);
        if (preGroup != NULL) {
            output.push_back(preGroup);
        }
    }
    return output;
}


