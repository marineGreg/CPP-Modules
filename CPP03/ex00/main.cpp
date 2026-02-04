#include "ClapTrap.hpp"

int main() {
    std::cout << "--- Construction ---" << std::endl;
    ClapTrap clap("Clappy");
    ClapTrap enemy("Target Dummy");

    std::cout << "\n--- Actions ---" << std::endl;
    clap.attack("Target Dummy");
    enemy.takeDamage(0); // Attack damage est à 0 par défaut

    clap.beRepaired(5);
    
    std::cout << "\n--- Energy Test ---" << std::endl;
    // Utilisons toute l'énergie (il en reste 8 après attack et repair)
    for (int i = 0; i < 9; i++) {
        clap.attack("a fly");
    }

    std::cout << "\n--- Death Test ---" << std::endl;
    enemy.takeDamage(20); // Doit mourir (HP tombe à 0)
    enemy.beRepaired(10); // Ne doit pas fonctionner

    std::cout << "\n--- Destruction ---" << std::endl;
    return 0;
}