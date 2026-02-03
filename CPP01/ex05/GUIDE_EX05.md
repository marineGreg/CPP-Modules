# Guide CPP01 - Exercice 05 : Harl 2.0

## 📋 Objectif de l'exercice

Créer une classe `Harl` qui simule un client difficile se plaignant dans un restaurant. L'exercice vise à vous faire découvrir et utiliser les **pointeurs vers des fonctions membres** en C++, une technique avancée pour éviter de longues séries de conditions.

---

## 🎯 Concepts clés

### 1. Les pointeurs vers fonctions membres

En C++, on peut stocker l'adresse d'une fonction membre d'une classe dans un pointeur. Cela permet d'appeler différentes méthodes de manière dynamique.

**Syntaxe générale :**
```cpp
type_retour (NomClasse::*nom_pointeur)(parametres) = &NomClasse::fonction;
```

**Exemple concret :**
```cpp
void (Harl::*ptr)(void) = &Harl::debug;
```

### 2. Tableaux de pointeurs vers fonctions membres

On peut créer un tableau de pointeurs pour stocker plusieurs fonctions membres :

```cpp
void (Harl::*ptr_complain[])(void) = { 
    &Harl::debug, 
    &Harl::info, 
    &Harl::warning, 
    &Harl::error 
};
```

### 3. Appel d'une fonction via un pointeur membre

Pour appeler une fonction membre via un pointeur, on utilise la syntaxe :

```cpp
(objet.*pointeur)();           // Pour un objet
(pointeur_objet->*pointeur)(); // Pour un pointeur d'objet
```

Dans notre cas avec `this` :
```cpp
(this->*ptr_complain[i])();
```

---

## 🏗️ Structure du projet

```
ex05/
├── Harl.hpp       // Déclaration de la classe
├── Harl.cpp       // Implémentation
├── main.cpp       // Programme de test
└── Makefile       // Compilation
```

---

## 📝 Implémentation détaillée

### Harl.hpp

```cpp
class Harl {
    private:
        void debug(void);      // Niveau DEBUG
        void info(void);       // Niveau INFO
        void warning(void);    // Niveau WARNING
        void error(void);      // Niveau ERROR

    public:
        Harl();
        ~Harl();
        void complain(std::string level);  // Méthode publique
};
```

**Points importants :**
- Les 4 méthodes de plainte sont **privées** (seul Harl peut les appeler)
- La méthode `complain()` est **publique** et prend le niveau en paramètre
- Pas d'attributs nécessaires pour cette classe

### Harl.cpp - La méthode complain()

```cpp
void Harl::complain(std::string level) {
    // 1. Tableau de pointeurs vers fonctions membres
    void (Harl::*ptr_complain[])(void) = { 
        &Harl::debug, 
        &Harl::info, 
        &Harl::warning, 
        &Harl::error 
    };

    // 2. Tableau des niveaux correspondants
    std::string levels[] = { 
        "DEBUG", 
        "INFO", 
        "WARNING", 
        "ERROR" 
    };

    // 3. Recherche et appel de la bonne fonction
    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            (this->*ptr_complain[i])();  // Appel via pointeur
            return;
        }
    }
    
    // 4. Si aucun niveau ne correspond
    std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
}
```

**Explication ligne par ligne :**

1. **Ligne 3-8** : On crée un tableau de 4 pointeurs vers les méthodes membres
   - `void (Harl::*ptr_complain[])(void)` : tableau de pointeurs de fonctions
   - Chaque élément pointe vers une méthode de Harl

2. **Ligne 11-16** : Tableau de strings correspondant aux niveaux
   - L'index du niveau correspond à l'index du pointeur de fonction

3. **Ligne 19-24** : Boucle de recherche
   - On compare le niveau demandé avec chaque string
   - Si trouvé, on appelle la fonction via `(this->*ptr_complain[i])()`
   - `this->*ptr_complain[i]` : déréférence le pointeur membre
   - Les parenthèses `()` appellent la fonction

4. **Ligne 27** : Message par défaut si le niveau est invalide

---

## 🔍 Pourquoi utiliser des pointeurs vers fonctions ?

### ❌ Sans pointeurs (approche naïve)

```cpp
void Harl::complain(std::string level) {
    if (level == "DEBUG")
        debug();
    else if (level == "INFO")
        info();
    else if (level == "WARNING")
        warning();
    else if (level == "ERROR")
        error();
    else
        std::cout << "Invalid level" << std::endl;
}
```

**Problèmes :**
- Code répétitif et verbeux
- Difficile à maintenir si on ajoute des niveaux
- Nombreuses comparaisons de strings

### ✅ Avec pointeurs vers fonctions

```cpp
void Harl::complain(std::string level) {
    void (Harl::*ptr_complain[])(void) = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
    std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };

    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            (this->*ptr_complain[i])();
            return;
        }
    }
}
```

**Avantages :**
- Code plus élégant et maintenable
- Facile d'ajouter de nouveaux niveaux
- Démontre la maîtrise des concepts avancés C++

---

## 🧪 Tests et utilisation

### main.cpp - Version complète

⚠️ **IMPORTANT** : Le sujet demande de créer des tests qui montrent que **"Harl complains a lot"** (Harl se plaint beaucoup). Un main avec seulement 5 appels n'est pas suffisant !

```cpp
int main()
{
    Harl harl;

    std::cout << "=== Test 1: Tous les niveaux ===" << std::endl;
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");

    std::cout << "\n=== Test 2: Harl se plaint beaucoup de DEBUG ===" << std::endl;
    for (int i = 0; i < 3; i++)
        harl.complain("DEBUG");

    std::cout << "\n=== Test 3: Harl est vraiment énervé (ERROR) ===" << std::endl;
    for (int i = 0; i < 5; i++)
        harl.complain("ERROR");

    std::cout << "\n=== Test 4: Mélange de plaintes ===" << std::endl;
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("DEBUG");
    harl.complain("ERROR");
    harl.complain("INFO");
    harl.complain("WARNING");

    std::cout << "\n=== Test 5: Niveau invalide ===" << std::endl;
    harl.complain("UNKNOWN");
    harl.complain("CRITICAL");
    harl.complain("");

    std::cout << "\n=== Test 6: Harl ne s'arrête jamais de se plaindre ===" << std::endl;
    std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    for (int i = 0; i < 10; i++)
        harl.complain(levels[i % 4]);

    return (0);
}
```

**Pourquoi ce main est meilleur ?**
- ✅ Montre vraiment que Harl se plaint **BEAUCOUP**
- ✅ Teste tous les niveaux multiples fois
- ✅ Utilise des boucles pour simuler des plaintes répétées
- ✅ Teste les cas invalides
- ✅ Démontre la robustesse du système

### Compilation et exécution

```bash
make
./harl
```

### Aperçu du résultat

Le programme affichera une **longue série** de messages (plus de 30 plaintes !), démontrant vraiment que Harl se plaint énormément :

```
=== Test 1: Tous les niveaux ===
[ DEBUG ] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special ketchup burger. I really do !
[ INFO ] I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger ! If you did, I wouldn't be asking for more !
[ WARNING ] I think I deserve to have some extra bacon for free. I've been coming for years whereas you started working here since last month.
[ ERROR ] This is unacceptable ! I want to speak to the manager now.

=== Test 2: Harl se plaint beaucoup de DEBUG ===
[ DEBUG ] I love having extra bacon...
[ DEBUG ] I love having extra bacon...
[ DEBUG ] I love having extra bacon...

=== Test 3: Harl est vraiment énervé (ERROR) ===
[ ERROR ] This is unacceptable ! I want to speak to the manager now.
[ ERROR ] This is unacceptable ! I want to speak to the manager now.
[ ERROR ] This is unacceptable ! I want to speak to the manager now.
[ ERROR ] This is unacceptable ! I want to speak to the manager now.
[ ERROR ] This is unacceptable ! I want to speak to the manager now.

... et ainsi de suite (30+ messages au total)
```

---

## 💡 Points importants à retenir

### 1. Syntaxe des pointeurs membres

```cpp
// Déclaration
type_retour (Classe::*nom_ptr)(params);

// Initialisation
nom_ptr = &Classe::fonction;

// Appel
(objet.*nom_ptr)();
(ptr_objet->*nom_ptr)();
```

### 2. Tableaux de pointeurs membres

```cpp
void (Harl::*tableau[])(void) = { &Harl::f1, &Harl::f2, &Harl::f3 };
```

### 3. Parenthèses obligatoires

```cpp
// ✅ CORRECT
(this->*ptr)();

// ❌ INCORRECT
this->*ptr();  // Erreur de syntaxe !
```

---

## 🎓 Concepts C++ utilisés

| Concept | Description |
|---------|-------------|
| **Pointeurs vers fonctions membres** | Stocker l'adresse d'une méthode de classe |
| **Tableaux de pointeurs** | Organiser plusieurs pointeurs de fonctions |
| **Encapsulation** | Méthodes privées, interface publique |
| **`this`** | Pointeur vers l'objet courant |
| **Tableaux parallèles** | `levels[]` et `ptr_complain[]` synchronisés |

---

## 🔧 Alternatives possibles

### Avec std::map (C++98 compatible)

```cpp
#include <map>

void Harl::complain(std::string level) {
    std::map<std::string, void (Harl::*)()> complaints;
    complaints["DEBUG"] = &Harl::debug;
    complaints["INFO"] = &Harl::info;
    complaints["WARNING"] = &Harl::warning;
    complaints["ERROR"] = &Harl::error;
    
    if (complaints.find(level) != complaints.end())
        (this->*complaints[level])();
}
```

### Avec switch (nécessite enum)

```cpp
enum Level { DEBUG, INFO, WARNING, ERROR };

void Harl::complain(Level level) {
    void (Harl::*ptr[])(void) = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
    (this->*ptr[level])();
}
```

---

## 📚 Ressources complémentaires

- **Pointeurs en C++** : Comprendre `*` et `&`
- **Membres de classe** : Public vs Private
- **Tableaux statiques** : Déclaration et initialisation
- **std::string** : Comparaison et manipulation

---

## ✅ Checklist de validation

- [ ] La classe Harl compile sans erreur ni warning
- [ ] Les 4 méthodes debug/info/warning/error sont privées
- [ ] La méthode complain() utilise des pointeurs vers fonctions membres
- [ ] Tous les niveaux ("DEBUG", "INFO", "WARNING", "ERROR") fonctionnent
- [ ] Un niveau invalide affiche un message par défaut
- [ ] ⚠️ **IMPORTANT** : Le main montre que Harl se plaint BEAUCOUP (pas juste 5 appels !)
- [ ] Le code respecte la norme C++98
- [ ] Pas de fuite mémoire (vérifier avec valgrind si nécessaire)
- [ ] Le Makefile compile avec `-Wall -Wextra -Werror -std=c++98`

---

## 🎯 Objectif pédagogique

Cet exercice vous apprend à :
1. Manipuler des **pointeurs vers fonctions membres**
2. Comprendre la syntaxe particulière de C++ pour ces pointeurs
3. Éviter les longues chaînes de if/else
4. Utiliser des **tableaux parallèles** (levels + pointeurs)
5. Maîtriser l'opérateur `->*` et `.*`

---

**Bon courage ! 🚀**

