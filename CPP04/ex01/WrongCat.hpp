/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:36:39 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/03 19:12:23 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {

	public:
    	WrongCat();
    	WrongCat(const WrongCat& other);
    	WrongCat& operator=(const WrongCat& other);
    	~WrongCat();

    	void makeSound() const;
};
