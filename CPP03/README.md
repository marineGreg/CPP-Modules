# C++ Module 03 - Inheritance (Héritage)

Ce module est une introduction aux concepts fondamentaux de l'**Héritage** en Programmation Orientée Objet (POO) avec le standard C++98.

## 📌 Objectifs du Module
- Comprendre la hiérarchie des classes (relation "Est un").
- Apprendre à réutiliser du code sans le dupliquer.
- Maîtriser les spécificateurs d'accès (`private` vs `protected`).
- Résoudre des problèmes complexes comme le **Diamant de l'héritage**.

---

## 🛠 Concepts Clés

### 1. L'Héritage (Inheritance)
L'héritage permet à une classe (enfant) de récupérer les attributs et les méthodes d'une autre classe (parent).
- **Exemple :** `ScavTrap` hérite de `ClapTrap`. 
- **Relation :** On dit que ScavTrap **est un** ClapTrap.

### 2. Le mot-clé `protected`
C'est le juste milieu entre `public` et `private`.
- **`private`** : Uniquement accessible par la classe elle-même.
- **`protected`** : Accessible par la classe elle-même **ET ses classes enfants**.
- **`public`** : Accessible par tout le monde.
> *Note : Dans ce module, on passe les attributs de ClapTrap en `protected` pour que ses enfants puissent modifier leurs propres PV, Énergie, etc.*

### 3. Ordre de Construction et Destruction
L'ordre est strictement hiérarchique et logique :
- **Construction (Haut vers le Bas) :** Parent -> Enfant. 
    - *Pourquoi ?* Les fondations (parent) doivent exister avant de construire l'étage (enfant).
- **Destruction (Bas vers le Haut) :** Enfant -> Parent.
    - *Pourquoi ?* On retire les éléments spécifiques avant de détruire la base pour éviter de laisser des ressources orphelines.

### 4. Le Destructeur Virtuel (`virtual ~ClapTrap()`)
**C'est la règle d'or de l'héritage.**
Si une classe est destinée à être héritée, son destructeur doit être `virtual`. 
- **Problème :** Si on supprime un `ScavTrap` via un pointeur `ClapTrap*`, seul le destructeur du parent sera appelé.
- **Conséquence :** Fuites de mémoire et comportement indéfini.
- **Solution :** `virtual` garantit que toute la chaîne de destruction (de l'enfant vers le parent) est exécutée.

---

## 💎 Le Problème du Diamant (Exercice 03)

L'exercice 03 introduit le cas où une classe `DiamondTrap` hérite de `ScavTrap` et `FragTrap`, qui eux-mêmes héritent de `ClapTrap`.

### Le Problème
Sans précaution, `DiamondTrap` recevrait deux copies de `ClapTrap`. Cela crée une ambiguïté : quel `_name` ou quel `_hitPoints` utiliser ?

### La Solution : L'Héritage Virtuel
En utilisant `class ScavTrap : virtual public ClapTrap`, on indique au compilateur de ne créer qu'**une seule instance partagée** de la classe de base.

### Points particuliers du DiamondTrap :
- **Shadowing** : DiamondTrap a son propre `_name`. Pour accéder à celui du grand-parent, on doit utiliser `ClapTrap::_name`.
- **Using** : Comme ScavTrap et FragTrap ont tous deux une méthode `attack()`, on utilise `using ScavTrap::attack;` pour lever l'ambiguïté.

---

## 📋 Résumé des Exercices

| Exercice | Classe | Concept Principal |
| :--- | :--- | :--- |
| **Ex00** | `ClapTrap` | Base, Encapsulation, Forme Canonique. |
| **Ex01** | `ScavTrap` | Héritage simple, `protected`, ordre de vie. |
| **Ex02** | `FragTrap` | Multiples branches d'héritage, spécialisation. |
| **Ex03** | `DiamondTrap` | Héritage multiple, héritage virtuel, résolution d'ambiguïté. |

---

## ⚠️ Checklist pour l'Évaluation

1. **Forme Canonique :** Chaque classe a-t-elle son constructeur par défaut, de recopie, son opérateur `=` et son destructeur ?
2. **Messages de Log :** Chaque constructeur/destructeur affiche-t-il un message unique pour prouver l'ordre d'appel ?
3. **Destructeur Virtuel :** Est-ce que `~ClapTrap()` est bien `virtual` ?
4. **Héritage Virtuel (Ex03) :** Est-ce que Scav et Frag héritent virtuellement de Clap ?
5. **Standard :** Le code compile-t-il avec `-std=c++98` ?
6. **Pas de Fuites :** Est-ce que `valgrind` est "green" (surtout lors de l'utilisation de pointeurs de base) ?

---
*Ce module permet de comprendre que l'héritage n'est pas juste une copie de code, mais une structure de données organisée et sécurisée.*