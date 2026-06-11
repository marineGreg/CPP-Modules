/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:00:00 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/11 17:21:33 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AMateria.hpp"

/**
 * CONCEPT : INTERFACE DE GÉNÉRATION (FACTORY)
 * - Définit le contrat pour une classe capable d'apprendre des modèles de Materias
 *   et de les cloner sur demande via leur nom.
 */
class IMateriaSource {

	public:
		virtual ~IMateriaSource() {}
		
		virtual void learnMateria(AMateria*) = 0;
		virtual AMateria* createMateria(std::string const & type) = 0;
};

