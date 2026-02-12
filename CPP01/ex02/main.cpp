/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:18:29 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/12 11:19:37 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main() {
	std::string  str = "HI THIS IS BRAIN";
	std::string* strPTR = &str;
	std::string& strREF = str;

	std::cout << "--- ADRESSES ---" << std::endl;
	std::cout << "Adresse de &str :	" << &str << std::endl;
	std::cout << "Adresse de strPTR :	" << strPTR << std::endl;
	std::cout << "Adresse de &strRef :	" << &strREF << std::endl;

	std::cout << std::endl;

	std::cout << "--- VALEURS ---" << std::endl;
	std::cout << "Valeur de str : " << str << std::endl;
	std::cout << "Valeur via *strPTR : " << *strPTR << std::endl;
	std::cout << "Valeur via strREF : " << strREF << std::endl;

	return (0);
}
