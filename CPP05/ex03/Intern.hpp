#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include <string>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
    public:
        Intern();
        Intern(const Intern &src);
        Intern &operator=(const Intern &other);
        ~Intern();

        AForm *makeForm(std::string name, std::string target);

    private:
        // Fonctions d'aide pour la création
        AForm *createShrubbery(std::string target);
        AForm *createRobotomy(std::string target);
        AForm *createPresidential(std::string target);
};

#endif
