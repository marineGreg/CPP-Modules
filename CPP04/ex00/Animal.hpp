/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:02 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/03 19:13:33 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Animal {

	protected:
    	std::string type;

	public:
    	Animal();
    	Animal(const Animal& other);
    	Animal& operator=(const Animal& other);
    	virtual ~Animal(); // Virtuel pour permettre la destruction des classes derivees

    	virtual void makeSound() const;
    	std::string getType() const;
};
