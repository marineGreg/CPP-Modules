*This project has been created as part of the 42 curriculum by mgregoir*

# C++ - Module 00 : Introduction à la POO

Ce module marque la transition du langage C (impératif) vers le C++ (orienté objet). Ce document résume les concepts fondamentaux nécessaires pour comprendre et valider le module.

## 1. La Philosophie : Du Sac à la Boîte
En C, on manipule des données avec des fonctions externes. En C++, on crée des **Classes** (des plans) pour fabriquer des **Objets** (des machines autonomes). Un objet regroupe ses données (**Attributs**) et ses boutons d'action (**Méthodes**).

---

## 2. Concepts de base

### Le Namespace `std::`
Le C++ range ses outils standards dans une boîte appelée `std`.
- **`::` (Opérateur de portée)** : Permet d'accéder au contenu d'un namespace.
- **Pourquoi ?** Éviter les collisions de noms (deux fonctions avec le même nom dans des boîtes différentes).
- *Règle 42* : Ne jamais utiliser `using namespace std;` pour rester explicite.

### Flux de données (`iostream`)
- **`std::cout <<` (Sortie)** : On "pousse" les données vers le terminal. Plus sûr que `printf` car il détecte les types automatiquement.
- **`std::cin >>` (Entrée)** : On "aspire" les données vers une variable.
- **`std::endl`** : Saute une ligne et force l'affichage immédiat (flush).

---

## 3. La Classe : Encapsulation et Sécurité

### Public vs Private
- **`private`** : Les variables (attributs) sont cachées. Elles ne sont accessibles que par les fonctions membres de la classe.
- **`public`** : Les fonctions (méthodes) accessibles depuis l'extérieur (le `main`).
- **Encapsulation** : On protège les données en forçant l'utilisation de fonctions "filtres" :
    - **Getters** : Fonctions pour lire une donnée privée.
    - **Setters** : Fonctions pour modifier une donnée privée en vérifiant sa validité.

### Le mot-clé `const`
Placé après une méthode (ex: `void display() const;`), il garantit que cette fonction ne modifiera aucun attribut de l'objet. C'est une sécurité indispensable pour la "Const-correctness".

---

## 4. Cycle de vie : Constructeur et Destructeur
- **Constructeur** : Fonction appelée **automatiquement** à la création de l'objet. Sert à initialiser les variables.
- **Destructeur** : Fonction appelée **automatiquement** quand l'objet est détruit (fin de scope). Sert à nettoyer la mémoire.
- Ils portent le même nom que la classe.

---

## 5. Le mot-clé `static` (L'employé global)
Utilisé principalement dans l'exercice `Account`.
- **Attribut Statique** : Une variable commune à **toutes** les instances d'une classe. Il n'en existe qu'une seule copie (ex: le montant total de la banque).
- **Méthode Statique** : Une fonction qui peut être appelée sans objet (via `Classe::Fonction()`). Elle ne peut accéder qu'aux membres statiques et n'a pas accès à `this`.
- **Initialisation** : Les membres statiques doivent être initialisés dans le `.cpp`.

---

## 6. Manipulation de texte : `std::string`
- Contrairement au `char*`, c'est un objet intelligent.
- Gère sa propre mémoire (pas de `malloc` ou de `free`).
- Méthodes utiles : `.length()` (taille), `.substr()` (extraire une partie), `.empty()` (vérifier si vide).

---

## 7. Gestion robuste des entrées (`getline`)

### Pourquoi `std::getline` ?
`std::cin >>` s'arrête au premier espace. `std::getline(std::cin, str)` lit toute la ligne, espaces compris, jusqu'au retour à la ligne.

### Gestion du CTRL-D (EOF)
C'est le test crucial de l'évaluation. Si l'utilisateur coupe le flux d'entrée :
```cpp
if (!std::getline(std::cin, command)) {
    // Le flux est fermé (EOF)
    break; // Quitte proprement pour éviter une boucle infinie
}
```
`std::getline` renvoie le flux, qui est évalué comme `false` si le flux est cassé ou fermé.

---

## 8. Formatage avec `iomanip`
Utilisé pour l'exercice `PhoneBook` afin d'afficher des colonnes propres.
- **`std::setw(10)`** : Définit une largeur de 10 caractères pour la prochaine donnée.
- **`std::right` / `std::left`** : Aligne le texte à droite ou à gauche (Attention : `left/right` restent actifs pour tout le flux ensuite).

---

## Checklist pour l'évaluation
1. [ ] Aucun `printf`, `malloc` ou `free`.
2. [ ] Compilation avec `-std=c++98`.
3. [ ] Gestion propre du CTRL-D (pas de boucle infinie).
4. [ ] Attributs en `private` et méthodes en `public`.
5. [ ] Utilisation du `const` sur les fonctions de lecture.
6. [ ] Pas de `using namespace std;`.
```
