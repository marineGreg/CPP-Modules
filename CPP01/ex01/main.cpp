/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:18:29 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/12 17:39:48 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
    int N = 5;
    Zombie* maHorde = zombieHorde(N, "Zoldat");

    for (int i = 0; i < N; i++) {
        maHorde[i].announce();
    }

    delete[] maHorde;

    return 0;
}
