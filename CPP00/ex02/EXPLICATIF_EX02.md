# 📖 Guide Explicatif - CPP00 ex02 : Account Class (GlobalBanksters United)

## 📋 Table des matières
1. [Vue d'ensemble](#vue-densemble)
2. [Structure du projet](#structure-du-projet)
3. [Variables et méthodes statiques](#variables-et-méthodes-statiques)
4. [Attributs de la classe](#attributs-de-la-classe)
5. [Fonctions détaillées](#fonctions-détaillées)
6. [Fichier de test](#fichier-de-test)
7. [Concepts C++ utilisés](#concepts-c-utilisés)
8. [Déroulement complet](#déroulement-complet)

---

## 🎯 Vue d'ensemble

Cet exercice implémente une **classe Account** pour un système bancaire fictif (GlobalBanksters United). L'objectif est de recréer le comportement exact d'une classe en se basant sur :
- Un **fichier header** fourni (Account.hpp) - **non modifiable**
- Un **fichier de test** fourni (tests.cpp) - **non modifiable**
- Un **fichier log** de référence (19920104_091532.log) - **sortie attendue**

### Particularités de l'exercice
- ✅ Le header et les tests sont **imposés**
- ✅ Vous devez **implémenter** Account.cpp
- ✅ La sortie doit **correspondre exactement** au fichier log
- ✅ Introduction aux **variables et méthodes statiques**
- ✅ Gestion de **timestamps** avec `<ctime>`

### Objectifs pédagogiques
- Comprendre les **variables statiques** (partagées entre instances)
- Comprendre les **méthodes statiques** (appelables sans instance)
- Manipulation de **dates et timestamps**
- Formatage précis de la sortie
- Analyse de code existant pour comprendre le comportement attendu

---

## 📁 Structure du projet

```
ex02/
├── Account.hpp              # Header fourni (NE PAS MODIFIER)
├── Account.cpp              # Votre implémentation
├── tests.cpp                # Fichier de test fourni (NE PAS MODIFIER)
├── 19920104_091532.log      # Sortie de référence attendue
└── Makefile                 # Fichier de compilation
```

---

## 🔧 Variables et méthodes statiques

### Qu'est-ce qu'une variable statique ?

Une **variable statique** appartient à la **classe** et non à une **instance particulière**.

```cpp
class Account {
    static int _nbAccounts;  // Partagée par TOUS les objets Account
    int _amount;             // Spécifique à CHAQUE objet Account
};
```

**💡 Visualisation :**
```
Account acc1(100);  →  _nbAccounts = 1 (partagé)
                       acc1._amount = 100 (propre)

Account acc2(200);  →  _nbAccounts = 2 (partagé, mis à jour)
                       acc1._amount = 100 (inchangé)
                       acc2._amount = 200 (propre)
```

### Qu'est-ce qu'une méthode statique ?

Une **méthode statique** peut être appelée **sans créer d'objet**.

```cpp
class Account {
    static int getNbAccounts();  // Méthode statique
    void displayStatus();        // Méthode d'instance
};

// Utilisation :
int total = Account::getNbAccounts();  // ✅ Appel sans objet
Account acc(100);
acc.displayStatus();                   // ✅ Appel sur un objet
```

**⚠️ Restrictions des méthodes statiques :**
- ❌ Ne peuvent pas accéder aux attributs d'instance (`_amount`, `_accountIndex`)
- ✅ Peuvent accéder aux attributs statiques (`_nbAccounts`, `_totalAmount`)
- ✅ Peuvent appeler d'autres méthodes statiques

---

## 📊 Attributs de la classe

### Fichier : Account.hpp (fourni)

#### Attributs statiques (partagés)
```cpp
private:
    static int _nbAccounts;          // Nombre total de comptes créés
    static int _totalAmount;         // Somme totale de tous les comptes
    static int _totalNbDeposits;     // Nombre total de dépôts effectués
    static int _totalNbWithdrawals;  // Nombre total de retraits effectués
```

**📝 Pourquoi statiques ?**
Ces données sont **globales** à tous les comptes :
- On veut savoir combien de comptes existent **au total**
- On veut la somme d'argent **dans toute la banque**
- On veut le nombre total d'opérations **sur tous les comptes**

#### Attributs d'instance (propres à chaque compte)
```cpp
private:
    int _accountIndex;    // Numéro unique du compte (0, 1, 2, ...)
    int _amount;          // Solde du compte
    int _nbDeposits;      // Nombre de dépôts sur CE compte
    int _nbWithdrawals;   // Nombre de retraits sur CE compte
```

**📝 Pourquoi d'instance ?**
Chaque compte a :
- Son propre **numéro** unique
- Son propre **solde**
- Son propre **historique** de transactions

---

## 🔨 Fonctions détaillées

### 1. Initialisation des variables statiques

```cpp
// Account.cpp
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;
```

**📝 Explications :**
- Les variables statiques doivent être **initialisées hors de la classe**
- Syntaxe : `Type Classe::variable = valeur;`
- **Obligatoire** : Sans ça, erreur de compilation (undefined reference)
- Initialisation à 0 : Au démarrage, aucun compte n'existe

---

### 2. Constructeur : `Account(int initial_deposit)`

```cpp
Account::Account(int initial_deposit) {
    // 1. Initialisation des attributs d'instance
    this->_accountIndex = _nbAccounts;      // Index = nombre actuel de comptes
    this->_amount = initial_deposit;        // Solde initial
    this->_nbDeposits = 0;                  // Aucun dépôt pour l'instant
    this->_nbWithdrawals = 0;               // Aucun retrait pour l'instant

    // 2. Mise à jour des variables statiques
    _nbAccounts++;                          // Un compte de plus
    _totalAmount += initial_deposit;        // Ajout au total de la banque

    // 3. Affichage de la création
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "created" << std::endl;
}
```

**📝 Explications détaillées :**

#### Étape 1 : Initialisation des attributs
```cpp
this->_accountIndex = _nbAccounts;
```
- **Ordre d'indexation** : Le premier compte créé aura l'index 0, le deuxième l'index 1, etc.
- À ce moment, `_nbAccounts` vaut 0 pour le premier compte, puis sera incrémenté

```cpp
this->_amount = initial_deposit;
this->_nbDeposits = 0;
this->_nbWithdrawals = 0;
```
- Initialise le solde avec le dépôt initial
- Les compteurs de transactions commencent à 0

#### Étape 2 : Mise à jour globale
```cpp
_nbAccounts++;
_totalAmount += initial_deposit;
```
- Incrémente le nombre total de comptes
- Ajoute le dépôt initial au montant total de la banque

#### Étape 3 : Log de création
```cpp
_displayTimestamp();
std::cout << "index:" << this->_accountIndex << ";";
std::cout << "amount:" << this->_amount << ";";
std::cout << "created" << std::endl;
```

**Sortie attendue :**
```
[19920104_091532] index:0;amount:42;created
```

---

### 3. Destructeur : `~Account(void)`

```cpp
Account::~Account(void) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "closed" << std::endl;
}
```

**📝 Explications :**
- Appelé automatiquement quand un objet est détruit
- Affiche un message de fermeture avec l'index et le solde final
- **Note** : Ne modifie pas les variables statiques (car on ne gère pas leur décrémentation dans cet exercice)

**Sortie attendue :**
```
[19920104_091532] index:0;amount:47;closed
```

---

### 4. Getters statiques

```cpp
int Account::getNbAccounts(void) {
    return _nbAccounts;
}

int Account::getTotalAmount(void) {
    return _totalAmount;
}

int Account::getNbDeposits(void) {
    return _totalNbDeposits;
}

int Account::getNbWithdrawals(void) {
    return _totalNbWithdrawals;
}
```

**📝 Explications :**
- Méthodes **statiques** : Accessibles sans créer d'objet
- Retournent les variables statiques (données globales)
- Utilisées pour obtenir les **statistiques globales** de la banque

**Utilisation dans tests.cpp :**
```cpp
Account::displayAccountsInfos();  // Utilise ces getters
```

---

### 5. Affichage global : `displayAccountsInfos()`

```cpp
void Account::displayAccountsInfos(void) {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts << ";";
    std::cout << "total:" << _totalAmount << ";";
    std::cout << "deposits:" << _totalNbDeposits << ";";
    std::cout << "withdrawals:" << _totalNbWithdrawals << std::endl;
}
```

**📝 Explications :**
- Méthode **statique**
- Affiche un **résumé global** de la banque
- Utilise uniquement les variables statiques

**Sortie attendue :**
```
[19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0
```

**💡 Signification :**
- 8 comptes existent
- Montant total dans la banque : 20049
- 0 dépôts effectués (hors dépôts initiaux)
- 0 retraits effectués

---

### 6. Dépôt : `makeDeposit(int deposit)`

```cpp
void Account::makeDeposit(int deposit) {
    // 1. Affichage avant modification
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "p_amount:" << this->_amount << ";";  // p_ = previous
    std::cout << "deposit:" << deposit << ";";

    // 2. Mise à jour du compte
    this->_amount += deposit;           // Ajoute au solde du compte
    this->_nbDeposits++;                // Incrémente le compteur de dépôts

    // 3. Mise à jour globale
    _totalAmount += deposit;            // Ajoute au total de la banque
    _totalNbDeposits++;                 // Incrémente le compteur global

    // 4. Affichage après modification
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "nb_deposits:" << this->_nbDeposits << std::endl;
}
```

**📝 Explications détaillées :**

#### Format de sortie
```
[timestamp] index:X;p_amount:Y;deposit:Z;amount:A;nb_deposits:B
```

**Exemple :**
```
[19920104_091532] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
```

**💡 Décomposition :**
- `index:0` : Compte n°0
- `p_amount:42` : Solde **avant** le dépôt (previous amount)
- `deposit:5` : Montant déposé
- `amount:47` : Solde **après** le dépôt (42 + 5)
- `nb_deposits:1` : Premier dépôt sur ce compte

#### Mise à jour en cascade
```
Instance :  _amount += deposit          (solde du compte)
            _nbDeposits++                (compteur du compte)

Globale  :  _totalAmount += deposit     (somme totale)
            _totalNbDeposits++           (compteur global)
```

---

### 7. Retrait : `makeWithdrawal(int withdrawal)`

```cpp
bool Account::makeWithdrawal(int withdrawal) {
    // 1. Affichage avant vérification
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "p_amount:" << this->_amount << ";";

    // 2. Vérification des fonds
    if (withdrawal > this->_amount) {
        std::cout << "withdrawal:refused" << std::endl;
        return false;  // ❌ Solde insuffisant
    }

    // 3. Affichage du montant du retrait
    std::cout << "withdrawal:" << withdrawal << ";";

    // 4. Mise à jour du compte
    this->_amount -= withdrawal;        // Soustrait du solde
    this->_nbWithdrawals++;             // Incrémente le compteur

    // 5. Mise à jour globale
    _totalAmount -= withdrawal;         // Soustrait du total
    _totalNbWithdrawals++;              // Incrémente le compteur global

    // 6. Affichage après modification
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;

    return true;  // ✅ Retrait réussi
}
```

**📝 Explications détaillées :**

#### Cas 1 : Retrait refusé (solde insuffisant)
```cpp
if (withdrawal > this->_amount) {
    std::cout << "withdrawal:refused" << std::endl;
    return false;
}
```

**Sortie :**
```
[19920104_091532] index:0;p_amount:47;withdrawal:refused
```

**💡 Points importants :**
- Le solde **n'est pas modifié**
- Les compteurs **ne sont pas incrémentés**
- Retourne `false` pour signaler l'échec

#### Cas 2 : Retrait réussi
**Sortie :**
```
[19920104_091532] index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1
```

**💡 Décomposition :**
- `index:1` : Compte n°1
- `p_amount:819` : Solde avant retrait
- `withdrawal:34` : Montant retiré
- `amount:785` : Solde après retrait (819 - 34)
- `nb_withdrawals:1` : Premier retrait sur ce compte

---

### 8. Vérification du solde : `checkAmount()`

```cpp
int Account::checkAmount(void) const {
    return this->_amount;
}
```

**📝 Explications :**
- Méthode **d'instance** (pas statique)
- **Constante** : Ne modifie pas l'objet
- Simple getter du solde du compte
- **Note** : Non utilisée dans tests.cpp, mais nécessaire pour la compilation

---

### 9. Affichage du statut : `displayStatus()`

```cpp
void Account::displayStatus(void) const {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "deposits:" << this->_nbDeposits << ";";
    std::cout << "withdrawals:" << this->_nbWithdrawals << std::endl;
}
```

**📝 Explications :**
- Méthode **d'instance constante**
- Affiche toutes les informations d'un compte spécifique
- Utilisée pour afficher l'état de tous les comptes

**Sortie attendue :**
```
[19920104_091532] index:0;amount:42;deposits:0;withdrawals:0
```

**💡 Différence avec displayAccountsInfos() :**
- `displayAccountsInfos()` : **Global**, toute la banque (statique)
- `displayStatus()` : **Individuel**, un seul compte (instance)

---

### 10. Timestamp : `_displayTimestamp()`

```cpp
void Account::_displayTimestamp(void) {
    std::time_t now = std::time(0);           // Timestamp actuel (secondes depuis 1970)
    std::tm* ltm = std::localtime(&now);      // Conversion en temps local

    std::cout << "[" 
              << (1900 + ltm->tm_year)                    // Année
              << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon)   // Mois (01-12)
              << std::setfill('0') << std::setw(2) << ltm->tm_mday        // Jour (01-31)
              << "_"
              << std::setfill('0') << std::setw(2) << ltm->tm_hour        // Heure (00-23)
              << std::setfill('0') << std::setw(2) << ltm->tm_min         // Minutes (00-59)
              << std::setfill('0') << std::setw(2) << ltm->tm_sec         // Secondes (00-59)
              << "] ";
}
```

**📝 Explications détaillées :**

#### Structure `std::tm`
```cpp
struct tm {
    int tm_sec;   // Secondes (0-59)
    int tm_min;   // Minutes (0-59)
    int tm_hour;  // Heures (0-23)
    int tm_mday;  // Jour du mois (1-31)
    int tm_mon;   // Mois (0-11) ⚠️ Commence à 0 !
    int tm_year;  // Années depuis 1900 ⚠️
    // ... autres champs
};
```

#### Obtention du temps actuel
```cpp
std::time_t now = std::time(0);
```
- `std::time(0)` : Retourne le nombre de secondes depuis le 1er janvier 1970 (Unix epoch)
- Type `time_t` : Généralement un `long int`

```cpp
std::tm* ltm = std::localtime(&now);
```
- `std::localtime()` : Convertit le timestamp en structure `tm` (temps local)
- Retourne un **pointeur** vers une structure statique

#### Formatage du timestamp

**Année :**
```cpp
(1900 + ltm->tm_year)
```
- `tm_year` : Années **depuis 1900**
- Exemple : Si on est en 2026, `tm_year = 126` → `1900 + 126 = 2026`

**Mois :**
```cpp
std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon)
```
- `tm_mon` : Mois de **0 à 11** (janvier = 0, décembre = 11)
- `(1 + ltm->tm_mon)` : Conversion en **1 à 12**
- `std::setw(2)` : Largeur de 2 caractères
- `std::setfill('0')` : Remplissage avec des zéros
- Exemple : Janvier → `tm_mon = 0` → `1 + 0 = 1` → `"01"`

**Jour, Heure, Minutes, Secondes :**
```cpp
std::setfill('0') << std::setw(2) << ltm->tm_mday
std::setfill('0') << std::setw(2) << ltm->tm_hour
std::setfill('0') << std::setw(2) << ltm->tm_min
std::setfill('0') << std::setw(2) << ltm->tm_sec
```
- Même principe : largeur de 2 avec zéros de remplissage

**Format final :**
```
[YYYYMMDD_HHMMSS]
[19920104_091532]  ← 4 janvier 1992, 09:15:32
```

#### ⚠️ Note importante pour les tests
```cpp
// Pour matcher exactement le fichier log, vous pouvez temporairement :
std::cout << "[19920104_091532] ";  // Timestamp fixe du fichier log

// Ou utiliser le timestamp réel :
_displayTimestamp();  // Timestamp actuel
```

---

## 📝 Fichier de test : tests.cpp

### Structure du fichier de test (fourni)

```cpp
int main(void) {
    // 1. Création des tableaux de données
    int const amounts[]   = { 42, 54, 957, 432, 1234, 0, 754, 16576 };
    int const d[]         = { 5, 765, 564, 2, 87, 23, 9, 20 };        // Dépôts
    int const w[]         = { 321, 34, 657, 4, 76, 275, 657, 7654 };  // Retraits

    // 2. Création de vecteurs
    accounts_t accounts( amounts, amounts + amounts_size );
    ints_t deposits( d, d + d_size );
    ints_t withdrawals( w, w + w_size );

    // 3. Affichage initial
    Account::displayAccountsInfos();
    std::for_each( acc_begin, acc_end, std::mem_fun_ref( &Account::displayStatus ) );

    // 4. Dépôts
    for ( acc_int_t it( acc_begin, dep_begin );
          it.first != acc_end && it.second != dep_end;
          ++(it.first), ++(it.second) ) {
        (*(it.first)).makeDeposit( *(it.second) );
    }

    // 5. Affichage après dépôts
    Account::displayAccountsInfos();
    std::for_each( acc_begin, acc_end, std::mem_fun_ref( &Account::displayStatus ) );

    // 6. Retraits
    for ( acc_int_t it( acc_begin, wit_begin );
          it.first != acc_end && it.second != wit_end;
          ++(it.first), ++(it.second) ) {
        (*(it.first)).makeWithdrawal( *(it.second) );
    }

    // 7. Affichage final
    Account::displayAccountsInfos();
    std::for_each( acc_begin, acc_end, std::mem_fun_ref( &Account::displayStatus ) );

    return 0;
}
```

**📝 Explications :**

### Étape 1 : Création des comptes
```cpp
int const amounts[] = { 42, 54, 957, 432, 1234, 0, 754, 16576 };
accounts_t accounts( amounts, amounts + amounts_size );
```

**Ce qui se passe :**
1. Le vecteur `accounts` est créé avec 8 éléments
2. Pour chaque montant, le **constructeur** `Account(int)` est appelé
3. 8 comptes sont créés avec les index 0 à 7

**Sortie :**
```
[19920104_091532] index:0;amount:42;created
[19920104_091532] index:1;amount:54;created
...
[19920104_091532] index:7;amount:16576;created
```

### Étape 2 : Affichage initial
```cpp
Account::displayAccountsInfos();  // Statistiques globales
```
**Sortie :**
```
[19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0
```

```cpp
std::for_each( acc_begin, acc_end, std::mem_fun_ref( &Account::displayStatus ) );
```
**Ce que ça fait :**
- Parcourt tous les comptes
- Appelle `displayStatus()` sur chacun

**Sortie :**
```
[19920104_091532] index:0;amount:42;deposits:0;withdrawals:0
[19920104_091532] index:1;amount:54;deposits:0;withdrawals:0
...
```

### Étape 3 : Dépôts
```cpp
int const d[] = { 5, 765, 564, 2, 87, 23, 9, 20 };

for (...) {
    (*(it.first)).makeDeposit( *(it.second) );
}
```

**Ce qui se passe :**
- Compte 0 : dépôt de 5 → 42 + 5 = 47
- Compte 1 : dépôt de 765 → 54 + 765 = 819
- Compte 2 : dépôt de 564 → 957 + 564 = 1521
- etc.

**Sortie :**
```
[19920104_091532] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
[19920104_091532] index:1;p_amount:54;deposit:765;amount:819;nb_deposits:1
...
```

### Étape 4 : Retraits
```cpp
int const w[] = { 321, 34, 657, 4, 76, 275, 657, 7654 };

for (...) {
    (*(it.first)).makeWithdrawal( *(it.second) );
}
```

**Ce qui se passe :**
- Compte 0 : retrait de 321, solde = 47 → **REFUSÉ** (insuffisant)
- Compte 1 : retrait de 34, solde = 819 → 819 - 34 = 785 ✅
- Compte 2 : retrait de 657, solde = 1521 → 1521 - 657 = 864 ✅
- etc.

**Sortie :**
```
[19920104_091532] index:0;p_amount:47;withdrawal:refused
[19920104_091532] index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1
[19920104_091532] index:2;p_amount:1521;withdrawal:657;amount:864;nb_withdrawals:1
...
```

### Étape 5 : Destruction
À la fin de `main()`, le vecteur `accounts` est détruit, ce qui appelle le **destructeur** pour chaque compte.

**Sortie :**
```
[19920104_091532] index:0;amount:47;closed
[19920104_091532] index:1;amount:785;closed
...
```

---

## 🎓 Concepts C++ utilisés

### 1. Variables statiques de classe

```cpp
class Account {
    static int _nbAccounts;  // Déclaration dans la classe
};

int Account::_nbAccounts = 0;  // Définition et initialisation hors de la classe
```

**Caractéristiques :**
- **Partagée** par toutes les instances
- **Une seule copie** en mémoire
- **Doit être initialisée** hors de la classe

### 2. Méthodes statiques

```cpp
static int getNbAccounts(void);  // Déclaration

int Account::getNbAccounts(void) {  // Définition
    return _nbAccounts;  // Accès uniquement aux membres statiques
}

// Utilisation :
int nb = Account::getNbAccounts();  // Appel via le nom de classe
```

**Caractéristiques :**
- Appelable **sans instance**
- Accès uniquement aux **membres statiques**
- Pas de `this` disponible

### 3. Manipulation de dates avec `<ctime>`

```cpp
#include <ctime>

std::time_t now = std::time(0);         // Timestamp Unix
std::tm* ltm = std::localtime(&now);    // Conversion en structure tm

int year = 1900 + ltm->tm_year;
int month = 1 + ltm->tm_mon;
```

**Fonctions utiles :**
- `std::time()` : Obtient le timestamp actuel
- `std::localtime()` : Convertit en temps local
- `std::gmtime()` : Convertit en temps UTC

### 4. Formatage avec `<iomanip>`

```cpp
#include <iomanip>

std::cout << std::setw(2);       // Largeur de 2 caractères
std::cout << std::setfill('0');  // Remplissage avec '0'
std::cout << 5;                  // Affiche "05"
```

**Manipulateurs utiles :**
- `std::setw(n)` : Définit la largeur du champ
- `std::setfill(c)` : Définit le caractère de remplissage
- `std::left` / `std::right` : Alignement

### 5. Méthodes constantes

```cpp
void displayStatus(void) const;  // Méthode constante
int checkAmount(void) const;      // Méthode constante
```

**Caractéristiques :**
- Ne peut **pas modifier** les attributs de l'objet
- Peut être appelée sur des objets **constants**
- Garantit la non-modification

### 6. Constructeurs et destructeurs

```cpp
Account::Account(int initial_deposit) {
    // Appelé automatiquement à la création
    _displayTimestamp();
    std::cout << "created" << std::endl;
}

Account::~Account(void) {
    // Appelé automatiquement à la destruction
    _displayTimestamp();
    std::cout << "closed" << std::endl;
}
```

### 7. Valeur de retour booléenne

```cpp
bool Account::makeWithdrawal(int withdrawal) {
    if (withdrawal > this->_amount) {
        return false;  // Échec
    }
    // ... traitement ...
    return true;  // Succès
}
```

**Utilisation :**
```cpp
if (account.makeWithdrawal(100)) {
    std::cout << "Success!" << std::endl;
} else {
    std::cout << "Insufficient funds!" << std::endl;
}
```

---

## 📊 Déroulement complet

### État initial (après création des 8 comptes)

| Index | Montant | Dépôts | Retraits |
|-------|---------|--------|----------|
| 0     | 42      | 0      | 0        |
| 1     | 54      | 0      | 0        |
| 2     | 957     | 0      | 0        |
| 3     | 432     | 0      | 0        |
| 4     | 1234    | 0      | 0        |
| 5     | 0       | 0      | 0        |
| 6     | 754     | 0      | 0        |
| 7     | 16576   | 0      | 0        |

**Statistiques globales :**
- Comptes : 8
- Total : 20049
- Dépôts : 0
- Retraits : 0

---

### Après les dépôts

| Index | Montant initial | Dépôt | Nouveau montant | Dépôts |
|-------|----------------|-------|-----------------|--------|
| 0     | 42             | +5    | 47              | 1      |
| 1     | 54             | +765  | 819             | 1      |
| 2     | 957            | +564  | 1521            | 1      |
| 3     | 432            | +2    | 434             | 1      |
| 4     | 1234           | +87   | 1321            | 1      |
| 5     | 0              | +23   | 23              | 1      |
| 6     | 754            | +9    | 763             | 1      |
| 7     | 16576          | +20   | 16596           | 1      |

**Statistiques globales :**
- Comptes : 8
- Total : 21524 (20049 + 1475)
- Dépôts : 8
- Retraits : 0

---

### Après les retraits

| Index | Montant avant | Retrait | Résultat | Nouveau montant | Retraits |
|-------|---------------|---------|----------|-----------------|----------|
| 0     | 47            | -321    | ❌ REFUSÉ | 47              | 0        |
| 1     | 819           | -34     | ✅ OK     | 785             | 1        |
| 2     | 1521          | -657    | ✅ OK     | 864             | 1        |
| 3     | 434           | -4      | ✅ OK     | 430             | 1        |
| 4     | 1321          | -76     | ✅ OK     | 1245            | 1        |
| 5     | 23            | -275    | ❌ REFUSÉ | 23              | 0        |
| 6     | 763           | -657    | ✅ OK     | 106             | 1        |
| 7     | 16596         | -7654   | ✅ OK     | 8942            | 1        |

**Statistiques globales :**
- Comptes : 8
- Total : 12442 (21524 - 9082)
- Dépôts : 8
- Retraits : 6 (2 refusés)

---

## 💡 Points clés à retenir

### ✅ Variables statiques

**Pourquoi utiliser des variables statiques ?**
- Partager des données entre **toutes les instances**
- Compter le nombre d'objets créés
- Maintenir des **statistiques globales**

**Erreurs courantes :**
```cpp
// ❌ ERREUR : Pas d'initialisation hors de la classe
class Account {
    static int _nbAccounts = 0;  // Erreur en C++98
};

// ✅ CORRECT :
class Account {
    static int _nbAccounts;
};
int Account::_nbAccounts = 0;  // Dans le .cpp
```

### ✅ Méthodes statiques vs méthodes d'instance

| Critère | Statique | Instance |
|---------|----------|----------|
| Appel | `Classe::methode()` | `objet.methode()` |
| Accès membres statiques | ✅ Oui | ✅ Oui |
| Accès membres d'instance | ❌ Non | ✅ Oui |
| Pointeur `this` | ❌ Non disponible | ✅ Disponible |

### ✅ Gestion du timestamp

**Deux approches possibles :**

1. **Timestamp fixe** (pour matcher le log exact) :
```cpp
std::cout << "[19920104_091532] ";
```

2. **Timestamp dynamique** (pour un programme réel) :
```cpp
void Account::_displayTimestamp(void) {
    std::time_t now = std::time(0);
    std::tm* ltm = std::localtime(&now);
    // ... formatage ...
}
```

### ✅ Ordre des opérations

**Important :** L'ordre de mise à jour est crucial !

```cpp
// ✅ CORRECT :
std::cout << "p_amount:" << this->_amount << ";";  // Affiche AVANT
this->_amount += deposit;                          // Puis modifie
std::cout << "amount:" << this->_amount << ";";    // Affiche APRÈS

// ❌ ERREUR :
this->_amount += deposit;                          // Modifie AVANT
std::cout << "p_amount:" << this->_amount << ";";  // Affiche le montant déjà modifié !
```

### ✅ Validation des retraits

```cpp
if (withdrawal > this->_amount) {
    std::cout << "withdrawal:refused" << std::endl;
    return false;  // ⚠️ Important : ne pas modifier les compteurs !
}
```

**Checklist :**
- ✅ Vérifier le solde **avant** toute modification
- ✅ Ne **rien modifier** si le retrait est refusé
- ✅ Retourner `false` pour signaler l'échec

---

## 🎯 Résumé

Ce projet démontre :
- La puissance des **variables statiques** pour partager des données
- L'utilité des **méthodes statiques** pour les opérations globales
- La gestion de **timestamps** avec la bibliothèque `<ctime>`
- Le **formatage précis** de la sortie
- L'**analyse de logs** pour comprendre le comportement attendu

**Architecture :**
```
Classe Account
├── Attributs statiques (partagés)
│   ├── _nbAccounts
│   ├── _totalAmount
│   ├── _totalNbDeposits
│   └── _totalNbWithdrawals
│
├── Attributs d'instance (propres)
│   ├── _accountIndex
│   ├── _amount
│   ├── _nbDeposits
│   └── _nbWithdrawals
│
├── Méthodes statiques
│   ├── getNbAccounts()
│   ├── getTotalAmount()
│   ├── getNbDeposits()
│   ├── getNbWithdrawals()
│   ├── displayAccountsInfos()
│   └── _displayTimestamp()
│
└── Méthodes d'instance
    ├── Account(int)         [Constructeur]
    ├── ~Account()           [Destructeur]
    ├── makeDeposit(int)
    ├── makeWithdrawal(int)
    ├── checkAmount()
    └── displayStatus()
```

**Concept clé :** Les variables statiques permettent de maintenir un **état global** partagé par toutes les instances, essentiel pour des systèmes comme une banque où on veut suivre des statistiques globales.

