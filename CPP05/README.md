*This project has been created as part of the 42 curriculum by mgregoir*

# C++ - Module 05 : Repetition and Exceptions

## Présentation
Ce module marque une transition majeure dans l'apprentissage du C++. L'objectif est d'abandonner la gestion d'erreurs "à la C" (codes de retour `-1` ou pointeurs `NULL`) pour adopter le mécanisme robuste des **Exceptions**. Il introduit également les notions de **Classes Abstraites** et de **Design Patterns** (Factory).

---

## Concepts Clés

### 1. Le mécanisme Try / Throw / Catch
C'est le cœur du module.
- **Throw** : On "lance" un objet (souvent une classe d'exception) quand une erreur survient.
- **Try** : On entoure le code "à risque" d'un bloc `try`.
- **Catch** : On "attrape" l'objet lancé pour gérer l'erreur sans faire crasher le programme.

### 2. La hiérarchie `std::exception`
Toutes nos exceptions personnalisées héritent de `public std::exception`.
- **`what()`** : C'est une méthode virtuelle de la classe de base qu'on surcharge pour retourner un message d'erreur explicite.
- **`throw()`** : Présent à la fin de la signature de `what()`, il garantit que cette fonction ne lancera elle-même aucune exception (spécification C++98).

---

## Détail des Exercices

### Exercice 00 : Mommy, when I grow up, I want to be a bureaucrat!
**Objectif :** Créer une classe de base et gérer ses limites de création.
- **Logique des Grades** : 1 est le plus haut, 150 est le plus bas.
- **Validation** : Toute tentative de créer ou de modifier un grade hors de ces limites doit lancer une exception.
- **Surcharge `<<`** : Permet d'afficher l'état de l'objet simplement.

### Exercice 01 : Form up, maggots!
**Objectif :** Faire interagir deux classes via les exceptions.
- **Interaction** : Le Bureaucrate essaie de signer, le Formulaire vérifie si le grade est suffisant.
- **Constantes** : Le nom et les grades requis d'un formulaire sont `const`. On utilise obligatoirement la **liste d'initialisation** dans le constructeur.
- **Exceptions** : Si le grade est trop bas, `beSigned()` lance une exception que `signForm()` doit attraper pour afficher un message d'erreur poli au lieu de crasher.

### Exercice 02 : No, you need form 28B, not 28C...
**Objectif :** Abstraction et Polymorphisme.
- **`AForm` (Classe Abstraite)** : On ne peut pas créer un "Formulaire" de base. La méthode `execute()` est **virtuelle pure** (`= 0`).
- **Destructeur Virtuel** : Crucial ! Sans `virtual ~AForm()`, supprimer une classe fille via un pointeur `AForm*` causerait des fuites de mémoire.
- **Les 3 spécialisations** :
    1. `Shrubbery` : Manipulation de fichiers (`std::ofstream`) et ASCII Art.
    2. `Robotomy` : Utilisation de l'aléatoire (`rand()`, `srand()`).
    3. `Presidential` : Simple affichage.
- **Vérification centralisée** : La méthode `checkExec` dans la classe mère évite de dupliquer la vérification "est-ce signé + grade suffisant" dans chaque enfant.

### Exercice 03 : At least this beats coffee-making
**Objectif :** Éviter les structures de contrôle lourdes (`if/else`).
- **L'Interne** : Il fabrique les formulaires.
- **Tableau de pointeurs sur fonctions membres** : C'est la solution élégante. On lie une chaîne de caractères (le nom du formulaire) à une fonction qui le crée.
- **Gestion Mémoire** : L'interne fait un `new`. La responsabilité du `delete` est transférée à celui qui reçoit le pointeur (le `main`).

---

## 💡 Notes Techniques Importantes

### Aléatoire (Robotomy)
- **`rand() % 2`** : Donne 0 ou 1 (50% de chance).
- **`srand(time(NULL))`** : Doit être appelé **une seule fois au début du `main`**. Il initialise la "graine" (seed) de l'aléatoire sur le temps actuel pour que les résultats changent à chaque lancement.

### Backslash dans les strings (Shrubbery)
- En C++, le caractère `\` est un caractère d'échappement. Pour afficher un seul `\` dans un fichier ASCII, il faut écrire `\\` dans ton code source.

### Inclusions Circulaires
- Si `Bureaucrat` a besoin de `AForm` et inversement, on utilise une **Forward Declaration** (`class AForm;`) dans le `.hpp` et on place le `#include` uniquement dans le `.cpp`.

---

##  Questions fréquentes en Soutenance

1. **Pourquoi hériter de `std::exception` ?**
   *Réponse* : Pour pouvoir attraper toutes nos exceptions personnalisées via un seul `catch (std::exception &e)`. C'est le principe de l'interopérabilité.

2. **Pourquoi le destructeur de `AForm` doit être virtuel ?**
   *Réponse* : Pour s'assurer que lorsqu'on détruit un objet via un pointeur sur sa classe de base, le destructeur de la classe dérivée (l'enfant) soit bien appelé, évitant ainsi les fuites de mémoire.

3. **Quelle est la différence entre une classe Abstraite et une Interface ?**
   *Réponse* : En C++, une classe est abstraite dès qu'elle possède au moins une méthode virtuelle pure. Une interface est une classe qui **ne possède que** des méthodes virtuelles pures et aucun attribut. `AForm` est une classe abstraite (car elle a des attributs).

4. **Pourquoi l'Interne retourne-t-il un pointeur ?**
   *Réponse* : Parce qu'on ne peut pas retourner une classe abstraite par valeur, et le polymorphisme ne fonctionne qu'avec des pointeurs ou des références.
