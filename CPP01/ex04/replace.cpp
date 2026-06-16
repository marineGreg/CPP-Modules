
#include <iostream>
#include <fstream>
#include <string> 

/**
 * @brief Ouvre un fichier, remplace chaque occurrence de s1 par s2 
 * et écrit le résultat dans un fichier <filename>.replace.
 * 
 * Étapes clés :
 * 1. Ouverture sécurisée du fichier source (utilisation de c_str() pour C++98).
 * 2. Vérification si le fichier est vide via peek() pour éviter un traitement inutile.
 * 3. Création du fichier de sortie .replace.
 * 4. Lecture ligne par ligne : pour chaque ligne, on cherche s1 en boucle.
 * 5. Algorithme de remplacement : on découpe la ligne avec substr() pour insérer s2,
 *    en faisant avancer l'index 'pos' pour éviter les boucles infinies.
 * 6. Gestion précise du formatage : on rajoute std::endl seulement s'il ne s'agit 
 *    pas de la dernière ligne du fichier.
 */
void	run_replace(std::string filename, std::string s1, std::string s2)
{
	std::ifstream	input(filename.c_str());
	if (!input.is_open())
	{
		std::cerr << "Error: Could not open file" << std::endl;
		return ;
	}
	if (input.peek() == std::ifstream::traits_type::eof())
	{
		std::cerr << "Error: The input file is empty" << std::endl;
		input.close();
		return ;
	}
	std::ofstream	output((filename + ".replace").c_str());
	if (!output.is_open())
	{
		std::cerr << "Error: Could not create output file" << std::endl;
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
