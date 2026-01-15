/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:35:56 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/15 19:37:25 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <string>

/*
* This Contact Class represents a contact in the phonebook 
*
* It stores the first name, last name, nickname, phone number and darkest secret
* It allows to define informations, to display them
*/
class Contact {
	private:
		std::string _firstName;
		std::string _lastName;
		std::string _nickName;
		std::string _phoneNumber;
		std::string _darkestSecret;

	public:
		Contact();
		~Contact();
		
		/* ------------- S E T T E R S ------------- */
        void setFirstName(std::string& str);
        void setLastName(std::string& str);
        void setNickName(std::string& str);
        void setPhoneNumber(std::string& str);
		void setDarkestSecret(std::string& str);
		
        /* ------------- G E T T E R S ------------- */
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getNickName() const;
        std::string getPhoneNumber() const;
        std::string getDarkestSecret() const;
};

#endif
