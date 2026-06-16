
#include "Form.hpp"

Form::Form() : _name("Default"), _is_signed(false), _grade_to_sign(150), _grade_to_exec(150) {}

Form::Form(const std::string name, int grade_to_sign, int grade_to_exec) :
 _name(name), _grade_to_sign(grade_to_sign), _grade_to_exec(grade_to_exec)
{
	if (grade_to_sign < 1 || grade_to_exec < 1)
		throw Form::GradeTooHighException();
	if (grade_to_sign > 150 || grade_to_exec > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form& src) : 
_name(src._name), _is_signed(src._is_signed),_grade_to_sign(src._grade_to_sign),
_grade_to_exec(src._grade_to_exec) {}

Form& Form::operator=(const Form& other) {
    if (this != &other) {
		this->_is_signed = other._is_signed;
    }
    return *this;
}

Form::~Form() {}

std::string Form::getName(void) const {
	return (this->_name);
}

bool Form::getIsSigned(void) {
	return (this->_is_signed);
}

int	Form::getGradeToSign(void) const {
	return (this->_grade_to_sign);
}

int	Form::getGradeToExec(void) const {
	return (this-> _grade_to_exec);
}

void Form::beSigned(Bureaucrat& bureaucrat) {
	if (_is_signed)
		throw std::logic_error("This form is already signed");
	if (bureaucrat.getGrade() <= _grade_to_sign)
		_is_signed = true;
	else
		throw Form::GradeTooLowException();
}

std::ostream &operator<<(std::ostream &out,const Form& form) {
    out << form.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
    return out;
}
