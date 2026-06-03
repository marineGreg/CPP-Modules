/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:17:40 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/03 19:13:53 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

class WrongAnimal {

	protected:
    	std::string type;

	public:
    	WrongAnimal();
    	WrongAnimal(const WrongAnimal& other);
    	WrongAnimal& operator=(const WrongAnimal& other);
    	~WrongAnimal(); // PAS de virtual ici

    	void makeSound() const; // PAS de virtual ici
    	std::string getType() const;
};
