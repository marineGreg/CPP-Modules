# Guide CPP03 - Exercice 00 : Aaaaand... OPEN!

## 📋 Objectif de l'exercice

Créer une classe `ClapTrap` qui représente un robot de combat avec des points de vie, d'énergie et de dégâts. Ce premier exercice pose les bases pour l'apprentissage de l'**héritage** dans les exercices suivants.

---

## 🎮 Concept : ClapTrap

ClapTrap est un robot de combat (référence au jeu Borderlands) avec :
- **Hit Points** (HP) : Points de vie (10 au départ)
- **Energy Points** : Points d'énergie pour agir (10 au départ)
- **Attack Damage** : Dégâts infligés (0 au départ)

### Actions possibles

| Action | Coût | Effet |
|--------|------|-------|
| **attack()** | 1 énergie | Attaque une cible |
| **takeDamage()** | Aucun | Perd des HP |
| **beRepaired()** | 1 énergie | Récupère des HP |

---

## 🏗️ Structure de la classe

### ClapTrap.hpp

```cpp
class ClapTrap {
    private:
        std::string     _name;          // Nom du robot
        unsigned int    _hitPoints;     // Points de vie (10 par défaut)
        unsigned int    _energyPoints;  // Points d'énergie (10 par défaut)
        unsigned int    _attackDamage;  // Dégâts d'attaque (0 par défaut)

    public:
        // Forme Canonique Orthodoxe
        ClapTrap();                                  // Constructeur par défaut
        ClapTrap(std::string name);                  // Constructeur avec nom
        ClapTrap(const ClapTrap& other);             // Constructeur de recopie
        ClapTrap& operator=(const ClapTrap& other);  // Opérateur d'affectation
        ~ClapTrap();                                 // Destructeur

        // Méthodes d'action
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};
```

**Points importants :**
- Attributs `unsigned int` : jamais négatifs
- Attributs **privés** : encapsulation
- Pas de getters/setters (non demandés)

---

## 🔍 Implémentation détaillée

### 1. Constructeurs

#### Constructeur par défaut
```cpp
ClapTrap::ClapTrap() 
    : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap Default constructor called" << std::endl;
}
```

#### Constructeur avec nom
```cpp
ClapTrap::ClapTrap(std::string name) 
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap Name constructor called for " << _name << std::endl;
}
```

**Initialisation par liste :**
- `: _name(name), _hitPoints(10), ...`
- Plus efficace que l'affectation dans le corps
- Ordre respecte l'ordre de déclaration dans la classe

---

### 2. Constructeur de recopie et opérateur d'affectation

```cpp
ClapTrap::ClapTrap(const ClapTrap& other) {
    std::cout << "ClapTrap Copy constructor called" << std::endl;
    *this = other;  // Délègue à l'opérateur d'affectation
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    std::cout << "ClapTrap Assignment operator called" << std::endl;
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return *this;
}
```

**Protection auto-affectation :** `if (this != &other)`

---

### 3. Destructeur

```cpp
ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap Destructor called for " << _name << std::endl;
}
```

**Affiche le nom** pour mieux suivre la destruction des objets.

---

### 4. Méthode attack()

```cpp
void ClapTrap::attack(const std::string& target) {
    // Vérification : mort ?
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name 
                  << " is dead and cannot attack!" << std::endl;
        return;
    }
    
    // Vérification : assez d'énergie ?
    if (_energyPoints == 0) {
        std::cout << "ClapTrap " << _name 
                  << " is out of energy and cannot attack!" << std::endl;
        return;
    }

    // Action
    _energyPoints -= 1;
    std::cout << "ClapTrap " << _name << " attacks " << target 
              << ", causing " << _attackDamage << " points of damage!" << std::endl;
}
```

**Logique :**
1. ✅ Vérifier si le robot est mort (`_hitPoints == 0`)
2. ✅ Vérifier si le robot a de l'énergie (`_energyPoints > 0`)
3. ✅ Consommer 1 point d'énergie
4. ✅ Afficher le message d'attaque

**Note :** N'affecte PAS la cible (pas d'interaction entre objets ici).

---

### 5. Méthode takeDamage()

```cpp
void ClapTrap::takeDamage(unsigned int amount) {
    // Déjà mort ?
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " is already dead!" << std::endl;
        return;
    }
    
    // Calcul des dégâts (éviter les valeurs négatives)
    if (amount >= _hitPoints)
        _hitPoints = 0;
    else
        _hitPoints -= amount;

    std::cout << "ClapTrap " << _name << " took " << amount 
              << " points of damage! Remaining HP: " << _hitPoints << std::endl;
}
```

**Logique :**
1. ✅ Vérifier si déjà mort
2. ✅ Soustraire les dégâts (minimum 0)
3. ✅ Afficher les HP restants

**Gestion unsigned int :**
```cpp
// ❌ DANGEREUX avec unsigned int
_hitPoints -= amount;  // Si amount > _hitPoints, overflow !

// ✅ SÉCURISÉ
if (amount >= _hitPoints)
    _hitPoints = 0;
else
    _hitPoints -= amount;
```

---

### 6. Méthode beRepaired()

```cpp
void ClapTrap::beRepaired(unsigned int amount) {
    // Mort ?
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name 
                  << " is dead and cannot be repaired!" << std::endl;
        return;
    }
    
    // Assez d'énergie ?
    if (_energyPoints == 0) {
        std::cout << "ClapTrap " << _name 
                  << " is out of energy and cannot repair itself!" << std::endl;
        return;
    }

    // Action
    _energyPoints -= 1;
    _hitPoints += amount;
    std::cout << "ClapTrap " << _name << " repairs itself by " << amount 
              << " points! Current HP: " << _hitPoints << std::endl;
}
```

**Logique :**
1. ✅ Vérifier si mort
2. ✅ Vérifier si assez d'énergie
3. ✅ Consommer 1 énergie
4. ✅ Ajouter les HP
5. ✅ Afficher les HP actuels

---

## 🧪 Test et analyse du main

### Vue d'ensemble des tests

Le main.cpp contient **11 tests complets** qui couvrent tous les aspects de la classe ClapTrap :

| Test | Objectif | Concepts testés |
|------|----------|-----------------|
| **1** | Construction basique | Constructeur avec paramètre |
| **2** | Actions de base | attack(), takeDamage(), beRepaired() |
| **3** | Constructeur de copie | Copie d'objet |
| **4** | Opérateur d'affectation | Affectation entre objets |
| **5** | Épuisement d'énergie | Limite de 10 energy points |
| **6** | Série de réparations | Multiples beRepaired() |
| **7** | Combat simulé | Interaction entre 2 ClapTraps |
| **8** | Dégâts progressifs | Accumulation de dégâts |
| **9** | Tentatives après mort | Actions impossibles (HP=0) |
| **10** | Mort instantanée | Dégâts > HP en un coup |
| **11** | Multiple ClapTraps | Tableau d'objets |

### Extrait du main (Tests clés)

```cpp
// TEST 3: Constructeur de copie
ClapTrap copyClap(clap);
copyClap.attack("dummy");

// TEST 4: Opérateur d'affectation
ClapTrap assignedClap("Temporary");
assignedClap = clap;

// TEST 5: Épuisement d'énergie (12 actions, max = 10)
ClapTrap tired("Exhausted");
for (int i = 0; i < 12; i++) {
    tired.attack("training dummy");
}

// TEST 8: Dégâts progressifs
ClapTrap victim("Victim");
victim.takeDamage(3);
victim.takeDamage(4);
victim.takeDamage(5);  // Total: 12 dégâts → mort

// TEST 11: Multiple ClapTraps
ClapTrap army[3] = {ClapTrap("Soldier1"), ClapTrap("Soldier2"), ClapTrap("Soldier3")};
```

### Aperçu de la sortie

```
=== TEST 1: Construction basique ===
ClapTrap Name constructor called for Clappy
ClapTrap Name constructor called for Target

=== TEST 3: Constructeur de copie ===
ClapTrap Copy constructor called
ClapTrap Assignment operator called
ClapTrap copyClap attacks dummy, causing 0 points of damage!

=== TEST 5: Épuisement d'énergie ===
Action 1: ClapTrap Exhausted attacks training dummy...
...
Action 11: ClapTrap Exhausted is out of energy and cannot attack!

=== TEST 8: Dégâts progressifs ===
ClapTrap Victim took 3 points of damage! Remaining HP: 7
ClapTrap Victim took 4 points of damage! Remaining HP: 3
ClapTrap Victim took 5 points of damage! Remaining HP: 0

=== TEST 9: Tentative d'action après mort ===
ClapTrap Victim is dead and cannot attack!
ClapTrap Victim is dead and cannot be repaired!

=== Destruction de tous les ClapTraps ===
ClapTrap Destructor called for [tous les ClapTraps]
```

**Total :** Plus de 30 ClapTraps créés et testés dans différents scénarios !

---

## 💡 Concepts clés

### 1. Unsigned int et overflow

```cpp
unsigned int a = 5;
unsigned int b = 10;

a - b;  // ❌ Overflow ! Résultat : 4294967291 (très grand nombre)

// Solution :
if (b >= a)
    a = 0;
else
    a -= b;
```

### 2. Early return

```cpp
void attack(...) {
    if (_hitPoints == 0) {
        std::cout << "Dead!" << std::endl;
        return;  // Sortie anticipée
    }
    
    if (_energyPoints == 0) {
        std::cout << "No energy!" << std::endl;
        return;
    }
    
    // Code principal seulement si les conditions sont OK
    _energyPoints--;
    // ...
}
```

**Avantages :**
- Évite les imbrications de if
- Code plus lisible
- Logique de validation claire

### 3. Passage par référence const

```cpp
void attack(const std::string& target);
//          ^^^^^^^^^^^^^^^^^^^^
//          Évite la copie du string
```

**Pourquoi ?**
- `const` : la fonction ne modifie pas target
- `&` : évite la copie (plus efficace)

### 4. const après une méthode

```cpp
void getName() const;  // Méthode constante (ne modifie pas l'objet)
```

Pour cet exercice, non demandé, mais utile si on ajoutait des getters.

---

## 🎨 Diagramme d'état

```
┌─────────────────────────┐
│   ClapTrap créé         │
│  HP: 10, Energy: 10     │
└───────────┬─────────────┘
            │
            ▼
┌─────────────────────────┐
│    Actions possibles     │
│  ┌──────────────────┐   │
│  │ attack()         │   │ -1 Energy
│  │ beRepaired()     │   │ -1 Energy, +HP
│  │ takeDamage()     │   │ -HP
│  └──────────────────┘   │
└───────────┬─────────────┘
            │
            ▼
    ┌───────┴────────┐
    │                │
    ▼                ▼
┌────────┐      ┌─────────┐
│ HP = 0 │      │Energy=0│
│  MORT  │      │ÉPUISÉ  │
└────────┘      └─────────┘
```

---

## 🚨 Erreurs courantes

### 1. Oublier les vérifications

```cpp
// ❌ FAUX - Pas de vérification
void attack(const std::string& target) {
    _energyPoints--;
    std::cout << "Attack!" << std::endl;
}
// Problème : peut attaquer même mort ou sans énergie

// ✅ CORRECT
void attack(const std::string& target) {
    if (_hitPoints == 0 || _energyPoints == 0)
        return;
    _energyPoints--;
    // ...
}
```

### 2. Overflow avec unsigned int

```cpp
// ❌ DANGEREUX
unsigned int hp = 5;
hp -= 10;  // Overflow ! hp = 4294967291

// ✅ SÉCURISÉ
if (amount >= hp)
    hp = 0;
else
    hp -= amount;
```

### 3. Ne pas initialiser dans le bon ordre

```cpp
// ❌ Ordre différent de la déclaration (warning)
class ClapTrap {
    private:
        std::string _name;
        unsigned int _hitPoints;
};

ClapTrap::ClapTrap() : _hitPoints(10), _name("Default") { }
//                     ^^^^^^^^^^^^^^^^  ^^^^^^^^^^^^^^^
//                     Initialisé 2e     Déclaré 1er
//                     → Warning !

// ✅ Respecte l'ordre de déclaration
ClapTrap::ClapTrap() : _name("Default"), _hitPoints(10) { }
```

### 4. Oublier le message dans destructeur

```cpp
// ❌ Pas informatif
~ClapTrap() {
    std::cout << "Destructor called" << std::endl;
}

// ✅ Affiche le nom
~ClapTrap() {
    std::cout << "Destructor called for " << _name << std::endl;
}
```

---

## ✅ Checklist de validation

- [ ] La classe ClapTrap compile sans erreur
- [ ] Les attributs sont privés
- [ ] Les 4 fonctions de la forme canonique sont présentes
- [ ] Les constructeurs initialisent HP=10, Energy=10, Damage=0
- [ ] attack() vérifie HP et Energy avant d'agir
- [ ] attack() consomme 1 énergie
- [ ] takeDamage() gère correctement les unsigned int
- [ ] beRepaired() vérifie HP et Energy
- [ ] beRepaired() consomme 1 énergie et ajoute des HP
- [ ] Tous les messages sont affichés correctement
- [ ] Compilation sans erreur avec `-Wall -Wextra -Werror -std=c++98`

---

## 🎯 Objectif pédagogique

Cet exercice vous apprend à :

1. ✅ Créer une classe avec **logique métier** (pas juste des getters/setters)
2. ✅ Gérer un **système d'état** (HP, énergie)
3. ✅ Implémenter des **vérifications** avant actions
4. ✅ Manipuler des **unsigned int** en sécurité
5. ✅ Utiliser les **early returns** pour clarifier le code
6. ✅ Préparer le terrain pour l'**héritage** (ex01, ex02)

---

## 🔮 Exercices suivants

### Ex01 : ScavTrap (Héritage)

```cpp
class ScavTrap : public ClapTrap {  // Hérite de ClapTrap
    // ...
};
```

ScavTrap aura :
- HP différents (100 au lieu de 10)
- Energy différents (50 au lieu de 10)
- Méthode spéciale `guardGate()`

### Ex02 : FragTrap

Troisième type de robot avec ses propres caractéristiques.

---

## 📚 Vocabulaire

| Terme | Description |
|-------|-------------|
| **Hit Points (HP)** | Points de vie du robot |
| **Energy Points** | Points d'énergie pour agir |
| **Attack Damage** | Dégâts infligés par attaque |
| **Early return** | Sortie anticipée d'une fonction |
| **Overflow** | Dépassement de capacité (unsigned) |
| **Encapsulation** | Attributs privés, méthodes publiques |

---

## 🎮 Tests supplémentaires suggérés

```cpp
// Test 1 : Créer plusieurs ClapTraps
ClapTrap team[3] = {ClapTrap("Alpha"), ClapTrap("Beta"), ClapTrap("Gamma")};

// Test 2 : Bataille simulée
ClapTrap fighter("Fighter");
ClapTrap target("Target");
fighter.attack("Target");
target.takeDamage(0);  // Damage est 0 par défaut

// Test 3 : Épuisement complet
for (int i = 0; i < 15; i++)
    fighter.attack("dummy");  // Testera le manque d'énergie

// Test 4 : Mort et résurrection impossible
target.takeDamage(100);
target.beRepaired(50);  // Ne devrait pas fonctionner
```

---

**Bon courage ! 🤖**

ClapTrap est le fondement de tout le module CPP03. Comprendre cette classe est essentiel pour maîtriser l'héritage dans les exercices suivants !

**Next step: ScavTrap avec l'héritage ! 🚀**
