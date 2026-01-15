/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:35:50 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/15 14:00:23 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {}

Contact::~Contact() {}

// --- Setters ---
void Contact::setFirstName(const std::string& str) {
	 this->_firstName = str; 
}
void Contact::setLastName(const std::string& str) {
	 this->_lastName = str; 
}
void Contact::setNickName(const std::string& str) {
	 this->_nickName = str; 
}
void Contact::setPhoneNumber(const std::string& str) {
	 this->_phoneNumber = str; 
}
void Contact::setDarkestSecret(const std::string& str) {
	 this->_darkestSecret = str; 
}

// --- Getters ---
std::string Contact::getFirstName(void) const { 
	return (this->_firstName); 
}
std::string Contact::getLastName(void) const {
	 return (this->_lastName); 
}
std::string Contact::getNickName(void) const {
	 return (this->_nickName); 
}
std::string Contact::getPhoneNumber(void) const {
	 return (this->_phoneNumber); 
}
std::string Contact::getDarkestSecret(void) const {
	return (this->_darkestSecret); 
}