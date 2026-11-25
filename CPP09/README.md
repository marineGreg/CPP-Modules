# CPP Module 09 - STL

CPP09 termine les modules C++ de 42 avec trois problèmes indépendants fondés sur la STL : rechercher une donnée ordonnée, évaluer une expression avec une pile et appliquer le tri Ford-Johnson à deux conteneurs.

Le projet est écrit en C++98 et compilé avec :

```bash
-Wall -Wextra -Werror -std=c++98
```

## Vue d'ensemble

| Exercice | Programme | Conteneur principal | Problème résolu |
|---|---|---|---|
| ex00 | `btc` | `std::map` | Retrouver un taux de Bitcoin par date |
| ex01 | `RPN` | `std::stack` | Évaluer une expression en notation polonaise inversée |
| ex02 | `PmergeMe` | `std::vector`, `std::deque` | Trier avec Ford-Johnson et comparer les temps |

Le sujet interdit de réutiliser, dans les exercices suivants, un conteneur déjà choisi. Ici, les choix explicites sont donc `map`, puis `stack`, puis `vector` et `deque`.

## Compilation

Chaque exercice possède son propre Makefile :

```bash
cd ex00 && make
cd ex01 && make
cd ex02 && make
```

Règles disponibles : `all`, `clean`, `fclean` et `re`.

---

# Ex00 - Bitcoin Exchange

## Objectif

`btc` charge les taux contenus dans `data.csv`, puis traite un fichier fourni en argument :

```text
date | value
2011-01-03 | 3
2011-01-09 | 1
```

Pour chaque ligne valide, le programme affiche :

```text
date => quantité = quantité * taux
```

## Pourquoi `std::map<std::string, double>` ?

La map associe une date à un taux et maintient automatiquement ses clés triées.

Le format fixe `YYYY-MM-DD` possède le même ordre lexicographique que l'ordre chronologique :

```text
2011-01-03 < 2011-02-01 < 2012-01-01
```

La recherche d'une date s'effectue en `O(log N)` avec `lower_bound()`.

## Chargement de la base

`loadDatabase()` :

1. ouvre `data.csv` ;
2. vérifie l'en-tête `date,exchange_rate` ;
3. valide chaque date et chaque taux ;
4. remplit une map temporaire ;
5. échange cette map avec `_dB` seulement si tout le CSV est valide.

L'utilisation d'une structure temporaire évite de conserver une base partiellement chargée.

## Validation des dates

`_isValidDate()` contrôle :

- le format exact de dix caractères ;
- les tirets aux positions 4 et 7 ;
- les chiffres ;
- le nombre de jours de chaque mois ;
- les années bissextiles.

Règle d'une année bissextile : divisible par 4, sauf les multiples de 100, à moins qu'ils soient aussi divisibles par 400.

## Validation des valeurs

`_isValidValue()` accepte une écriture numérique complète, éventuellement décimale ou scientifique, puis convertit avec `strtod()`.

`processInput()` applique ensuite les limites du sujet :

- valeur inférieure à 0 : `Error: not a positive number.` ;
- valeur supérieure à 1000 : `Error: too large a number.` ;
- 0 et 1000 sont acceptés.

## Recherche du taux inférieur le plus proche

```cpp
std::map<std::string, double>::const_iterator rate = _dB.lower_bound(date);
```

`lower_bound(date)` renvoie la première clé supérieure ou égale à `date`.

- si la clé est égale, le taux exact est utilisé ;
- si la clé est supérieure ou si l'itérateur vaut `end()`, le code recule avec `--rate` ;
- si l'itérateur vaut déjà `begin()` sans égalité, aucune date antérieure n'existe.

`first` désigne la date et `second` le taux :

```cpp
rate->first   // date
rate->second  // taux
```

## Gestion des erreurs

Une mauvaise ligne utilisateur affiche une erreur puis utilise `continue`. Le programme poursuit donc le traitement du reste du fichier, comme l'exige la grille.

Une erreur globale - fichier absent, mauvais en-tête, erreur grave de lecture - fait échouer `processInput()`.

## Utilisation

```bash
cd ex00
make
./btc input.txt
```

---

# Ex01 - Reverse Polish Notation

## Objectif

`RPN` évalue une expression en notation polonaise inversée :

```bash
./RPN "7 7 * 7 -"
```

Résultat :

```text
42
```

## Pourquoi `std::stack<int>` ?

Une pile fonctionne en LIFO : le dernier élément empilé est le premier retiré. Une expression RPN utilise précisément les deux résultats les plus récents lorsqu'elle rencontre un opérateur.

## Algorithme

L'expression est découpée avec `std::istringstream`.

- chiffre de `0` à `9` : `push()` ;
- opérateur : récupérer deux valeurs, calculer, puis réempiler le résultat ;
- fin de l'expression : la pile doit contenir exactement une valeur.

## Ordre des opérandes

Le sommet contient l'opérande droite :

```cpp
right = _stack.top();
_stack.pop();
left = _stack.top();
_stack.pop();
```

Le calcul est ensuite :

```text
left opérateur right
```

Pour `8 3 -`, il faut donc calculer `8 - 3`, et non `3 - 8`.

## Erreurs gérées

- mauvais nombre d'arguments ;
- token différent d'un chiffre ou de `+ - * /` ;
- moins de deux opérandes avant un opérateur ;
- division par zéro ;
- zéro ou plusieurs résultats restant à la fin.

Le sujet ne demande ni parenthèses, ni nombres décimaux, ni opérandes d'entrée supérieures ou égales à 10.

## Tests de la grille

```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"                  # 42
./RPN "9 8 * 4 * 4 / 2 + 9 - 8 - 8 - 1 - 6 -"      # 42
./RPN "1 2 * 2 / 2 + 5 * 6 - 1 3 * - 4 5 * * 8 /"  # 15
```

## Complexité

Chaque token est traité une fois. La complexité temporelle est `O(N)` et la pile peut contenir jusqu'à `O(N)` valeurs.

---

# Ex02 - PmergeMe

## Objectif

`PmergeMe` trie une séquence d'entiers strictement positifs avec le merge-insert sort de Ford-Johnson.

Deux implémentations séparées sont présentes :

```cpp
void _sortVector(std::vector<int> &numbers);
void _sortDeque(std::deque<int> &numbers);
```

Cette séparation suit la recommandation du sujet d'éviter une fonction de tri générique.

## Pourquoi `vector` et `deque` ?

Les deux fournissent :

- l'accès aléatoire avec `operator[]` ;
- des itérateurs à accès aléatoire utilisables par `lower_bound()` ;
- les insertions nécessaires à la construction de la chaîne triée.

`vector` utilise un bloc mémoire contigu, souvent favorable au cache. `deque` répartit ses éléments dans plusieurs blocs. Les insertions au milieu restent `O(N)` dans les deux cas, mais leurs constantes et leur localité mémoire diffèrent.

## Parsing

`_parseInput()` :

- accepte un ou plusieurs nombres par argument ;
- refuse les signes, décimales et caractères non numériques ;
- convertit avec `strtol()` ;
- refuse 0, les nombres négatifs et les valeurs supérieures à `INT_MAX`.

Les doublons sont autorisés : leur gestion est laissée au choix par le sujet.

## Ford-Johnson dans cette implémentation

### 1. Isoler l'élément impair

Si la taille est impaire, le dernier élément est temporairement retiré et conservé dans `straggler`.

### 2. Former les paires

Chaque paire est comparée une seule fois :

```text
high = plus grande valeur
low  = plus petite valeur
```

Le code construit deux séquences parallèles :

```text
highs[i] <-> lows[i]
```

### 3. Trier récursivement les `highs`

`mainChain` reçoit une copie de `highs`, puis la même fonction de tri est appelée récursivement.

Le cas de base est une séquence de taille 0 ou 1.

### 4. Réassocier les partenaires

Le tri récursif change l'ordre des `highs`. La double boucle reconstruit `pending` afin de préserver l'invariant :

```text
pending[i] est le partenaire de mainChain[i]
```

Le conteneur `used`, rempli initialement de zéros, empêche de sélectionner deux fois la même paire lorsque plusieurs `highs` ont la même valeur.

### 5. Construire la chaîne principale

Les `highs` triés forment la base de `sorted`.

`pending[0]`, c'est-à-dire `b1`, est placé directement au début : comme `b1 <= a1` et que `a1` est le plus petit des grands éléments, aucune recherche n'est nécessaire.

### 6. Construire l'ordre Jacobsthal

`_buildInsertionOrder()` génère les indices zéro-based correspondant à :

```text
b3, b2, b5, b4, b11, b10, b9, b8, b7, b6...
```

Les bornes utiles suivent :

```text
1, 3, 5, 11, 21, 43...
```

avec :

```text
next = current + 2 * previous
```

Jacobsthal ne détermine pas la position finale d'un nombre. Il détermine seulement quel `b_i` sera inséré ensuite.

### 7. Insérer les éléments de `pending`

Après la réassociation, si la taille d'entrée était impaire, le
`straggler` est ajouté à la fin de `pending`, avant de calculer
l'ordre Jacobsthal. Il participe donc au même ordre d'insertion
que les autres `b_i`.

Pour chaque indice choisi, on récupère `value = pending[index]` :

- Si l'élément a un partenaire, `mainChain[index]` donne sa valeur.
  Un premier `lower_bound` retrouve la première occurrence de cette
  valeur dans `sorted` et fixe la borne `upBound`.
- Si `index == mainChain.size()` et que la taille était impaire,
  c'est le `straggler`. Il n'a pas de partenaire : on ne lit pas
  `mainChain[index]` et `upBound` reste à `sorted.end()`.

Un second `lower_bound` cherche la position d'insertion dans
`[sorted.begin(), upBound)`. Pour un élément apparié, la recherche
s'arrête avant la borne, car la comparaison de la paire a déjà établi
`value <= partner`. Pour le `straggler`, la recherche couvre toute
la chaîne triée.

## Exemple avec le code actuel

Entrée :

```text
12 4 6 9 3 8 2 10 1
```

Au premier niveau :

```text
highs = [12, 9, 8, 10]
lows  = [ 4, 6, 3,  2]
straggler = 1
```

Après le tri récursif, la réassociation et l'ajout du `straggler` :

```text
mainChain = [8, 9, 10, 12]
pending   = [3, 6,  2,  4, 1]
             b1 b2 b3 b4 b5
```

`b1 = 3` est placé directement au début de `sorted`, qui vaut alors
`[3, 8, 9, 10, 12]`.

Pour cinq éléments dans `pending`, l'ordre d'insertion vaut
`[2, 1, 4, 3]` en indices C++, soit `b3`, `b2`, `b5`, `b4`.

| Élément inséré | Borne exclue de la recherche | `sorted` après insertion |
|---|---|---|
| `b3 = 2` | `10` | `[2, 3, 8, 9, 10, 12]` |
| `b2 = 6` | `9` | `[2, 3, 6, 8, 9, 10, 12]` |
| `b5 = 1` (straggler) | `sorted.end()` : toute la chaîne | `[1, 2, 3, 6, 8, 9, 10, 12]` |
| `b4 = 4` | `12` | `[1, 2, 3, 4, 6, 8, 9, 10, 12]` |

## Chronométrage

`run()` mesure séparément, en microsecondes :

```text
assignation de l'entrée + tri du vector
assignation de l'entrée + tri du deque
```

Le parsing commun et l'affichage sont hors mesure.

Les résultats varient avec la machine, le cache, l'ordonnanceur et la taille de l'entrée. Il ne faut pas affirmer que l'un des deux conteneurs sera toujours plus rapide.

## Vérifications internes

Après les tris :

1. les tailles doivent être identiques ;
2. `std::equal()` vérifie que vector et deque ont le même contenu ;
3. une boucle vérifie que le vector est croissant.

Puisque le deque est identique au vector, la vérification de l'ordre du vector garantit aussi indirectement que le deque est trié.

## Complexité pratique

Ford-Johnson cherche avant tout à réduire les comparaisons.

Dans cette implémentation :

- les recherches bornées utilisent `O(log N)` comparaisons ;
- les insertions au milieu peuvent déplacer `O(N)` éléments ;
- la réassociation avec deux boucles peut coûter `O(N²)`.

Il faut distinguer l'optimisation théorique des comparaisons et le temps d'exécution réel de cette implémentation.

## Utilisation et tests

```bash
cd ex02
make
./PmergeMe 3 5 9 7 4
./PmergeMe 12 4 6 9 3 8 2 10 1
```

Test Linux avec 3 000 entiers distincts :

```bash
./PmergeMe $(shuf -i 1-100000 -n 3000)
```

La commande `shuf -i 1-1000 -n 3000` visible dans certaines versions de la grille ne peut fournir que 1 000 valeurs distinctes sans l'option `-r`.

---

# Questions courantes d'évaluation

## Pourquoi `map` dans l'ex00 ?

Parce qu'elle associe une date à un taux, conserve les dates triées et permet à `lower_bound()` de retrouver une date en `O(log N)`.

## Pourquoi `stack` dans l'ex01 ?

Parce que RPN consomme les deux résultats les plus récents selon le principe LIFO.

## Pourquoi `vector` et `deque` dans l'ex02 ?

Ils proposent tous deux l'accès aléatoire nécessaire, mais possèdent des organisations mémoire différentes permettant une comparaison de performances.

## Pourquoi former des paires ?

Une comparaison établit `b_i <= a_i`. Cette information permet ensuite de limiter la zone d'insertion de `b_i` à ce qui précède `a_i`.

## Pourquoi trier les `highs` récursivement ?

Ils constituent la base ordonnée de la chaîne principale. Le même problème, plus petit, est donc résolu par récursion.

## À quoi sert Jacobsthal ?

À choisir l'ordre des insertions afin de conserver des zones de recherche binaire proches de tailles avantageuses `2^k - 1`.

## Pourquoi deux `lower_bound()` dans PmergeMe ?

Le premier retrouve le ceiling `a_i` dans la chaîne actuelle. Le second cherche la position de `b_i` uniquement avant ce ceiling.

## Pourquoi deux fonctions de tri presque identiques ?

Le sujet conseille d'implémenter l'algorithme pour chaque conteneur et d'éviter une fonction générique. La duplication est donc volontaire.

## Pourquoi les temps diffèrent-ils ?

À cause de la disposition mémoire, des allocations, du cache et du coût des déplacements. Pour de petites entrées, le bruit de mesure peut dominer.

---

# Bilan

CPP09 met en pratique :

- le choix d'un conteneur adapté ;
- les maps ordonnées et `lower_bound()` ;
- les piles LIFO ;
- les itérateurs ;
- la recherche binaire ;
- la récursion ;
- Ford-Johnson et Jacobsthal ;
- la validation d'entrée ;
- la mesure de performances ;
- la forme canonique orthodoxe.

L'idée essentielle du module est que le choix d'un conteneur dépend avant tout des opérations dont l'algorithme a besoin.


# fonction sortVector(numbers):

[A] si container contient 0 ou 1 élément:
        retourner

[B] si la taille est impaire:
        retirer le dernier élément
        le conserver dans straggler

[C] former les paires:
        mettre les grands dans highs
        mettre les petits dans lows

[D] mainChain = copie de highs

[E] sortVector(mainChain)       ← appel récursif

    -----------------------------------------------
    La suite attend que l'appel récursif soit fini.
    -----------------------------------------------

[F] construire pending en réassociant chaque low à son high trié

[G] si la taille d'entrée était impaire:
        ajouter straggler à la fin de pending

[H] former sorted avec b1 suivi de mainChain

[I] construire l'ordre Jacobsthal à partir de pending.size()

[J] pour chaque index de cet ordre:
        value = pending[index]
        upBound = sorted.end()

        si ce n'est pas le straggler:
            partner = mainChain[index]
            upBound = lower_bound(sorted.begin(), sorted.end(), partner)

        position = lower_bound(sorted.begin(), upBound, value)
        insérer value à position

[K] échanger numbers et sorted
