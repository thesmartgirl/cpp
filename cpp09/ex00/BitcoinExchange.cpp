#include "BitcoinExchange.hpp"

BitcoinExchange::ParseLineException::ParseLineException( const std::string& message ) : message(message) {}

BitcoinExchange::ParseLineException::~ParseLineException() throw() {}

const char* BitcoinExchange::ParseLineException::what() const throw()
{
    return message.c_str();
}

bool BitcoinExchange::valid_date( std::string date )
{
    // exactly 10 digit
    // - at index 4 and 7
    // mm is between 1 and 12
    // dd is between 1 and 31 ?? what about months with less days
    // feb: dd  <= 28 or 29 (leap)
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    int year, month, day;
    // Extract variables and ensure exactly 3 items are successfully read
    if (std::sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
        return false;
    }

    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap) daysInMonth[1] = 29;
    }

    return day >= 1 && day <= daysInMonth[month - 1];
}

bool BitcoinExchange::is_positive( std::string rate )
{
    // positive double
    // the function extracts exactly 
    //  one item, no leftover characters remain in the string, 
    //  and the parsed value is greater than zero
    double value = 0.0;
    char dummy = '\0';

    // %lf reads a double. %c catches any trailing characters.
    int matched = std::sscanf(rate.c_str(), "%lf %c", &value, &dummy);

    // Valid if exactly one item matched (the double) and value >= 0
    return (matched == 1) && (value >= 0.0);
}

std::pair<std::string, double> BitcoinExchange::parse_line( const std::string& line, char sep )
{
    std::stringstream ss(line);
    std::string date, rate;
    if (!std::getline(ss, date, sep) || !std::getline(ss, rate, sep))
        throw ParseLineException("Error: bad input => " + line);
    if (!valid_date(date))
        throw ParseLineException("Error: bad input => " + line);
    if (!is_positive(rate))
        throw ParseLineException("Error: not a positive number.");

    std::stringstream rateStream(rate);
    double drate = 0.0;
    rateStream >> drate;
    if (rateStream.fail())
        throw ParseLineException("Error: not a positive number.");

    return std::make_pair(date, drate);
}

double BitcoinExchange::apply_rate( std::pair<std::string, double> line )
{
    //lookup the closet date using lower_bound method and apply rate
    std::map<std::string, double>::iterator it = rates.lower_bound( line.first );
    if ( it == rates.begin() || it->first == line.first)
        return it->second * line.second;
    else
    {
        it--;
        return it->second * line.second;
    }
}

/* 
    expects a line of format:
        "date | value"
    valid date format:
        yyyy-mm-dd
    valid value:
        float or positive int between 0 & 1000
*/
void BitcoinExchange::exchange( std::string line )
{
    if (line == "date | value")
        return;

    std::string::size_type pos = 0;
    while ((pos = line.find(" | ", pos)) != std::string::npos)
    {
        line.replace(pos, 3, "|");
        pos += 1;
    }

    try {
        std::pair<std::string, double> parsed = parse_line(line , '|');
        //validate parsed line
        // parsed.first is valid date
        // parsed.second i between 0 and 1000
        if ( parsed.second > 1000 )
            std::cout << "Error: too large a number number." << std::endl;
        else
            std::cout << parsed.first << " => " << parsed.second << " = " << apply_rate( parsed ) << std::endl;
    }
    catch (const ParseLineException& error)
    {
        std::cout << error.what() << std::endl;
    }
}

BitcoinExchange::BitcoinExchange() {
    //load file into map
    std::ifstream file("rates.csv");
    if(!file)
        throw std::runtime_error("Error: could not open file.");

    std::string line;
    while (std::getline(file, line))
    {
        if (line == "date,exchange_rate")
            continue;

        try {
            std::pair<std::string, double> parsed = parse_line(line, ',');
            if (!parsed.first.empty())
                rates[parsed.first] = parsed.second;
        }
        catch (const ParseLineException& error) {
            std::cout << error.what() << std::endl;
        }
        catch (...) {
            std::cout << "Error: could not process file." << std::endl;
        }
    }
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    this->rates = other.rates;
};

BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange& other) {
    if (this != &other)
        this->rates = other.rates;
    return *this;
};

BitcoinExchange::~BitcoinExchange() {};

void BitcoinExchange::print_exchangeRates() {
    for (std::map<std::string, double>::const_iterator it = rates.begin(); it != rates.end(); it++) {
        std::cout << it->first << " : " << std::setprecision(15) << it->second << "\n";
    }
};