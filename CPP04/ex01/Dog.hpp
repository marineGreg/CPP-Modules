/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:18 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/03 19:12:37 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	
	private:
    	Brain* _brain; // Attribut prive
	
	public:
    	Dog();
    	Dog(const Dog& other);
    	Dog& operator=(const Dog& other);
    	~Dog();

    	void makeSound() const;
};

