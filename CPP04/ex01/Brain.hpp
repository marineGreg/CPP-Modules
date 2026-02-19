/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:38:48 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/19 17:38:49 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>

class Brain {
	public:
    	std::string ideas[100];

    	Brain();
    	Brain(const Brain& other);
    	Brain& operator=(const Brain& other);
    	~Brain();
};

#endif
