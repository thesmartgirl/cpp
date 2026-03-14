#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {

    public:
        static void convert(const std::string input);

    private:
        ScalarConverter();
        ~ScalarConverter();  
        ScalarConverter( const ScalarConverter& other );
        ScalarConverter& operator= ( const ScalarConverter& other );      
};

#endif