
#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Form
{
	private:
		const std::string	_name;
		bool				_is_signed;
		const int			_grade_to_sign;
		const int			_grade_to_exec;

	public:
		Form();
		Form(std::string name, int grade_to_sign, int grade_to_exec);
		Form(const Form& src);
		Form& operator=(const Form& other);
		~Form();

		std::string		getName() const;
		bool			getIsSigned();
		int				getGradeToSign() const;
		int				getGradeToExec() const;

		void	beSigned(Bureaucrat& bureaucrat);

		// Exceptions
		class GradeTooHighException : public std::exception
		{
    		public:
        		virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
    		public:
        		virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& out, const Form& form);

#endif
