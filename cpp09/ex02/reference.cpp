#include <iostream>
#include <vector>
#include <algorithm>

// Custom structure to hold pairs for explicit C++98 compliance
struct ElementPair {
    int main_elem;
    int pend_elem;
};

// Binary search insertion based on standard comparisons
void binaryInsertion(std::vector<int>& dest, int value, int upper_bound_idx) {
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

// The recursive Ford-Johnson implementation
std::vector<int> fordJohnsonSort(std::vector<int>& arr) {
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
    for (size_t i = 0; i < pairs.size(); ++i) {
        main_chain_elements.push_back(pairs[i].main_elem);
    }
    
    std::vector<int> sorted_main = fordJohnsonSort(main_chain_elements);

    // 4. Arrange the 'pend' elements to match the new sorted order of 'main'
    std::vector<int> main_chain;
    std::vector<int> pend_chain;
    main_chain.reserve(sorted_main.size() + pairs.size());
    pend_chain.resize(sorted_main.size());

    for (size_t i = 0; i < sorted_main.size(); ++i) {
        main_chain.push_back(sorted_main[i]);
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].main_elem == sorted_main[i]) {
                pend_chain[i] = pairs[j].pend_elem;
                break;
            }
        }
    }

    // 5. Always insert the first pend element at the absolute front (0 comparisons required)
    main_chain.insert(main_chain.begin(), pend_chain[0]);

    // 6. Generate the Jacobsthal index sequence for the optimal insertion group sizes
    std::vector<size_t> jacob = generateJacobsthal(pend_chain.size());
    size_t last_jacob = 1;

    for (size_t i = 1; i < jacob.size(); ++i) {
        size_t current_jacob = jacob[i];
        
        // Insert elements back-to-front within the Jacobsthal group bounds
        for (size_t j = current_jacob - 1; j >= last_jacob; --j) {
            int value_to_insert = pend_chain[j];
            
            // Optimization constraint: limit binary search window
            size_t upper_bound = main_chain.size();
            for (size_t k = 0; k < main_chain.size(); ++k) {
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

int main() {
    int initial_data[] = {19, 143, 7, 18, 13, 4, 102, 1, 765, 230, 2};
    std::vector<int> data(initial_data, initial_data + sizeof(initial_data) / sizeof(int));

    std::cout << "Original: ";
    for (size_t i = 0; i < data.size(); ++i) std::cout << data[i] << " ";
    std::cout << "\n";

    std::vector<int> sorted = fordJohnsonSort(data);

    std::cout << "Sorted:   ";
    for (size_t i = 0; i < sorted.size(); ++i) std::cout << sorted[i] << " ";
    std::cout << "\n";

    return 0;
}