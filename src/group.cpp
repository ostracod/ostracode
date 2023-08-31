
#include "group.hpp"

PreGroup::PreGroup(std::vector<Component *> components) : Group() {
    this->components = components;
}

PreGroupParser::PreGroupParser(std::vector<Token *> *tokens) {
    this->tokens = tokens;
    this->index = 0;
}


