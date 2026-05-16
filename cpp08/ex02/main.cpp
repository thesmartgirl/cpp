#include "MutantStack.hpp"
#include <iostream>

template <typename StackT>
void printStack(const StackT &stack, const std::string &label)
{
    typename StackT::const_iterator it = stack.begin();
    typename StackT::const_iterator ite = stack.end();

    std::cout << label << " [size=" << stack.size() << "]: ";
    if (it == ite)
    {
        std::cout << "<empty>" << std::endl;
        return;
    }
    while (it != ite)
    {
        std::cout << *it;
        ++it;
        if (it != ite)
            std::cout << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "-- MutantStack coverage --" << std::endl;

    MutantStack<int> mstack;
    std::cout << "[basic] push 5, 17" << std::endl;
    mstack.push(5);
    mstack.push(17);
    std::cout << "[basic] top: " << mstack.top() << std::endl;
    mstack.pop();
    std::cout << "[basic] size after pop: " << mstack.size() << std::endl;

    std::cout << "[iterator] push 3, 5, 737, 0" << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    printStack(mstack, "[iterator] forward iteration");

    const MutantStack<int> &constRef = mstack;
    printStack(constRef, "[iterator] const view");

    std::cout << "[iterator] manual iterator walk with pre-increment/decrement" << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    std::cout << "[copy] construct from existing stack" << std::endl;
    MutantStack<int> copied(mstack);
    printStack(copied, "[copy] copied stack");

    std::cout << "[copy] assign into a fresh stack" << std::endl;
    MutantStack<int> assigned;
    assigned.push(-1);
    assigned = mstack;
    printStack(assigned, "[copy] assigned stack");

    std::cout << "[compatibility] convert to std::stack" << std::endl;
    std::stack<int> s(mstack);
    std::cout << "[compatibility] std::stack size: " << s.size() << std::endl;
    std::cout << "[compatibility] std::stack top: " << s.top() << std::endl;

    std::cout << "[empty] check empty stack iteration" << std::endl;
    MutantStack<int> empty;
    printStack(empty, "[empty] empty stack");

    return 0;
}