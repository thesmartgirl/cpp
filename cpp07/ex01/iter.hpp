#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T, typename F> void iter( T* arr, const int len, F *func)
{
    if ( arr == NULL || func == NULL )
        return;
    for ( int i = 0; i < len; i++ )
        func(arr[i]);
}

#endif