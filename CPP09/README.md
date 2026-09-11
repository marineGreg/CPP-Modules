# CPP Module 09 — STL

Ce module clôt la série des modules C++ de 42 et se concentre sur l’utilisation de la **STL** (*Standard Template Library*).

Il contient trois exercices indépendants :

1. `BitcoinExchange` : recherche de données dans une `std::map` ;
2. `RPN` : évaluation d’une expression avec une `std::stack` ;
3. `PmergeMe` : tri Ford-Johnson avec `std::vector` et `std::deque`.

Chaque exercice doit utiliser un ou plusieurs conteneurs différents :

| Exercice | Programme  | Conteneurs principaux       |
| -------- | ---------- | --------------------------- |
| ex00     | `btc`      | `std::map`                  |
| ex01     | `RPN`      | `std::stack`                |
| ex02     | `PmergeMe` | `std::vector`, `std::deque` |

Le projet est compilé en **C++98** avec les options :

```bash
-Wall -Wextra -Werror -std=c++98
```

---

## Structure du module

```text
CPP09/
├── ex00/
│   ├── BitcoinExchange.cpp
│   ├── BitcoinExchange.hpp
│   ├── data.csv
│   ├── input.txt
│   ├── main.cpp
│   └── Makefile
│
├── ex01/
│   ├── RPN.cpp
│   ├── RPN.hpp
│   ├── main.cpp
│   └── Makefile
│
└── ex02/
    ├── PmergeMe.cpp
    ├── PmergeMe.hpp
    ├── main.cpp
    └── Makefile
```

---

# Exercice 00 — Bitcoin Exchange

## Objectif

Le programme `btc` calcule la valeur d’une quantité de Bitcoin à une date donnée.

Il utilise deux fichiers :

* `data.csv` contient l’historique des taux du Bitcoin ;
* un fichier fourni en argument contient les dates et quantités à évaluer.

Exemple :

```bash
./btc input.txt
```

Format du fichier d’entrée :

```text
date | value
2011-01-03 | 3
2012-01-11 | 1.5
```

Sortie correspondante :

```text
2011-01-03 => 3 = 0.9
2012-01-11 => 1.5 = 10.65
```

## Conteneur utilisé

Les taux sont stockés dans :

```cpp
std::map<std::string, double>
```

La clé représente la date et la valeur représente le taux :

```text
"2011-01-03" → 0.3
"2011-01-04" → 0.3
"2011-01-05" → 0.3
```

Une `std::map` présente plusieurs avantages :

* ses clés sont automatiquement triées ;
* une date peut être recherchée efficacement ;
* `lower_bound()` permet de retrouver la date inférieure la plus proche.

## Pourquoi les dates peuvent-elles être comparées comme des chaînes ?

Les dates utilisent le format :

```text
YYYY-MM-DD
```

L’année se trouve avant le mois, et le mois avant le jour. Chaque partie possède une taille fixe.

L’ordre lexicographique correspond donc à l’ordre chronologique :

```text
2011-01-03 < 2011-02-01 < 2012-01-01
```

Cela permet d’utiliser directement les dates comme clés de la `std::map`.

## Chargement de la base

La fonction :

```cpp
bool loadDatabase(const std::string &databasePath);
```

ouvre `data.csv`, vérifie son en-tête puis analyse chaque ligne :

```text
date,exchange_rate
2009-01-02,0
2009-01-05,0
...
```

Chaque date et chaque taux sont validés avant d’être insérés dans la map.

Une map temporaire est utilisée pendant le chargement. L’attribut `_database` n’est remplacé qu’une fois tout le fichier validé :

```cpp
_database.swap(database);
```

Cela évite de conserver une base partiellement chargée lorsqu’une erreur est rencontrée.

## Validation des dates

Une date doit :

* contenir exactement 10 caractères ;
* posséder des tirets aux positions 4 et 7 ;
* ne contenir que des chiffres en dehors des tirets ;
* avoir un mois compris entre 1 et 12 ;
* posséder un jour valide pour le mois concerné.

Les années bissextiles suivent cette règle :

```text
divisible par 4
ET
non divisible par 100, sauf si divisible par 400
```

Ainsi :

```text
2012-02-29 → valide
2011-02-29 → invalide
1900-02-29 → invalide
2000-02-29 → valide
```

## Validation des valeurs

Une valeur peut être un entier ou un nombre décimal.

Le programme vérifie d’abord sa syntaxe, puis utilise :

```cpp
std::strtod()
```

pour effectuer la conversion en `double`.

Selon le sujet, la quantité doit être comprise entre `0` et `1000`.

Exemples :

```text
42       → valide
1.5      → valide
-1       → nombre négatif
1000     → valide
1000.01  → trop grand
hello    → entrée invalide
```

## Recherche du taux

La recherche utilise :

```cpp
_database.lower_bound(date);
```

`lower_bound()` renvoie le premier élément dont la clé est supérieure ou égale à la date demandée.

Trois situations sont possibles.

### Date exacte

Si la date existe dans la base, son taux est utilisé directement.

```text
Date demandée : 2011-01-03
Date trouvée  : 2011-01-03
```

### Date absente mais située après le début de la base

Si `lower_bound()` renvoie une date supérieure, l’itérateur est reculé d’une position.

```text
Dates disponibles :
2011-01-03
2011-01-05

Date demandée :
2011-01-04

Date utilisée :
2011-01-03
```

Le sujet demande en effet d’utiliser la date **inférieure** la plus proche, jamais la date supérieure.

### Date antérieure à toute la base

Si l’itérateur se trouve déjà sur `begin()` sans correspondance exacte, aucune date antérieure n’existe.

La ligne est alors rejetée.

## Complexité

Pour une base contenant `N` taux :

* insertion dans la map : `O(log N)` ;
* recherche d’une date : `O(log N)` ;
* chargement complet : environ `O(N log N)`.

## Compilation et utilisation

```bash
cd ex00
make
./btc input.txt
```

Nettoyage :

```bash
make clean
make fclean
make re
```

---

# Exercice 01 — Reverse Polish Notation

## Objectif

Le programme `RPN` évalue une expression écrite en **notation polonaise inversée**.

Dans cette notation, les opérateurs sont placés après leurs opérandes.

Notation classique :

```text
7 × 7 - 7
```

Notation polonaise inversée :

```text
7 7 * 7 -
```

Utilisation :

```bash
./RPN "7 7 * 7 -"
```

Résultat :

```text
42
```

## Conteneur utilisé

Le programme utilise :

```cpp
std::stack<int>
```

Une `std::stack` fonctionne selon le principe **LIFO** :

```text
Last In, First Out
```

Le dernier élément ajouté est le premier retiré.

Cela correspond parfaitement au fonctionnement d’une expression RPN.

## Fonctionnement général

L’expression est découpée en tokens grâce à :

```cpp
std::istringstream
```

Pour chaque token :

* s’il s’agit d’un chiffre, il est ajouté à la pile ;
* s’il s’agit d’un opérateur, deux valeurs sont retirées ;
* le résultat de l’opération est remis dans la pile.

À la fin, la pile doit contenir exactement une valeur.

## Exemple détaillé

Expression :

```text
7 7 * 7 -
```

### Token `7`

```text
Pile : [7]
```

### Deuxième token `7`

```text
Pile : [7, 7]
```

### Token `*`

Les deux valeurs sont retirées :

```text
7 × 7 = 49
```

Le résultat est empilé :

```text
Pile : [49]
```

### Token `7`

```text
Pile : [49, 7]
```

### Token `-`

La valeur située au sommet est retirée en premier :

```text
right = 7
left  = 49
```

Le calcul doit respecter l’ordre :

```text
left - right
49 - 7 = 42
```

Résultat final :

```text
Pile : [42]
```

## Importance de l’ordre des opérandes

Pour l’addition et la multiplication, inverser les opérandes ne change pas le résultat.

Ce n’est pas vrai pour la soustraction et la division :

```text
8 2 -
```

doit produire :

```text
8 - 2 = 6
```

et non :

```text
2 - 8 = -6
```

Le premier élément retiré de la pile est donc l’opérande droite.

## Validation des tokens

Le sujet limite les nombres d’entrée aux chiffres inférieurs à 10.

Chaque token doit donc contenir exactement un caractère :

```text
0 à 9
+
-
*
/
```

Exemples invalides :

```text
12
-5
hello
(1 + 1)
```

Les calculs et résultats intermédiaires peuvent toutefois dépasser 9.

## Gestion des erreurs

Une expression est invalide si :

* elle contient un token inconnu ;
* un opérateur ne possède pas deux opérandes ;
* une division par zéro est demandée ;
* plusieurs valeurs restent dans la pile à la fin ;
* aucune valeur ne reste dans la pile.

Exemples :

```bash
./RPN "1 +"
```

Il manque une opérande.

```bash
./RPN "1 2"
```

Il manque un opérateur.

```bash
./RPN "1 0 /"
```

Division par zéro.

```bash
./RPN "(1 + 1)"
```

Les parenthèses ne sont pas autorisées.

## Pourquoi doit-il rester une seule valeur ?

Une expression complète réduit progressivement tous ses opérandes jusqu’à obtenir un unique résultat.

Pile vide :

```text
aucun résultat
```

Plusieurs valeurs :

```text
certains opérandes n’ont pas été utilisés
```

Exactement une valeur :

```text
expression complète et résultat valide
```

## Complexité

Pour une expression contenant `N` tokens :

* chaque token est traité une seule fois ;
* `push()`, `pop()` et `top()` sont des opérations constantes.

La complexité est donc :

```text
O(N)
```

## Compilation et utilisation

```bash
cd ex01
make
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

Résultat :

```text
42
```

---

# Exercice 02 — PmergeMe

## Objectif

Le programme `PmergeMe` trie une séquence d’entiers positifs avec l’algorithme **Ford-Johnson**, aussi appelé **merge-insert sort**.

Le tri est implémenté séparément avec :

```cpp
std::vector<int>
std::deque<int>
```

Le programme affiche :

1. la séquence avant le tri ;
2. la séquence après le tri ;
3. le temps de traitement du `vector` ;
4. le temps de traitement du `deque`.

Exemple :

```bash
./PmergeMe 3 5 9 7 4
```

```text
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::vector : 16.00000 us
Time to process a range of 5 elements with std::deque : 31.00000 us
```

Les temps changent à chaque exécution.

## Pourquoi deux conteneurs ?

Le sujet impose l’utilisation d’au moins deux conteneurs différents.

Les deux implémentations reçoivent exactement la même entrée et exécutent le même algorithme.

### `std::vector`

Les éléments sont stockés dans une zone mémoire contiguë.

Avantages :

* accès rapide par index ;
* bonne localité mémoire ;
* parcours généralement rapide.

Inconvénient :

* une insertion au milieu déplace les éléments suivants.

### `std::deque`

Les éléments sont répartis dans plusieurs blocs mémoire.

Avantages :

* insertions efficaces aux extrémités ;
* accès aléatoire toujours disponible.

Inconvénient :

* mémoire non contiguë ;
* parcours parfois moins favorable au cache processeur.

Une exécution isolée ne permet cependant pas de conclure qu’un conteneur est toujours plus rapide que l’autre.

## Validation de l’entrée

Le programme accepte uniquement des entiers strictement positifs compris entre `1` et `INT_MAX`.

Sont notamment rejetés :

```text
0
-1
2.5
abc
2147483648
```

Chaque argument peut contenir un ou plusieurs nombres :

```bash
./PmergeMe 3 5 9 7 4
```

et :

```bash
./PmergeMe "3 5 9 7 4"
```

sont tous les deux acceptés.

`strtol()` effectue la conversion et `errno` permet de détecter un dépassement de capacité.

---

## Principe de Ford-Johnson

Ford-Johnson cherche principalement à réduire le nombre de comparaisons nécessaires au tri.

Il ne faut pas le confondre avec un simple tri utilisant `std::sort()`.

L’algorithme suit plusieurs grandes étapes :

1. former des paires ;
2. comparer les valeurs de chaque paire ;
3. trier récursivement les plus grandes valeurs ;
4. construire une chaîne principale ;
5. insérer les petites valeurs dans un ordre particulier ;
6. limiter la recherche de chaque valeur à son partenaire.

## 1. Formation des paires

Les nombres sont regroupés deux par deux.

Exemple :

```text
3 5 9 7
```

Paires initiales :

```text
(3, 5)
(9, 7)
```

Chaque paire est réorganisée sous la forme :

```text
(a_i, b_i)
```

avec :

```text
a_i >= b_i
```

On obtient :

```text
(a1 = 5, b1 = 3)
(a2 = 9, b2 = 7)
```

Dans le code :

```cpp
pair.first  = a_i
pair.second = b_i
```

## 2. Gestion d’un élément impair

Si la séquence contient un nombre impair d’éléments, le dernier est temporairement isolé.

Avec :

```text
3 5 9 7 4
```

les paires sont :

```text
(5, 3)
(9, 7)
```

et l’élément isolé est :

```text
4
```

Cet élément rejoindra ensuite les valeurs en attente d’insertion.

## 3. Tri récursif des maxima

Les maxima `a_i` sont extraits :

```text
5 9
```

Ils sont triés récursivement avec le même algorithme.

Cette récursion continue jusqu’au cas de base :

```cpp
if (sequence.size() <= 1)
	return;
```

Une séquence de zéro ou un élément est déjà triée.

## 4. Réorganisation des paires

Une fois les maxima triés, les paires doivent être replacées dans le même ordre.

Si les maxima triés sont :

```text
a1 a2 a3
```

leurs minima associés doivent rester :

```text
b1 b2 b3
```

Le tableau `used` garantit que chaque paire n’est sélectionnée qu’une seule fois, y compris lorsque des valeurs sont dupliquées.

## 5. Construction de la chaîne principale

La chaîne principale est initialement construite ainsi :

```text
b1, a1, a2, a3...
```

Les maxima sont déjà triés.

`b1` peut être placé directement avant `a1` car la comparaison de la première paire garantit :

```text
b1 <= a1
```

Les valeurs en attente sont représentées par :

```text
pending = b1, b2, b3...
```

`b1` est présent dans `pending` pour conserver les indices, mais il est déjà inséré dans la chaîne principale.

## 6. Suite de Jacobsthal

Les autres minima ne sont pas insérés dans l’ordre naturel.

Ford-Johnson utilise des bornes dérivées de la suite de Jacobsthal :

```text
J(0) = 0
J(1) = 1
J(n) = J(n - 1) + 2 × J(n - 2)
```

Premiers nombres :

```text
0, 1, 1, 3, 5, 11, 21, 43...
```

L’ordre d’insertion correspondant commence ainsi :

```text
b1, b3, b2, b5, b4, b11, b10, b9, b8, b7, b6...
```

Comme `b1` est déjà inséré, `_buildInsertionOrder()` génère les indices correspondant à :

```text
b3, b2, b5, b4, b11...
```

Avec des indices commençant à zéro :

```text
2, 1, 4, 3, 10, 9, 8, 7, 6, 5...
```

Cet ordre permet de maintenir des tailles de zones de recherche particulièrement adaptées à la recherche binaire.

## 7. Recherche bornée

Chaque `b_i` possède un partenaire `a_i` avec la relation :

```text
b_i <= a_i
```

Il est donc inutile de chercher une position après `a_i`.

La recherche binaire est limitée à :

```text
[début de la chaîne, position de a_i[
```

Dans le code :

```cpp
std::lower_bound(
	mainChain.begin(),
	mainChain.begin() + searchEnd,
	pending[index]
);
```

L’élément impair n’a pas de partenaire. Sa borne de recherche correspond donc à la fin de la chaîne.

## 8. Mise à jour des positions

Chaque insertion dans la chaîne peut déplacer les maxima vers la droite.

Le tableau :

```cpp
partnerPositions
```

conserve la position actuelle de chaque `a_i`.

Après une insertion, toutes les positions situées après le point d’insertion sont incrémentées :

```cpp
if (partnerPositions[j] >= insertPosition)
	++partnerPositions[j];
```

Sans cette mise à jour, les recherches suivantes utiliseraient des bornes devenues incorrectes.

---

## Exemple complet simplifié

Séquence :

```text
3 5 9 7 4
```

### Paires

```text
(5, 3)
(9, 7)
```

Élément impair :

```text
4
```

### Maxima triés

```text
5 9
```

### Chaîne principale

```text
3 5 9
```

### Éléments en attente

```text
3 7 4
```

Le premier `3` est déjà présent dans la chaîne.

Pour cette taille, l’ordre calculé commence par l’indice `2`, puis l’indice `1`.

### Insertion de `4`

L’élément impair n’a pas de partenaire : la recherche utilise toute la chaîne.

```text
3 4 5 9
```

### Insertion de `7`

`7` est associé à `9`. La recherche s’arrête donc avant `9`.

```text
3 4 5 7 9
```

La séquence est triée.

---

## Mesure du temps

Le programme utilise :

```cpp
gettimeofday()
```

Le temps est converti en microsecondes :

```cpp
(end.tv_sec - start.tv_sec) * 1000000.0
	+ (end.tv_usec - start.tv_usec);
```

La mesure comprend :

* le remplissage du conteneur ;
* la gestion des données ;
* le tri Ford-Johnson.

Le parsing initial est commun aux deux conteneurs et est effectué avant les mesures.

Pour une très petite séquence, les temps sont instables car le coût du chronométrage et des allocations devient important.

Des résultats comme ceux-ci sont normaux :

```text
std::vector : 16.00000 us
std::deque  : 31.00000 us
```

Ils peuvent être différents à l’exécution suivante.

## Vérification interne

Après les deux tris, le programme vérifie que `vector` et `deque` ont produit exactement le même résultat :

```cpp
std::equal(
	_vector.begin(),
	_vector.end(),
	_deque.begin()
);
```

Une différence entre les deux conteneurs provoque une exception.

## Complexité de l’implémentation

Ford-Johnson est conçu pour limiter le nombre de comparaisons.

Cependant, cette implémentation réassocie les maxima triés à leurs paires avec une double boucle :

```text
pour chaque maximum
    parcourir les paires
```

Cette étape peut atteindre une complexité de `O(N²)`.

Il faut donc distinguer :

* la logique de Ford-Johnson, qui optimise les comparaisons ;
* la complexité pratique de cette implémentation particulière ;
* les performances réelles de `vector` et `deque`.

Le sujet exige surtout une implémentation correcte de l’algorithme et la capacité de traiter au moins 3000 entiers.

## Compilation et utilisation

```bash
cd ex02
make
./PmergeMe 3 5 9 7 4
```

Test avec 3000 valeurs différentes sous Linux :

```bash
./PmergeMe $(shuf -i 1-100000 -n 3000)
```

Test avec 3000 valeurs sous macOS :

```bash
./PmergeMe $(jot -r 3000 1 100000)
```

Exemples invalides :

```bash
./PmergeMe
./PmergeMe -1 2
./PmergeMe 0
./PmergeMe 1 2.5 3
./PmergeMe 2147483648
```

---

# Concepts importants du module

## STL

La STL fournit notamment :

* des conteneurs ;
* des itérateurs ;
* des algorithmes génériques ;
* des adaptateurs de conteneurs.

Exemples utilisés dans ce module :

```cpp
std::map
std::stack
std::vector
std::deque
std::lower_bound
std::equal
```

## Itérateurs

Un itérateur désigne une position dans un conteneur.

Exemple :

```cpp
std::map<std::string, double>::const_iterator it;
```

Il permet de parcourir ou de désigner un élément sans manipuler directement sa représentation mémoire.

## `lower_bound()`

Deux versions de `lower_bound()` apparaissent conceptuellement dans le module.

### Méthode de `std::map`

```cpp
_database.lower_bound(date);
```

Elle recherche une clé dans un arbre trié.

### Algorithme de la STL

```cpp
std::lower_bound(begin, end, value);
```

Il effectue une recherche binaire dans une plage déjà triée.

Les deux portent le même nom mais ne sont pas la même fonction.

## Forme canonique orthodoxe

Les classes du module possèdent :

* un constructeur par défaut ;
* un constructeur de copie ;
* un opérateur d’affectation ;
* un destructeur.

Exemple :

```cpp
ClassName();
ClassName(const ClassName &src);
ClassName &operator=(const ClassName &other);
~ClassName();
```

---

# Questions possibles en évaluation

## Pourquoi utiliser une map dans BitcoinExchange ?

Parce qu’elle conserve les dates triées et permet de rechercher efficacement une date exacte ou la date inférieure la plus proche.

## Pourquoi les dates sont-elles stockées comme des chaînes ?

Parce que le format fixe `YYYY-MM-DD` possède le même ordre lexicographique que l’ordre chronologique.

## Pourquoi utiliser une stack pour RPN ?

Parce que l’évaluation RPN utilise toujours en premier les dernières opérandes rencontrées, ce qui correspond au fonctionnement LIFO d’une pile.

## Pourquoi l’opérande droite est-elle retirée en premier ?

Parce qu’elle se trouve au sommet de la pile. Pour `8 2 -`, le premier retrait donne `2`, mais le calcul doit rester `8 - 2`.

## Pourquoi trier une copie dans `shortestSpan()` ?

Cette question appartient au CPP08, pas au CPP09. Dans le CPP09, l’équivalent à retenir est que `PmergeMe` travaille sur deux copies identiques de l’entrée pour comparer les deux conteneurs.

## Pourquoi Ford-Johnson forme-t-il des paires ?

Chaque comparaison de paire établit immédiatement une relation `b_i <= a_i`. Cette information permet ensuite de limiter la zone dans laquelle `b_i` doit être recherché.

## Pourquoi trier les maxima récursivement ?

Ils forment la base triée de la chaîne principale. Les minima peuvent ensuite y être insérés en profitant de leur relation avec leurs partenaires.

## À quoi sert Jacobsthal ?

La suite détermine un ordre d’insertion qui produit des zones de recherche binaire de tailles avantageuses et limite le nombre de comparaisons.

## Pourquoi conserver `partnerPositions` ?

Parce que les insertions déplacent les maxima. Le programme doit toujours connaître la position actuelle du partenaire de chaque minimum afin de conserver une recherche correctement bornée.

## Pourquoi implémenter le tri deux fois ?

Le sujet recommande explicitement une implémentation propre à chaque conteneur afin d’observer leur comportement et leurs performances.

---

# Bilan

Ce module permet de travailler plusieurs usages complémentaires de la STL :

* `std::map` pour organiser et rechercher des données triées ;
* `std::stack` pour modéliser un traitement LIFO ;
* `std::vector` et `std::deque` pour comparer deux représentations d’une même séquence ;
* les itérateurs et algorithmes standards ;
* le parsing et la validation d’entrées ;
* les recherches binaires ;
* la récursivité ;
* l’algorithme Ford-Johnson ;
* la suite de Jacobsthal ;
* la mesure de performances.

La principale idée à retenir est que choisir un conteneur ne dépend pas seulement des données à stocker : ce choix dépend surtout des opérations que le programme doit effectuer sur ces données.
