#include "RPN.hpp"
#include <iostream>

bool valid_char( char c )
{
    if ( c != '+' && c != '-' && c != '*' && c != '/' && c != ' ' && !std::isdigit(c) )
        return 0;
    return 1;
}

int main( int argc, char** argv)
{
    if ( argc != 2 )
    {
        std::cout << "wrong number of arguments" << std::endl;
        return 1;
    }

    std::string arg(argv[1]);
    for (std::string::iterator it = arg.begin(); it != arg.end(); ++it)
    {
        if ( !valid_char(*it) )
        {
            std::cout << "Error" << std::endl;
            return 1;
        }
    }

    RPN exp(arg);
    try {

        std::cout << exp.eval() << std::endl;
    }
    catch(...)
    {}

    return 0;
}