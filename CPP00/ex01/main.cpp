/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:36:16 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/16 17:06:10 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>

# define PB_LINE " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
# define PB_TITLE "/             My Awesome PhoneBook            /\n"

int main()
{
    PhoneBook phoneBook;
    std::string command;
    
	std::cout << PB_LINE << PB_TITLE << PB_LINE;
    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command))
        {
            std::cout << std::endl;
            break;
        }
        
        if (command == "ADD")
            phoneBook.addContact();
        else if (command == "SEARCH")
            phoneBook.searchContact();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Invalid command!" << std::endl;
    }
    
    return (0);
}
