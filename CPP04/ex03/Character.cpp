/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:00:00 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/23 15:00:00 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() : _name("Unnamed"), _floorCount(0) {
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; i++)
		_floor[i] = NULL;
}

Character::Character(std::string const & name) : _name(name), _floorCount(0) {
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; i++)
		_floor[i] = NULL;
}

Character::Character(const Character& other) : _name(other._name), _floorCount(0) {
	for (int i = 0; i < 4; i++) {
		if (other._inventory[i])
			_inventory[i] = other._inventory[i]->clone();
		else
			_inventory[i] = NULL;
	}
	for (int i = 0; i < 100; i++)
		_floor[i] = NULL;
}

Character& Character::operator=(const Character& other) {
	if (this != &other) {
		_name = other._name;
		
		// Nettoyage de l'inventaire actuel
		for (int i = 0; i < 4; i++) {
			if (_inventory[i]) {
				delete _inventory[i];
				_inventory[i] = NULL;
			}
		}
		
		// Copie profonde de l'inventaire
		for (int i = 0; i < 4; i++) {
			if (other._inventory[i])
				_inventory[i] = other._inventory[i]->clone();
			else
				_inventory[i] = NULL;
		}
	}
	return *this;
}

Character::~Character() {
	// Nettoyage de l'inventaire
	for (int i = 0; i < 4; i++) {
		if (_inventory[i]) {
			delete _inventory[i];
			_inventory[i] = NULL;
		}
	}
	
	// Nettoyage du floor
	for (int i = 0; i < _floorCount; i++) {
		if (_floor[i]) {
			delete _floor[i];
			_floor[i] = NULL;
		}
	}
}

std::string const & Character::getName() const {
	return _name;
}

void Character::equip(AMateria* m) {
	if (!m) {
		std::cout << _name << " cannot equip a NULL materia!" << std::endl;
		return;
	}
	
	for (int i = 0; i < 4; i++) {
		if (!_inventory[i]) {
			_inventory[i] = m;
			// std::cout << _name << " equipped " << m->getType() << " in slot " << i << std::endl;
			return;
		}
	}
	
	// Inventaire plein : on met la materia sur le floor pour éviter les leaks
	std::cout << _name << "'s inventory is full! Materia dropped on the floor." << std::endl;
	if (_floorCount < 100) {
		_floor[_floorCount] = m;
		_floorCount++;
	} else {
		delete m; // Si le floor est plein aussi, on delete
	}
}

void Character::unequip(int idx) {
	if (idx < 0 || idx >= 4) {
		std::cout << "Invalid inventory slot: " << idx << std::endl;
		return;
	}
	
	if (!_inventory[idx]) {
		std::cout << "Slot " << idx << " is already empty!" << std::endl;
		return;
	}
	
	// On met la materia sur le floor au lieu de la delete
	if (_floorCount < 100) {
		_floor[_floorCount] = _inventory[idx];
		_floorCount++;
		// std::cout << _name << " unequipped " << _inventory[idx]->getType() << " from slot " << idx << std::endl;
		_inventory[idx] = NULL;
	} else {
		std::cout << "Floor is full! Cannot unequip." << std::endl;
	}
}

void Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx >= 4) {
		std::cout << "Invalid inventory slot: " << idx << std::endl;
		return;
	}
	
	if (!_inventory[idx]) {
		std::cout << "No materia in slot " << idx << "!" << std::endl;
		return;
	}
	
	_inventory[idx]->use(target);
}
