/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:18:18 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/18 13:05:08 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main()
{
	Harl harl;

	std::cout << "=== Test 1: Tous les niveaux ===" << std::endl;
	harl.complain("DEBUG");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");

	std::cout << "\n=== Test 2: Harl se plaint beaucoup de DEBUG ===" << std::endl;
	for (int i = 0; i < 3; i++)
		harl.complain("DEBUG");

	std::cout << "\n=== Test 3: Harl est vraiment énervé (ERROR) ===" << std::endl;
	for (int i = 0; i < 5; i++)
		harl.complain("ERROR");

	std::cout << "\n=== Test 4: Mélange de plaintes ===" << std::endl;
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("DEBUG");
	harl.complain("ERROR");
	harl.complain("INFO");
	harl.complain("WARNING");

	std::cout << "\n=== Test 5: Niveau invalide ===" << std::endl;
	harl.complain("UNKNOWN");
	harl.complain("CRITICAL");
	harl.complain("");

	return (0);
}
