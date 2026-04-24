#include "Span.hpp"
#include <iostream>

int main()
{
    Span s1(4);
    s1.addNumber(6);
    s1.addNumber(9);
    s1.addNumber(0);
    s1.addNumber(-5);
    std::cout << s1.shortestSpan() << std::endl;
    std::cout << s1.longestSpan() << std::endl;

    std::srand(time(NULL));
    std::vector<int> in(0);
    for (  int i = 0; i < 100000; i++ )
        in.push_back( rand() );

    Span s2(100008);
    s2.addRange(in.begin(), in.end());
    std::cout << s2.shortestSpan() << std::endl;
    std::cout << s2.longestSpan() << std::endl;
    return 0;
}