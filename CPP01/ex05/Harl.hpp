
#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>
/*
  Objectif principal du sujet:
  - Utiliser des pointeurs vers fonctions membres
  - Éviter "forêts" de if/else if/else

  La classe Harl a:
  - 4 fonctions privées: debug/info/warning/error
  - 1 fonction publique: complain(level) qui appelle la bonne fonction
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