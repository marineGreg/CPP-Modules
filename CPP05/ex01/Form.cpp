
#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("default"), _is_signed(false), _grade_to_sign(150),
 _grade_to_exec(150) {}

Form::Form(const std::string &name, int grade_to_sign, int grade_to_exec) :
	_name(name), _is_signed(false), _grade_to_sign(grade_to_sign),
	_grade_to_exec(grade_to_exec)
{
	if (grade_to_sign < 1 || grade_to_exec < 1)
		throw Form::GradeTooHighException();
	if (grade_to_sign > 150 || grade_to_exec > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form& src) :
	_name(src._name), _is_signed(src._is_signed),
	_grade_to_sign(src._grade_to_sign), _grade_to_exec(src._grade_to_exec) {}

Form& Form::operator=(const Form& other) {
    if (this != &other) {
		this->_is_signed = other._is_signed;
    }
    return *this;
}

Form::~Form() {}

std::string	Form::getName(void) const { return _name; }
bool Form::getIsSigned(void) const { return _is_signed; }
int	Form::getGradeToSign(void) const { return _grade_to_sign; }
int	Form::getGradeToExec(void) const { return _grade_to_exec; }

void Form::beSigned(const Bureaucrat& bureaucrat) {
	if (_is_signed)
		throw Form::AlreadySignedException();
	if (bureaucrat.getGrade() > _grade_to_sign)
		throw Form::GradeTooLowException();
	_is_signed = true;
}

const char *Form::GradeTooHighException::what() const throw() {
	return "Grade is too high";
}

const char *Form::GradeTooLowException::what() const throw() {
	return "Grade is too low";
}

const char *Form::AlreadySignedException::what() const throw() {
	return "Form is already signed";
}

std::ostream &operator<<(std::ostream &out, const Form &form) {
    out << "Form " << form.getName()
	<< " (signed: " << (form.getIsSigned() ? "yes" : "no")
	<< ", sign-grade: " << form.getGradeToSign()
	<< ", exec-grade: " << form.getGradeToExec() << ")";
    return out;
}
