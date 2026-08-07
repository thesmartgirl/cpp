#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe( std::vector<int> unsorted ) : unsorted(unsorted) {
        this->sort();
        this->print();
}

PmergeMe::PmergeMe( const PmergeMe& other )
{
        this->unsorted = other.unsorted;
        this->sorted_q = other.sorted_q;
        this->sorted_v = other.sorted_v;
}

PmergeMe& PmergeMe::operator=( const PmergeMe& other )
{
        if ( this != &other )
        {
                this->unsorted = other.unsorted;
                this->sorted_q = other.sorted_q;
                this->sorted_v = other.sorted_v;     
        }
        return *this;
}

template <typename T>
void print_container( T& v )
{
	int i = 0;
    for ( typename T::const_iterator it = v.begin(); it != v.end(); it++ ) {
        std::cout << *it << " ";
		if ( i++ == 6)
		{
			std::cout << " [...] ";
			return ;
		}
    }
}

void PmergeMe::print()
{
    std::cout << "Before: ";
    print_container(unsorted);
    std::cout << std::endl << "After: ";
    print_container(sorted_v);
    std::cout << std::endl << "Time to process a range of " << unsorted.size() << " elements with std::vector : " << time_v << "us" << std::endl;
    std::cout << "Time to process a range of " << unsorted.size() << " elements with std::deque : " << time_q << "us" << std::endl;
}

// Custom structure to hold pairs for explicit C++98 compliance
struct ElementPair {
    int main_elem;
    int pend_elem;
};

// Binary search insertion based on standard comparisons
template <typename T>
void binaryInsertion(T& dest, int value, int upper_bound_idx) {
    int low = 0;
    int high = upper_bound_idx;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (dest[mid] < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    dest.insert(dest.begin() + low, value);
}

// Generate Jacobsthal numbers up to a specific limit
std::vector<size_t> generateJacobsthal(size_t n) {
    std::vector<size_t> jacob;
    if (n == 0) return jacob;
    
    jacob.push_back(1);
    if (n == 1) return jacob;
    
    jacob.push_back(3);
    while (true) {
        size_t next = jacob.back() + 2 * jacob[jacob.size() - 2];
        if (next >= n) {
            jacob.push_back(n);
            break;
        }
        jacob.push_back(next);
    }
    return jacob;
}

// Custom functor for C++98 compatibility
struct MatchMainElement {
    int target;
    MatchMainElement(int t) : target(t) {}
    
    // The comparison operator used by std::find_if
    bool operator()(const ElementPair& p) const {
        return p.main_elem == target;
    }
};

// The recursive Ford-Johnson implementation
template <typename T>
T fordJohnsonSort(T& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    // 1. Separate an odd element if present
    bool has_straggler = (arr.size() % 2 != 0);
    int straggler = 0;
    if (has_straggler) {
        straggler = arr.back();
        arr.pop_back();
    }

    // 2. Pair elements up and sort each pair locally
    std::vector<ElementPair> pairs;
    // pairs.reserve(arr.size() / 2);
    for (size_t i = 0; i < arr.size(); i += 2) {
        ElementPair p;
        if (arr[i] > arr[i + 1]) {
            p.main_elem = arr[i];
            p.pend_elem = arr[i + 1];
        } else {
            p.main_elem = arr[i + 1];
            p.pend_elem = arr[i];
        }
        pairs.push_back(p);
    }

    // 3. Extract the larger elements (main_elem) and sort them recursively
    std::vector<int> main_chain_elements;
    // main_chain_elements.reserve(pairs.size());
    for (size_t i = 0; i < pairs.size(); i++) {
        main_chain_elements.push_back(pairs[i].main_elem);
    }
    
    std::vector<int> sorted_main = fordJohnsonSort(main_chain_elements);

   

    // 4. Arrange the 'pend' elements to match the new sorted order of 'main'
    T main_chain;
    std::vector<int> pend_chain;

    // main_chain.reserve(sorted_main.size() + pairs.size());
    // pend_chain.reserve(sorted_main.size()); 

    // C++98 Iterator loop over sorted_main
    for (std::vector<int>::const_iterator mit = sorted_main.begin(); mit != sorted_main.end(); ++mit) {
        main_chain.push_back(*mit);
        
        // Use std::find_if with our custom C++98 functor
        std::vector<ElementPair>::const_iterator pit = std::find_if(
            pairs.begin(), 
            pairs.end(), 
            MatchMainElement(*mit)
        );
        
        // If the pair partner is found, push it safely into the pend chain
        if (pit != pairs.end()) {
            pend_chain.push_back(pit->pend_elem);
        }
    }


    // 5. Always insert the first pend element at the absolute front (0 comparisons required)
    main_chain.insert(main_chain.begin(), pend_chain[0]);

    // 6. Generate the Jacobsthal index sequence for the optimal insertion group sizes
    std::vector<size_t> jacob = generateJacobsthal(pend_chain.size());
    size_t last_jacob = 1;

    for (size_t i = 1; i < jacob.size(); i++) {
        size_t current_jacob = jacob[i];
        
        // FIX: Cap the starting index so it never exceeds the last element of pend_chain
        size_t start_idx = (current_jacob - 1 >= pend_chain.size()) ? pend_chain.size() - 1 : current_jacob - 1;
        
        // Insert elements back-to-front within the Jacobsthal group bounds
        for (size_t j = start_idx; j >= last_jacob; j--) {
            int value_to_insert = pend_chain[j];
            
            // Optimization constraint: limit binary search window
            size_t upper_bound = main_chain.size();
            for (size_t k = 0; k < main_chain.size(); k++) {
                if (main_chain[k] == sorted_main[j]) {
                    upper_bound = k;
                    break;
                }
            }
            
            binaryInsertion(main_chain, value_to_insert, upper_bound);
            if (j == last_jacob) break; // Avoid underflow wrap-around with size_t
        }
        last_jacob = current_jacob;
    }

    // 7. Insert the straggler if the initial input array size was odd
    if (has_straggler) {
        binaryInsertion(main_chain, straggler, main_chain.size());
    }

    return main_chain;
}


void PmergeMe::sort(){

    std::vector<int> working = this->unsorted;
	timeval start, end;
    
	gettimeofday(&start, NULL);
	
	this->sorted_v = fordJohnsonSort(working);
	
	gettimeofday(&end, NULL);

    // Calculate precise microsecond difference
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    this->time_v = (seconds * 1000000.0) + microseconds;

	std::deque<int> q(unsorted.begin(), unsorted.end());
	gettimeofday(&start, NULL);
	

	this->sorted_q = fordJohnsonSort(q);
		

	gettimeofday(&end, NULL);
	// Calculate precise microsecond difference
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	this->time_q = (seconds * 1000000.0) + microseconds;

}
