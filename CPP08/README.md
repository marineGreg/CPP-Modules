# C++ - Module 08 : Templated Containers, Iterators, Algorithms

> **École 42** | Projet C++ Module 08  
> **Norme :** C++98 (`c++ -Wall -Wextra -Werror -std=c++98`)

---

## 📋 Table des Matières
- [À propos du projet](#-à-propos-du-projet)
- [Concepts Clés & Théorie](#-concepts-clés--théorie)
  - [1. Les Templates (Génélicité)](#1-les-templates-généricité)
  - [2. Les 3 Piliers de la STL](#2-les-3-piliers-de-la-stl)
  - [3. Le mot-clé `typename` (Types dépendants)](#3-le-mot-clé-typename-types-dépendants)
- [Aperçu des Exercices](#-aperçu-des-exercices)
  - [Exercice 00 : Easy find](#exercice-00--easy-find)
  - [Exercice 01 : Span](#exercice-01--span)
  - [Exercice 02 : Mutated abomination (MutantStack)](#exercice-02--mutated-abomination-mutantstack)
- [Compilation & Utilisation](#-compilation--utilisation)
- [Aide-Mémoire pour l'Évaluation](#-aide-mémoire-pour-lévaluation)

---

## ℹ️ À propos du projet

Le **Module 08** est une étape charnière dans le cursus C++ de l'École 42. Après avoir réimplémenté manuellement de nombreuses structures dans les modules précédents, ce module introduit l'utilisation de la **STL (Standard Template Library)**.

L'objectif principal est d'apprendre à écrire du code générique à l'aide des **templates**, tout en exploitant la puissance des **conteneurs**, des **itérateurs** et des **algorithmes** fournis par la bibliothèque standard de C++.

---

## 🧠 Concepts Clés & Théorie

### 1. Les Templates (Génélicité)
Un template permet d'écrire du code capable de fonctionner avec n'importe quel type de donnée (`int`, `double`, `std::string`, ou des classes personnalisées).

* **Compilation :** Les templates sont instanciés par le compilateur **au moment de la compilation**.
* **Fichiers d'en-tête (`.hpp`) :** Comme le compilateur a besoin du code complet pour instancier un template avec un type spécifique, **l'implémentation des fonctions/classes templates doit impérativement se trouver dans les fichiers de header (`.hpp`)** (ou dans des fichiers `.tpp` inclus à la fin du `.hpp`).

### 2. Les 3 Piliers de la STL

1. **Les Conteneurs (`Containers`) :**
   * `std::vector` : Tableau dynamique contigu en mémoire. Accès direct ultra-rapide $O(1)$.
   * `std::list` : Liste doublement chaînée. Insertion/suppression rapides $O(1)$, mais accès séquentiel $O(N)$.
   * `std::deque` : File à double entrée.
   * `std::stack` : Adaptateur de conteneur (structure LIFO - *Last In, First Out*).
2. **Les Itérateurs (`Iterators`) :**
   * Objets agissant comme des pointeurs intelligents pour naviguer dans un conteneur.
   * `begin()` pointe sur le premier élément, `end()` pointe **juste après** le dernier élément (plage demi-ouverte `[begin, end[`).
3. **Les Algorithmes (`<algorithm>`) :**
   * Ensemble de fonctions optimisées travaillant sur des plages d'itérateurs.
   * Exemples : `std::find`, `std::sort`, `std::min_element`, `std::max_element`.

### 3. Le mot-clé `typename` (Types dépendants)
Lorsqu'on manipule un type dépendant d'un paramètre template (ex: `T::iterator`), le compilateur ne sait pas au préalable si `iterator` est un type ou une variable statique.
Pour lever cette ambiguïté, il est obligatoire de faire précéder le type par le mot-clé **`typename`** :

```cpp
template <typename T>
typename T::iterator my_function(T &container);
