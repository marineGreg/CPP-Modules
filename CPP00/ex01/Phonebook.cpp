/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:36:23 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/15 16:38:58 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void PhoneBook::addContact(Contact &contact) {
    std::string input;
    Contact&    new_contact = this->_contacts[this->_index % 8];

    // On boucle tant que le champ est vide
    while (true) {
        std::cout << "First Name: ";
        if (!std::getline(std::cin, input) || std::cin.eof()) return;
        if (!input.empty()) break;
    }
    new_contact.setFirstName(input);

    // Tu répètes la même logique pour les 4 autres champs...
    
    this->_index++;
}