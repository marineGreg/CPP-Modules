*This project has been created as part of the 42 curriculum by mgregoir*

# C++ - Module 04 : Polymorphisme, Classes Abstraites et Interfaces

## Présentation
Ce module marque une étape cruciale dans l'apprentissage de la Programmation Orientée Objet (POO) en C++. L'objectif est de comprendre comment rendre un code **flexible**, **évolutif** et **sécurisé** en utilisant le polymorphisme de sous-type.

---

## Concepts Clés

### 1. Le Polymorphisme de sous-type
C'est la capacité de manipuler des objets de classes différentes (ex: `Dog`, `Cat`) via un pointeur de leur classe parente (`Animal*`).
- **Liaison Statique (par défaut) :** Le compilateur choisit la fonction selon le type du *pointeur*.
- **Liaison Dynamique (avec `virtual`) :** Le programme choisit la fonction selon l'objet *réel* au moment de l'exécution (Runtime).

### 2. Le Destructeur Virtuel ⚠️
**La règle d'or :** Si une classe est destinée à être héritée, son destructeur **doit** être virtuel.
- **Pourquoi ?** Pour garantir que `delete animalPtr;` appelle le destructeur de l'enfant (`~Dog()`) AVEC celui du parent. Sans cela, seule la partie parente est détruite, provoquant des **fuites de mémoire** (leaks).

### 3. Deep Copy (Copie Profonde)
Dans l'exercice 01, on manipule des pointeurs internes (`Brain*`).
- **Shallow Copy :** On copie l'adresse. Deux objets partagent le même cerveau. Danger de crash (*Double Free*).
- **Deep Copy :** On alloue une nouvelle mémoire (`new Brain`) et on copie le contenu. Les objets sont indépendants.

### 4. Classes Abstraites & Interfaces
- **Classe Abstraite (Ex02) :** Contient au moins une fonction virtuelle pure (`virtual void f() = 0;`). On ne peut pas l'instancier. Elle sert de modèle.
- **Interface (Ex03) :** En C++98, c'est une classe sans attributs avec uniquement des fonctions virtuelles pures. Elle définit un contrat (ex: `ICharacter`).

---

## Structure des Exercices

### Exercice 00 : Polymorphisme de base
- **But :** Découvrir le mot-clé `virtual`.
- **Test "Wrong" :** Démontre que sans `virtual`, le polymorphisme échoue (liaison statique).

### Exercice 01 : I don’t want to set the world on fire
- **But :** Gérer des allocations dynamiques complexes.
- **Le Brain :** Chaque `Dog` et `Cat` possède son propre cerveau.
- **Vérification :** Utilisation de `valgrind` pour prouver l'absence de leaks grâce au destructeur virtuel.

### Exercice 02 : Classe Abstraite
- **But :** Sécuriser la conception.
- **Action :** Rendre `Animal` non-instanciable pour empêcher de créer un animal "générique" qui n'a pas de sens.

### Exercice 03 : Interface & Recap
- **But :** Créer un système de RPG (Materia).
- **Concepts :** Utilisation de `clone()` (Pattern Prototype) et gestion d'un inventaire complexe de pointeurs.

---

## Forme Canonique d'Orthodox (OCF)
Chaque classe doit implémenter :
1. **Constructeur par défaut**
2. **Constructeur de recopie** (gérant la Deep Copy si nécessaire)
3. **Opérateur d'affectation** (nettoyage de l'ancienne mémoire + Deep Copy)
4. **Destructeur** (Virtuel pour les classes de base)

---

## "Cheat Sheet" pour l'Évaluation

| Question possible | Réponse courte |
| :--- | :--- |
| **Pourquoi un destructeur virtuel ?** | Pour appeler le destructeur de l'enfant lors d'un `delete` sur un pointeur parent. |
| **C'est quoi `= 0` ?** | Une fonction virtuelle pure. Elle rend la classe abstraite. |
| **Différence Deep vs Shallow Copy ?** | Deep copie le contenu, Shallow copie juste l'adresse mémoire. |
| **Pourquoi `this != &other` ?** | Pour éviter l'auto-affectation qui pourrait supprimer la mémoire qu'on veut copier. |
| **C'est quoi une Interface ?** | Une classe qui définit "ce qu'un objet fait" sans dire "comment il le fait". |
