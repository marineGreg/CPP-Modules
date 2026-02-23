/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:00:00 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/23 15:00:00 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include <iostream>

MateriaSource::MateriaSource() {
	for (int i = 0; i < 4; i++)
		_templates[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource& other) {
	for (int i = 0; i < 4; i++) {
		if (other._templates[i])
			_templates[i] = other._templates[i]->clone();
		else
			_templates[i] = NULL;
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
	if (this != &other) {
		// Nettoyage des templates actuels
		for (int i = 0; i < 4; i++) {
			if (_templates[i]) {
				delete _templates[i];
				_templates[i] = NULL;
			}
		}
		
		// Copie profonde des templates
		for (int i = 0; i < 4; i++) {
			if (other._templates[i])
				_templates[i] = other._templates[i]->clone();
			else
				_templates[i] = NULL;
		}
	}
	return *this;
}

MateriaSource::~MateriaSource() {
	for (int i = 0; i < 4; i++) {
		if (_templates[i]) {
			delete _templates[i];
			_templates[i] = NULL;
		}
	}
}

void MateriaSource::learnMateria(AMateria* m) {
	if (!m) {
		std::cout << "Cannot learn a NULL materia!" << std::endl;
		return;
	}
	
	for (int i = 0; i < 4; i++) {
		if (!_templates[i]) {
			_templates[i] = m;
			// std::cout << "Learned materia: " << m->getType() << std::endl;
			return;
		}
	}
	
	// Si la source est pleine, on delete la materia pour éviter les leaks
	std::cout << "MateriaSource is full! Cannot learn more materias." << std::endl;
	delete m;
}

AMateria* MateriaSource::createMateria(std::string const & type) {
	for (int i = 0; i < 4; i++) {
		if (_templates[i] && _templates[i]->getType() == type) {
			// std::cout << "Creating materia: " << type << std::endl;
			return _templates[i]->clone();
		}
	}
	
	// std::cout << "Unknown materia type: " << type << std::endl;
	return NULL;
}
