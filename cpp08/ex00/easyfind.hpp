#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>

template <typename T>
typename T::iterator  easyfind(T& container, int n) {
    typename T::iterator iter = std::find(container.begin(), container.end(), n);
    if (iter == container.end())
        throw std::exception();
    return iter;
}

template <typename T>
typename T::const_iterator  easyfind(const T& container, int n) {
    typename T::const_iterator iter = std::find(container.begin(), container.end(), n);
    if (iter == container.end())
        throw std::exception();
    return iter;
}

#endif