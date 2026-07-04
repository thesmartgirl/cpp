#include "RPN.hpp"

RPN::RPN() {
    std::cout << "EMpty" << std::endl;
};

RPN::RPN( std::string exp ) {
    this->exp = exp;
};

RPN::~RPN() {};

RPN::RPN( const RPN& other ) {
    this->exp = other.exp;
};

RPN& RPN::operator= ( const RPN& other ) {
    if ( this != &other )
    {
        this->exp = other.exp;
    }
    return *this;
};

int RPN::eval() {
    int a = 0;
    int b = 0;
    for ( std::string::iterator it = this->exp.begin(); it != this->exp.end(); it++ )
    {
        if ( std::isdigit( *it ) )
            this->val.push( *it - '0');
        else if ( *it == ' ' )
            continue;
        else 
        {
            if (this->val.size() < 2)
                throw std::runtime_error("Error");
            a = this->val.top();
            this->val.pop();
            b = this->val.top();
            this->val.pop();
            switch ( *it )
            {
                case '+':
                    this->val.push( a + b );
                    break;
                case '-':
                    this->val.push( b - a );
                    break;
                case '*':
                    this->val.push( a * b );
                    break;
                case '/':
                    if ( b == 0 )
                        throw std::runtime_error("Error");
                    this->val.push( b / a );
                    break;
            }   
        }
    }
    if ( this->val.size() != 1 )
        throw std::runtime_error("Error");
    return this->val.top();
};