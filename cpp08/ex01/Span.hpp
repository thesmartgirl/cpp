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

        template <typename Iterator>
        void addRange( Iterator begin, Iterator end ) {
            if ( this->v.size() + std::distance( begin, end ) > this->N )
                throw std::runtime_error( "Cannot add more numbers. Maximum size reached" );
            else
                this->v.insert( this->v.end(), begin, end );
        };
    
    private:

        std::vector<int> v;
        unsigned int N;

};

#endif