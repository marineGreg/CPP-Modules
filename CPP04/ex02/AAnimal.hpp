/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:02 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/03 19:14:13 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
