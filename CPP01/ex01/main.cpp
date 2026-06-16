
#include "Zombie.hpp"

int main() {
    int N = 5;
    Zombie* maHorde = zombieHorde(N, "Zoldat");

    for (int i = 0; i < N; i++) {
        maHorde[i].announce();
    }

    delete[] maHorde;

    return 0;
}
