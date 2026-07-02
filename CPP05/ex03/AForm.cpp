
#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("default"), _is_signed(false), _grade_to_sign(150),
 _grade_to_exec(150) {}

AForm::AForm(const std::string &name, int grade_to_sign, int grade_to_exec) :
 _name(name), _is_signed(false), _grade_to_sign(grade_to_sign),
 _grade_to_exec(grade_to_exec)
{
	if (grade_to_sign < 1 || grade_to_exec < 1)
		throw AForm::GradeTooHighException();
	if (grade_to_sign > 150 || grade_to_exec > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm& src) :
_name(src._name), _is_signed(src._is_signed),_grade_to_sign(src._grade_to_sign),
_grade_to_exec(src._grade_to_exec) {}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other) {
		this->_is_signed = other._is_signed;
    }
    return *this;
}

AForm::~AForm() {}

std::string	AForm::getName(void) const { return this->_name; }
bool AForm::getIsSigned(void) const { return this->_is_signed; }
int	AForm::getGradeToSign(void) const { return this->_grade_to_sign; }
int	AForm::getGradeToExec(void) const { return this->_grade_to_exec; }

void AForm::beSigned(const Bureaucrat& bureaucrat) {
	if (this->_is_signed)
		throw AForm::AlreadySignedException();
	if (bureaucrat.getGrade() > this->_grade_to_sign)
		throw AForm::GradeTooLowException();
	this->_is_signed = true;
}

void AForm::checkExec(const Bureaucrat &executor) const {
	if (!this->_is_signed)
		throw AForm::NotSignedException();
	if (executor.getGrade() > this->_grade_to_exec)
		throw AForm::GradeTooLowException();
}

const char *AForm::GradeTooHighException::what() const throw() {
	return "Form grade required is too high";
}

const char *AForm::GradeTooLowException::what() const throw() {
	return "Form grade required is too low";
}

const char *AForm::AlreadySignedException::what() const throw() {
	return "Form is already signed";
}

const char *AForm::NotSignedException::what() const throw() {
	return "Form is not signed";
}

std::ostream &operator<<(std::ostream &out, const AForm &form) {
    out << "Form " << form.getName()
	<< " (signed: " << (form.getIsSigned() ? "yes" : "no")
	<< ", sign-grade: " << form.getGradeToSign()
	<< ", exec-grade: " << form.getGradeToExec() << ")";
    return out;
}
