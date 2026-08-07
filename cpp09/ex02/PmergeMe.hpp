#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <deque>
#include <algorithm>
#include <sys/time.h>

class PmergeMe {
    public:
        PmergeMe();
        PmergeMe( std::vector<int> unsorted );
        ~PmergeMe();
        PmergeMe( const PmergeMe& other);
        PmergeMe& operator=( const PmergeMe& other );
        void print();
    
    private:
        std::vector<int> unsorted;
        std::vector<int> sorted_v;
        std::deque<int> sorted_q;
        double time_v;
        double time_q;
        void sort();
};

#endif