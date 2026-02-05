/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:02 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/05 16:21:02 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {

	protected:
    	std::string type;

	public:
    	Animal();
    	Animal(const Animal& other);
    	Animal& operator=(const Animal& other);
    	virtual ~Animal(); // Virtuel pour permettre la destruction des classes dérivées

    	virtual void makeSound() const;
    	std::string getType() const;
};

#endif