/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:13 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/10 11:38:30 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Animal.hpp"

class Cat : public Animal {

	public:
    	Cat();
    	Cat(const Cat& other);
    	Cat& operator=(const Cat& other);
    	~Cat();

    	void makeSound() const;
};
