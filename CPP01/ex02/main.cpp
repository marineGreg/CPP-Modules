/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:18:29 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/24 12:32:34 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
/*
  Objectif:
  - Comprendre la différence entre un pointeur et une référence,
    et voir que les deux désignent une même variable.

  - Une variable (ici: std::string str) est stockée quelque part en mémoire.
  - Un pointeur contient une adresse mémoire (ex: &str).
  - Une référence est un "alias" (un autre nom) de la même variable.

  Afficher une adresse:
  - On affiche des adresses avec std::cout.
  - Pour la string:          &str
  - Pour le pointeur:        stringPTR (car il contient déjà une adresse)
  - Pour la référence:       &stringREF (adresse de la variable référencée)
*/
int main() {
	std::string  str = "HI THIS IS BRAIN";
	std::string* strPTR = &str;
	std::string& strREF = str;

	std::cout << "=== ADRESSES ===" << std::endl;
	std::cout << "Adresse de &str :	" << &str << std::endl;
	std::cout << "Adresse de strPTR :	" << strPTR << std::endl;
	std::cout << "Adresse de &strRef :	" << &strREF << std::endl;

	std::cout << std::endl;

	std::cout << "=== VALEURS ===" << std::endl;
	std::cout << "Valeur de str : " << str << std::endl;
	std::cout << "Valeur via *strPTR : " << *strPTR << std::endl;
	std::cout << "Valeur via strREF : " << strREF << std::endl;

	return (0);
}
