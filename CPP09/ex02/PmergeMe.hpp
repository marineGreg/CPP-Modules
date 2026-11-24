#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <cstddef>
# include <vector>
# include <deque>
# include <string>

/**
 * Trie une sequence d'entiers positifs avec l'algorithme
 * de tri fusion-insertion de Ford-Johnson.
 *
 * L'algorithme est implemente separement pour :
 * - std::vector<int>
 * - std::deque<int>
 *
 * Ces deux conteneurs fournissent :
 * - un acces direct par indice en temps constant O(1);
 * - des iterateurs a acces aleatoire ;
 * - les operations necessaires a std::lower_bound() ;
 * - l'insertion d'un element a une position determinee.
 *
 * std::vector stocke ses elements dans une zone memoire contigue.
 * Il favorise donc les parcours et l'utilisation du cache processeur,
 * mais une insertion au milieu peut necessiter le deplacement de tous
 * les elements suivants.
 *
 * std::deque stocke ses elements dans une memoire non contigue
 * un deque est decoupe en plusieurs petits blocs memoire fixes.
 * Chaque saut vers le milieu necessite une double indirection 
 * (trouver le bon bloc, puis l'element dans le bloc), ce qui sollicite un 
 * peu plus le cache processeur
 *
 * Les insertions au milieu restent lineaires pour les deux conteneurs.
 * Leur organisation memoire differente permet cependant de comparer
 * concretement leur comportement avec le meme algorithme.
 *
 * Le programme mesure separement le temps de traitement obtenu
 * pour chaque implementation.
 */
class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void run(int ac, char** av);

	private:
        std::vector<int> _vector;
        std::deque<int>  _deque;

		void _parseInput(int ac, char **av, std::vector<int> &input) const;
		
		void _sortVector(std::vector<int> &numbers);
		void _sortDeque(std::deque<int> &numbers);

        static std::vector<size_t> _buildInsertionOrder(size_t size);
		
        void _printSequence(
            const std::string& label,
            const std::vector<int>& sequence
        ) const;
};

#endif
