#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>

// Returns the positive integer value parsed from `s`, or 0 on error.
int positive_int( char* s )
{
    if (s == NULL || *s == '\0')
        return 0;

    errno = 0;
    char* endptr = NULL;
    long val = std::strtol(s, &endptr, 10);

    // Check for parse errors: non-digit characters, overflow, or non-positive
    if (endptr == s || *endptr != '\0')
        return 0;
    if (errno == ERANGE || val > INT_MAX || val <= 0)
        return 0;

    return static_cast<int>(val);
}

int main (int argc, char** argv)
{
    if ( argc < 2 )
    {
        std::cout << "Error" << std::endl;
        return 1;
    }

    std::vector<int> unsorted;
    for (int i = 1; i < argc; i++)
    {
        int val = positive_int(argv[i]);
        if (!val)
        {
            std::cout << "Error" << std::endl;
            return 1;
        }
        unsorted.push_back(val);
    }

    PmergeMe s(unsorted);

    return 0;
}