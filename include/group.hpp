
#ifndef GROUP_HEADER_FILE
#define GROUP_HEADER_FILE

#import <vector>
#import "token.hpp"
#import "component.hpp"

class Group {
    
};

class PreGroup: virtual public Group {
    public:
    
    std::vector<Component *> components;
    
    PreGroup(std::vector<Component *> components);
};

// `T` must be `PreStmt` or `PreExpr`.
template <class T = Group>
using CreatePreGroup = T *(*)(std::vector<Component *>);

class PreGroupParser {
    public:
    
    std::vector<Token *> *tokens;
    int index;
    
    PreGroupParser(std::vector<Token *> *tokens);
    Token *peekToken();
    Token *readToken();
    GroupSeq<> *parseGroupSeq();
    Component *parseComponent();
    // `T` must conform to `PreGroup`.
    template <class T>
    T *parsePreGroup(CreatePreGroup<T> createPreGroup);
    // `T` must conform to `PreGroup`.
    template <class T>
    std::vector<T *> parsePreGroups(CreatePreGroup<T> createPreGroup);
};

#endif


