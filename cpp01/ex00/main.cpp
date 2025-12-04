#include "Zombie.hpp"

int main()
{
    Zombie *zombieOnHeap;
    zombieOnHeap = newZombie("onHeap");
    zombieOnHeap->announce();
    delete zombieOnHeap;

    randomChump("onStack");
}