#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <stdexcept>
#include <iostream>

class RPN {

    public:
        RPN();
        RPN(std::string exp);
        ~RPN();
        RPN(const RPN& other);
        RPN& operator= (const RPN& other);
        int eval();

    private:
        std::string exp;
        std::stack<int> val;
};

#endif