/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:18:29 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/27 11:33:38 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
    int N = 5;
    Zombie* maHorde = zombieHorde(N, "Soldat");

    for (int i = 0; i < N; i++) {
        maHorde[i].announce();
    }

    delete[] maHorde; 

    return 0;
}
