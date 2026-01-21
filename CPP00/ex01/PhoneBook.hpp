/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:36:27 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/21 14:24:40 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <iomanip>
# include <sstream>
# include "Contact.hpp"

class PhoneBook {
	private:
		Contact _contacts[8];
		int     _contactCount;
    	int     _index;
		
		void printColumn(std::string str) const;
		
	public:
		PhoneBook();
		~PhoneBook();
		
		void addContact();
		void searchContact() const;
};

#endif