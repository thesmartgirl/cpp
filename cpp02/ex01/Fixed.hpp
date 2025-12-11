#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
    private:
        int                 raw_bits;
        static const int    fractionalBits = 8; 
    public:
        Fixed();
        Fixed( const Fixed& other );
        Fixed &operator = ( const Fixed &other );
        Fixed( const int intNum );
        Fixed( const float floatNum );
        float toFloat( void ) const;
        int toInt( void ) const;
        int getRawBits( void ) const;
        void setRawBits( int const raw );
        ~Fixed();
        friend std::ostream &operator << ( std::ostream &out, const Fixed &fnum );
};

#endif