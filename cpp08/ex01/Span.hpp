#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>

class Span {
   
    public: 

        Span(unsigned int N);
        ~Span();
        Span(const Span& other);
        Span& operator=(const Span& other);
        void addNumber(int n);
        int shortestSpan();
        int longestSpan();

        void addRange( std::vector<int>::iterator begin, std::vector<int>::iterator end) ;
    
    private:

        std::vector<int> v;
        unsigned int N;

};

#endif