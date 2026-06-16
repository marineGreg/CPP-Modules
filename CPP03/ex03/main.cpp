
#include "DiamondTrap.hpp"

int main() {
    std::cout << "=== TEST 1: Construction ===" << std::endl;
    DiamondTrap diamond("Monster");

    std::cout << "\n=== TEST 2: whoAmI() ===" << std::endl;
    diamond.whoAmI();

    std::cout << "\n=== TEST 3: Attack (de ScavTrap) ===" << std::endl;
    diamond.attack("enemy");

    std::cout << "\n=== TEST 4: Capacites heritees ===" << std::endl;
    diamond.guardGate();       // De ScavTrap
    diamond.highFivesGuys();   // De FragTrap
    diamond.takeDamage(30);    // De ClapTrap
    diamond.beRepaired(15);    // De ClapTrap

    std::cout << "\n=== TEST 5: Constructeur de copie ===" << std::endl;
    DiamondTrap copy(diamond);
    copy.whoAmI();

    std::cout << "\n=== TEST 6: Endurance (50 energy) ===" << std::endl;
    DiamondTrap marathon("Marathon");
    for (int i = 0; i < 52; i++)
        marathon.attack("dummy");

    std::cout << "\n=== TEST 7: Comparaison ===" << std::endl;
    ClapTrap clap("Clap");
    ScavTrap scav("Scav");
    FragTrap frag("Frag");
    DiamondTrap ultimate("Ultimate");
    
    clap.attack("target");
    scav.attack("target");
    frag.attack("target");
    ultimate.attack("target");
    ultimate.whoAmI();

    std::cout << "\n=== Destruction ===" << std::endl;
    return 0;
}
