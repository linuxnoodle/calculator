#pragma once
#include <map>
#include <regex>

enum TOKEN{
    UNUSABLE,
    KEYWORDS,
    NUMBER,
    TWO_OPERATION
};

namespace analyzer{
    std::map<size_t, std::pair<std::string, TOKEN>> lex(std::string str);
    void execute(std::string str);
}
