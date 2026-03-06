/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:02 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/06 11:07:04 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>
#include <string>

class AAnimal {

	protected:
    	std::string type;

	public:
    	AAnimal();
    	AAnimal(const AAnimal& other);
    	AAnimal& operator=(const AAnimal& other);
    	virtual ~AAnimal(); // Virtuel pour permettre la destruction des classes derivees

    	virtual void makeSound() const = 0; // Methode virtuelle pure -> Classe abstraite
    	std::string getType() const;
};

#endif