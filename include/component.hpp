
#ifndef COMPONENT_HEADER_FILE
#define COMPONENT_HEADER_FILE

enum class ComponentType {
    Token, GroupSeq
};

class Component {
    public:
    
    ComponentType type;
    
    Component(ComponentType type);
};

class Token;

class TokenComponent: public Component {
    public:
    
    Token *token;
    
    TokenComponent(Token *token);
};

class Group;

template <class T = Group>
class GroupSeq;

class GroupSeqComponent: public Component {
    public:
    
    GroupSeq<> *groupSeq;
    
    GroupSeqComponent(GroupSeq<> *groupSeq);
};

#endif


