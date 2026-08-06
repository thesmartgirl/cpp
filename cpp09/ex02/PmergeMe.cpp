#include "PmergeMe.hpp"

        PmergeMe::PmergeMe(){};
        PmergeMe::PmergeMe( std::vector<int> unsorted ) : unsorted(unsorted), sorted_v(sorted_v), sorted_q(sorted_q) {};
        PmergeMe::~PmergeMe(){};
        PmergeMe::PmergeMe( const PmergeMe& other )
        {
                this->unsorted = other.unsorted;
                this->sorted_q = other.sorted_q;
                this->sorted_v = other.sorted_v;
        };
        PmergeMe& PmergeMe::operator=( const PmergeMe& other )
        {
                if ( this != &other )
                {
                        this->unsorted = other.unsorted;
                        this->sorted_q = other.sorted_q;
                        this->sorted_v = other.sorted_v;     
                }
                return *this;
        };

        template <typename T>
        void v_print( T v )
        {
                for ( T::const_iterator it = v.begin(); it != v.end(); ++it ) {
                        std::cout << *it << " ";
                }
        }

        void PmergeMe::print()
        {
                std::cout << "Before: ";
                v_print(unsorted);
                std::cout << std::endl << "After: ";
                v_print(sorted_v);
                std::cout << std::endl << "Time to process a range of " << unsorted.size() << " elements with std::vector : " << time_v << "us" << std::endl;
                std::cout << std::endl << "Time to process a range of " << unsorted.size() << " elements with std::deque : " << time_q << "us" << std::endl;
        };

        void PmergeMe::sort_v(){
                //1. make pairs
                std::vector<std::pair<unsigned int, unsigned int> > pairs;
                std::size_t i = 0;
                for ( ; i + 1 < unsorted.size(); i += 2 )
                        pairs.push_back( std::make_pair( unsorted[i], unsorted[i + 1] ) );
                if ( unsorted.size() % 2 != 0 )
                        pairs.push_back( std::make_pair( unsorted[i], -1) ); //if odd number of numbers last one pairs with -1 
                
                //2. swap pairs if needed
                //3. build main and pending chains
                std::vector<unsigned int> main;
                std::vector<std::pair<unsigned int, unsigned int>> pending;
                for ( size_t i = 0; i < pairs.size(); i++ )
                {
                        if ( pairs[i].first < pairs[i].second )
                                std::swap( pairs[i].first, pairs[i].second) ;
                        main.push_back( pairs[i].first );
                        pending.push_back( std::make_pair( i, pairs[i].second ) );
                }

                //4. sort the main

                
                



        };
        void PmergeMe::sort_q(){};