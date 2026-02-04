#include "ScavTrap.hpp"

int main() {
    std::cout << "--- Construction de Scav ---" << std::endl;
    ScavTrap scav("Scavenger");

    std::cout << "\n--- Tests de stats ---" << std::endl;
    scav.attack("un intrus"); // Doit faire 20 dégâts
    scav.beRepaired(10);
    scav.guardGate();

    std::cout << "\n--- Test de mort ---" << std::endl;
    scav.takeDamage(150);
    scav.attack("quelqu'un"); // Ne peut pas car mort

    std::cout << "\n--- Destruction ---" << std::endl;
    return 0;
}
