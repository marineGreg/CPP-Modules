/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:27:19 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/17 18:24:55 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main(void)
{
	Fixed		a;
	Fixed const	b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;

	Fixed		c( 12.42f );
	Fixed const	d( 5 );
	std::cout << c << std::endl;
	c = c - d;
	std::cout << c << std::endl;
	c = c + d;
	std::cout << c << std::endl;
	c = c / d;
	std::cout << c << std::endl;
	c = c * d;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << Fixed::min( c, d ) << std::endl;
	
	return 0;
}
