/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:18:18 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/23 19:21:09 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main() {
	
	randomChump("StackZombie");
	
	Zombie *heapZombie = newZombie("HeapZombie");
	
	heapZombie->announce();

	delete heapZombie;
	
	return 0;
}
