
#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class AForm
{
	private:
		const std::string	_name;
		bool				_is_signed;
		const int			_grade_to_sign;
		const int			_grade_to_exec;

	public:
		AForm();
		AForm(const std::string &name, int grade_to_sign, int grade_to_exec);
		AForm(const AForm &src);
		AForm &operator=(const AForm &other);
		virtual ~AForm();

		std::string		getName() const;
		bool			getIsSigned() const;
		int				getGradeToSign() const;
		int				getGradeToExec() const;

		void			beSigned(const Bureaucrat &bureaucrat);
		virtual void	execute(const Bureaucrat &executor) const = 0;
		void			checkExec(const Bureaucrat &executor) const;

		// Exceptions
		class GradeTooHighException : public std::exception
		{
    		public:
        		virtual const char *what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
    		public:
        		virtual const char *what() const throw();
		};
		class AlreadySignedException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class NotSignedException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif
