#include <string>
#include <iostream>

int main()
{
    std::string str="HI THIS IS BRAIN";
    std::string *stringPTR;
    stringPTR = &str;
    std::string &stringREF = str;

    //The value of the string variable.
    std::cout << str << "\n";
    //The value pointed to by stringPTR.
    std::cout << *stringPTR << "\n";
    //The value pointed to by stringREF.
    std::cout << stringREF << "\n";
    
    return 0;
}