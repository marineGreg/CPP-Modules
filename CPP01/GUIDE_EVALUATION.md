# Guide d'Évaluation - CPP Module 01

## 📋 Vue d'ensemble du module

**Thème principal** : Allocation mémoire, pointeurs vers membres, références et switch statements

**Concepts clés** :
- Allocation dynamique (`new` / `delete`)
- Références vs Pointeurs
- Pointeurs vers membres de classe
- Gestion mémoire (stack vs heap)
- Switch statements avec fall-through

---

## 🎯 Exercise 00: BraiiiiiiinnnzzzZ

### 📖 Explication du programme

Programme qui démontre la différence entre :
- **Allocation sur la stack** : `Zombie zombie("Stack Zombie");`
- **Allocation sur le heap** : `Zombie* zombie = new Zombie("Heap Zombie");`

**Fonctions importantes** :
- `newZombie(std::string name)` : Crée un zombie sur le heap avec `new` (doit être `delete` plus tard)
- `randomChump(std::string name)` : Crée un zombie sur la stack (détruit automatiquement)

### 🔑 Points clés à comprendre

1. **Stack vs Heap** :
   - Stack : allocation automatique, destruction automatique en fin de scope
   - Heap : allocation manuelle avec `new`, destruction manuelle avec `delete`

2. **Quand utiliser quoi ?**
   - Stack : objets temporaires, durée de vie limitée au scope
   - Heap : objets persistants, durée de vie contrôlée manuellement

3. **Destructeur** :
   - Appelé automatiquement pour les objets stack
   - Doit être appelé explicitement avec `delete` pour les objets heap

### 🧪 Tests à démontrer

```bash
./zombie
```

**Ce que tu dois montrer** :
1. Création d'un zombie sur le heap qui persiste après la fonction
2. Création d'un zombie sur la stack qui meurt à la fin de la fonction
3. Les messages du destructeur qui montrent quand chaque zombie est détruit

**Ordre attendu** :
```
Zombie Heap créé
Zombie Stack créé
Zombie Stack annonce
Zombie Stack destructeur (fin de fonction randomChump)
Zombie Heap annonce
Zombie Heap destructeur (après delete explicite)
```

### ⚠️ Erreurs courantes

1. **Memory leak** : Oublier de `delete` le zombie créé avec `new`
2. **Double delete** : Appeler `delete` sur un objet stack
3. **Dangling pointer** : Retourner un pointeur vers un objet stack

### 💡 Conseils de présentation

- Explique pourquoi `newZombie` retourne un **pointeur** (objet sur le heap)
- Explique pourquoi `randomChump` ne retourne rien (objet temporaire)
- Montre que tu comprends la différence entre `Zombie z;` et `Zombie* z = new Zombie();`

---

## 🎯 Exercise 01: Moar brainz!

### 📖 Explication du programme

Crée une **horde de zombies** : allocation dynamique d'un **tableau d'objets**.

**Fonction clé** :
```cpp
Zombie* zombieHorde(int N, std::string name);
```

Cette fonction :
1. Alloue un tableau de N zombies avec `new Zombie[N]`
2. Initialise chaque zombie avec le même nom
3. Retourne un pointeur vers le premier zombie

### 🔑 Points clés à comprendre

1. **Allocation de tableau** :
   - `new Type[N]` : alloue N objets contigus en mémoire
   - `delete[] ptr` : libère TOUT le tableau (pas juste le premier élément)

2. **Constructeur par défaut obligatoire** :
   - `new Zombie[N]` appelle le constructeur par défaut pour chaque zombie
   - On doit ensuite initialiser manuellement avec `setName()` ou équivalent

3. **Différence `delete` vs `delete[]`** :
   - `delete` : pour un seul objet (`new Type`)
   - `delete[]` : pour un tableau (`new Type[]`)

### 🧪 Tests à démontrer

```bash
./zombie_horde
```

**Ce que tu dois montrer** :
1. Création d'une horde de N zombies (ex: 5)
2. Chaque zombie annonce correctement
3. Tous les zombies sont détruits avec un seul `delete[]`

**Sortie attendue** :
```
Zombie1 created
Zombie2 created
...
ZombieN created
Zombie1: BraiiiiiiinnnzzzZ...
Zombie2: BraiiiiiiinnnzzzZ...
...
Zombie1 destroyed
Zombie2 destroyed
```

### ⚠️ Erreurs courantes

1. **Utiliser `delete` au lieu de `delete[]`** → Undefined Behavior (seul le 1er destructeur est appelé)
2. **Oublier `delete[]`** → Memory leak
3. **Ne pas avoir de constructeur par défaut** → Erreur de compilation

### 💡 Conseils de présentation

- Explique pourquoi on ne peut pas utiliser directement le constructeur paramétré dans `new Zombie[N]`
- Montre que tu comprends la différence entre `new` et `new[]`
- Discute des alternatives modernes (`std::vector`, `std::array`)

---

## 🎯 Exercise 02: HI THIS IS BRAIN

### 📖 Explication du programme

Programme simple qui démontre la différence entre **pointeurs** et **références**.

**Code clé** :
```cpp
std::string str = "HI THIS IS BRAIN";
std::string* stringPTR = &str;
std::string& stringREF = str;
```

### 🔑 Points clés à comprendre

1. **Référence** :
   - Alias d'une variable existante
   - **Doit être initialisée** à la déclaration
   - **Ne peut pas être réassignée** (toujours alias de la même variable)
   - Syntaxe : `Type& ref = variable;`

2. **Pointeur** :
   - Variable qui contient une **adresse mémoire**
   - Peut être **NULL/nullptr**
   - Peut être **réassigné** vers une autre adresse
   - Syntaxe : `Type* ptr = &variable;`

3. **Comparaison** :
   | Aspect | Pointeur | Référence |
   |--------|----------|-----------|
   | Peut être NULL | ✅ Oui | ❌ Non |
   | Peut être réassigné | ✅ Oui | ❌ Non |
   | Déréférencement | `*ptr` | Automatique |
   | Adresse | `&ptr` (adresse du pointeur) | `&ref` (adresse de l'original) |

### 🧪 Tests à démontrer

```bash
./brain
```

**Ce que tu dois montrer** :
1. L'adresse de la string originale
2. L'adresse stockée dans le pointeur (doit être identique)
3. L'adresse de la référence (doit être identique)
4. La valeur via le pointeur (`*stringPTR`)
5. La valeur via la référence (`stringREF`)

**Sortie attendue** :
```
Memory address of str: 0x...
Memory address in stringPTR: 0x...  (même adresse)
Memory address of stringREF: 0x...  (même adresse)
Value via stringPTR: HI THIS IS BRAIN
Value via stringREF: HI THIS IS BRAIN
```

### ⚠️ Erreurs courantes

1. **Confondre `&` (adresse-of) et `&` (type référence)**
2. **Oublier de déréférencer le pointeur** : `cout << stringPTR` affiche l'adresse, pas la valeur
3. **Penser qu'une référence crée une copie** (c'est juste un alias)

### 💡 Conseils de présentation

- Explique quand utiliser une référence vs un pointeur
- Donne des exemples : passage par référence dans les fonctions pour éviter les copies
- Mentionne les références `const` pour protéger les données

---

## 🎯 Exercise 03: Unnecessary violence

### 📖 Explication du programme

Implémente deux classes : `Weapon` et `HumanA` / `HumanB`.

**Différence clé** :
- `HumanA` : **référence** vers Weapon (arme obligatoire à la construction)
- `HumanB` : **pointeur** vers Weapon (arme optionnelle, peut être NULL)

### 🔑 Points clés à comprendre

1. **HumanA utilise une référence** :
   ```cpp
   class HumanA {
       Weapon& _weapon;  // Référence
   public:
       HumanA(std::string name, Weapon& weapon);  // Doit fournir l'arme
   };
   ```
   - L'arme DOIT exister à la construction
   - Ne peut jamais être NULL
   - Ne peut jamais changer d'arme

2. **HumanB utilise un pointeur** :
   ```cpp
   class HumanB {
       Weapon* _weapon;  // Pointeur
   public:
       HumanB(std::string name);  // Peut être sans arme
       void setWeapon(Weapon& weapon);  // Peut recevoir une arme plus tard
   };
   ```
   - Peut commencer sans arme (NULL)
   - Peut changer d'arme avec `setWeapon()`

3. **Weapon avec référence** :
   - `getType()` retourne `const std::string&` pour éviter une copie inutile
   - `setType()` prend `const std::string&` pour la même raison

### 🧪 Tests à démontrer

```bash
./violence
```

**Ce que tu dois montrer** :
1. HumanA attaque avec son arme initiale
2. Changement du type d'arme → HumanA attaque avec la nouvelle arme
3. HumanB commence (potentiellement) sans arme
4. HumanB reçoit une arme avec `setWeapon()`
5. HumanB attaque avec son arme

**Sortie attendue** (selon le sujet) :
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

### ⚠️ Erreurs courantes

1. **Ne pas initialiser la référence dans la liste d'initialisation** de HumanA
2. **Ne pas vérifier si le pointeur est NULL** avant d'appeler `attack()` dans HumanB
3. **Retourner `std::string` au lieu de `const std::string&`** dans `getType()`

### 💡 Conseils de présentation

- Explique POURQUOI HumanA utilise une référence et HumanB un pointeur
- Montre que tu comprends le principe : référence = obligatoire, pointeur = optionnel
- Discute des avantages de retourner une référence const vs une copie

---

## 🎯 Exercise 04: Sed is for losers

### 📖 Explication du programme

Programme qui remplace toutes les occurrences d'une chaîne dans un fichier.

**Signature** :
```bash
./replace <filename> <s1> <s2>
```

**Comportement** :
1. Ouvre `<filename>`
2. Crée `<filename>.replace`
3. Remplace toutes les occurrences de `s1` par `s2`
4. Écrit le résultat dans le nouveau fichier

### 🔑 Points clés à comprendre

1. **Gestion des fichiers en C++** :
   ```cpp
   std::ifstream infile("input.txt");   // Lecture
   std::ofstream outfile("output.txt"); // Écriture
   ```

2. **Lecture ligne par ligne** :
   ```cpp
   std::string line;
   while (std::getline(infile, line)) {
       // Traiter la ligne
   }
   ```

3. **Algorithme de remplacement** :
   ```cpp
   size_t pos = 0;
   while ((pos = str.find(s1, pos)) != std::string::npos) {
       str.erase(pos, s1.length());
       str.insert(pos, s2);
       pos += s2.length();  // Important pour éviter boucle infinie
   }
   ```

4. **Gestion d'erreurs** :
   - Vérifier le nombre d'arguments
   - Vérifier si le fichier s'ouvre correctement
   - Vérifier si `s1` est vide

### 🧪 Tests à démontrer

**Test 1 : Remplacement basique**
```bash
echo "Hello world, Hello universe" > test.txt
./replace test.txt "Hello" "Bonjour"
cat test.txt.replace
# Attendu: Bonjour world, Bonjour universe
```

**Test 2 : s1 non trouvé**
```bash
echo "Nothing to replace" > test2.txt
./replace test2.txt "XXX" "YYY"
cat test2.txt.replace
# Attendu: Nothing to replace (inchangé)
```

**Test 3 : Cas limite - s1 vide**
```bash
./replace test.txt "" "something"
# Attendu: Message d'erreur
```

**Test 4 : Fichier inexistant**
```bash
./replace nonexistent.txt "a" "b"
# Attendu: Message d'erreur
```

**Test 5 : Remplacement chevauchant**
```bash
echo "aaa" > test3.txt
./replace test3.txt "aa" "b"
cat test3.txt.replace
# Attendu: ba (pas bbb, seulement la première occurrence trouvée)
```

### ⚠️ Erreurs courantes

1. **Boucle infinie** : Si on ne décale pas `pos` après le remplacement et que `s2` contient `s1`
2. **Ne pas vérifier si `s1` est vide** → Boucle infinie
3. **Utiliser des fonctions C** (`fopen`, `fprintf`) au lieu de C++ streams
4. **Ne pas fermer les fichiers** (généralement géré automatiquement par les destructeurs)
5. **Mauvaise gestion des permissions** du fichier

### 💡 Conseils de présentation

- Explique pourquoi on utilise `std::string::npos` (valeur spéciale pour "non trouvé")
- Discute de la complexité temporelle de ton algorithme
- Mentionne les alternatives : `std::regex_replace`, mais c'est interdit dans le sujet
- Montre que tu gères les cas limites (fichier vide, s1 vide, s1 non trouvé)

---

## 🎯 Exercise 05: Harl 2.0

### 📖 Explication du programme

Classe `Harl` qui peut se plaindre à différents niveaux : DEBUG, INFO, WARNING, ERROR.

**Concept clé** : Utiliser des **pointeurs vers fonctions membres** au lieu d'une cascade de `if/else`.

### 🔑 Points clés à comprendre

1. **Syntaxe des pointeurs vers fonctions membres** :
   ```cpp
   void (Harl::*ptr)(void) = &Harl::debug;
   ```
   - `void (Harl::*ptr)(void)` : déclaration du type
   - `&Harl::debug` : adresse de la fonction membre

2. **Appel via un pointeur vers fonction membre** :
   ```cpp
   (this->*ptr)();  // Appelle la fonction pointée
   ```

3. **Tableau de pointeurs vers fonctions membres** :
   ```cpp
   void (Harl::*complains[])(void) = {
       &Harl::debug,
       &Harl::info,
       &Harl::warning,
       &Harl::error
   };
   ```

4. **Implémentation de `complain()`** :
   ```cpp
   void Harl::complain(std::string level) {
       std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
       void (Harl::*ptr[])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
       
       for (int i = 0; i < 4; i++) {
           if (levels[i] == level) {
               (this->*ptr[i])();
               return;
           }
       }
       // Niveau inconnu
   }
   ```

### 🧪 Tests à démontrer

```bash
./harl
```

**Ce que tu dois montrer** :
1. Appel avec différents niveaux : DEBUG, INFO, WARNING, ERROR
2. Appel avec un niveau invalide
3. Harl "complain a lot" (beaucoup d'appels pour montrer que ça fonctionne)

**Sortie attendue** :
```
Harl: complain("DEBUG")
[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!

Harl: complain("WARNING")
[ WARNING ]
I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.

Harl: complain("INVALID")
[ Probably complaining about insignificant problems ]
```

### ⚠️ Erreurs courantes

1. **Utiliser une cascade de if/else** → Ne respecte pas le sujet qui demande explicitement des pointeurs
2. **Mauvaise syntaxe** pour déclarer/appeler le pointeur vers fonction membre
3. **Oublier `this->` dans l'appel** : `(this->*ptr)()` est obligatoire
4. **Confondre avec les pointeurs de fonctions normaux** (qui n'ont pas besoin de `this`)

### 💡 Conseils de présentation

- Explique POURQUOI on utilise des pointeurs vers fonctions membres ici
- Montre que tu comprends la syntaxe (demande courante en évaluation)
- Compare avec une version `if/else` pour montrer la différence
- Mentionne les avantages : extensibilité, élégance, pas de duplication

---

## 🎯 Exercise 06: Harl filter

### 📖 Explication du programme

Version améliorée de Harl avec un **filtre** : affiche seulement les messages d'un certain niveau et au-dessus.

**Utilisation** :
```bash
./harlFilter <level>
```

**Concept clé** : Utiliser un **switch avec fall-through** (sans `break`) pour afficher tous les niveaux à partir d'un certain seuil.

### 🔑 Points clés à comprendre

1. **Fall-through dans un switch** :
   ```cpp
   switch (level) {
       case 0:  // DEBUG
           harl.complain("DEBUG");
       case 1:  // INFO
           harl.complain("INFO");
       case 2:  // WARNING
           harl.complain("WARNING");
       case 3:  // ERROR
           harl.complain("ERROR");
           break;
       default:
           std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
   }
   ```
   - **Pas de `break`** entre les cases 0, 1, 2, 3
   - Si on entre au case 1, on exécute aussi 2 et 3
   - C'est le comportement voulu ici !

2. **Arguments en ligne de commande** :
   ```cpp
   int main(int argc, char **argv) {
       if (argc != 2) {
           // Erreur
       }
       std::string level = argv[1];
   }
   ```

3. **Conversion string → int pour le switch** :
   ```cpp
   int getLevelIndex(std::string level) {
       std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
       for (int i = 0; i < 4; i++) {
           if (levels[i] == level)
               return i;
       }
       return -1;  // Niveau invalide
   }
   ```

### 🧪 Tests à démontrer

**Test 1 : Niveau DEBUG (affiche tout)**
```bash
./harlFilter DEBUG
# Attendu: DEBUG + INFO + WARNING + ERROR
```

**Test 2 : Niveau WARNING**
```bash
./harlFilter WARNING
# Attendu: WARNING + ERROR seulement
```

**Test 3 : Niveau ERROR**
```bash
./harlFilter ERROR
# Attendu: ERROR seulement
```

**Test 4 : Niveau invalide**
```bash
./harlFilter INVALID
# Attendu: [ Probably complaining about insignificant problems ]
```

**Test 5 : Pas d'arguments**
```bash
./harlFilter
# Attendu: Message d'erreur d'usage
```

### ⚠️ Erreurs courantes

1. **Mettre des `break` partout** → Ne respecte pas le comportement de filtre
2. **Ne pas gérer le cas "pas d'arguments"**
3. **Ne pas gérer le cas "niveau invalide"**
4. **Dupliquer le code de Harl** au lieu de réutiliser l'exercice 05

### 💡 Conseils de présentation

- Explique le concept de **fall-through** et pourquoi c'est pertinent ici
- Compare avec une version sans switch (ex: plusieurs `if` séparés)
- Montre que tu comprends `argc` et `argv`
- Discute des cas où fall-through est dangereux vs utile

---

## 🎁 Bonus : Questions anticipées

### Q1 : "Quelle est la différence entre `new` et `malloc` ?"

**Réponse** :
- `malloc` : allocation brute de mémoire (C)
  - Ne **pas** appeler les constructeurs
  - Retourne `void*` (nécessite cast)
  - Nécessite `free()`

- `new` : allocation + construction (C++)
  - **Appelle** le constructeur
  - Retourne un pointeur typé
  - Nécessite `delete`

**Ne JAMAIS mélanger** `new`/`free` ou `malloc`/`delete` !

### Q2 : "Pourquoi utiliser des références au lieu de pointeurs ?"

**Réponse** :
1. **Sécurité** : Une référence ne peut pas être NULL
2. **Simplicité** : Pas besoin de déréférencement (`*ptr`)
3. **Intention** : Une référence indique que la variable DOIT exister
4. **Performance** : Évite les copies inutiles (passage par référence)

**Cas d'usage** :
- Références : Paramètres de fonctions, opérateurs
- Pointeurs : Structures de données dynamiques, optionalité

### Q3 : "Qu'est-ce qu'une memory leak et comment l'éviter ?"

**Réponse** :
- **Memory leak** : Mémoire allouée avec `new` mais jamais libérée avec `delete`
- **Conséquences** : Le programme consomme de plus en plus de mémoire

**Comment l'éviter** :
1. Pour chaque `new`, un `delete` correspondant
2. Pour chaque `new[]`, un `delete[]` correspondant
3. Utiliser des destructeurs pour nettoyer automatiquement
4. **Mieux** : Utiliser des smart pointers (C++11+) → `std::unique_ptr`, `std::shared_ptr`

**Outils de détection** :
- `valgrind --leak-check=full ./program`

### Q4 : "Pourquoi éviter les fonctions C (printf, fopen, etc.) ?"

**Réponse** :
1. **Pas de type safety** : `printf` ne vérifie pas les types
2. **Pas d'overloading** : `cout` marche avec tous les types
3. **Pas de RAII** : `fopen` nécessite un `fclose` manuel
4. **Exceptions** : Les streams C++ peuvent lancer des exceptions

**Le module demande explicitement du C++** : utilise `std::cout`, `std::ifstream`, etc.

### Q5 : "C'est quoi RAII ?"

**Réponse** :
- **R**esource **A**cquisition **I**s **I**nitialization
- Principe : Lier la durée de vie d'une ressource à la durée de vie d'un objet

**Exemple** :
```cpp
{
    std::ifstream file("test.txt");  // Ouverture dans le constructeur
    // Utilisation du fichier
}  // Fermeture automatique dans le destructeur
```

**Avantages** :
- Pas d'oubli de libération
- Exception-safe
- Code plus propre

---

## 📝 Checklist finale

Avant l'évaluation, assure-toi de pouvoir :

### Compétences techniques
- [ ] Expliquer la différence entre stack et heap
- [ ] Expliquer la différence entre référence et pointeur
- [ ] Déclarer et utiliser un pointeur vers fonction membre
- [ ] Utiliser un switch avec fall-through intentionnel
- [ ] Gérer les fichiers avec `ifstream`/`ofstream`
- [ ] Expliquer `new`/`delete` et `new[]`/`delete[]`

### Concepts théoriques
- [ ] Expliquer RAII
- [ ] Expliquer les memory leaks
- [ ] Expliquer quand utiliser une référence vs un pointeur
- [ ] Expliquer l'intérêt des pointeurs vers fonctions membres

### Tests pratiques
- [ ] Compiler tous les exercices sans warnings
- [ ] Démontrer chaque exercice avec des tests variés
- [ ] Vérifier avec `valgrind` qu'il n'y a pas de leaks

### Makefile
- [ ] `make` compile tout
- [ ] `make clean` supprime les `.o`
- [ ] `make fclean` supprime les `.o` et l'exécutable
- [ ] `make re` fait un clean + recompile
- [ ] Flags : `-Wall -Wextra -Werror -std=c++98`

---

## 🚀 Conseils généraux de présentation

1. **Sois précis** : Utilise le vocabulaire correct (référence, pointeur, déréférencement, etc.)
2. **Montre que tu comprends** : Ne récite pas, explique avec tes mots
3. **Teste en live** : Compile et exécute devant l'évaluateur
4. **Anticipe les questions** : Prépare des réponses sur les concepts clés
5. **Reste humble** : Si tu ne sais pas, dis-le franchement et propose de chercher ensemble

Bonne chance ! 🍀
