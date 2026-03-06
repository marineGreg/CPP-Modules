/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:18 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/06 15:49:22 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP
#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {
	
	private:
    	Brain* _brain;
	
	public:
    	Dog();
    	Dog(const Dog& other);
    	Dog& operator=(const Dog& other);
    	~Dog();

    	void makeSound() const;
};

#endif
