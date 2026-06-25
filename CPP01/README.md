
# 🧠 C++ Module 01 - Guide de Survie

Ce module se concentre sur trois piliers du C++ : la gestion de la mémoire (**Stack vs Heap**), la différence entre **Pointeurs et Références**, et l'utilisation des **Pointeurs sur fonctions membres**.

---

## 1. Stack (Pile) vs Heap (Tas)
C'est le concept le plus important des exercices 00 et 01.

| Caractéristique | Stack (Pile) | Heap (Tas) |
| :--- | :--- | :--- |
| **Comment ?** | `Zombie z;` | `Zombie* z = new Zombie();` |
| **Durée de vie** | Automatique (meurt au `}`) | Manuelle (vit jusqu'au `delete`) |
| **Vitesse** | Très rapide | Plus lente |
| **Gestion** | Sûre (pas de fuites) | Risquée (attention aux leaks) |
| **Usage** | Objets temporaires / locaux | Objets qui doivent survivre à la fonction |

**Règle d'or :** Si tu n'as pas de raison spécifique d'utiliser `new`, utilise la **Stack**.

---

## 2. Pointeurs (`*`) vs Références (`&`)
Le C++ introduit les références, qui sont souvent préférables aux pointeurs.

*   **Pointeur (`type*`)** : Une variable qui stocke une adresse.
    *   Peut être `NULL`.
    *   Peut changer de cible.
    *   Accès aux membres via `->`.
*   **Référence (`type&`)** : Un alias (surnom) pour une variable existante.
    *   **Ne peut pas** être `NULL`.
    *   **Ne peut pas** changer de cible après initialisation.
    *   Accès aux membres via `.` (comme une variable normale).

### Application (Ex03) :
*   **HumanA** utilise une **Référence** car il a *toujours* une arme (obligatoire, non-nulle).
*   **HumanB** utilise un **Pointeur** car il peut ne pas avoir d'arme au début (optionnel, peut être `NULL`).

---

## 3. Manipulation de fichiers et Strings (Ex04)
L'exercice 04 (Sed) apprend à manipuler les flux de données et les chaînes.

*   **`std::ifstream`** : Flux pour lire un fichier.
*   **`std::ofstream`** : Flux pour écrire dans un fichier.
*   **`c_str()`** : Convertit une `std::string` en `const char*`. Indispensable en **C++98** pour ouvrir un fichier.
*   **`std::string::npos`** : Valeur spéciale renvoyée par `find()` quand elle ne trouve rien ("Not POSition").

### Algorithme de remplacement :
On ne peut pas utiliser `std::string::replace`. On utilise donc une boucle :
1. Trouver la position de `s1` (`find`).
2. Copier ce qui précède dans une nouvelle chaîne (`substr`).
3. Ajouter `s2` (le remplaçant).
4. Avancer le curseur de lecture après `s1` pour éviter les boucles infinies.

---

## 4. Pointeurs sur fonctions membres (Ex05)
C'est la syntaxe la plus complexe du module. Elle permet d'appeler une fonction à partir d'une variable.

**Syntaxe de déclaration :**
`void (Harl::*ptr)(void);`
*(Un pointeur `ptr` vers une fonction membre de `Harl` qui ne prend rien et ne renvoie rien).*

**Syntaxe d'appel :**
`(this->*ptr)();`
*(On exécute la fonction pointée sur l'objet actuel `this`).*

**Pourquoi ?** Pour éviter les forêts de `if/else if/else`. On range les adresses des fonctions dans un tableau et on appelle l'index correspondant au niveau de log.

---

## 5. Switch et "Fall-through" (Ex06)
Le `switch` ne fonctionne que sur des entiers ou des caractères en C++. Pour filtrer les logs de Harl :
1. Convertir la string du niveau (`DEBUG`, `INFO`...) en index `int` (0, 1, 2, 3).
2. Utiliser le `switch` sur cet index.
3. Ne pas mettre de `break` entre les `case` pour permettre le **Fall-through** : si on demande `WARNING`, le code "coule" et affiche aussi `ERROR`.

---

## 6. Conseils pour l'évaluation

1.  **Compilation :** Toujours compiler avec `-Wall -Wextra -Werror -std=c++98`.
2.  **Mémoire :** Aucun leak toléré. Utilise `valgrind` pour vérifier.
3.  **Orthodox Canonical Form :** Même si c'est le sujet du Module 02, avoir des classes propres avec Constructeur/Destructeur/Assignation est un gros plus.
4.  **Initialisation :** Utilise les **listes d'initialisation** dans tes constructeurs :
    `HumanA::HumanA(string name) : _name(name) {}` (C'est plus efficace et obligatoire pour les références).
5.  **Pas de `using namespace std;`** : C'est une mauvaise pratique qui pollue l'espace de nom. Utilise toujours le préfixe `std::`.

---
*Guide réalisé pour le projet C++ - 42 School*