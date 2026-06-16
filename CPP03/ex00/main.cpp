
#include "ClapTrap.hpp"

int main() {
    std::cout << "=== TEST 1: Construction et actions ===" << std::endl;
    ClapTrap clap("Clappy");
    clap.attack("enemy");
    clap.takeDamage(3);
    clap.beRepaired(5);

    std::cout << "\n=== TEST 2: Constructeur de copie ===" << std::endl;
    ClapTrap copy(clap);
    copy.attack("target");
	copy.takeDamage(12);

    std::cout << "\n=== TEST 3: Epuisement d'energie ===" << std::endl;
    ClapTrap tired("Exhausted");
    for (int i = 0; i < 12; i++)
        tired.attack("dummy");

    std::cout << "\n=== TEST 4: Mort par degats ===" << std::endl;
    ClapTrap victim("Victim");
    victim.takeDamage(15);
    victim.attack("ghost");

    std::cout << "\n=== Destruction ===" << std::endl;
    return 0;
}
