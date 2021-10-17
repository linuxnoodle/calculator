#include <handler.hpp>
#include <analyzer.hpp>
#include <iterator>

std::string handler::evaluate(std::string str){
    auto matches = analyzer::lex(str);
    float currentValue = 0;
    for (auto match = matches.begin(); match != matches.end(); ++match){
        switch (match->second.second){
            case KEYWORDS:
                if (match->second.first == "exit"){
                    std::exit(0);
                } else if (match->second.first == "clear"){
                    //TODO: Windows clearing
                    std::system("clear"); 
                }
                break;
            case NUMBER:
                break;
            case TWO_OPERATION:
                try{
                    if (match == matches.begin() || match == matches.end() || matches.size() < 3){
                        std::cerr << "ERROR: Incorrect usage of the \"" << match->second.first << "\" operator";
                        return "";
                    }
                    auto prior = &std::prev(match)->second, next = &std::next(match)->second;
                    if (prior->second == NUMBER && next->second == NUMBER){
                        if (match->second.first == "+"){
                            currentValue += std::stof(prior->first) + std::stof(next->first);
                        } else if (match->second.first == "-"){
                            currentValue += std::stof(prior->first) - std::stof(next->first);
                        } else if (match->second.first == "*"){
                            currentValue += std::stof(prior->first) * std::stof(next->first);
                        } else if (match->second.first == "/"){
                            currentValue += std::stof(prior->first) / std::stof(next->first);
                        } else if (match->second.first == "%"){
                            currentValue += (fmod(std::stof(prior->first),  std::stof(next->first)));
                        }
                        prior->second = UNUSABLE;
                        next->second = UNUSABLE;
                    } else if (prior->second == UNUSABLE && next->second == NUMBER){
                        if (match->second.first == "+"){
                            currentValue += std::stof(next->first);
                        } else if (match->second.first == "-"){
                            currentValue -= std::stof(next->first);
                        //TODO: Order of operations, currently operations below won't work
                        } else if (match->second.first == "*"){
                            currentValue += std::stof(prior->first) * std::stof(next->first);
                        } else if (match->second.first == "/"){
                            currentValue += std::stof(prior->first) / std::stof(next->first);
                        } else if (match->second.first == "%"){
                            currentValue += (fmod(std::stof(prior->first),  std::stof(next->first)));
                        }
                        next->second = UNUSABLE; 
                    } else {
                        std::cerr << "ERROR: Incorrect usage of the \"" << match->second.first << "\" operator";
                        return "";
                    }
                } catch (std::out_of_range &err){
                    std::cerr << "ERROR: Out of range.";
                    return "";
                }
                break;
            default:
                break;
        }
    }
    return std::to_string(currentValue);
}
