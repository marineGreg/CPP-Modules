/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:36:27 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/16 18:01:04 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

/*
* This PhoneBook Class represents the phonebook 
* It stores the 8 Contacts max, the total of contacts and the old index
*/
class PhoneBook {
	private:
		Contact _contacts[8];
		int     _contactCount;  // Nombre total de contacts ajoutés
    	int     _index;	// Index du plus vieux contact (pour le remplacer)
		
		void printColumn(std::string str) const;
		
	public:
		PhoneBook();
		~PhoneBook();
		
		void addContact();
		void searchContact() const;
};

#endif