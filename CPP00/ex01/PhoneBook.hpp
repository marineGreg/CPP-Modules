/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:36:27 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/15 16:39:39 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook {
	private:
		Contact _contact[8];
		int		_index; // quel est le prochain contact a remplir
		int		_count; // combien de contacts existent reellement (max 8)
		
	public:
		PhoneBook();
		~PhoneBook();
		
		void addContact(Contact &contact);
		void searchContact() const;
};

#endif