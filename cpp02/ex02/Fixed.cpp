#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : raw_bits(0) {
    // std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed( const Fixed& other ) {
    // std::cout << "Copy constructor called" << std::endl;
    this->raw_bits = other.raw_bits;
}

Fixed& Fixed::operator = ( const Fixed& other ) {
    // std::cout << "Copy assignment operator called" << std::endl;
    if( this != &other ) {
        this->raw_bits = other.raw_bits;
    }
    return *this;
}

Fixed::~Fixed() {
    // std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits( void ) const {
    // std::cout << "getRawBits member function called" << std::endl;
    return this->raw_bits;
}

void Fixed::setRawBits( int const raw ) {
    // std::cout << "setRawBits member function called" << std::endl;
    this->raw_bits = raw;
}

Fixed::Fixed( const int intNum ) {
    // std::cout << "Int constructor called" << std::endl;
    raw_bits = intNum << fractionalBits;
}

Fixed::Fixed( const float floatNum ) {
    // std::cout << "Float constructor called" << std::endl;
    raw_bits = roundf(floatNum * 256);
}

float Fixed::toFloat( void ) const {
    return raw_bits / 256.0f;
}

int Fixed::toInt( void ) const{
    return raw_bits >> fractionalBits;
}

std::ostream &operator << ( std::ostream &out, const Fixed &fnum ) {
    out << fnum.toFloat();
    return out;
}

bool Fixed::operator > ( const Fixed &fnum ) {
    return this->raw_bits > fnum.raw_bits;
}

bool Fixed::operator < ( const Fixed &fnum ) {
    return this->raw_bits < fnum.raw_bits;
}

bool Fixed::operator >= ( const Fixed &fnum ) {
    return this->raw_bits >= fnum.raw_bits;
}

bool Fixed::operator <= ( const Fixed &fnum ) {
    return this->raw_bits <= fnum.raw_bits;
}

bool Fixed::operator == ( const Fixed &fnum ) {
    return this->raw_bits == fnum.raw_bits;
}

bool Fixed::operator != ( const Fixed &fnum ) {
    return this->raw_bits != fnum.raw_bits;
}

Fixed Fixed::operator + ( const Fixed &fnum ) {
    Fixed res;
    res.raw_bits = this->raw_bits + fnum.raw_bits;
    return res;}

Fixed Fixed::operator - ( const Fixed &fnum ) {
    Fixed res;
    res.raw_bits = this->raw_bits - fnum.raw_bits;
    return res;
}

Fixed Fixed::operator * ( const Fixed &fnum ) {
    Fixed res;
    res.raw_bits = (this->raw_bits * fnum.raw_bits) / 256;
    return res;
}

Fixed Fixed::operator / ( const Fixed &fnum ) {
    Fixed res;
    res.raw_bits = (this->raw_bits * 256) / fnum.raw_bits;
    return res;
}

Fixed Fixed::operator++( int ) {
    Fixed tmp(*this);
    this->raw_bits += 1;
    return tmp;
}

Fixed& Fixed::operator ++ (  ) {
    raw_bits += 1;
    return *this;
}; 

Fixed& Fixed::operator--( int ) {
    raw_bits -= 1;
    return *this;
}

Fixed& Fixed::operator -- (  ) {
    raw_bits -= 1;
    return *this;
}; 

const Fixed& Fixed::min( const Fixed &f1, const Fixed &f2 ) {
    return (f1.getRawBits() < f2.getRawBits()) ? f1 : f2;
};

const Fixed& Fixed::max( const Fixed &f1, const Fixed &f2 ) {
    return (f1.getRawBits() > f2.getRawBits()) ? f1 : f2;
};