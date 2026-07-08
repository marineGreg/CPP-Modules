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

### Exercise 01: Serialization
**But :** Implémenter un mécanisme de sérialisation pour transformer un pointeur d'objet en un entier `uintptr_t` et vice-versa.
- **Apprentissage :** Comprendre que les adresses mémoires sont des valeurs numériques et apprendre à les manipuler sans perte de données.
- **Cast utilisé :** `reinterpret_cast`.

### Exercise 02: Identify real type
**But :** Identifier le type réel d'un objet caché derrière un pointeur ou une référence de classe de base, sans utiliser le mot-clé `typeid`.
- **Apprentissage :** Utilisation du RTTI (Run-Time Type Information) et gestion des échecs de cast (retour `NULL` pour les pointeurs vs `std::bad_cast` pour les références).
- **Cast utilisé :** `dynamic_cast`.

---

## Utilisation

### Compilation
Chaque exercice dispose d'un `Makefile` et respecte la norme **C++98**.
```bash
make