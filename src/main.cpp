
#include <iostream>
#include "json/json.h"

int main() {
    Json::Value value;
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();
    std::string text = "{\"message\": \"Hello, world!\"}";
    std::string error;
    reader->parse(text.c_str(), text.c_str() + text.length(), &value, &error);
    std::cout << value["message"].asString() << std::endl;
    return 0;
}


