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
