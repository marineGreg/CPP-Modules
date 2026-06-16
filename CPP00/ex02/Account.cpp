
#include "Account.hpp"
#include <iostream>

/*
  CONCEPTS C++ :

    - L'exercice demande de reproduire exactement un comportement à partir 
      de fichiers de logs. C'est un exercice de rétro-ingénierie (comprendre 
      le code interne juste en regardant les résultats en sortie).
	  
    - Membres Statiques (Attributs statiques):
      Les variables marquées 'static' (ex: _nbAccounts) n'appartiennent pas 
      à un objet précis, mais à la CLASSE entière. 
      Il n'en existe qu'une seule copie pour TOUS les comptes. 
      C'est le "coffre-fort global" de la banque.

    - Méthodes Statiques (Fonctions statiques):
      Une fonction 'static' peut être appelée sans avoir besoin d'un objet.
      (Ex: Account::displayAccountsInfos()).
      Elle ne peut accéder qu'aux variables statiques. Elle n'a pas 
      accès à 'this' (elle ne sait pas quel compte individuel elle regarde).

    - Initialisation Hors-Classe:
      En C++, les attributs statiques doivent être initialisés obligatoirement 
      dans le fichier .cpp, en dehors de toute fonction.

    - Typedef:
      'typedef Account t;' crée un alias. 't' devient un synonyme de 'Account'.
      C'est une pratique courante pour raccourcir les noms de types complexes.
*/

// --- Initialisation des membres statiques ---
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

// --- Getters statiques (fournis dans le .hpp) ---
int Account::getNbAccounts(void) { return _nbAccounts; }
int Account::getTotalAmount(void) { return _totalAmount; }
int Account::getNbDeposits(void) { return _totalNbDeposits; }
int Account::getNbWithdrawals(void) { return _totalNbWithdrawals; }

void Account::_displayTimestamp(void) {
    std::cout << "[20260205_173241] ";
}

// --- Constructeur ---
Account::Account(int initial_deposit) {
    this->_accountIndex = _nbAccounts;
    this->_amount = initial_deposit;
    this->_nbDeposits = 0;
    this->_nbWithdrawals = 0;

    // Mise à jour des membres statiques globaux
    _nbAccounts++;
    _totalAmount += initial_deposit;

    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "created" << std::endl;
}

// --- Destructeur ---
Account::~Account(void) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "closed" << std::endl;
}

// makeDeposit: Déposer de l'argent sur le compte
void Account::makeDeposit(int deposit) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "p_amount:" << this->_amount << ";"
              << "deposit:" << deposit << ";";

    this->_amount += deposit;
    this->_nbDeposits++;

    _totalAmount += deposit;
    _totalNbDeposits++;

    std::cout << "amount:" << this->_amount << ";"
              << "nb_deposits:" << this->_nbDeposits << std::endl;
}

// makeWithdrawal: Retirer de l'argent du compte
bool Account::makeWithdrawal(int withdrawal) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "p_amount:" << this->_amount << ";";

    if (withdrawal > this->_amount) {
        std::cout << "withdrawal:refused" << std::endl;
        return false;
    }

    this->_amount -= withdrawal;
    this->_nbWithdrawals++;

    _totalAmount -= withdrawal;
    _totalNbWithdrawals++;

    std::cout << "withdrawal:" << withdrawal << ";"
              << "amount:" << this->_amount << ";"
              << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
    return true;
}

int Account::checkAmount(void) const {
    return this->_amount;
}

// displayStatus: Affiche le statut actuel d'un compte
void Account::displayStatus(void) const {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "deposits:" << this->_nbDeposits << ";"
              << "withdrawals:" << this->_nbWithdrawals << std::endl;
}

// --- Fonction statique d'affichage global ---
void Account::displayAccountsInfos(void) {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts << ";"
              << "total:" << _totalAmount << ";"
              << "deposits:" << _totalNbDeposits << ";"
              << "withdrawals:" << _totalNbWithdrawals << std::endl;
}
