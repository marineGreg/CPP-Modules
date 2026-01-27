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
	std::ifstream	ifs(filename.c_str());
	if (!ifs.is_open())
	{
		std::cerr << "Could not open file" << std::endl;
		return ;
	}

	std::ofstream ofs((filename + ".replace").c_str());
	if (!ofs.is_open())
	{
		std::cerr << "Error: could not create output file" << std::endl;
		ifs.close();
		return ;
	}
	
	std::string	line;
	while (std::getline(ifs, line))
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
		ofs << newLine;
		if (ifs.eof())
			ofs << std::endl;
	}
	ifs.close();
	ofs.close();
}