C'est **LA** question classique de l'exercice 00. Elle montre que tu as l'œil, et c'est exactement ce qu'un évaluateur attend que tu expliques.

Voici pourquoi Valgrind affiche **0 leak** alors que le destructeur de `WrongCat` n'a **jamais été appelé** :

### 1. Valgrind compte les octets, pas les fonctions
Valgrind surveille le "tas" (la Heap). Quand tu fais `new WrongCat()`, le système alloue un bloc de mémoire (disons 32 octets). Le gestionnaire de mémoire (malloc/free) garde en mémoire que "l'adresse 0xABC fait 32 octets".

Quand tu fais `delete wrongCatPtr` :
*   **Côté C++ (Logique) :** Comme le destructeur n'est pas `virtual`, il ne regarde que le type du pointeur (`WrongAnimal*`). Il appelle donc uniquement `~WrongAnimal()`. **Le code à l'intérieur de `~WrongCat()` est sauté.**
*   **Côté Système (Mémoire) :** L'instruction `delete` dit au système : "Libère le bloc à l'adresse 0xABC". Le système libère les 32 octets.

**Bilan Valgrind :** 32 octets alloués, 32 octets libérés = **0 fuite.**

### 2. Pourquoi est-ce quand même un bug ?
Dans l'exercice 00, ta classe `WrongCat` est vide. Son destructeur ne fait rien d'autre qu'afficher un message. Le sauter ne "coûte" rien en mémoire.

**C'est là que l'exercice 01 intervient pour prouver le danger :**
Imagine que `WrongCat` possède un `Brain*` (comme dans l'ex01) :
1.  Le constructeur de `WrongCat` fait `_brain = new Brain()`.
2.  Le destructeur de `WrongCat` fait `delete _brain`.
3.  **Si le destructeur n'est pas virtuel :** tu fais `delete wrongCatPtr`, le destructeur de `WrongCat` est sauté, donc le `delete _brain` n'est **jamais exécuté**.
4.  Le bloc du chat est libéré, mais le bloc du cerveau reste bloqué en mémoire.
5.  **LÀ, Valgrind afficherait un "Memory Leak".**

### 3. Ce que tu dois dire à l'évaluateur (Le "Topo")

Si l'évaluateur te demande : *"Pourquoi Valgrind est au vert alors qu'on ne voit pas le message du destructeur du WrongCat ?"*

> **Ta réponse :**
> "C'est parce que Valgrind vérifie si la mémoire allouée a été libérée, mais il ne sait pas si la logique de destruction a été respectée.
>
> Ici, le `delete` a bien libéré le bloc mémoire de l'objet, donc il n'y a pas de fuite d'octets. Par contre, à cause du manque de `virtual`, le **comportement est incorrect** : la chaîne de destruction s'est arrêtée au parent.
>
> Dans l'Ex00 ce n'est pas grave pour la mémoire car l'enfant n'a pas de ressources propres. Mais dans l'Ex01, ce même bug empêcherait de supprimer le `Brain`, et Valgrind détecterait alors une fuite réelle."

### En résumé :
*   **Ex00 :** Prouve que le `virtual` est nécessaire pour la **logique** (appeler le bon destructeur et faire le bon son).
*   **Ex01 :** Prouve que le `virtual` est nécessaire pour la **sécurité mémoire** (libérer les attributs complexes comme `Brain`).

**Note :** L'absence de destructeur virtuel sur une classe destinée à l'héritage est techniquement un "Comportement Indéfini" (Undefined Behavior) en C++, même si dans la pratique, les compilateurs se contentent souvent de libérer le bloc mémoire sans appeler les destructeurs enfants.