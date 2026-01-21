# 📖 Guide Explicatif - CPP00 ex01 : My Awesome PhoneBook

## 📋 Table des matières
1. [Vue d'ensemble](#vue-densemble)
2. [Structure du projet](#structure-du-projet)
3. [Classe Contact](#classe-contact)
4. [Classe PhoneBook](#classe-phonebook)
5. [Programme principal](#programme-principal)
6. [Fonctionnement détaillé](#fonctionnement-détaillé)
7. [Concepts C++ utilisés](#concepts-c-utilisés)

---

## 🎯 Vue d'ensemble

Cet exercice implémente un **annuaire téléphonique** (PhoneBook) en C++98 qui permet de :
- **Stocker jusqu'à 8 contacts**
- **Ajouter** de nouveaux contacts (remplace le plus ancien si plein)
- **Rechercher** et afficher des contacts
- **Gérer** les entrées utilisateur de manière robuste

### Objectifs pédagogiques
- Manipulation de classes et objets
- Encapsulation avec attributs privés
- Gestion de tableaux statiques
- Manipulation de chaînes de caractères (`std::string`)
- Gestion des flux d'entrée/sortie (`std::cin`, `std::cout`)

---

## 📁 Structure du projet

```
ex01/
├── Contact.hpp          # Déclaration de la classe Contact
├── Contact.cpp          # Implémentation de la classe Contact
├── PhoneBook.hpp        # Déclaration de la classe PhoneBook
├── Phonebook.cpp        # Implémentation de la classe PhoneBook
├── main.cpp             # Programme principal
└── Makefile             # Fichier de compilation
```

---

## 👤 Classe Contact

### Description
La classe `Contact` représente **un contact individuel** dans l'annuaire. Elle stocke 5 informations personnelles.

### Fichier : Contact.hpp

#### Attributs privés
```cpp
private:
    std::string _firstName;      // Prénom
    std::string _lastName;       // Nom de famille
    std::string _nickName;       // Surnom
    std::string _phoneNumber;    // Numéro de téléphone
    std::string _darkestSecret;  // Secret le plus sombre
```

**💡 Pourquoi privés ?**
- **Encapsulation** : Protection des données
- **Contrôle** : Accès uniquement via les getters/setters
- **Sécurité** : Évite les modifications non contrôlées

#### Méthodes publiques

##### Constructeur et Destructeur
```cpp
Contact();   // Initialise un contact vide
~Contact();  // Détruit le contact (rien de spécial ici)
```

##### Setters (Modificateurs)
```cpp
void setFirstName(const std::string& str);
void setLastName(const std::string& str);
void setNickName(const std::string& str);
void setPhoneNumber(const std::string& str);
void setDarkestSecret(const std::string& str);
```

**📝 Explications :**
- `void` : Ne retourne rien
- `const std::string&` : Référence constante (évite la copie, paramètre non modifiable)
- `this->_firstName = str` : Affecte la valeur à l'attribut de l'objet courant

##### Getters (Accesseurs)
```cpp
std::string getFirstName() const;
std::string getLastName() const;
std::string getNickName() const;
std::string getPhoneNumber() const;
std::string getDarkestSecret() const;
```

**📝 Explications :**
- `std::string` : Retourne une copie de la chaîne
- `const` (à la fin) : Méthode constante, ne modifie pas l'objet
- `return (this->_firstName)` : Retourne l'attribut privé

### Fichier : Contact.cpp

**Implémentation simple :**
- Constructeur vide : `Contact::Contact() {}`
- Destructeur vide : `Contact::~Contact() {}`
- Chaque setter assigne simplement la valeur
- Chaque getter retourne simplement la valeur

---

## 📇 Classe PhoneBook

### Description
La classe `PhoneBook` gère **l'ensemble des contacts** (maximum 8) et fournit les fonctionnalités d'ajout et de recherche.

### Fichier : PhoneBook.hpp

#### Attributs privés
```cpp
private:
    Contact _contacts[8];    // Tableau de 8 contacts
    int     _contactCount;   // Nombre total de contacts ajoutés (max 8)
    int     _index;          // Index du prochain emplacement à remplir
```

**💡 Pourquoi ces attributs ?**
- `_contacts[8]` : Tableau fixe de 8 contacts (limite imposée)
- `_contactCount` : Garde trace du nombre de contacts valides (0 à 8)
- `_index` : Système circulaire pour remplacer le plus ancien contact

#### Méthodes privées
```cpp
void printColumn(std::string str) const;
```
- **Utilité** : Formater l'affichage en colonnes de 10 caractères
- **Privée** : Fonction utilitaire interne uniquement

#### Méthodes publiques
```cpp
PhoneBook();              // Constructeur
~PhoneBook();             // Destructeur
void addContact();        // Ajoute un nouveau contact
void searchContact() const; // Recherche et affiche un contact
```

### Fichier : Phonebook.cpp

#### Constructeur
```cpp
PhoneBook::PhoneBook()
{
    this->_contactCount = 0;
    this->_index = 0;
}
```
**📝 Initialise :**
- `_contactCount` à 0 : Aucun contact au départ
- `_index` à 0 : Commence à remplir depuis le début

---

### Fonction : `printColumn()`

```cpp
void PhoneBook::printColumn(std::string str) const
{
    if (str.length() > 10) {
        std::cout << str.substr(0, 9) << ".|";
    } else {
        std::cout << std::setw(10) << str << "|";
    }
}
```

**🎯 Objectif :**
Afficher une chaîne dans une colonne de **exactement 10 caractères**.

**📝 Explications :**
1. **Si la chaîne est trop longue** (`> 10`) :
   - `str.substr(0, 9)` : Extrait les 9 premiers caractères
   - Ajoute un point `.` pour indiquer la troncature
   - Ajoute `|` pour la séparation de colonne
   - Exemple : `"Christopher"` → `"Christoph.|"`

2. **Si la chaîne est courte** (`<= 10`) :
   - `std::setw(10)` : Définit la largeur à 10 caractères
   - Aligne à droite avec des espaces
   - Exemple : `"John"` → `"      John|"`

---

### Fonction : `addContact()`

```cpp
void PhoneBook::addContact()
{
    std::string fields[5] = {"First Name", "Last Name", "Nickname", 
                              "Phone Number", "Darkest Secret"};
    std::string inputs[5];

    // 1. Collecte des informations
    for (int i = 0; i < 5; i++) {
        while (true) {
            std::cout << fields[i] << ": ";
            if (!std::getline(std::cin, inputs[i])) // Gestion Ctrl+D
                return; 
            if (!inputs[i].empty()) // Vérifie si vide
                break;
            std::cout << "Field cannot be empty!" << std::endl;
        }
    }

    // 2. Stockage des informations dans le contact
    _contacts[_index].setFirstName(inputs[0]);
    _contacts[_index].setLastName(inputs[1]);
    _contacts[_index].setNickName(inputs[2]);
    _contacts[_index].setPhoneNumber(inputs[3]);
    _contacts[_index].setDarkestSecret(inputs[4]);

    // 3. Mise à jour des compteurs
    if (_contactCount < 8)
        _contactCount++;
    _index = (_index + 1) % 8;  // Modulo pour revenir à 0 après 7
    
    std::cout << "Contact added successfully!" << std::endl;
}
```

**📝 Explications détaillées :**

#### Étape 1 : Collecte des informations
- **Boucle `for`** : Parcourt les 5 champs à remplir
- **Boucle `while(true)`** : Redemande tant que l'entrée est invalide
- **`std::getline(std::cin, inputs[i])`** :
  - Lit une ligne complète (avec espaces)
  - Retourne `false` si EOF (Ctrl+D) → quitte la fonction
- **`!inputs[i].empty()`** : Vérifie que le champ n'est pas vide
  - Si vide : affiche un message d'erreur et redemande
  - Si valide : `break` pour passer au champ suivant

#### Étape 2 : Stockage
- Utilise les **setters** de la classe `Contact`
- Stocke dans `_contacts[_index]` (position actuelle)

#### Étape 3 : Gestion de l'index circulaire
```cpp
if (_contactCount < 8)
    _contactCount++;      // Incrémente jusqu'à 8 maximum
_index = (_index + 1) % 8;  // 0→1→2→...→7→0 (circulaire)
```

**💡 Système circulaire :**
- Premiers ajouts (0-7) : Remplit progressivement
- Ajouts suivants (8+) : Remplace le plus ancien (index 0, puis 1, etc.)
- **Opérateur modulo `%`** : `8 % 8 = 0` (retour au début)

---

### Fonction : `searchContact()`

```cpp
void PhoneBook::searchContact() const
{
    // 1. Vérification si l'annuaire est vide
    if (_contactCount == 0) {
        std::cout << "Phonebook is empty!" << std::endl;
        return;
    }

    // 2. Affichage de l'en-tête du tableau
    std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;

    // 3. Affichage des contacts
    for (int i = 0; i < _contactCount; i++) {
        std::cout << "|";
        std::cout << std::setw(10) << i << "|";
        printColumn(_contacts[i].getFirstName());
        printColumn(_contacts[i].getLastName());
        printColumn(_contacts[i].getNickName());
        std::cout << std::endl;
    }

    // 4. Demande de l'index à afficher
    std::cout << "Enter index to display: ";
    std::string indexStr;
    if (!std::getline(std::cin, indexStr)) return;

    // 5. Validation de l'index
    std::stringstream ss(indexStr);
    int index;
    std::string extra;

    if (!(ss >> index) || (ss >> extra)) {
        std::cout << "Invalid index!" << std::endl;
    } else if (index < 0 || index >= _contactCount) {
        std::cout << "Index out of range!" << std::endl;
    } else {
        // 6. Affichage détaillé du contact
        std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
        std::cout << "Last Name: " << _contacts[index].getLastName() << std::endl;
        std::cout << "Nickname: " << _contacts[index].getNickName() << std::endl;
        std::cout << "Phone Number: " << _contacts[index].getPhoneNumber() << std::endl;
        std::cout << "Darkest Secret: " << _contacts[index].getDarkestSecret() << std::endl;
    }
}
```

**📝 Explications détaillées :**

#### Étape 1 : Vérification
```cpp
if (_contactCount == 0) return;
```
- Si aucun contact : affiche un message et quitte

#### Étape 2 & 3 : Affichage du tableau
```cpp
std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
```
- En-tête formaté avec colonnes de 10 caractères

```cpp
for (int i = 0; i < _contactCount; i++) {
    std::cout << std::setw(10) << i << "|";
    printColumn(_contacts[i].getFirstName());
    // ...
}
```
- Boucle sur les contacts valides uniquement
- Utilise `printColumn()` pour le formatage

**Exemple d'affichage :**
```
|     Index|First Name| Last Name|  Nickname|
|         0|      John|       Doe|     JayDe|
|         1|     Alice|     Smith|      Ally|
```

#### Étape 4 : Lecture de l'index
```cpp
std::string indexStr;
if (!std::getline(std::cin, indexStr)) return;
```
- Lit l'entrée en tant que chaîne (pas directement en `int`)
- Gestion du EOF (Ctrl+D)

#### Étape 5 : Validation rigoureuse
```cpp
std::stringstream ss(indexStr);
int index;
std::string extra;

if (!(ss >> index) || (ss >> extra)) {
    std::cout << "Invalid index!" << std::endl;
}
```

**💡 Validation en deux étapes :**

1. **`!(ss >> index)`** : Vérifie si la conversion en entier échoue
   - ❌ `"abc"` → échec de conversion
   - ✅ `"42"` → conversion réussie

2. **`(ss >> extra)`** : Vérifie s'il y a du texte après le nombre
   - ❌ `"42 hello"` → `extra` contiendra `"hello"`
   - ✅ `"42"` → rien à extraire, la condition est fausse

**Exemple de validations :**
- `"5"` → ✅ Valide
- `"abc"` → ❌ Pas un nombre
- `"5 abc"` → ❌ Texte après le nombre
- `"5.7"` → ❌ Nombre décimal (le `.7` sera dans `extra`)
- `"-1"` → Validé comme nombre, mais rejeté ensuite

```cpp
else if (index < 0 || index >= _contactCount) {
    std::cout << "Index out of range!" << std::endl;
}
```
- Vérifie que l'index est dans les limites valides

#### Étape 6 : Affichage détaillé
```cpp
std::cout << "First Name: " << _contacts[index].getFirstName() << std::endl;
// ... (tous les champs)
```
- Utilise les **getters** pour récupérer et afficher toutes les informations

---

## 🚀 Programme principal

### Fichier : main.cpp

```cpp
int main()
{
    PhoneBook phoneBook;
    std::string command;
    
    std::cout << PB_LINE << PB_TITLE << PB_LINE;
    
    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, command))
        {
            std::cout << std::endl;
            break;
        }
        
        if (command == "ADD")
            phoneBook.addContact();
        else if (command == "SEARCH")
            phoneBook.searchContact();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Invalid command!" << std::endl;
    }
    
    return (0);
}
```

**📝 Explications :**

### Initialisation
```cpp
PhoneBook phoneBook;
std::string command;
```
- Crée une instance de `PhoneBook`
- Variable pour stocker la commande saisie

### Bannière
```cpp
# define PB_LINE " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
# define PB_TITLE "/             My Awesome PhoneBook            /\n"

std::cout << PB_LINE << PB_TITLE << PB_LINE;
```
- Affiche un titre stylisé au démarrage

### Boucle principale
```cpp
while (true) { ... }
```
- Boucle infinie jusqu'à `EXIT` ou EOF

### Lecture de la commande
```cpp
if (!std::getline(std::cin, command))
{
    std::cout << std::endl;
    break;
}
```
- **`std::getline()`** : Lit la commande
- Si EOF (Ctrl+D) : affiche un retour à la ligne et quitte

### Traitement des commandes
```cpp
if (command == "ADD")
    phoneBook.addContact();
else if (command == "SEARCH")
    phoneBook.searchContact();
else if (command == "EXIT")
    break;
else
    std::cout << "Invalid command!" << std::endl;
```

**Commandes disponibles :**
- **`ADD`** : Ajoute un nouveau contact
- **`SEARCH`** : Recherche et affiche un contact
- **`EXIT`** : Quitte le programme
- **Autre** : Message d'erreur

---

## 🔧 Fonctionnement détaillé

### Scénario d'utilisation complet

#### 1. Ajout d'un contact (ADD)
```
Enter command (ADD, SEARCH, EXIT): ADD
First Name: John
Last Name: Doe
Nickname: JayDe
Phone Number: 0123456789
Darkest Secret: Afraid of spiders
Contact added successfully!
```

**Ce qui se passe :**
1. L'utilisateur tape `ADD`
2. Le programme demande les 5 champs un par un
3. Validation : aucun champ ne peut être vide
4. Stockage dans `_contacts[0]`
5. `_contactCount` passe à 1, `_index` passe à 1

#### 2. Recherche d'un contact (SEARCH)
```
Enter command (ADD, SEARCH, EXIT): SEARCH
|     Index|First Name| Last Name|  Nickname|
|         0|      John|       Doe|     JayDe|
Enter index to display: 0
First Name: John
Last Name: Doe
Nickname: JayDe
Phone Number: 0123456789
Darkest Secret: Afraid of spiders
```

**Ce qui se passe :**
1. Affichage du tableau avec colonnes formatées
2. Demande d'un index
3. Validation de l'index (nombre valide, dans la plage)
4. Affichage détaillé du contact

#### 3. Gestion des limites (8 contacts max)

**Ajout des contacts 1 à 8 :**
- `_index` : 0 → 1 → 2 → 3 → 4 → 5 → 6 → 7
- `_contactCount` : 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8

**Ajout du 9ème contact :**
- `_index` : 7 → (7 + 1) % 8 = 0
- Le contact à l'index 0 est **remplacé**
- `_contactCount` reste à 8

---

## 🎓 Concepts C++ utilisés

### 1. Classes et Objets
```cpp
class Contact { ... };
Contact contact;  // Instanciation
```
- **Encapsulation** : Données privées + méthodes publiques
- **Constructeur/Destructeur** : Gestion automatique

### 2. Attributs privés
```cpp
private:
    std::string _firstName;
```
- Préfixe `_` : Convention pour les attributs privés
- Protection des données

### 3. Références constantes
```cpp
void setFirstName(const std::string& str);
```
- `const` : Le paramètre ne peut pas être modifié
- `&` : Passage par référence (évite la copie)
- **Avantage** : Efficacité + sécurité

### 4. Méthodes constantes
```cpp
std::string getFirstName() const;
```
- `const` (à la fin) : La méthode ne modifie pas l'objet
- Peut être appelée sur des objets constants

### 5. Tableaux statiques
```cpp
Contact _contacts[8];
```
- Taille fixe définie à la compilation
- Allocation sur la pile (stack)

### 6. Manipulation de chaînes
```cpp
std::string str = "Hello";
str.length()        // Longueur
str.substr(0, 9)    // Sous-chaîne
str.empty()         // Teste si vide
```

### 7. Flux d'entrée/sortie
```cpp
std::cout << "Text" << std::endl;
std::getline(std::cin, str);
```
- `std::cout` : Sortie standard
- `std::cin` : Entrée standard
- `std::getline()` : Lit une ligne complète

### 8. Formatage d'affichage
```cpp
#include <iomanip>
std::cout << std::setw(10) << str;
```
- `std::setw(n)` : Définit la largeur du champ
- Aligne à droite par défaut

### 9. StringStream
```cpp
#include <sstream>
std::stringstream ss("42");
int number;
ss >> number;  // Conversion string → int
```
- Conversion de types
- Validation des entrées

### 10. Opérateur modulo
```cpp
_index = (_index + 1) % 8;
```
- **`%`** : Reste de la division
- Crée un cycle : 0→1→...→7→0

---

## 💡 Points clés à retenir

### ✅ Bonnes pratiques implémentées

1. **Encapsulation forte**
   - Attributs privés
   - Accès via getters/setters

2. **Validation robuste**
   - Vérification des champs vides
   - Validation des index
   - Gestion de EOF (Ctrl+D)

3. **Gestion mémoire**
   - Pas d'allocation dynamique
   - Tableau statique (pas de fuite mémoire)

4. **Formatage soigné**
   - Colonnes de 10 caractères
   - Troncature avec point
   - Affichage aligné

5. **Code modulaire**
   - Séparation des responsabilités
   - Fonctions dédiées (printColumn)
   - Fichiers séparés (hpp/cpp)

### 🔍 Détails techniques

**Système circulaire :**
```
Index: 0 1 2 3 4 5 6 7 0 1 2 ...
       ↑ Premier contact
                       ↑ 8ème contact
                         ↑ 9ème contact (remplace le 1er)
```

**Validation d'index :**
```cpp
!(ss >> index)        // Pas un nombre
(ss >> extra)         // Texte après le nombre
index < 0             // Négatif
index >= _contactCount // Hors limites
```

---

## 🎯 Résumé

Ce projet démontre :
- La **conception orientée objet** en C++
- La **gestion de données structurées**
- Les **bonnes pratiques** d'encapsulation
- La **validation robuste** des entrées
- L'**interaction utilisateur** en ligne de commande

**Architecture :**
```
main() → PhoneBook → Contact[8]
         ↓
    addContact()
    searchContact()
         ↓
    getters/setters
```

Le code est simple mais illustre parfaitement les concepts fondamentaux du C++ : classes, encapsulation, validation, et gestion de la mémoire statique.

