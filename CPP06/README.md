# C++ - Module 06 : C++ Casts

## Présentation
Ce module explore les différents types de **casts** (conversions de type) introduits par le C++. L'objectif est d'abandonner les "casts à la C" `(type)valeur` au profit des opérateurs de cast spécifiques et sécurisés de C++.

## Concepts Clés

Le module se concentre sur les 4 opérateurs de cast C++ :

| Opérateur | Utilisation principale | Vérification |
| :--- | :--- | :--- |
| `static_cast` | Conversions logiques (ex: int vers double) ou hiérarchie de classes certaine. | Compilation |
| `dynamic_cast` | Navigation sécurisée dans une hiérarchie polymorphe (downcasting). | Exécution (RTTI) |
| `reinterpret_cast` | Conversion de bas niveau (ex: pointeur vers entier). Très dangereux. | Aucune |
| `const_cast` | Ajouter ou supprimer le modificateur `const` ou `volatile`. | Compilation |

---

## Exercices

### Exercise 00: Conversion of scalar types
**But :** Créer une classe statique `ScalarConverter` capable de transformer une représentation textuelle (string) d'un littéral en ses types réels (`char`, `int`, `float`, `double`).
- **Apprentissage :** Manipulation des types scalaires, gestion des limites (overflow), détection de types et gestion des cas spéciaux (`nan`, `inf`).
- **Cast utilisé :** `static_cast`.
Pourquoi static_cast ?

    Utilisation : Conversion entre types numériques (double → int, char, float).

    Justification : Le static_cast est l'opérateur dédié aux conversions scalaires ayant un lien logique. Contrairement au cast de style C, il est vérifié à la compilation. Il effectue une véritable transformation de la valeur (ex: troncature des décimales lors d'un passage de double à int) de manière sécurisée.

### Exercise 01: Serialization
**But :** Implémenter un mécanisme de sérialisation pour transformer un pointeur d'objet en un entier `uintptr_t` et vice-versa.
- **Apprentissage :** Comprendre que les adresses mémoires sont des valeurs numériques et apprendre à les manipuler sans perte de données.
- **Cast utilisé :** `reinterpret_cast`.
Pourquoi reinterpret_cast ?

    Utilisation : Conversion entre un pointeur d'objet (Data*) et un entier (uintptr_t).

    Justification : Il n'existe aucun lien logique ou hiérarchique entre une adresse mémoire et un nombre entier. Le reinterpret_cast est le seul opérateur capable de forcer le compilateur à réinterpréter un motif de bits d'un type vers un autre sans aucune transformation. C'est l'outil de prédilection pour le "bas niveau" et la sérialisation.

### Exercise 02: Identify real type
**But :** Identifier le type réel d'un objet caché derrière un pointeur ou une référence de classe de base, sans utiliser le mot-clé `typeid`.
- **Apprentissage :** Utilisation du RTTI (Run-Time Type Information) et gestion des échecs de cast (retour `NULL` pour les pointeurs vs `std::bad_cast` pour les références).
- **Cast utilisé :** `dynamic_cast`.
Pourquoi dynamic_cast ?

    Utilisation : Identification du type réel d'une instance dans une hiérarchie polymorphe.

    Justification : C'est le seul cast qui effectue une vérification à l'exécution (RTTI).
    Sur un pointeur, il renvoie NULL en cas d'échec, permettant une structure if/else.

    Sur une référence, il lance une exception std::bad_cast en cas d'échec, car une référence ne peut être nulle.
    Note : Il nécessite obligatoirement que la classe de base possède au moins une fonction virtuelle (destructeur virtuel ici).

Pourquoi pas const_cast ?

    Justification : Le const_cast sert exclusivement à ajouter ou supprimer les modificateurs const ou volatile. Aucun exercice de ce module ne nécessitait de modifier la mutabilité des objets, cet opérateur n'a donc pas été utilisé.
---
## Utilisation

### Compilation
Chaque exercice dispose d'un `Makefile` et respecte la norme **C++98**.
```bash
make