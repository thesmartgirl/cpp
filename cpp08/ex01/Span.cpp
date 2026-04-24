#include "Span.hpp"
#include <iostream>

Span::Span( unsigned int N ) {
    this->N = N;
};

Span::~Span() {};

Span::Span( const Span& other ) {
    this->N = other.N;
    this->v = other.v;
};

Span& Span::operator=( const Span& other ) {
    if ( this != &other )
    {
        this->N = other.N;
        this->v = other.v;
    }
    return *this;
};

void Span::addNumber( int n ) {
    if ( v.size() == N )
        throw std::runtime_error("Cannot add more numbers. Maximum size reached"); 
    else
        v.push_back( n );
};

int Span::shortestSpan() {
    if ( v.size() < 2 )
        throw std::runtime_error("no span found");
    else
    {
        sort(v.begin(), v.end());
        int span = v[1] - v[0];
        for ( std::vector<int>::size_type i = 1; i < v.size() - 1; i++ )
        {
            if ( (v[i+1] - v[i]) < span )
                span =  (v[i+1] - v[i]);
        }
        return span;
    }
};

int Span::longestSpan() {
    if ( v.size() < 2 )
        throw std::runtime_error("no span found");
    else
    {
        sort(v.begin(), v.end());
        return v[v.size()-1] - v[0];
    }
};

void Span::addRange( std::vector<int>::iterator begin, std::vector<int>::iterator end ) {
    if ( this->v.size() + std::distance( begin, end ) > this->N )
        throw std::runtime_error("Cannot add more numbers. Maximum size reached");
    else
        this->v.insert(this->v.end(), begin, end);
};
