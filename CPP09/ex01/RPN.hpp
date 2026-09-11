#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>


/**
 * Evalue une expression en notation polonaise inversée (RPN) et retourne le résultat.
 * 
 * Les operandes sont empiles jusqu'a la rencontre d'un operateur.
 * L'operateur retire les deux dernieres valeurs, effectue le calcul et
 * remet le resultat sur la pile.
 */
class RPN {
	private:
    	std::stack<int> _stack;

    	bool _isOperator(char c) const;
    	bool _performOperation(char op);

	public:
    	RPN();
    	RPN(const RPN& src);
    	RPN& operator=(const RPN& other);
    	~RPN();

    	bool resolve(const std::string& expression);
};

#endif
