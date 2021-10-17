#include <iostream>
#include <handler.hpp>

int main(){
    std::string userInput;
    while (true){
        std::cout << "> ";
        std::getline(std::cin, userInput);
        std::cout << handler::evaluate(userInput) << "\n";
    }
    return 0;
}
