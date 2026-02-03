/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:35:50 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/27 17:53:51 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string> 

void	run_replace(std::string filename, std::string s1, std::string s2)
{
	std::ifstream	input(filename.c_str());
	if (!input.is_open())
	{
		std::cerr << "Could not open file" << std::endl;
		return ;
	}

	std::ofstream	output((filename + ".replace").c_str());
	if (!output.is_open())
	{
		std::cerr << "Error: could not create output file" << std::endl;
		input.close();
		return ;
	}
	
	std::string	line;
	while (std::getline(input, line))
	{
		size_t		pos = 0;
		std::string	newLine;
		
		while (true)
		{
			size_t	found = line.find(s1, pos);
			if (found == std::string::npos)
			{
				newLine += line.substr(pos);
				break ;
			}
			newLine += line.substr(pos, found - pos);
			newLine += s2;
			pos = found + s1.length();
		}
		output << newLine;
		if (!input.eof())
			output << std::endl;
	}
	input.close();
	output.close();
}
