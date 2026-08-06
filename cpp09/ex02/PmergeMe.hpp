#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <deque>

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
        float time_v;
        float time_q;
        void sort_v();
        void sort_q();

};

#endif