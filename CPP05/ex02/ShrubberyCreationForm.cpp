
#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() :
	AForm("ShrubberyCreationForm", 145, 137), _target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) :
	AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src) : 
    AForm(src), _target(src._target) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
    if (this != &other) {
        AForm::operator=(other); // Appelle l'assignation du parent
        this->_target = other._target;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const {
    // 1. Vérifier si l'exécution est possible (doit être fait dans AForm normalement)
    // On suppose que tu as créé checkExec() dans AForm :
    this->checkExec(executor); 

    // 2. Action spécifique : Créer le fichier et écrire l'ASCII Art
    std::string filename = this->_target + "_shrubbery";
    std::ofstream outfile(filename.c_str());

    if (!outfile.is_open()) {
        std::cerr << "Error: could not create file " << filename << std::endl;
        return;
    }
	outfile << "        # o        " << std::endl;
	outfile << "       o # o        " << std::endl;
}