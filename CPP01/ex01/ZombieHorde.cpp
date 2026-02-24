/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:18:15 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/24 12:26:22 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
/*
  zombieHorde()

  CONCEPTS C++:
  - new[] : alloue un tableau d'objets sur la heap (une seule allocation)
  - delete[] : libère le tableau alloué avec new[]
  - initialisation : après new Zombie[N], on donne un nom à chaque Zombie
*/
Zombie* zombieHorde(int N, std::string name) {
	Zombie* horde = new Zombie[N];
	
	for (int i = 0; i < N; i++) {
		horde[i].setName(name);
	}
	return horde;
}
