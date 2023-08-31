
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
};

#endif


