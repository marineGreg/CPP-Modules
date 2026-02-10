/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:18:18 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/10 13:53:15 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main() {

	Zombie stackZombie("StackZombie");
    stackZombie.announce();
	
	randomChump("RandomStackZombie");
	
	Zombie* heapZombie = newZombie("HeapZombie");
	
	heapZombie->announce();

	delete heapZombie;
	
	return 0;
}
