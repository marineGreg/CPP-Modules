#ifndef BASE_HPP
#define BASE_HPP

/**
 * Si Base n'avait aucune fonction virtuelle, alors le compilateur sait, dès la
 * compilation, qu'il n'y aura aucune vtable, donc aucune info de type à l'exécution.
 * Résultat : il refuse carrément de compiler ton dynamic_cast<A*>(p), parce
 * qu'il sait à l'avance que ce serait impossible à résoudre.
 */
class Base
{
	public:
		virtual ~Base();
};

#endif