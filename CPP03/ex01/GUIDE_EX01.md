# Guide CPP03 - Exercice 01 : Serena, my love!

## 📋 Objectif de l'exercice

Créer une classe `ScavTrap` qui **hérite** de `ClapTrap`. Cet exercice introduit les concepts fondamentaux de l'**héritage** en C++ : classe dérivée, protected, redéfinition de méthodes, et appel des constructeurs parents.

---

## 🎯 Qu'est-ce que l'héritage ?

L'héritage permet de créer une nouvelle classe basée sur une classe existante.

```
      ClapTrap (classe de base / parent)
          │
          │ hérite de
          ▼
      ScavTrap (classe dérivée / enfant)
```

**ScavTrap** est un type spécialisé de **ClapTrap** avec :
- ✅ Toutes les fonctionnalités de ClapTrap
- ✅ Des attributs modifiés (HP, Energy, Damage différents)
- ✅ Une méthode redéfinie (`attack()`)
- ✅ Une capacité spéciale (`guardGate()`)

---

## 🏗️ Modification de ClapTrap

### Changement clé : private → protected

```cpp
class ClapTrap {
    protected:  // ← CHANGÉ de private à protected !
        std::string     _name;
        unsigned int    _hitPoints;
        unsigned int    _energyPoints;
        unsigned int    _attackDamage;

    public:
        // ... méthodes
};
```

### Niveaux d'accès en C++

| Modificateur | Classe elle-même | Classes dérivées | Extérieur |
|--------------|------------------|------------------|-----------|
| `private` | ✅ Oui | ❌ Non | ❌ Non |
| `protected` | ✅ Oui | ✅ **Oui** | ❌ Non |
| `public` | ✅ Oui | ✅ Oui | ✅ Oui |

**Pourquoi protected ?**
```cpp
// Avec private :
class ScavTrap : public ClapTrap {
    void attack(...) {
        std::cout << _name;  // ❌ ERREUR : _name est private !
    }
};

// Avec protected :
class ScavTrap : public ClapTrap {
    void attack(...) {
        std::cout << _name;  // ✅ OK : _name est protected !
    }
};
```

---

## 🏗️ Structure de ScavTrap

### ScavTrap.hpp

```cpp
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {  // Héritage public
    public:
        // Forme Canonique Orthodoxe
        ScavTrap();
        ScavTrap(std::string name);
        ScavTrap(const ScavTrap& other);
        ScavTrap& operator=(const ScavTrap& other);
        ~ScavTrap();

        // Redéfinition (override)
        void attack(const std::string& target);
        
        // Capacité spéciale
        void guardGate();
};
```

**Points clés :**
- `: public ClapTrap` = héritage public
- Pas besoin de redéclarer `takeDamage()` et `beRepaired()` (hérités)
- `attack()` est **redéfini** (override)
- `guardGate()` est **nouvelle**

---

## 🔍 Implémentation détaillée

### 1. Constructeur par défaut

```cpp
ScavTrap::ScavTrap() : ClapTrap() {
    //                  ^^^^^^^^^^^
    //                  Appelle le constructeur parent

    // Modification des attributs hérités
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    
    std::cout << "ScavTrap Default constructor called" << std::endl;
}
```

**Ordre d'exécution :**
1. Constructeur de `ClapTrap()` (parent)
2. Corps du constructeur de `ScavTrap()`

**Sortie :**
```
ClapTrap Default constructor called       ← Parent
ScavTrap Default constructor called       ← Enfant
```

---

### 2. Constructeur avec nom

```cpp
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    //                                  ^^^^^^^^^^^^^^
    //                                  Passe name au parent

    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    
    std::cout << "ScavTrap Name constructor called for " << name << std::endl;
}
```

**Important :** Le parent `ClapTrap(name)` initialise `_name`.

---

### 3. Constructeur de recopie

```cpp
ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
    //                                       ^^^^^^^^^^^^^^^^
    //                                       Copie via parent

    std::cout << "ScavTrap Copy constructor called" << std::endl;
}
```

**Magie de l'héritage :**
- `ClapTrap(other)` copie tous les attributs de base
- Pas besoin de recopier manuellement `_name`, `_hitPoints`, etc.

---

### 4. Opérateur d'affectation

```cpp
ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    std::cout << "ScavTrap Assignment operator called" << std::endl;
    
    if (this != &other) {
        ClapTrap::operator=(other);  // Appelle l'opérateur= du parent
    }
    
    return *this;
}
```

**Syntaxe :** `ClapTrap::operator=(other)` appelle explicitement la méthode du parent.

---

### 5. Destructeur

```cpp
ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap Destructor called" << std::endl;
}
```

**Ordre d'exécution :**
1. Destructeur de `ScavTrap` (enfant)
2. Destructeur de `ClapTrap` (parent) - automatique !

**Sortie :**
```
ScavTrap Destructor called       ← Enfant
ClapTrap Destructor called       ← Parent (automatique)
```

---

### 6. Redéfinition de attack()

```cpp
void ScavTrap::attack(const std::string& target) {
    if (_hitPoints == 0 || _energyPoints == 0) {
        std::cout << "ScavTrap " << _name << " can't attack!" << std::endl;
        return;
    }
    
    _energyPoints -= 1;
    std::cout << "ScavTrap " << _name << " savagely attacks " << target 
              << ", causing " << _attackDamage << " points of damage!" << std::endl;
}
```

**Différence avec ClapTrap :**
- Message : "savagely attacks" au lieu de "attacks"
- Dégâts : 20 au lieu de 0

**Override (redéfinition) :**
```cpp
ClapTrap clap("Clap");
clap.attack("enemy");  // Appelle ClapTrap::attack()

ScavTrap scav("Scav");
scav.attack("enemy");  // Appelle ScavTrap::attack() (redéfini)
```

---

### 7. Capacité spéciale guardGate()

```cpp
void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << _name << " is now in Gate keeper mode." << std::endl;
}
```

**Nouvelle méthode** spécifique à ScavTrap (n'existe pas dans ClapTrap).

---

## 🧪 Test et analyse du main

### Vue d'ensemble des tests

Le main.cpp contient **10 tests complets** qui démontrent l'héritage et comparent ClapTrap et ScavTrap :

| Test | Objectif | Concepts testés |
|------|----------|-----------------|
| **1** | Construction comparée | ClapTrap vs ScavTrap côte à côte |
| **2** | Comparaison attaques | Messages différents (override) |
| **3** | Capacité spéciale | guardGate() multiple fois |
| **4** | Constructeur de copie | Copie de ScavTrap |
| **5** | Opérateur d'affectation | Affectation de ScavTrap |
| **6** | Endurance ScavTrap | 52 attaques (50 energy max) |
| **7** | Résistance ScavTrap | 105 dégâts (100 HP max) |
| **8** | Combat comparatif | ClapTrap vs ScavTrap |
| **9** | Réparations multiples | Série de 5 réparations |
| **10** | Mode garde en combat | guardGate() pendant actions |

### Extraits clés du main

```cpp
// TEST 2: Comparaison des attaques
std::cout << "ClapTrap attack:" << std::endl;
clap.attack("enemy");  // Message normal, 0 dégâts

std::cout << "\nScavTrap attack:" << std::endl;
scav.attack("enemy");  // Message "savagely", 20 dégâts

// TEST 6: Endurance ScavTrap (50 energy)
ScavTrap endurance("Marathon");
for (int i = 0; i < 52; i++) {  // 50 max + 2 qui échouent
    endurance.attack("dummy");
}

// TEST 8: Combat ClapTrap vs ScavTrap
ClapTrap weakling("Weakling");
ScavTrap warrior("Warrior");
weakling.attack("Warrior");
warrior.takeDamage(0);
warrior.attack("Weakling");
weakling.takeDamage(20);  // ClapTrap meurt en un coup !

// TEST 10: Mode Gate keeper pendant combat
ScavTrap defender("Defender");
defender.guardGate();
defender.attack("attacker");
defender.takeDamage(25);
defender.beRepaired(15);
defender.guardGate();  // Remet en mode garde
```

### Aperçu de la sortie

```
=== TEST 1: Construction ClapTrap vs ScavTrap ===
ClapTrap Name constructor called for Basic
ClapTrap Name constructor called for Guardian
ScavTrap Name constructor called for Guardian

=== TEST 2: Comparaison des attaques ===
ClapTrap attack:
ClapTrap Basic attacks enemy, causing 0 points of damage!

ScavTrap attack:
ScavTrap Guardian savagely attacks enemy, causing 20 points of damage!

=== TEST 3: Capacité spéciale ScavTrap ===
ScavTrap Guardian is now in Gate keeper mode.
ScavTrap Guardian is now in Gate keeper mode.

=== TEST 6: Endurance ScavTrap (50 energy) ===
Attaque 1: ScavTrap Marathon savagely attacks dummy...
...
Attaque 51: ScavTrap Marathon can't attack! (plus d'énergie)

=== TEST 8: Combat ClapTrap vs ScavTrap ===
Tour 1 - ClapTrap attaque:
ClapTrap Weakling attacks Warrior, causing 0 points of damage!
Tour 2 - ScavTrap riposte:
ScavTrap Warrior savagely attacks Weakling, causing 20 points of damage!
ClapTrap Weakling took 20 points of damage! Remaining HP: 0

=== Destruction de tous les robots ===
ScavTrap Destructor called
ClapTrap Destructor called for [nom]
...
```

### Points clés démontrés

✅ **Override** : attack() de ScavTrap différent de ClapTrap  
✅ **Héritage** : takeDamage() et beRepaired() fonctionnent sans redéfinition  
✅ **Constructeurs** : Ordre parent → enfant  
✅ **Destructeurs** : Ordre enfant → parent (automatique)  
✅ **Stats différentes** : HP=100, Energy=50, Damage=20 (vs 10/10/0)  
✅ **Capacité unique** : guardGate() n'existe pas dans ClapTrap

---

## 💡 Concepts clés

### 1. Syntaxe de l'héritage

```cpp
class Enfant : public Parent {
//            ^^^^^^ ^^^^^^
//            |      |
//            |      Classe parent
//            Type d'héritage
};
```

### 2. Types d'héritage

| Type | Effet sur les membres public du parent |
|------|----------------------------------------|
| `public` | Restent public dans l'enfant ✅ |
| `protected` | Deviennent protected |
| `private` | Deviennent private |

**Note :** On utilise presque toujours `public` inheritance.

### 3. Appel du constructeur parent

```cpp
// ✅ CORRECT - Appel explicite
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    // ...
}

// ⚠️ Appel implicite du constructeur par défaut
ScavTrap::ScavTrap(std::string name) {
    // ClapTrap() est appelé automatiquement (pas ClapTrap(name))
}
```

### 4. Ordre de construction/destruction

**Construction (de la base vers le dérivé) :**
```
ClapTrap → ScavTrap
Parent     Enfant
```

**Destruction (du dérivé vers la base) :**
```
ScavTrap → ClapTrap
Enfant     Parent
```

### 5. Accès aux membres du parent

```cpp
class ScavTrap : public ClapTrap {
    void attack(...) {
        // Accès direct aux membres protected
        _name;           // ✅ OK (protected)
        _hitPoints;      // ✅ OK (protected)
        
        // Appel de méthodes publiques du parent
        takeDamage(10);  // ✅ OK (public)
    }
};
```

---

## 🎨 Diagramme de classe UML

```
┌─────────────────────────────┐
│       ClapTrap              │
├─────────────────────────────┤
│ # _name: string             │
│ # _hitPoints: uint          │
│ # _energyPoints: uint       │
│ # _attackDamage: uint       │
├─────────────────────────────┤
│ + attack(target)            │
│ + takeDamage(amount)        │
│ + beRepaired(amount)        │
└─────────────┬───────────────┘
              │
              │ hérite
              ▼
┌─────────────────────────────┐
│       ScavTrap              │
├─────────────────────────────┤
│ (hérite des attributs)      │
├─────────────────────────────┤
│ + attack(target)  ← override│
│ + guardGate()     ← nouveau │
└─────────────────────────────┘
```

---

## 📊 Comparaison ClapTrap vs ScavTrap

| Attribut/Méthode | ClapTrap | ScavTrap |
|------------------|----------|----------|
| **Hit Points** | 10 | 100 |
| **Energy Points** | 10 | 50 |
| **Attack Damage** | 0 | 20 |
| **attack()** | "attacks" | "savagely attacks" |
| **takeDamage()** | Hérité tel quel | Hérité tel quel |
| **beRepaired()** | Hérité tel quel | Hérité tel quel |
| **guardGate()** | ❌ N'existe pas | ✅ Capacité spéciale |

---

## 🚨 Erreurs courantes

### 1. Oublier de changer private en protected

```cpp
// ❌ FAUX - Attributs private
class ClapTrap {
    private:  // ScavTrap ne peut pas y accéder !
        std::string _name;
};

class ScavTrap : public ClapTrap {
    void attack(...) {
        std::cout << _name;  // ❌ ERREUR de compilation
    }
};

// ✅ CORRECT
class ClapTrap {
    protected:  // ScavTrap peut y accéder
        std::string _name;
};
```

### 2. Ne pas appeler le constructeur parent

```cpp
// ❌ FAUX - Pas d'appel explicite
ScavTrap::ScavTrap(std::string name) {
    // ClapTrap() est appelé (par défaut)
    // Mais _name n'est pas initialisé avec name !
    _name = name;  // Affectation, pas initialisation
}

// ✅ CORRECT
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    // ClapTrap(name) initialise _name correctement
}
```

### 3. Oublier d'appeler operator= du parent

```cpp
// ❌ FAUX - Ne copie pas les attributs du parent
ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    // Les attributs de ClapTrap ne sont pas copiés !
    return *this;
}

// ✅ CORRECT
ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other);  // Important !
    }
    return *this;
}
```

### 4. Confondre redéfinition et surcharge

```cpp
// Redéfinition (override) : même signature
class ClapTrap {
    void attack(const std::string& target);
};

class ScavTrap : public ClapTrap {
    void attack(const std::string& target);  // Redéfinit
};

// Surcharge (overload) : signatures différentes
class ClapTrap {
    void attack(const std::string& target);
    void attack(int damage);  // Surcharge (autre signature)
};
```

---

## ✅ Checklist de validation

- [ ] ClapTrap : attributs changés de `private` à `protected`
- [ ] ScavTrap hérite publiquement de ClapTrap
- [ ] Constructeurs de ScavTrap appellent les constructeurs de ClapTrap
- [ ] ScavTrap initialise HP=100, Energy=50, Damage=20
- [ ] ScavTrap::attack() est redéfini avec message différent
- [ ] guardGate() est implémenté
- [ ] L'opérateur= de ScavTrap appelle celui de ClapTrap
- [ ] Les messages de construction/destruction sont dans le bon ordre
- [ ] takeDamage() et beRepaired() fonctionnent sur ScavTrap (hérités)
- [ ] Compilation sans erreur avec `-Wall -Wextra -Werror -std=c++98`

---

## 🎯 Objectif pédagogique

Cet exercice vous apprend à :

1. ✅ Créer une **classe dérivée** (héritage)
2. ✅ Utiliser le modificateur **protected**
3. ✅ Appeler les **constructeurs du parent**
4. ✅ **Redéfinir** des méthodes (override)
5. ✅ Comprendre l'**ordre de construction/destruction**
6. ✅ Différencier **héritage public/protected/private**
7. ✅ Ajouter des **capacités spécifiques** à une classe dérivée

---

## 🔮 Exercice suivant : FragTrap (ex02)

L'exercice 02 ajoutera :
- Une troisième classe : `FragTrap`
- Autres stats (HP=100, Energy=100, Damage=30)
- Capacité spéciale : `highFivesGuys()`

**Hiérarchie complète :**
```
        ClapTrap
        /      \
   ScavTrap  FragTrap
```

---

## 📚 Vocabulaire

| Terme | Anglais | Description |
|-------|---------|-------------|
| Héritage | Inheritance | Relation "est-un" entre classes |
| Classe de base | Base class | Classe parent |
| Classe dérivée | Derived class | Classe enfant |
| Redéfinition | Override | Remplacer une méthode du parent |
| Surcharge | Overload | Plusieurs fonctions avec signatures différentes |
| Protected | Protected | Accessible dans la classe et ses dérivées |

---

**Félicitations ! 🎉**

Vous maîtrisez maintenant les bases de l'héritage en C++ !

**Next step: FragTrap et complétion du module ! 🚀**
