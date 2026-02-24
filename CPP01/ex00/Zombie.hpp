/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:36:57 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/24 12:24:24 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>
/*
    CONCEPTS C++:

    1) Classe (class)
       - Une classe regroupe des données (attributs) + des fonctions (méthodes).
       - Ici un Zombie possède un nom et sait "s'annoncer".

    2) Encapsulation (private/public)
       - private: inaccessible depuis l'extérieur (protège l'état interne).
       - public: interface utilisable par le reste du programme.

    3) Constructeur / Destructeur
       - Constructeur: appelé à la création de l'objet.
       - Destructeur: appelé à la destruction de l'objet.
       - Ici: on affiche un message dans le destructeur pour vérifier
         quand le Zombie est détruit
*/
class Zombie {
	private:
		std::string _name;

	public:
		Zombie();
		Zombie(std::string name);
		~Zombie();
		
		void	announce(void);

};

Zombie* newZombie(std::string name);
void	randomChump(std::string name);

#endif
