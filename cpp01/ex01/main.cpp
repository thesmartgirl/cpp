#include "Zombie.hpp"

int main()
{
    Zombie *zombieOnHeap;
    zombieOnHeap = zombieHorde(5, "HordeMember");
    for (int i = 0; i < 5; ++i) {
        zombieOnHeap[i].announce();
    }
    delete[] zombieOnHeap;
}