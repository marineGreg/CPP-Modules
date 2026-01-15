/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:35:56 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/15 16:39:57 by mgregoir         ###   ########.fr       */
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

		// Setters individuels
        void setFirstName(const std::string& str);
        void setLastName(const std::string& str);
        void setNickName(const std::string& str);
        void setPhoneNumber(const std::string& str);
        void setDarkestSecret(const std::string& str);

        // Getters
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getNickName() const;
        std::string getPhoneNumber() const;
        std::string getDarkestSecret() const;
};

#endif
