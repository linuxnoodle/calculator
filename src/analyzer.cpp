#include <analyzer.hpp>

std::map<std::string, TOKEN> patterns{
    {"(exit|clear)", KEYWORDS},
    {"[0-9\\.]+", NUMBER},
    {"[+\\-\\/*%]", TWO_OPERATION}
};

// Taken from https://stackoverflow.com/questions/34229328/writing-a-very-simple-lexical-analyser-in-c
std::map<size_t, std::pair<std::string, TOKEN>> analyzer::lex(std::string str){
    std::map<size_t, std::pair<std::string, TOKEN>> matches;

    for (auto pattern = patterns.begin(); pattern != patterns.end(); ++pattern){
        std::regex regexPattern(pattern->first);
        auto words_begin = std::sregex_iterator(str.begin(), str.end(), regexPattern);
        auto words_end = std::sregex_iterator();

        for (auto it = words_begin; it != words_end; ++it)
            matches[it->position()] = std::make_pair(it->str(), pattern->second);
    }

    return matches;
}

void analyzer::execute(std::string str){
    
}
