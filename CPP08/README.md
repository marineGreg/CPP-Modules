# C++ Module 08 — Templated Containers, Iterators & Algorithms

> Projet de l'École 42 consacré aux conteneurs de la STL, aux itérateurs, aux algorithmes standards et aux templates.

## Informations générales

- Standard : C++98
- Compilation : `c++ -Wall -Wextra -Werror -std=c++98`
- Exercices : `ex00`, `ex01`, `ex02`
- Sujet : [cpp08.pdf]

## Objectifs pédagogiques

Ce module introduit une utilisation plus idiomatique de la bibliothèque standard C++. Il met notamment en pratique :

- les fonctions et classes templates ;
- les conteneurs séquentiels de la STL ;
- les itérateurs mutables, constants et inversés ;
- les algorithmes de `<algorithm>` ;
- les adaptateurs de conteneurs, comme `std::stack` ;
- la gestion des erreurs avec les exceptions standards.

Les implémentations templates sont placées dans les fichiers d'en-tête afin que le compilateur puisse les instancier avec les types utilisés par le programme.

## Structure

```text
CPP08/
├── README.md
├── cpp08.pdf
├── ex00/
│   ├── Makefile
│   ├── easyfind.hpp
│   └── main.cpp
├── ex01/
│   ├── Makefile
│   ├── Span.hpp
│   ├── Span.cpp
│   └── main.cpp
└── ex02/
    ├── Makefile
    ├── MutantStack.hpp
    └── main.cpp
```

## Exercice 00 — Easy find

`easyfind` recherche un entier dans un conteneur séquentiel à l'aide de `std::find`.

Deux surcharges sont proposées :

```cpp
template <typename T>
typename T::iterator easyfind(T &container, int value);

template <typename T>
typename T::const_iterator easyfind(const T &container, int value);
```

La première permet de modifier l'élément trouvé à travers l'itérateur retourné. La seconde accepte un conteneur constant et retourne donc un `const_iterator`.

Comportement :

- la première occurrence est retournée lorsque la valeur existe ;
- une `std::runtime_error` est levée lorsque la valeur est absente ;
- les tests couvrent `std::vector`, `std::list`, `std::deque`, les doublons, les conteneurs constants et les conteneurs vides.

Complexité :

- temps : O(n) dans le pire cas ;
- mémoire supplémentaire : O(1).

## Exercice 01 — Span

La classe `Span` stocke au maximum `N` entiers et calcule l'écart le plus court ou le plus long entre deux valeurs.

### Ajout des valeurs

Un nombre peut être ajouté individuellement :

```cpp
span.addNumber(42);
```

Une plage complète peut également être ajoutée grâce à des itérateurs :

```cpp
span.addNumber(values.begin(), values.end());
```

La capacité est contrôlée avant l'insertion. Une `std::out_of_range` est levée lorsque le `Span` ne dispose pas d'assez de place.

### Calcul des écarts

`longestSpan()` recherche les valeurs minimale et maximale avec `std::min_element` et `std::max_element`, puis calcule leur différence.

- temps : O(n) ;
- mémoire supplémentaire : O(1).

`shortestSpan()` trie une copie des valeurs puis compare chaque paire voisine. Après le tri, l'écart minimal se trouve nécessairement entre deux éléments consécutifs.

- temps : O(n log n) ;
- mémoire supplémentaire : O(n).

Les deux méthodes retournent un `unsigned int`. Les soustractions sont effectuées en arithmétique non signée afin de prendre en charge sans débordement signé toute la plage des valeurs `int`, notamment `INT_MIN` et `INT_MAX`.

Une `std::logic_error` est levée lorsqu'un calcul est demandé avec moins de deux valeurs.

Les tests comprennent notamment :

- le cas officiel du sujet ;
- l'insertion de 15 000 nombres en un seul appel ;
- une plage provenant d'une `std::list` ;
- les nombres négatifs ;
- les valeurs extrêmes `INT_MIN` et `INT_MAX` ;
- les dépassements de capacité et les calculs impossibles.

## Exercice 02 — MutantStack

`std::stack` est un adaptateur de conteneur : il expose une interface LIFO, mais ne fournit pas directement d'itérateurs.

`MutantStack` hérite de `std::stack` et rend itérable son conteneur sous-jacent protégé, `c` :

```cpp
MutantStack<int>::iterator begin();
MutantStack<int>::iterator end();
```

L'implémentation fournit également :

- `const_iterator` avec les surcharges constantes de `begin()` et `end()` ;
- `reverse_iterator` avec `rbegin()` et `rend()` ;
- `const_reverse_iterator` pour le parcours inversé d'une pile constante.

La pile conserve les opérations habituelles de `std::stack`, comme `push`, `pop`, `top`, `size` et `empty`, tout en autorisant un parcours similaire à celui du conteneur sous-jacent.

## Compilation et exécution

Chaque exercice possède son propre `Makefile`.

### Exercice 00

```bash
cd CPP08/ex00
make
./easyfind
```

### Exercice 01

```bash
cd CPP08/ex01
make
./span
```

### Exercice 02

```bash
cd CPP08/ex02
make
./mutant
```

Commandes disponibles dans chaque exercice :

```bash
make        # Compile le programme
make clean  # Supprime les fichiers objets
make fclean # Supprime les objets et l'exécutable
make re     # Recompile entièrement le projet
```

## Points clés pour l'évaluation

- Un template doit être visible au moment de son instanciation, d'où son implémentation dans le fichier `.hpp`.
- `typename` indique au compilateur qu'un nom dépendant, comme `T::iterator`, représente un type.
- `end()` désigne la position située juste après le dernier élément et ne doit jamais être déréférencé.
- Un `const_iterator` autorise la lecture, mais interdit la modification de l'élément pointé.
- `std::find` retourne la première occurrence correspondante ou l'itérateur `end()`.
- Après un tri, l'écart minimal se trouve entre deux valeurs adjacentes.
- Trier une copie dans `shortestSpan()` préserve l'ordre interne des valeurs du `Span`.
- `std::stack` utilise par défaut un `std::deque` et conserve son conteneur sous-jacent dans le membre protégé `c`.

## Ressources

- [Documentation de `std::find`](https://en.cppreference.com/w/cpp/algorithm/find)
- [Documentation de `std::vector`](https://en.cppreference.com/w/cpp/container/vector)
- [Documentation de `std::stack`](https://en.cppreference.com/w/cpp/container/stack)
- [Documentation des catégories d'itérateurs](https://en.cppreference.com/w/cpp/iterator)
