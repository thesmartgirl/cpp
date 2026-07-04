#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

class BitcoinExchange {

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator= (const BitcoinExchange& other);
        ~BitcoinExchange();
        void print_exchangeRates();
        void exchange( std::string );
        
        class ParseLineException : public std::exception {
            public:
                explicit ParseLineException( const std::string& message );
                virtual ~ParseLineException() throw();
                virtual const char* what() const throw();
        
            private:
                std::string message;
        };
    
    private:
        std::map<std::string, double> rates;
        std::pair<std::string, double> parse_line( const std::string& line, char sep ); // please fix this
        bool valid_date( std::string date );
        bool is_positive( std::string rate );
        double apply_rate( std::pair<std::string, double> );

};



#endif