#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
        std::cout << "wrong number of arguments" << std::endl;
    else
        ScalarConverter::convert(argv[1]);
    return 0;

}