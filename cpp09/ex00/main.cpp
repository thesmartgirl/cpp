#include "BitcoinExchange.hpp"


int main(int argc, char **argv)
{
    BitcoinExchange ex;
    // ex.print_exchangeRates();

    if ( argc != 2 )
    {
        std::cout << "worng number of arguments" << std::endl;
        return ( 1 );
    }

    std::ifstream file(argv[1]);
    if(!file)
    {
        std::cout << "Error: could not open input file." << std::endl;
        return ( 1 );
    }

    std::string line;
    while ( std::getline(file, line) )
        ex.exchange( line );
}