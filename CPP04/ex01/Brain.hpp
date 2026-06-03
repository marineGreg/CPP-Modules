/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:38:48 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/03 19:12:57 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
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
