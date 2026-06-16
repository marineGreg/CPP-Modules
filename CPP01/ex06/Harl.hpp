
#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>

/*
  Objectif principal du sujet :
  - Apprendre à utiliser l'instruction "switch" pour le contrôle de flux.
  - Implémenter un système de filtrage de logs : on affiche le niveau 
    demandé ET tous les niveaux de gravité supérieure.
  
  Logique technique :
  - On convertit la chaîne (string) en index (int) car le switch ne 
    fonctionne pas sur les chaînes de caractères en C++.
  - Utilisation du "fall-through" (absence volontaire de 'break') dans 
    le switch pour laisser l'exécution couler vers les niveaux supérieurs.
  - Gestion du cas 'default' pour les entrées non valides ou insignifiantes.
*/
class Harl {
	private:
		void debug(void);
		void info(void);
		void warning(void);
		void error(void);

	public:
		Harl();
		~Harl();

		void complain(std::string level);
};

#endif
