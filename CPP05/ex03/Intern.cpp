#include "Intern.hpp"

Intern::Intern() {}
Intern::Intern(const Intern &src) { (void)src; }
Intern &Intern::operator=(const Intern &other) { (void)other; return *this; }
Intern::~Intern() {}

// Les fonctions d'aide
AForm *Intern::createShrubbery(std::string target) { return new ShrubberyCreationForm(target); }
AForm *Intern::createRobotomy(std::string target) { return new RobotomyRequestForm(target); }
AForm *Intern::createPresidential(std::string target) { return new PresidentialPardonForm(target); }

AForm *Intern::makeForm(std::string name, std::string target) {
    // 1. Définition des pointeurs sur fonctions membres
    std::string formNames[] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    // 2. Définition des pointeurs sur fonction membres
    AForm *(Intern::*methods[])(std::string) = {
        &Intern::createShrubbery,
        &Intern::createRobotomy,
        &Intern::createPresidential
    };

    // 3. Boucle pour trouver le bon formulaire
    for (int i = 0; i < 3; i++) {
        if (name == formNames[i]) {
            std::cout << "Intern creates " << name << std::endl;
            return (this->*methods[i])(target); // On appelle la fonction correspondante
        }
    }

    // 4. Si rien n'est trouvé
    std::cout << "Error: Intern cannot create form '" << name << "' (unknown name). " << std::endl;
    return NULL;
}
