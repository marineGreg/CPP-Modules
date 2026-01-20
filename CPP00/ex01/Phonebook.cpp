/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:36:23 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/20 19:17:06 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook()
{
	this->_contactCount = 0;
    this->_index = 0;
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::printColumn(std::string str) const
{
    if (str.length() > 10) {
        std::cout << str.substr(0, 9) << ".|";
    } else {
        std::cout << std::setw(10) << str << "|";
    }
}

void PhoneBook::addContact()
{
    std::string fields[5] = {"First Name", "Last Name", "Nickname", "Phone Number", "Darkest Secret"};
    std::string inputs[5];

    for (int i = 0; i < 5; i++) {
        while (true) {
            std::cout << fields[i] << ": ";
            if (!std::getline(std::cin, inputs[i])) // Gestion Ctrl+D
                return; 
            if (!inputs[i].empty()) // Vérifie si vide
                break;
            std::cout << "Field cannot be empty!" << std::endl;
        }
    }

    _contacts[_index].setFirstName(inputs[0]);
    _contacts[_index].setLastName(inputs[1]);
    _contacts[_index].setNickName(inputs[2]);
    _contacts[_index].setPhoneNumber(inputs[3]);
    _contacts[_index].setDarkestSecret(inputs[4]);

    if (_contactCount < 8)
		_contactCount++;
    _index = (_index + 1) % 8;
    std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContact() const
{
    if (_contactCount == 0) {
        std::cout << "Phonebook is empty!" << std::endl;
        return;
    }

    std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;

    for (int i = 0; i < _contactCount; i++) {
        std::cout << "|";
        std::cout << std::setw(10) << i << "|";
        printColumn(_contacts[i].getFirstName());
        printColumn(_contacts[i].getLastName());
        printColumn(_contacts[i].getNickName());
        std::cout << std::endl;
    }

    std::cout << "Enter index to display: ";
    std::string indexStr;
    if (!std::getline(std::cin, indexStr)) return;

    std::stringstream ss(indexStr);
    int index;
    std::string extra;

    if (!(ss >> index) || (ss >> extra)) { // Vérifie si c'est un nombre ET s'il n'y a pas de texte après
        std::cout << "Invalid index!" << std::endl;
    } else if (index < 0 || index >= _contactCount) {
        std::cout << "Index out of range!" << std::endl;
    } else {
        std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
		std::cout << "Last Name: " << _contacts[index].getLastName() << std::endl;
		std::cout << "Nickname: " << _contacts[index].getNickName() << std::endl;
		std::cout << "Phone Number: " << _contacts[index].getPhoneNumber() << std::endl;
		std::cout << "Darkest Secret: " << _contacts[index].getDarkestSecret() << std::endl;
    }
}
