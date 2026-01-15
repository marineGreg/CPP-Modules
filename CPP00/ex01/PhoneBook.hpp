/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:36:27 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/15 19:53:28 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook {
	private:
		Contact _contacts[8];
		int     _contactCount;     // Nombre total de contacts ajoutés
    	int     _oldestIndex;	// Index du plus vieux contact (pour le remplacer)
		
	public:
		PhoneBook();
		~PhoneBook();
		
		void addContact();
		void searchContact() const;
};

#endif