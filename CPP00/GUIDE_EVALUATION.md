# Guide d'Évaluation CPP00 🎓

Ce guide t'aidera à présenter efficacement chaque exercice lors de ton évaluation.

---

## 📋 Vue d'ensemble du module

**CPP00** introduit les concepts de base du C++ :
- Namespaces
- Classes et instances
- Fonctions membres et attributs
- `std::string`
- Entrées/Sorties avec `std::cout` et `std::cin`
- Membres statiques de classe

---

# Exercise 00 : Megaphone 📢

## 🎯 Objectif
Convertir les arguments de la ligne de commande en majuscules. Premier contact avec C++ et `std::cout`.

## 💡 Concepts présentés
- `std::cout` et `std::endl`
- `std::toupper()` de `<cctype>`
- Arguments de ligne de commande (`argc`, `argv`)

## 🔑 Points clés à expliquer

### 1. La structure du programme

```cpp
#include <iostream>
#include <cctype>

int main(int ac, char **av)
```

**À dire :** 
- `iostream` pour utiliser `std::cout`
- `cctype` pour accéder à `std::toupper()`
- On utilise `ac` et `av` au lieu de `argc` et `argv` (convention 42)

### 2. Gestion du cas sans arguments

```cpp
if (ac == 1) {
    std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    return 0;
}
```

**À dire :**
- Si aucun argument → affichage du message par défaut
- `std::endl` flush le buffer et ajoute un retour à la ligne

### 3. La boucle de conversion

```cpp
for (int i = 1; i < ac; i++) {
    for (int j = 0; av[i][j]; j++)
        std::cout << (char)std::toupper(av[i][j]);
}
std::cout << std::endl;
```

**À dire :**
- Double boucle : parcours de chaque argument, puis de chaque caractère
- `std::toupper()` retourne un `int` → cast en `char` nécessaire
- Pas d'espace entre les arguments (concaténation directe)
- Un seul `std::endl` à la fin

## 🧪 Tests à montrer

```bash
./megaphone "shhhhh... I think the students are asleep..."
# SHHHHH... I THINK THE STUDENTS ARE ASLEEP...

./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
# DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.

./megaphone
# * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

## ⚠️ Erreurs courantes à éviter
- ❌ Oublier le cast `(char)` devant `std::toupper()`
- ❌ Utiliser `std::cout << std::endl` dans la boucle (affichage par ligne)
- ❌ Commencer la boucle à `i = 0` au lieu de `i = 1` (inclure le nom du programme)

---

# Exercise 01 : PhoneBook 📱

## 🎯 Objectif
Créer un répertoire téléphonique avec une classe `PhoneBook` contenant 8 `Contact`. Gestion dynamique et affichage formaté.

## 💡 Concepts présentés
- **Classes** et **instances**
- **Encapsulation** : attributs privés, méthodes publiques
- **Getters** et **Setters**
- **Tableaux statiques** de classe (`Contact _contacts[8]`)
- Formatage avec `std::setw()` et `std::iomanip`
- `std::getline()` pour lire des lignes
- Comportement circulaire (remplacement du plus ancien contact)

## 🔑 Points clés à expliquer

### 1. Architecture des classes

```
PhoneBook
├── Contact _contacts[8]     (tableau statique de 8 contacts)
├── int _contactCount         (nombre de contacts actifs)
└── int _index                (index d'insertion circulaire)

Contact
├── std::string _firstName
├── std::string _lastName
├── std::string _nickName
├── std::string _phoneNumber
└── std::string _darkestSecret
```

**À dire :**
- Séparation des responsabilités : `Contact` = donnée, `PhoneBook` = gestion
- Tous les attributs sont **privés** (encapsulation)
- Accès via **getters/setters** uniquement

### 2. La classe Contact

```cpp
class Contact {
private:
    std::string _firstName;
    // ... autres attributs
public:
    Contact();
    ~Contact();
    
    void setFirstName(const std::string str);
    std::string getFirstName() const;
    // ... autres getters/setters
};
```

**À dire :**
- Attributs privés (préfixe `_` par convention)
- Setters prennent `const std::string` par valeur (simple ici, ou `const std::string&` par référence)
- Getters retournent `std::string` et sont marqués `const` (ne modifient pas l'objet)

### 3. La classe PhoneBook - Constructeur

```cpp
PhoneBook::PhoneBook() {
    this->_contactCount = 0;
    this->_index = 0;
}
```

**À dire :**
- Initialise le compteur de contacts à 0
- Initialise l'index d'insertion à 0
- `this->` explicite pour clarté (optionnel)

### 4. Ajout de contact (ADD)

```cpp
void PhoneBook::addContact() {
    std::string fields[5] = {"First Name", "Last Name", "Nickname", 
                             "Phone Number", "Darkest Secret"};
    std::string inputs[5];

    for (int i = 0; i < 5; i++) {
        while (true) {
            std::cout << fields[i] << ": ";
            if (!std::getline(std::cin, inputs[i]))
                return;  // EOF (Ctrl+D)
            if (!inputs[i].empty())
                break;
            std::cout << "Field cannot be empty!" << std::endl;
        }
    }

    _contacts[_index].setFirstName(inputs[0]);
    // ... autres setters

    if (_contactCount < 8)
        _contactCount++;
    _index = (_index + 1) % 8;  // Circulaire !
}
```

**À dire :**
- Validation : les champs ne peuvent pas être vides
- `std::getline()` gère les espaces dans les noms
- Gestion de EOF (`Ctrl+D`) → retour immédiat
- **Comportement circulaire** : `_index = (_index + 1) % 8`
  - Quand le répertoire est plein, on remplace le contact le plus ancien
- `_contactCount` plafonné à 8

### 5. Recherche de contact (SEARCH) - Affichage du tableau

```cpp
void PhoneBook::searchContact() const {
    if (_contactCount == 0) {
        std::cout << "Phonebook is empty!" << std::endl;
        return;
    }

    std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;

    for (int i = 0; i < _contactCount; i++) {
        std::cout << "|";
        std::cout << std::setw(10) << i << "|";
        _printColumn(_contacts[i].getFirstName());
        _printColumn(_contacts[i].getLastName());
        _printColumn(_contacts[i].getNickName());
        std::cout << std::endl;
    }
    // ... suite pour sélection
}
```

**À dire :**
- Vérification : répertoire vide → message d'erreur
- Formatage : colonnes de 10 caractères alignées à droite
- Affiche uniquement les contacts ajoutés (`_contactCount`)

### 6. Formatage des colonnes

```cpp
void PhoneBook::_printColumn(std::string str) const {
    if (str.length() > 10) {
        std::cout << str.substr(0, 9) << ".|";
    } else {
        std::cout << std::setw(10) << str << "|";
    }
}
```

**À dire :**
- Si plus de 10 caractères → tronqué à 9 + point `.`
- Sinon → aligné à droite avec `std::setw(10)`
- Méthode **privée** (préfixe `_`) : utilisée uniquement en interne

### 7. Sélection et affichage d'un contact

```cpp
std::cout << "Enter index to display: ";
std::string indexStr;
if (!std::getline(std::cin, indexStr)) return;

std::stringstream ss(indexStr);
int index;
std::string extra;

if (!(ss >> index) || (ss >> extra)) {
    std::cout << "Invalid index!" << std::endl;
} else if (index < 0 || index >= _contactCount) {
    std::cout << "Index out of range!" << std::endl;
} else {
    std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
    // ... affichage complet du contact
}
```

**À dire :**
- Lecture de l'index sous forme de `std::string`
- `std::stringstream` pour convertir et **valider**
- `!(ss >> index)` → échec si pas un nombre
- `(ss >> extra)` → échec s'il reste du texte après le nombre
- Vérification des bornes : `0 <= index < _contactCount`
- Affichage complet uniquement si valide

### 8. Le main - Boucle de commandes

```cpp
int main() {
    PhoneBook phoneBook;
    std::string command;
    
    while (true) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command)) {
            std::cout << std::endl;
            break;  // EOF
        }
        
        if (command == "ADD")
            phoneBook.addContact();
        else if (command == "SEARCH")
            phoneBook.searchContact();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Invalid command !" << std::endl;
    }
    return 0;
}
```

**À dire :**
- Instanciation d'un objet `PhoneBook`
- Boucle infinie avec gestion de `EOF`
- 3 commandes : `ADD`, `SEARCH`, `EXIT`
- Comparaison de `std::string` avec `==`

## 🧪 Tests à montrer

```bash
./phonebook
> ADD
First Name: John
Last Name: Doe
Nickname: JD
Phone Number: 0612345678
Darkest Secret: Loves pineapple pizza

> ADD
First Name: Jane
Last Name: Smith
Nickname: JS
Phone Number: 0698765432
Darkest Secret: Secretly a robot

> SEARCH
|     Index|First Name| Last Name|  Nickname|
|         0|      John|       Doe|        JD|
|         1|      Jane|     Smith|        JS|
Enter index to display: 0
First Name: John
Last Name: Doe
Nickname: JD
Phone Number: 0612345678
Darkest Secret: Loves pineapple pizza

> EXIT
```

**Test important : Troncature**
```bash
> ADD
First Name: Christopher
...
> SEARCH
|     Index|First Name| Last Name|  Nickname|
|         0|Christoph.|       ...|       ...|
```

**Test important : Comportement circulaire**
- Ajouter 9 contacts → le 9ème remplace le 1er

## 📊 Schéma du fonctionnement circulaire

```
Initial: [0][1][2][3][4][5][6][7]  _index = 0, _contactCount = 0
         [ ][ ][ ][ ][ ][ ][ ][ ]

Après 3 ADD: 
         [A][B][C][ ][ ][ ][ ][ ]  _index = 3, _contactCount = 3

Après 8 ADD:
         [A][B][C][D][E][F][G][H]  _index = 0, _contactCount = 8

9ème ADD (remplace A):
         [I][B][C][D][E][F][G][H]  _index = 1, _contactCount = 8
```

## ⚠️ Erreurs courantes à éviter
- ❌ Ne pas valider les champs vides
- ❌ Ne pas gérer EOF (`Ctrl+D`)
- ❌ Mauvaise validation de l'index (accepter "42abc")
- ❌ Oublier le comportement circulaire
- ❌ Afficher tous les 8 slots au lieu de `_contactCount`
- ❌ Getters non-`const`

---

# Exercise 02 : Account Class 💰

## 🎯 Objectif
Implémenter la classe `Account` à partir d'un header fourni et d'un log de sortie. Introduction aux **membres statiques**.

## 💡 Concepts présentés
- **Membres statiques** de classe (`static`)
- **Méthodes statiques**
- Portée de classe vs portée d'instance
- Agrégation de données globales
- Format de sortie précis

## 🔑 Points clés à expliquer

### 1. Comprendre les membres statiques

```cpp
class Account {
private:
    static int _nbAccounts;        // Partagé par TOUTES les instances
    static int _totalAmount;       // Valeur unique pour la classe
    static int _totalNbDeposits;
    static int _totalNbWithdrawals;
    
    int _accountIndex;             // Unique à chaque instance
    int _amount;
    int _nbDeposits;
    int _nbWithdrawals;
};
```

**À dire :**
- `static` = **une seule copie** pour toute la classe
- Non-`static` = une copie **par instance**
- Les membres statiques représentent des **statistiques globales**

### 2. Initialisation des membres statiques

```cpp
// Dans Account.cpp (HORS de la classe)
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;
```

**À dire :**
- **OBLIGATOIRE** : initialiser les membres statiques dans le `.cpp`
- Syntaxe : `Type Classe::membre = valeur;`
- Sans ça → erreur de linkage (undefined reference)

### 3. Méthodes statiques (getters)

```cpp
static int getNbAccounts(void);  // Déclaration dans .hpp

int Account::getNbAccounts(void) { return _nbAccounts; }
```

**À dire :**
- Méthode `static` = accessible **sans instance**
- Peut être appelée avec `Account::getNbAccounts()`
- Accède uniquement aux membres **statiques**

### 4. Le constructeur

```cpp
Account::Account(int initial_deposit) {
    this->_accountIndex = _nbAccounts;
    this->_amount = initial_deposit;
    this->_nbDeposits = 0;
    this->_nbWithdrawals = 0;

    // Mise à jour des stats globales
    _nbAccounts++;
    _totalAmount += initial_deposit;

    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "created" << std::endl;
}
```

**À dire :**
- Chaque compte reçoit un index unique (`_nbAccounts` avant incrémentation)
- Initialise les attributs de l'instance
- **Met à jour les membres statiques** (compteurs globaux)
- Affiche un message de création avec timestamp

### 5. Le destructeur

```cpp
Account::~Account(void) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "closed" << std::endl;
}
```

**À dire :**
- Appelé automatiquement à la destruction de l'objet
- Affiche les infos du compte fermé
- **Ne modifie PAS** les membres statiques (pour respecter le log fourni)

### 6. makeDeposit - Dépôt d'argent

```cpp
void Account::makeDeposit(int deposit) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "p_amount:" << this->_amount << ";"
              << "deposit:" << deposit << ";";

    this->_amount += deposit;
    this->_nbDeposits++;

    _totalAmount += deposit;        // Mise à jour globale
    _totalNbDeposits++;

    std::cout << "amount:" << this->_amount << ";"
              << "nb_deposits:" << this->_nbDeposits << std::endl;
}
```

**À dire :**
- Affiche l'état **avant** (p_amount = previous amount)
- Modifie l'instance **et** les membres statiques
- Affiche l'état **après**
- Format précis avec `;` entre les champs

### 7. makeWithdrawal - Retrait d'argent

```cpp
bool Account::makeWithdrawal(int withdrawal) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "p_amount:" << this->_amount << ";";

    if (withdrawal > this->_amount) {
        std::cout << "withdrawal:refused" << std::endl;
        return false;  // Échec
    }

    this->_amount -= withdrawal;
    this->_nbWithdrawals++;

    _totalAmount -= withdrawal;
    _totalNbWithdrawals++;

    std::cout << "withdrawal:" << withdrawal << ";"
              << "amount:" << this->_amount << ";"
              << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
    return true;  // Succès
}
```

**À dire :**
- **Validation** : vérifier si le solde est suffisant
- Si refus → affiche `withdrawal:refused` et retourne `false`
- Si succès → met à jour instance et globaux, retourne `true`
- Type de retour `bool` pour indiquer le succès

### 8. displayStatus - Affichage d'un compte

```cpp
void Account::displayStatus(void) const {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "deposits:" << this->_nbDeposits << ";"
              << "withdrawals:" << this->_nbWithdrawals << std::endl;
}
```

**À dire :**
- Méthode **const** : ne modifie pas l'objet
- Affiche l'état actuel d'une instance

### 9. displayAccountsInfos - Affichage global (static)

```cpp
void Account::displayAccountsInfos(void) {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts << ";"
              << "total:" << _totalAmount << ";"
              << "deposits:" << _totalNbDeposits << ";"
              << "withdrawals:" << _totalNbWithdrawals << std::endl;
}
```

**À dire :**
- Méthode **statique** : affiche les stats globales
- Pas besoin d'instance pour l'appeler
- Utilisée dans `tests.cpp` : `Account::displayAccountsInfos();`

### 10. _displayTimestamp - Affichage du timestamp

```cpp
void Account::_displayTimestamp(void) {
    std::cout << "[20260205_173241] ";
}
```

**À dire :**
- Méthode **privée** et **statique**
- Format : `[YYYYMMDD_HHMMSS]`
- **Simplifiée** ici : timestamp fixe pour matcher le log fourni
- En pratique, on utiliserait `<ctime>` pour l'heure réelle

**Version avec vraie date (bonus à mentionner) :**
```cpp
#include <ctime>

void Account::_displayTimestamp(void) {
    std::time_t now = std::time(0);
    std::tm* ltm = std::localtime(&now);
    std::cout << "[" << 1900 + ltm->tm_year
              << std::setfill('0') << std::setw(2) << 1 + ltm->tm_mon
              << std::setw(2) << ltm->tm_mday << "_"
              << std::setw(2) << ltm->tm_hour
              << std::setw(2) << ltm->tm_min
              << std::setw(2) << ltm->tm_sec << "] ";
}
```

### 11. Le fichier tests.cpp (fourni)

```cpp
int const amounts[] = { 42, 54, 957, 432, 1234, 0, 754, 16576 };
accounts_t accounts( amounts, amounts + amounts_size );
```

**À dire :**
- Créé un `std::vector<Account>` avec 8 comptes
- Chaque compte est initialisé avec un montant du tableau
- Utilise des **itérateurs** et `std::for_each` (concepts avancés)
- **Ne pas modifier** ce fichier

## 🧪 Tests à montrer

```bash
make
./account
```

**Sortie attendue (extrait) :**
```
[20260205_173241] index:0;amount:42;created
[20260205_173241] index:1;amount:54;created
...
[20260205_173241] accounts:8;total:20049;deposits:0;withdrawals:0
[20260205_173241] index:0;amount:42;deposits:0;withdrawals:0
...
[20260205_173241] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
...
[20260205_173241] index:0;p_amount:47;withdrawal:refused
...
[20260205_173241] index:0;amount:47;closed
...
```

**Comparer avec le log fourni :**
```bash
diff <(./account | cut -d' ' -f2-) <(cat 19920104_091532.log | cut -d' ' -f2-)
```

**À dire :**
- On ignore le timestamp (`cut -d' ' -f2-`) pour la comparaison
- Si aucune différence → implémentation correcte ✅

## 📊 Schéma membres static vs non-static

```
Classe Account (une seule copie)
├── static _nbAccounts = 3
├── static _totalAmount = 500
├── static _totalNbDeposits = 2
└── static _totalNbWithdrawals = 1

Instance 1              Instance 2              Instance 3
├─ _accountIndex = 0    ├─ _accountIndex = 1    ├─ _accountIndex = 2
├─ _amount = 100        ├─ _amount = 200        ├─ _amount = 200
├─ _nbDeposits = 1      ├─ _nbDeposits = 0      ├─ _nbDeposits = 1
└─ _nbWithdrawals = 0   └─ _nbWithdrawals = 1   └─ _nbWithdrawals = 0
```

## ⚠️ Erreurs courantes à éviter
- ❌ Oublier d'initialiser les membres statiques dans le `.cpp`
- ❌ Ne pas mettre à jour les membres statiques dans les méthodes
- ❌ Appeler `_displayTimestamp()` sans `static` (mais elle est statique)
- ❌ Mauvais format de sortie (espaces, `;`, ordre des champs)
- ❌ Modifier `_nbAccounts` dans le destructeur (ne pas faire)

---

# 🎯 Conseils généraux pour l'évaluation

## Ordre de présentation recommandé

1. **Montre d'abord le résultat** (compilation et exécution)
2. **Explique la structure** (architecture, classes, attributs)
3. **Détaille l'implémentation** (méthodes importantes)
4. **Réponds aux questions** de l'évaluateur

## Questions fréquentes à anticiper

### Pour ex00 :
- Pourquoi `std::toupper()` retourne un `int` ?
- Que se passe-t-il si on oublie le cast ?
- Différence entre `std::cout` et `printf` ?

### Pour ex01 :
- Pourquoi les attributs sont privés ?
- Qu'est-ce que l'encapsulation ?
- Pourquoi `const` dans les getters ?
- Comment fonctionne le comportement circulaire ?
- Pourquoi `std::string` au lieu de `char*` ?

### Pour ex02 :
- Différence entre membre statique et non-statique ?
- Pourquoi initialiser les statiques dans le `.cpp` ?
- Peut-on accéder à `_amount` dans une méthode statique ? (Non !)
- Pourquoi le destructeur n'affecte pas les membres statiques ?

## ✅ Points à vérifier avant l'évaluation

- [ ] Tous les exercices compilent avec `-Wall -Wextra -Werror -std=c++98`
- [ ] Aucune fuite mémoire (pas d'allocation dynamique dans CPP00)
- [ ] Les noms de fichiers respectent la convention
- [ ] Le code est propre et indenté
- [ ] Tu comprends chaque ligne de ton code
- [ ] Tu as testé les cas limites (EOF, index invalides, champs vides, etc.)

## 🚀 Bonus à mentionner (si on te pose la question)

- **ex01** : Possibilité d'utiliser une liste chaînée au lieu d'un tableau fixe
- **ex02** : Implémentation du vrai timestamp avec `<ctime>`
- Différence entre C++98 et C++11+ (nullptr, auto, range-based for, etc.)

---

## 📚 Récapitulatif des concepts par exercice

| Exercice | Concepts clés |
|----------|---------------|
| **ex00** | `std::cout`, `std::toupper()`, arguments CLI |
| **ex01** | Classes, encapsulation, getters/setters, `std::string`, formatage |
| **ex02** | Membres statiques, méthodes statiques, agrégation de données |

---

**Bonne chance pour ton évaluation ! 🎉**

N'hésite pas à relire ce guide et à bien tester tous tes programmes avant le jour J.
