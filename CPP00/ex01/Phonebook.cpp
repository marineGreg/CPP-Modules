/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:36:23 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/15 20:05:05 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>

PhoneBook::PhoneBook()
{
	this->_contactCount = 0;
    this->_oldestIndex = 0;
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::addContact()
{
    std::string input;
    
    std::cout << "First Name: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    this->_contacts[this->_oldestIndex].setFirstName(input);
    
    std::cout << "Last Name: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    this->_contacts[this->_oldestIndex].setLastName(input);
    
    std::cout << "Nickname: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    this->_contacts[this->_oldestIndex].setNickName(input);
    
    std::cout << "Phone Number: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    this->_contacts[this->_oldestIndex].setPhoneNumber(input);
    
    std::cout << "Darkest Secret: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    this->_contacts[this->_oldestIndex].setDarkestSecret(input);
    
    // Mise à jour des compteurs
    if (this->_contactCount < 8)
        this->_contactCount++;
    
    this->_oldestIndex = (this->_oldestIndex + 1) % 8;  // Tourne de 0 à 7
    
    std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContact() const
{
    if (this->_contactCount == 0)
    {
        std::cout << "Phonebook is empty!" << std::endl;
        return;
    }
    
    // Affiche la liste des contacts
    std::cout << std::setw(10) << "Index" << "|";
    std::cout << std::setw(10) << "First Name" << "|";
    std::cout << std::setw(10) << "Last Name" << "|";
    std::cout << std::setw(10) << "Nickname" << std::endl;
    
    for (int i = 0; i < this->_contactCount; i++)
    {
        std::cout << std::setw(10) << i << "|";
        
        // Affiche le prénom (tronqué si > 10 caractères)
        std::string firstName = this->_contacts[i].getFirstName();
        if (firstName.length() > 10)
            std::cout << firstName.substr(0, 9) << ".|";
        else
            std::cout << std::setw(10) << firstName << "|";
        
        // Affiche le nom (tronqué si > 10 caractères)
        std::string lastName = this->_contacts[i].getLastName();
        if (lastName.length() > 10)
            std::cout << lastName.substr(0, 9) << ".|";
        else
            std::cout << std::setw(10) << lastName << "|";
        
        // Affiche le surnom (tronqué si > 10 caractères)
        std::string nickname = this->_contacts[i].getNickName();
        if (nickname.length() > 10)
            std::cout << nickname.substr(0, 9) << ".|";
        else
            std::cout << std::setw(10) << nickname << "|";
        
        std::cout << std::endl;
    }
    
    // Demande l'index
    std::cout << "Enter index: ";
    std::string indexStr;
    std::getline(std::cin, indexStr);
    
    // Vérifie que c'est un nombre
    if (indexStr.empty() || indexStr.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    
    int index = std::atoi(indexStr.c_str());
    
    if (index < 0 || index >= this->_contactCount)
    {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    
    // Affiche le contact complet
    std::cout << "First Name: " << this->_contacts[index].getFirstName() << std::endl;
    std::cout << "Last Name: " << this->_contacts[index].getLastName() << std::endl;
    std::cout << "Nickname: " << this->_contacts[index].getNickName() << std::endl;
    std::cout << "Phone Number: " << this->_contacts[index].getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << this->_contacts[index].getDarkestSecret() << std::endl;
}
