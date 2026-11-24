#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

/**
 * Evalue une expression en notation polonaise inversee (RPN)
 * et affiche le resultat.
 *
 * Une std::stack est utilisee car l'evaluation RPN suit un ordre LIFO :
 * la derniere operande empilee est la premiere retiree.
 *
 * Les operandes sont empilees jusqu'a la rencontre d'un operateur.
 * L'operateur retire les deux dernieres valeurs :
 * - la premiere valeur retiree est l'operande droite ;
 * - la seconde est l'operande gauche.
 *
 * Le resultat du calcul est ensuite replace sur la pile.
 * A la fin, la pile doit contenir exactement une valeur.
 *
 * La stack expose uniquement les operations necessaires :
 * push(), top(), pop() et size(). Aucun acces aleatoire n'est requis.
 */
class RPN
{
	public:
		RPN();
		RPN(const RPN& src);
		RPN& operator=(const RPN& other);
		~RPN();

		bool resolve(const std::string& expression);

	private:
    	std::stack<int> _stack;

    	bool _isOperator(char c) const;
    	bool _performOperation(char op);

};

#endif
