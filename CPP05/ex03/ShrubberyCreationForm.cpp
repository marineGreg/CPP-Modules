
#include "ShrubberyCreationForm.hpp"

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
    this->checkExec(executor); 

    std::string filename = this->_target + "_shrubbery";
    std::ofstream outfile(filename.c_str());

    if (!outfile.is_open()) {
        std::cerr << "Error: could not create file " << filename << std::endl;
        return;
    }
	outfile << "               ,@@@@@@@," << std::endl;
	outfile << "       ,,,.   ,@@@@@@/@@,  .oo8888o." << std::endl;
	outfile << "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\\\88/8o" << std::endl;
	outfile << "   ,%&\\\\%&&%&&%,@@@\\\\@@@/@@@88\\\\88888/88'" << std::endl;
	outfile << "   %&&%&%&/%&&%@@\\\\@@/ /@@@88888\\\\88888'" << std::endl;
	outfile << "   %&&%/ %&%%&&@@\\\\ V /@@' `88\\\\8 `/88'" << std::endl;
	outfile << "   `&%\\\\ `/%&'    |.|        \\\\ '|8'" << std::endl;
	outfile << "       |o|        | |         | |" << std::endl;
	outfile << "       |.|        | |         | |" << std::endl;
	outfile << " _\\/_\\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/" << std::endl;

	outfile.close();
	std::cout << "Shrubbery file created: " << filename << std::endl;
}
