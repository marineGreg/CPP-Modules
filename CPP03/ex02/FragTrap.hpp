/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:37:03 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/11 15:00:27 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
	
	public:
    	FragTrap();
    	FragTrap(std::string name);
    	FragTrap(const FragTrap& other);
    	FragTrap& operator=(const FragTrap& other);
    	~FragTrap();

    	void highFivesGuys(void);
};

#endif