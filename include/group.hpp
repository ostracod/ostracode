
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
    T *parsePreGroup(T *(*createPreGroup)(std::vector<Component *>));
    // `T` must conform to `PreGroup`.
    template <class T>
    std::vector<T *> parsePreGroups(T *(*createPreGroup)(std::vector<Component *>));
};

#endif


