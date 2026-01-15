# Explications - Exercice 01 : PhoneBook

## 📚 Vue d'ensemble

L'exercice 01 du module CPP00 consiste à créer un répertoire téléphonique (PhoneBook) en utilisant les classes C++. C'est une introduction aux concepts de **programmation orientée objet** en C++.

## 🏗️ Architecture du projet

Le projet est composé de **2 classes principales** :

### 1. La classe `Contact`
Représente un contact individuel avec ses informations personnelles.

### 2. La classe `PhoneBook`
Gère un tableau de 8 contacts maximum et fournit les fonctionnalités d'ajout et de recherche.

---

## 📁 Structure des fichiers

```
ex01/
├── Contact.hpp          # Déclaration de la classe Contact
├── Contact.cpp          # Implémentation de la classe Contact
├── PhoneBook.hpp        # Déclaration de la classe PhoneBook
├── Phonebook.cpp        # Implémentation de la classe PhoneBook
├── main.cpp             # Point d'entrée du programme
└── Makefile             # Fichier de compilation
```

---

## 🔍 Explications détaillées par fichier

### `Contact.hpp` - Le header de Contact

```cpp
class Contact {
    private:
        std::string _firstName;
        std::string _lastName;
        std::string _nickName;
        std::string _phoneNumber;
        std::string _darkestSecret;

    public:
        Contact();
        ~Contact();
        
        // Setters
        void setFirstName(const std::string& str);
        // ... autres setters
        
        // Getters
        std::string getFirstName() const;
        // ... autres getters
};
```

**Points clés :**

#### 1. **Attributs privés** (`private:`)
Les données sont **encapsulées** : on ne peut pas y accéder directement depuis l'extérieur de la classe. C'est une bonne pratique en POO qui protège les données.

#### 2. **Setters avec `const std::string&`**
```cpp
void setFirstName(const std::string& str);
```
- `const` : On promet de ne pas modifier le paramètre
- `&` (référence) : On évite de copier toute la chaîne (plus efficace)
- Pourquoi `const` ? Permet de passer des valeurs temporaires comme `setFirstName("John")`

#### 3. **Getters avec `const`**
```cpp
std::string getFirstName() const;
```
Le `const` à la fin signifie que cette méthode **ne modifie pas** l'objet. C'est important pour pouvoir appeler ces méthodes sur des objets constants.

---

### `PhoneBook.hpp` - Le header de PhoneBook

```cpp
class PhoneBook {
    private:
        Contact _contacts[8];      // Tableau fixe de 8 contacts
        int     _contactCount;     // Nombre total de contacts ajoutés
        int     _oldestIndex;      // Index du plus ancien contact

    public:
        PhoneBook();
        ~PhoneBook();
        
        void addContact();
        void searchContact() const;
};
```

**Points clés :**

#### 1. **Tableau de Contact** : `Contact _contacts[8]`
- Taille fixe de 8 contacts maximum (comme demandé dans le sujet)
- Utilise un **tableau C** classique (pas de vector, pas de liste dynamique)

#### 2. **Système de rotation avec `_oldestIndex`**
Quand on atteint 8 contacts, le prochain contact remplace le plus ancien :
```cpp
this->_oldestIndex = (this->_oldestIndex + 1) % 8;  // Tourne de 0 à 7
```
L'opérateur `%` (modulo) fait "boucler" l'index : 7+1 = 8, et 8%8 = 0

#### 3. **`_contactCount` vs `_oldestIndex`**
- `_contactCount` : Nombre de contacts actuellement dans le répertoire (max 8)
- `_oldestIndex` : Position où sera ajouté le prochain contact

---

### `Phonebook.cpp` - L'implémentation

#### **Fonction `addContact()`**

```cpp
void PhoneBook::addContact()
{
    std::string input;
    
    // Pour chaque champ :
    std::cout << "First Name: ";
    std::getline(std::cin, input);
    
    // Vérification que le champ n'est pas vide
    if (input.empty())
    {
        std::cout << "Field cannot be empty!" << std::endl;
        return;  // Abandon de l'ajout
    }
    
    // Stockage via le setter
    this->_contacts[this->_oldestIndex].setFirstName(input);
    
    // ... répété pour tous les champs ...
    
    // Mise à jour des compteurs
    if (this->_contactCount < 8)
        this->_contactCount++;
    
    this->_oldestIndex = (this->_oldestIndex + 1) % 8;
}
```

**Explications :**

1. **`std::getline(std::cin, input)`** : Lit une ligne complète (espaces inclus)
2. **`input.empty()`** : Vérifie si la chaîne est vide
3. **`return;`** : Si un champ est vide, on quitte la fonction (le contact n'est PAS ajouté)
4. **`this->`** : Accès aux membres de l'objet courant (optionnel mais explicite)

---

#### **Fonction `searchContact()`**

```cpp
void PhoneBook::searchContact() const
{
    // Vérification que le répertoire n'est pas vide
    if (this->_contactCount == 0)
    {
        std::cout << "Phonebook is empty!" << std::endl;
        return;
    }
    
    // Affichage de l'en-tête du tableau
    std::cout << std::setw(10) << "Index" << "|";
    std::cout << std::setw(10) << "First Name" << "|";
    // ...
    
    // Affichage de chaque contact
    for (int i = 0; i < this->_contactCount; i++)
    {
        std::cout << std::setw(10) << i << "|";
        
        // Gestion de la troncature pour firstName
        std::string firstName = this->_contacts[i].getFirstName();
        if (firstName.length() > 10)
            std::cout << firstName.substr(0, 9) << ".|";
        else
            std::cout << std::setw(10) << firstName << "|";
        
        // ... répété pour lastName et nickname ...
    }
    
    // Demande de l'index
    std::cout << "Enter index: ";
    std::string indexStr;
    std::getline(std::cin, indexStr);
    
    // Validation : vérifier que c'est un nombre
    if (indexStr.empty() || 
        indexStr.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    
    int index = std::atoi(indexStr.c_str());
    
    // Vérification de la validité de l'index
    if (index < 0 || index >= this->_contactCount)
    {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    
    // Affichage complet du contact
    std::cout << "First Name: " << this->_contacts[index].getFirstName() << std::endl;
    // ... tous les champs ...
}
```

**Explications des concepts importants :**

##### 1. **Formatage avec `std::setw()`**
```cpp
#include <iomanip>
std::cout << std::setw(10) << "Index";
```
- `setw(10)` : Définit la largeur du prochain élément à 10 caractères
- Alignement à **droite** par défaut
- Permet de créer des colonnes alignées

##### 2. **Troncature des textes longs**
```cpp
if (firstName.length() > 10)
    std::cout << firstName.substr(0, 9) << ".|";
else
    std::cout << std::setw(10) << firstName << "|";
```
- `length()` : Retourne la taille de la chaîne
- `substr(0, 9)` : Extrait les 9 premiers caractères (indices 0 à 8)
- On ajoute un point : `"VeryLongName"` devient `"VeryLongN."`

##### 3. **Problème `std::cin >>` vs `std::getline()`**

**❌ Mauvaise approche :**
```cpp
std::getline(std::cin, command);  // Lit "ADD\n"
// ...
std::cin >> index;  // PROBLÈME : le '\n' précédent reste dans le buffer !
```

**✅ Bonne approche :**
```cpp
std::string indexStr;
std::getline(std::cin, indexStr);  // Lit tout, y compris les espaces
int index = std::atoi(indexStr.c_str());
```

Pourquoi ? `std::cin >> index` laisse le caractère de nouvelle ligne (`\n`) dans le buffer, ce qui cause des bugs avec les `getline()` suivants.

##### 4. **Validation de l'input numérique**
```cpp
indexStr.find_first_not_of("0123456789") != std::string::npos
```
- `find_first_not_of("0123456789")` : Cherche le premier caractère qui n'est PAS un chiffre
- Si trouvé (≠ `npos`), c'est que l'input contient autre chose que des chiffres
- Donc l'input n'est pas un nombre valide

##### 5. **Conversion string → int**
```cpp
int index = std::atoi(indexStr.c_str());
```
- `c_str()` : Convertit `std::string` en `const char*` (chaîne C)
- `std::atoi()` : Convertit une chaîne C en entier (ASCII TO Integer)
- Nécessite `#include <cstdlib>`

---

### `main.cpp` - La boucle principale

```cpp
int main()
{
    PhoneBook phoneBook;
    std::string command;
    
    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        
        // Gestion de l'EOF (Ctrl+D)
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

**Points importants :**

#### 1. **Gestion de l'EOF (End Of File)**
```cpp
if (!std::getline(std::cin, command))
```
- Si l'utilisateur tape **Ctrl+D** (ou Ctrl+Z sur Windows), `std::cin` atteint EOF
- `std::getline()` retourne `false`
- Sans cette vérification, le programme tournerait en boucle infinie !

#### 2. **Boucle infinie avec `while (true)`**
- Continue jusqu'à ce qu'on tape "EXIT" ou Ctrl+D
- Simple et efficace pour un menu interactif

---

## 🎯 Concepts C++ utilisés

### 1. **Classes et Encapsulation**
- Données privées, méthodes publiques
- Protection des données : on ne peut modifier un contact que via les setters

### 2. **Références constantes (`const Type&`)**
```cpp
void setFirstName(const std::string& str);
```
- Évite la copie (plus rapide)
- `const` = on ne modifie pas le paramètre
- Permet de passer des temporaires

### 3. **Méthodes constantes**
```cpp
std::string getFirstName() const;
```
- La méthode ne modifie pas l'objet
- Permet d'appeler la méthode sur un objet `const`

### 4. **Manipulation de chaînes**
- `length()` : Taille de la chaîne
- `substr(start, len)` : Extraction d'une sous-chaîne
- `empty()` : Vérifie si vide
- `find_first_not_of()` : Cherche un caractère différent

### 5. **Formatage avec `<iomanip>`**
- `std::setw(n)` : Largeur de champ
- Alignement automatique des colonnes

### 6. **Gestion des flux d'entrée**
- `std::getline()` : Lit une ligne complète
- Gestion de l'EOF
- Validation des inputs

---

## 🔄 Flux d'exécution typique

### Scénario : Ajouter 2 contacts puis en afficher un

```
1. Lancement du programme
   └─> Création d'un objet PhoneBook (constructeur appelé)
       └─> _contactCount = 0, _oldestIndex = 0

2. Utilisateur tape "ADD"
   └─> phoneBook.addContact() appelé
       ├─> Demande firstName → "John"
       ├─> Demande lastName → "Doe"
       ├─> Demande nickname → "Johnny"
       ├─> Demande phoneNumber → "555-1234"
       ├─> Demande darkestSecret → "Afraid of spiders"
       ├─> Stockage dans _contacts[0]
       └─> _contactCount = 1, _oldestIndex = 1

3. Utilisateur tape "ADD" à nouveau
   └─> phoneBook.addContact() appelé
       └─> Stockage dans _contacts[1]
       └─> _contactCount = 2, _oldestIndex = 2

4. Utilisateur tape "SEARCH"
   └─> phoneBook.searchContact() appelé
       ├─> Affiche tableau avec 2 lignes (index 0 et 1)
       ├─> Demande index → "0"
       └─> Affiche toutes les infos de _contacts[0]

5. Utilisateur tape "EXIT"
   └─> break dans la boucle while
   └─> Fin du programme (destructeurs appelés)
```

---

## ⚠️ Pièges courants et comment les éviter

### 1. **Mélanger `cin >>` et `getline()`**
❌ **Évite ça :**
```cpp
std::cin >> age;
std::getline(std::cin, name);  // Ne fonctionnera pas bien !
```

✅ **Utilise uniquement `getline()` :**
```cpp
std::string ageStr;
std::getline(std::cin, ageStr);
int age = std::atoi(ageStr.c_str());
```

### 2. **Oublier de vérifier que les champs ne sont pas vides**
```cpp
if (input.empty())
    return;  // Important !
```

### 3. **Oublier le modulo pour la rotation**
```cpp
this->_oldestIndex = (this->_oldestIndex + 1) % 8;
// Sans le % 8, l'index dépasserait 7 et causerait un segfault !
```

### 4. **Ne pas gérer l'EOF**
Sans vérification, Ctrl+D cause une boucle infinie.

---

## 🧪 Comment tester ton programme

### Test 1 : Ajout simple
```
ADD
John
Doe
Johnny
555-1234
Secret1
SEARCH
0
EXIT
```

### Test 2 : Champs vides (doit refuser)
```
ADD
John
[Appuie sur Entrée sans rien taper]
→ Devrait afficher "Field cannot be empty!"
```

### Test 3 : Plus de 8 contacts (rotation)
Ajoute 9 contacts. Le 9ème devrait remplacer le 1er.

### Test 4 : Index invalide
```
SEARCH
999
→ Devrait afficher "Invalid index!"
```

### Test 5 : Troncature
Ajoute un contact avec un prénom de plus de 10 caractères :
```
Christopher → Affichera "Christoph.|"
```

### Test 6 : EOF (Ctrl+D)
Tape Ctrl+D → le programme doit se terminer proprement.

---

## 📚 Pour aller plus loin

### Amélioration possible (hors sujet)
- Utiliser `std::vector<Contact>` au lieu d'un tableau fixe
- Ajouter une fonction de suppression
- Sauvegarder/charger depuis un fichier
- Valider le format du numéro de téléphone

### Concepts C++ à approfondir ensuite
- Constructeurs par copie
- Opérateurs (surcharge)
- Allocation dynamique (`new`/`delete`)
- Héritage et polymorphisme

---

## 🎓 Résumé des bonnes pratiques appliquées

✅ Encapsulation (attributs privés)
✅ Références constantes pour les paramètres
✅ Méthodes constantes pour les getters
✅ Validation des inputs
✅ Gestion des erreurs (EOF, index invalide, champs vides)
✅ Formatage propre de l'affichage
✅ Code commenté et organisé
✅ Makefile avec les bons flags

---

Bon courage pour la suite du module CPP ! 🚀
