#include "Harl.hpp"
#include <iostream>



void Harl::debug(){
    std::cout << "DEBUG\n";
};
void Harl::info(){
    std::cout << "INFO\n";
};
void Harl::warning(){
    std::cout << "WARNNING\n";
};
void Harl::error(){
    std::cout << "ERROR\n";
};

void Harl::complain(std::string level){
    std::string levels[4] = {"DEBUG", "INFO", "WARNNING", "ERROR"};

    void (Harl::*func[4])() = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };
    
    for(int i =0; i<4; i++){
        if(levels[i] == level){
            (this->*func[i])();
            return;
        }
        }
    std::cout << "Invalid level\n";
};
