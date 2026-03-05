/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amber <amber@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:18 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/05 18:07:46 by amber            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP
#include "Animal.hpp"

class Dog : public AAnimal {

	public:
    	Dog();
    	Dog(const Dog& other);
    	Dog& operator=(const Dog& other);
    	~Dog();

    	void makeSound() const;
};

#endif
