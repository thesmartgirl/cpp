#include "ScalarConverter.hpp"
#include <iostream>
#include <errno.h>
#include <limits>
#include <stdlib.h>
#include <iomanip>

/*
    Detect the literal type
    Convert it to its real type
    Explicitly cast it to the other 3 types
    Print correctly
    Handle edge cases
*/

ScalarConverter::ScalarConverter() {};

ScalarConverter::~ScalarConverter() {}; 

ScalarConverter::ScalarConverter( const ScalarConverter& other )
{
    (void) other;
};

ScalarConverter& ScalarConverter::operator= ( const ScalarConverter& other )
{
    (void) other;
    return *this;
};    

/*
    all digits
    possible + or -
    no decimal point
    with limits
*/
int is_integer( std::string str )
{
    if ( str.find('.') != std::string::npos )
        return 0;
    
    int i = 0;
    if ( str[0] == '+' || str[0] == '-' )
        i++;
    for ( unsigned long j = i; j < str.length(); j++ )
    {
        if (!isdigit(str[j]))
            return 0;
    }

    char *endptr;
    errno = 0;
    long val = std::strtol( str.c_str(), &endptr, 10 );
    if ( errno == ERANGE )
        return 0; //overflow
    else if ( endptr == str )
        return 0; //no conversion
    else if ( val > std::numeric_limits<int>::max() || val < std::numeric_limits<int>::min() )
        return 0;
    
    return 1;
}

char   detect_type( std::string literal )
{
    if ( literal == "-inff" || literal == "+inff" || literal == "nanf" )
        return 's';
    if ( literal == "-inf" || literal == "+inf" || literal == "nan" )
        return 's';
    if ( literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'' )
        return 'c';
    if ( literal.length() == 1 && !isdigit(literal[0]) )
        return 'c';   
    if ( literal[literal.length() - 1] == 'f' && literal.find('.') != std::string::npos )
        return 'f';
    if ( literal.find('.') != std::string::npos )
        return 'd';
    if ( is_integer(literal) )
        return 'i';
    return 'x';
}

void print_special( std::string str )
{
    if ( str == "nan" || str == "nanf" )
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    else if ( str == "+inf" || str == "+inff" )
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: inff" << std::endl;
        std::cout << "double: inf" << std::endl;
    }
    else if ( str == "-inf" || str == "-inff" )
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}

void print_char( std::string str )
{
    char c;

    if(str.length() == 1)
        c = str[0];
    else
        c = str[1];

    if ( isprint(c) )
        std::cout << "char: "   << "'" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: "    << static_cast<int>(c) << std::endl;
    std::cout << "float: "  << std::fixed << std::setprecision(1) << static_cast<float>(c) << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;          
}

void print_float( std::string str )
{
    
    char *endptr;
    errno = 0;
    float n = std::strtof( str.c_str(), &endptr );
    
    // std::cout << "printing float " << n << std::endl;
    if ( errno == ERANGE ||  endptr == str.c_str() || (*endptr != 'f' && *endptr != '\0') || (*(endptr + 1) != '\0' && *endptr == 'f') )
        std::cout << "Invalid Input" << std::endl;
    else
    {
        if ( n >= 0 && n <= 127 && isprint(static_cast<int>(n)) )
            std::cout << "char: "   << "'" << static_cast<char>(n) << "'" << std::endl;
        else
            std::cout << "char: Non displayable"   << std::endl;
        
        if ( n > std::numeric_limits<int>::max() || n < std::numeric_limits<int>::min() )
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: "    << static_cast<int>(n) << std::endl;
        
        std::cout << "float: "  << std::fixed << std::setprecision(1) << static_cast<float>(n) << std::endl;
        std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(n) << std::endl;   
    }
}

void print_double( std::string str )
{
    char *endptr;
    errno = 0;
    double n = std::strtod( str.c_str(), &endptr );
    // std::cout << "printing double " << n << std::endl;

    if ( errno == ERANGE ||  endptr == str.c_str() || *endptr != '\0' )
        std::cout << "Invalid Input" << std::endl;
    else
    {
        if ( n >= 0 && n <= 127 && isprint(static_cast<int>(n)) )
            std::cout << "char: "   << "'" << static_cast<char>(n) << "'" << std::endl;
        else
            std::cout << "char: Non displayable"   << std::endl;
        
        if ( n > std::numeric_limits<int>::max() || n < std::numeric_limits<int>::min() )
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: "    << static_cast<int>(n) << std::endl;
        
        if ( n > std::numeric_limits<float>::max() || n < -std::numeric_limits<float>::max() )
            std::cout << "float: impossible" << std::endl;
        else    
            std::cout << "float: "  << std::fixed << std::setprecision(1) << static_cast<float>(n) << std::endl;
        
        std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(n) << std::endl;   
    }
}

void print_int( std::string str )
{
    // std::cout << "printing int" << std::endl;

    char *endptr;
    int n = strtol( str.c_str(), &endptr, 10 );

    if ( n >= 0 && n <= 127 && isprint(static_cast<int>(n)) )
        std::cout << "char: "   << "'" << static_cast<char>(n) << "'" << std::endl;
    else
        std::cout << "char: Non displayable"   << std::endl;
    std::cout << "int: "    << n << std::endl;
    std::cout << "float: "  << std::fixed << std::setprecision(1) << static_cast<float>(n) << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) <<  static_cast<double>(n) << std::endl;   
}

void ScalarConverter::convert( const std::string literal )
{
    switch (detect_type(literal)) {
        case 's':
            print_special(literal);
            break;
        case 'f':
            print_float(literal);
            break;
        case 'd':
            print_double(literal);
            break;
        case 'c':
            print_char(literal);
            break;
        case 'i':
            print_int(literal);
            break;
        default:
            std::cout << "Invalid Input" << std::endl;
            break;
    }
} 