### 🟢 EXERCICE 00 : Les bases du Polymorphisme

**Le mot-clé à sortir :** "Liaison Dynamique" (Dynamic Binding).

*   **Le Destructeur Virtuel :** Montre tout de suite que ton destructeur dans `Animal` est `virtual`. Explique que sans cela, si on supprime un `Dog` via un pointeur `Animal*`, seul le destructeur de base est appelé (fuite de mémoire).
*   **Le Polymorphisme :** Montre que `Animal* j = new Dog(); j->makeSound();` appelle bien le cri du chien. Explique que grâce à `virtual`, le programme décide quelle fonction appeler au moment de l'**exécution** (runtime) et non de la compilation.
*   **La preuve par "WrongAnimal" :** Montre la classe `WrongAnimal`. Explique que comme `makeSound` n'y est **pas** virtuelle, le programme appelle la fonction du type du pointeur. C'est la preuve par l'absurde que `virtual` est indispensable.

---

### 🔵 EXERCICE 01 : Gestion mémoire & Deep Copy

**Le mot-clé à sortir :** "Copie Profonde" (Deep Copy).

*   **L'indépendance des objets :** C’est le point crucial. Explique que chaque `Dog`/`Cat` possède son propre `Brain` alloué dynamiquement.
*   **Démonstration de la Deep Copy :** Montre ton constructeur de recopie. Explique que tu ne copies pas juste l'adresse du pointeur (`this->_brain = other._brain` serait une erreur fatale), mais que tu crées un **nouveau** cerveau avec `new Brain(*other._brain)`.
*   **L'Opérateur d'affectation :** Montre que tu vérifies l'auto-affectation (`if (this != &other)`) et que tu `delete` l'ancien cerveau avant d'en créer un nouveau pour éviter les fuites.
*   **Valgrind :** Sois prêt à lancer `valgrind --leak-check=full ./ex01`. Montre qu'il y a 0 fuite. Explique que c'est grâce au destructeur virtuel d'Animal qui permet de remonter jusqu'au `delete _brain` du chien/chat.

---

### 🟡 EXERCICE 02 : Classes Abstraites

**Le mot-clé à sortir :** "Contrat d'Interface" ou "Sûreté de conception".

*   **La Fonction Virtuelle Pure :** Montre le `= 0` dans `Animal.hpp`. Explique que cela définit une "interface" : on dit que tout Animal *doit* faire un son, mais on ne peut pas définir ce son pour un animal générique.
*   **L'impossibilité d'instancier :** Montre à l'évaluateur que si tu essaies de faire `Animal test;` dans le `main`, le code **ne compile pas**. C'est le but recherché : empêcher de créer des objets "incomplets".
*   **Héritage obligatoire :** Explique que maintenant, `Dog` et `Cat` sont **obligés** d'implémenter `makeSound()`, sinon ils deviennent eux aussi abstraits et ne compileront pas.

---

### 🚩 Checklist générale (Ce qu'ils vont vérifier partout)

1.  **Forme Canonique d'Orthodox (OCF) :** Pour chaque classe, montre que tu as les 4 fonctions (Destructeur, Constructeur par défaut, de Recopie, et Opérateur d'affectation).
2.  **Standard C++98 :** Vérifie que tu n'as pas utilisé de `nullptr` (utilise `NULL`), de `auto`, ou de `override`. Ton Makefile doit avoir `-std=c++98`.
3.  **Messages de Debug :** Le sujet demande des messages spécifiques pour les constructeurs/destructeurs. Montre que l'ordre est logique :
    *   *Construction :* Parent ➔ Enfant ➔ Brain.
    *   *Destruction :* Brain ➔ Enfant ➔ Parent.
4.  **Pas de STL (pour l'instant) :** Tu ne dois pas avoir utilisé de `std::vector` ou `std::list`. Le cerveau doit utiliser un tableau classique `std::string ideas[100]`.

### La question "piège" classique :
**L'évaluateur :** *"Pourquoi est-ce que dans ton opérateur d'affectation de Dog, tu fais un `delete` avant le `new` ?"*
**Ta réponse :** *"Parce que l'objet existe déjà. Si je ne supprime pas son cerveau actuel avant d'allouer le nouveau pour la copie, l'ancienne adresse est perdue mais la mémoire reste occupée : c'est une fuite de mémoire."*

Tu es maintenant prêt pour l'évaluation ! Est-ce que tu te sens d'attaque pour le dernier morceau, l'**Exercice 03** ? (Il est un peu long car il y a beaucoup de classes, mais c'est le même principe).