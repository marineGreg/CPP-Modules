/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amber <amber@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:13 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/05 18:07:46 by amber            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal {

	private:
    	Brain* _brain; // Attribut privé
		
	public:
    	Cat();
    	Cat(const Cat& other);
    	Cat& operator=(const Cat& other);
    	~Cat();

    	void makeSound() const;
};

#endif
