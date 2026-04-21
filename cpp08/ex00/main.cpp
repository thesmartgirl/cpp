#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>

// ----------- Utility: print container -----------
template <typename T>
void printContainer(const T& container) {
    typename T::const_iterator it = container.begin();
    typename T::const_iterator end = container.end();

    std::cout << "[ ";
    while (it != end) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << "]" << std::endl;
}

// ----------- Tests -----------

void test_vector_found() {
    std::cout << "\nTest vector - found:\n";
    std::vector<int> v;
    v.push_back(1);
    v.push_back(10);
    v.push_back(20);
    v.push_back(4);

    printContainer(v);

    try {
        std::vector<int>::iterator it = easyfind(v, 10);
        std::cout << "Found: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << "not found" << std::endl;
    }
}

void test_vector_not_found() {
    std::cout << "\nTest vector - not found:\n";
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);

    printContainer(v);

    try {
        std::cout << *easyfind(v, 42) << std::endl;
    } catch (std::exception& e) {
        std::cout << "not found" << std::endl;
    }
}

void test_list_found() {
    std::cout << "\nTest list - found:\n";
    std::list<int> l;
    l.push_back(5);
    l.push_back(15);
    l.push_back(25);

    printContainer(l);

    try {
        std::list<int>::iterator it = easyfind(l, 15);
        std::cout << "Found: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << "not found" << std::endl;
    }
}

void test_const_container() {
    std::cout << "\nTest const vector:\n";
    const std::vector<int> v(3, 7); // {7,7,7}

    printContainer(v);

    try {
        std::vector<int>::const_iterator it = easyfind(v, 7);
        std::cout << "Found: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << "not found" << std::endl;
    }
}

void test_modify_value() {
    std::cout << "\nTest modify via iterator:\n";
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << "Before: ";
    printContainer(v);

    try {
        std::vector<int>::iterator it = easyfind(v, 2);
        *it = 42;
    } catch (std::exception& e) {
        std::cout << "not found" << std::endl;
    }

    std::cout << "After:  ";
    printContainer(v);
}

void test_empty_container() {
    std::cout << "\nTest empty container:\n";
    std::vector<int> v;

    printContainer(v);

    try {
        easyfind(v, 1);
    } catch (std::exception& e) {
        std::cout << "not found" << std::endl;
    }
}

// void test_const_iterator_modification() {
//     std::cout << "\nTest const iterator modification attempt:\n";

//     const std::vector<int> v(3, 7);
//     printContainer(v);

//     try {
//         std::vector<int>::const_iterator it = easyfind(v, 7);

//         // ❌ This should NOT compile:
//         // *it = 42;

//         std::cout << "Cannot modify value through const_iterator (compile-time protection)" << std::endl;

//     } catch (std::exception& e) {
//         std::cout << "not found" << std::endl;
//     }
// }

// ----------- Main -----------

int main() {
    test_vector_found();
    test_vector_not_found();
    test_list_found();
    test_const_container();
    test_modify_value();
    test_empty_container();
    // test_const_iterator_modification();
    return 0;
}