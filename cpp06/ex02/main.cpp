#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <math.h>
#include <iostream>

/*
    randomly instantiates A, B, or C and returns the instance as a Base pointer.
*/
Base * generate(void) {
    switch (rand() % 3)
    {
        case 0:
            return new A();
        case 1:
            return new B();
        default:
            return new C();
    }
}

/*
    If the dynamic_cast is not possible, NULL is returned
*/
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "Object is identified as A" << std::endl;
    if (dynamic_cast<B*>(p))
        std::cout << "Object is identified as B" << std::endl;
    if (dynamic_cast<C*>(p))
        std::cout << "Object is identified as C" << std::endl;
}

/*
    If the dynamic_cast is not possible, NULL is returned
    Since refrences can not be NULL, an exception is thrown
    We need to catch the exception
*/
void identify(Base& p) {
    try { 
        A& ptr = dynamic_cast<A&>(p);
        (void) ptr;
        std::cout << "Object is identified as A" << std::endl;
    }
    catch (...) {}
    try { 
        B& ptr = dynamic_cast<B&>(p);
        (void) ptr;
        std::cout << "Object is identified as B" << std::endl;
    }
    catch (...) {}
    try { 
        C& ptr = dynamic_cast<C&>(p);
        (void) ptr;
        std::cout << "Object is identified as C" << std::endl;
    }
    catch (...) {}
}

int main()
{
    srand(time(NULL));
    Base *R = generate();
    identify(R);
    identify(*R);
    delete R; 
}