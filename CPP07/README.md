---

# C++ - Module 07 : Templates

## Présentation
Le **Module 07** du cursus C++ de 42 est une introduction à la **programmation générique**. L'objectif est de comprendre et de mettre en œuvre les **Templates** (patrons de modèles), qui permettent d'écrire du code réutilisable quel que soit le type de données manipulé, tout en conservant une vérification stricte des types à la compilation.

---

## Concepts Clés

### 1. Qu'est-ce qu'un Template ?
Un template est un **moule** (ou un plan). Au lieu d'écrire plusieurs versions de la même fonction (une pour `int`, une pour `float`, etc.), on écrit une seule fois la logique. Le compilateur génère ensuite le code spécifique ("instanciation") lorsqu'il rencontre l'appel de la fonction avec un type donné.

### 2. Compilation et Fichiers `.hpp` / `.tpp`
Contrairement au code C++ classique, les templates ne peuvent pas être compilés séparément dans un fichier `.cpp`. 
- **Pourquoi ?** Parce que le compilateur a besoin de voir la définition complète du template au moment où il l'instancie dans le `main`.
- **Organisation :** On place généralement la déclaration dans le `.hpp` et l'implémentation soit directement dans le `.hpp`, soit dans un fichier `.tpp` inclus à la fin du header.

### 3. Programmation Générique vs STL
Bien que la **STL** (Standard Template Library) soit l'exemple le plus célèbre de templates (ex: `std::vector`), ce module interdit son usage (jusqu'au module 08). L'enjeu est ici de recréer nos propres outils génériques.

---

## Détail des Exercices

### Exercice 00 : Start with a few functions
Implémentation de trois fonctions de base utilisables avec n'importe quel type supportant les opérateurs de comparaison :
- `swap` : Échange les valeurs de deux arguments.
- `min` : Retourne la plus petite valeur (ou la deuxième en cas d'égalité).
- `max` : Retourne la plus grande valeur (ou la deuxième en cas d'égalité).

**Point technique :** Les types passés doivent obligatoirement surcharger les opérateurs `<`, `>` et `==` pour que le template fonctionne.

### Exercice 01 : Iter
Création d'une fonction `iter` capable de parcourir n'importe quel tableau et d'appliquer une fonction sur chaque élément.
- **Paramètres :** Adresse du tableau, taille (`size_t const`), et fonction à appliquer.
- **Const-Correctness :** La fonction a été conçue pour supporter aussi bien les tableaux de données modifiables que les tableaux constants (`const T*`), respectant ainsi l'encapsulation des données.

### Exercice 02 : Array (Classe Template)
Développement d'une classe `Array` qui simule un tableau dynamique générique.
- **Gestion de la mémoire :** Utilisation de `new[]` pour l'allocation et `delete[]` pour la libération systématique.
- **Forme Canonique d'Orthodoxe :** Implémentation stricte du constructeur par défaut, constructeur de recopie, opérateur d'affectation et destructeur.
- **Deep Copy (Copie profonde) :** La copie d'un `Array` crée une nouvelle zone mémoire indépendante. Modifier la copie n'affecte jamais l'original.
- **Sécurité et Exceptions :** Surcharge de l'opérateur `[]`. Si l'index est hors limites (négatif ou supérieur à la taille), une exception personnalisée `OutOfBoundsException` (dérivée de `std::exception`) est lancée.

---

## Contraintes de Réalisation

- **Standard :** C++98.
- **Interdictions :**
    - Mot-clé `friend` (pour forcer l'utilisation de l'interface publique).
    - `using namespace` (pour éviter la pollution de l'espace de nommage).
    - Fonctions `*printf`, `*alloc`, `free`.
    - Bibliothèques externes (Boost, etc.) et C++11/14/17/20.

---

## Tests et Validation
Le projet inclut des tests complets démontrant :
1. L'instanciation avec des types primitifs (`int`, `char`, `double`).
2. L'instanciation avec des objets complexes (`std::string`).
3. Le comportement des exceptions lors d'accès mémoire invalides.
4. La robustesse de la gestion mémoire (vérifiée avec **Valgrind**).

### Compilation
```bash
make          # Compile l'exercice
./ex0X        # Lance les tests
```

---

## Réflexion sur l'architecture (FAQ Défense)

**Pourquoi `operator<<` est-il hors de la classe ?**
Puisque le mot-clé `friend` est interdit, l'opérateur de flux doit être une fonction globale utilisant l'interface publique de la classe (`size()` et `operator[]`). Cela garantit une encapsulation parfaite.

**Pourquoi utiliser `new T[n]()` au lieu de `new T[n]` ?**
L'ajout des parenthèses `()` force l'initialisation par défaut des éléments. Pour des `int`, cela garantit que le tableau contient des `0` au lieu de valeurs aléatoires résiduelles en mémoire.

---

Pour réussir une évaluation à 42, il ne suffit pas que le code fonctionne, il faut montrer que tu maîtrises les **concepts** et que tu as compris les **contraintes spécifiques** du sujet.

Voici une structure "clé en main" pour expliquer chaque exercice à ton évaluateur :

---

### Introduction Générale (Le "Pitch" du module)
*"Ce module porte sur la **programmation générique** via les **Templates**. L'idée est d'écrire des structures et des fonctions dont la logique est indépendante du type de donnée traité. Le compilateur utilise mon code comme un **patron** (blueprint) pour générer le code réel au moment de l'instanciation. C'est pour cette raison que mes implémentations sont dans les headers (`.hpp`), car le compilateur doit avoir accès à la 'recette' complète pour chaque nouveau type rencontré."*

---

### Exercice 00 : Start with a few functions
**Le but :** Implémenter des fonctions templates de base (`swap`, `min`, `max`).

**Ce que tu expliques :**
1.  **Généricité :** *"Mes fonctions fonctionnent avec n'importe quel type `T`, à condition que ce type supporte les opérateurs de comparaison (`<`, `>`)."*
2.  **La règle d'égalité (Le piège du sujet) :** *"Le sujet demande de retourner le deuxième paramètre en cas d'égalité. Pour `min`, j'utilise `if (a < b) return a; return b;`. Si `a` et `b` sont égaux, la condition est fausse, et je retourne bien `b`, le deuxième."*
3.  **Passage par référence :** *"J'utilise des références constantes (`T const &`) pour éviter des copies inutiles d'objets lourds, tout en garantissant que la fonction ne modifiera pas les valeurs originales (sauf pour `swap`)."*

---

### Exercice 01 : Iter
**Le but :** Créer une fonction qui parcourt un tableau et applique une fonction sur chaque élément.

**Ce que tu expliques :**
1.  **Double Template :** *"J'utilise deux types templates : `T` pour les éléments du tableau et `F` pour la fonction. Utiliser un template pour la fonction rend `iter` plus flexible : elle accepte des pointeurs de fonction classiques, mais aussi des instances d'autres fonctions templates."*
2.  **Gestion du `const` (L'encadré jaune) :** *"Le sujet demandait de bien gérer les éléments constants. Si je passe un tableau de `const int`, mon template `T` devient `const int`. Mon code reste donc robuste et respecte la sécurité des données."*
3.  **Simplicité :** *"La fonction est simple : elle prend l'adresse, la taille, et boucle sur chaque index en appelant la fonction passée en paramètre."*

---

### Exercice 02 : Array
**Le but :** Créer une classe template qui se comporte comme un tableau dynamique sécurisé.

**Ce que tu expliques :**
1.  **Gestion Mémoire :** *"J'utilise `new T[size]()` pour l'allocation. Les parenthèses sont cruciales : elles forcent la 'value-initialization' (les `int` sont mis à 0 par défaut au lieu d'avoir des valeurs aléatoires)."*
2.  **Forme Canonique & Deep Copy :** *"C'est le point le plus important. Mon constructeur de recopie et mon opérateur d'affectation font une **copie profonde**. Je crée un nouveau tableau en mémoire et je copie chaque élément. Cela évite que deux objets pointent sur la même mémoire, ce qui causerait des crashs (double free) au moment du destructeur."*
3.  **Surcharge de l'opérateur `[]` :**
    *   **Sécurité :** *"Je vérifie l'index avant chaque accès. S'il est invalide, je lance une `std::exception` (via ma classe `OutOfBoundsException`)."*
    *   **Const-correctness :** *"J'ai surchargé `[]` en version normale ET en version `const`. Cela permet de lire les données même si l'objet `Array` est passé en tant que référence constante."*
4.  **Pas de `friend` :** *"Pour l'affichage (operator<<), je n'ai pas utilisé `friend`. Je passe par l'interface publique (`size()` et `operator[]`), ce qui respecte mieux l'encapsulation."*

---

### 3 Conseils pour "gagner" l'évaluation :

1.  **Anticipe Valgrind :** *"J'ai vérifié mon code avec Valgrind, notamment pour l'exercice 02. Même en cas de copie ou d'affectation de tableaux vides, il n'y a aucune fuite mémoire (memory leaks)."*
2.  **Montre tes tests :** Ne te contente pas du main du sujet. Montre ton main avec des `std::string` et des tableaux constants. *"Regarde, ici je prouve que modifier une copie n'altère pas l'original."*
3.  **Utilise le bon vocabulaire :**
    *   Ne dis pas "le type", dis **"le paramètre de type T"**.
    *   Ne dis pas "créer la fonction", dis **"instancier le template"**.
    *   Ne dis pas "copier le pointeur", dis **"shallow copy"** (mauvais) vs **"deep copy"** (bon).

Avec cette structure, tu montres que tu as une vision d'ensemble du module et que tu maîtrises chaque détail technique. Tu as d'autres questions sur un point précis ?