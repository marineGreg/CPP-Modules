
#ifndef ROBOTOMY_CREATION_FORM_HPP
#define ROBOTOMY_CREATION_FORM_HPP

#include "AForm.hpp"

class RobotomyCreationForm : public AForm
{
	private:
		std::string	_target;

	public:
		RobotomyCreationForm();
		RobotomyCreationForm(std::string target);
		RobotomyCreationForm(const RobotomyCreationForm &src);
		RobotomyCreationForm &operator=(const RobotomyCreationForm &other);
		~RobotomyCreationForm();

		void	execute(const Bureaucrat &executor) const;
};

#endif
