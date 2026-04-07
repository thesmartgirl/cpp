#include "iter.hpp"
#include <iostream>

//template <typename T, typename F> void iter( T* arr, const int len, F *func)

void times2(int& n)
{
    n *= 2;
}

void echo(const int& n)
{
    std::cout << n << std::endl;
}

void caps(char& c)
{
    c -= 32;
}

void echo_c(const char& c)
{
    std::cout << c << std::endl;
}

int main()
{
    int arr[] = {0,1,2,3,4};
    int len = 5;
    const int arr2[] = {0,1,2,3,4};

    iter(arr, len, times2); //double each element
    iter(arr, len, echo);   //print the new values
    iter(arr2, len, echo);   //prints originals

    char c_arr[] = {'a', 'b', 'c'};
    int c_len = 3;
    iter(c_arr, c_len, caps); 
    iter(c_arr, c_len, echo_c);   
    // iter(c_arr, c_len, &len); 

    return 0;
}