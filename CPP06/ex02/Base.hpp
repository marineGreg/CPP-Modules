#ifndef BASE_HPP
#define BASE_HPP

/**
 * Le dynamic_cast est l'opérateur dédié à la navigation sécurisée dans une 
 * hiérarchie de classes polymorphes (downcasting). 
 * 
 * Contrairement au static_cast, il vérifie la validité de la conversion à 
 * l'exécution (Runtime) en utilisant les informations de type (RTTI). 
 * Si le type réel de l'objet ne correspond pas au type cible :
 * - Il retourne NULL pour les pointeurs.
 * - Il lance une exception std::bad_cast pour les références.
 * 
 * Note : Pour fonctionner, la classe de base doit être polymorphe, 
 * c'est-à-dire posséder au moins une fonction virtuelle (ici le destructeur).
 */
class Base
{
	public:
		virtual ~Base();
};

#endif