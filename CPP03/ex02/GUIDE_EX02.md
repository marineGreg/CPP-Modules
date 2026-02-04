# Guide CPP03 - Exercice 02 : Repetitive work

## 📋 Objectif de l'exercice

Créer une troisième classe dérivée `FragTrap` qui hérite de `ClapTrap`. Cet exercice consolide la maîtrise de l'héritage en créant une famille complète de robots avec des caractéristiques différentes.

---

## 🎯 Vue d'ensemble de la hiérarchie

```
              ClapTrap (classe de base)
            /           \
       ScavTrap      FragTrap
    (gardien)      (destructeur)
```

### Tableau comparatif complet

| Caractéristique | ClapTrap | ScavTrap | FragTrap |
|-----------------|----------|----------|----------|
| **Hit Points** | 10 | 100 | 100 |
| **Energy Points** | 10 | 50 | 100 |
| **Attack Damage** | 0 | 20 | 30 |
| **Message attack()** | "attacks" | "savagely attacks" | "attacks" |
| **Capacité spéciale** | ❌ Aucune | `guardGate()` | `highFivesGuys()` |
| **Rôle** | Robot basique | Gardien | Destructeur |

---

## 🏗️ Structure de FragTrap

### FragTrap.hpp

```cpp
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
    public:
        // Forme Canonique Orthodoxe
        FragTrap();
        FragTrap(std::string name);
        FragTrap(const FragTrap& other);
        FragTrap& operator=(const FragTrap& other);
        ~FragTrap();

        // Capacité spéciale unique
        void highFivesGuys(void);
};
```

**Points clés :**
- Hérite de `ClapTrap` (comme ScavTrap)
- **NE redéfinit PAS** `attack()` → utilise celle de ClapTrap
- Ajoute `highFivesGuys()` comme capacité spéciale

---

## 🔍 Implémentation détaillée

### 1. Constructeurs

#### Constructeur par défaut
```cpp
FragTrap::FragTrap() : ClapTrap() {
    this->_hitPoints = 100;
    this->_energyPoints = 100;  // Plus que ScavTrap !
    this->_attackDamage = 30;   // Le plus fort !
    
    std::cout << "FragTrap Default constructor called" << std::endl;
}
```

#### Constructeur avec nom
```cpp
FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    
    std::cout << "FragTrap Name constructor called for " << name << std::endl;
}
```

**Similaire à ScavTrap** mais avec des valeurs différentes.

---

### 2. Constructeur de recopie et opérateur d'affectation

```cpp
FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
    std::cout << "FragTrap Copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
    std::cout << "FragTrap Assignment operator called" << std::endl;
    if (this != &other) {
        ClapTrap::operator=(other);  // Délègue au parent
    }
    return *this;
}
```

**Pattern identique** à ScavTrap : délégation au parent.

---

### 3. Destructeur

```cpp
FragTrap::~FragTrap() {
    std::cout << "FragTrap Destructor called" << std::endl;
}
```

**Ordre de destruction :**
```
FragTrap destructor → ClapTrap destructor
```

---

### 4. Capacité spéciale : highFivesGuys()

```cpp
void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << _name 
              << " says: \"High five, anyone?\"" << std::endl;
}
```

**Rôle :** Capacité unique et amusante propre à FragTrap.

---

### 5. Méthode attack()

**Particularité :** FragTrap **N'override PAS** `attack()` !

```cpp
// FragTrap n'a PAS cette méthode :
// void FragTrap::attack(...) { ... }

// Il utilise celle héritée de ClapTrap :
void ClapTrap::attack(const std::string& target) {
    // ... message "attacks" (pas "savagely attacks")
    std::cout << "ClapTrap " << _name << " attacks " << target 
              << ", causing " << _attackDamage << " points of damage!" << std::endl;
}
```

**Résultat :**
```cpp
FragTrap frag("Frag");
frag.attack("enemy");
// Affiche : "ClapTrap Frag attacks enemy, causing 30 points of damage!"
//            ^^^^^^^^ (pas FragTrap !)
```

---

## 🧪 Test et analyse du main

### Vue d'ensemble des tests

Le main.cpp contient **10 tests exhaustifs** qui comparent et testent les 3 types de robots :

| Test | Objectif | Robots testés |
|------|----------|---------------|
| **1** | Construction des 3 types | ClapTrap, ScavTrap, FragTrap |
| **2** | Comparaison stats attaque | 0, 20, 30 dégâts |
| **3** | Capacités spéciales | guardGate() + highFivesGuys() |
| **4** | Endurance énergétique | 10 vs 50 vs 100 energy |
| **5** | Résistance aux dégâts | 10 vs 100 vs 100 HP |
| **6** | Constructeurs de copie | Copie des 3 types |
| **7** | Opérateurs d'affectation | Affectation des 3 types |
| **8** | Bataille royale | Combat entre les 3 types |
| **9** | Scénario de siège | ScavTrap vs 2 FragTraps |
| **10** | Armée de robots | 6 robots variés en action |

### Extraits clés du main

```cpp
// TEST 2: Comparaison des stats d'attaque
std::cout << "ClapTrap (Damage: 0):" << std::endl;
clap.attack("target");  // "ClapTrap Basic attacks..."

std::cout << "\nScavTrap (Damage: 20):" << std::endl;
scav.attack("target");  // "ScavTrap Guardian savagely attacks..."

std::cout << "\nFragTrap (Damage: 30):" << std::endl;
frag.attack("target");  // "ClapTrap Destroyer attacks..." (pas override !)

// TEST 3: Capacités spéciales
scav.guardGate();       // Mode gardien
frag.highFivesGuys();   // High five
frag.highFivesGuys();   // Peut être répété

// TEST 4: Endurance énergétique comparative
// ClapTrap: 10 energy → 12 attaques (2 échouent)
// ScavTrap: 50 energy → 52 attaques (2 échouent)
// FragTrap: 100 energy → 102 attaques (2 échouent)

// TEST 9: Scénario de siège
ScavTrap gatekeeper("Gatekeeper");
FragTrap attacker1("Attacker1");
FragTrap attacker2("Attacker2");

gatekeeper.guardGate();
attacker1.attack("Gatekeeper");
attacker2.attack("Gatekeeper");
gatekeeper.takeDamage(60);  // 30+30, survit (100 HP)
gatekeeper.attack("Attacker1");
attacker1.takeDamage(20);   // Prend 20 dégâts

// TEST 10: Armée de robots (6 robots)
ClapTrap army1[2] = {ClapTrap("Scout1"), ClapTrap("Scout2")};
ScavTrap army2[2] = {ScavTrap("Guard1"), ScavTrap("Guard2")};
FragTrap army3[2] = {FragTrap("Heavy1"), FragTrap("Heavy2")};
```

### Aperçu de la sortie

```
=== TEST 1: Construction des 3 types ===
ClapTrap Name constructor called for Basic
ClapTrap Name constructor called for Guardian
ScavTrap Name constructor called for Guardian
ClapTrap Name constructor called for Destroyer
FragTrap Name constructor called for Destroyer

=== TEST 2: Comparaison des stats d'attaque ===
ClapTrap (Damage: 0):
ClapTrap Basic attacks target, causing 0 points of damage!

ScavTrap (Damage: 20):
ScavTrap Guardian savagely attacks target, causing 20 points of damage!

FragTrap (Damage: 30):
ClapTrap Destroyer attacks target, causing 30 points of damage!
                    ^^^^^^^^ Utilise la méthode de ClapTrap !

=== TEST 3: Capacités spéciales ===
ScavTrap - Gate keeper mode:
ScavTrap Guardian is now in Gate keeper mode.

FragTrap - High five request:
FragTrap Destroyer says: "High five, anyone?"
FragTrap Destroyer says: "High five, anyone?"

=== TEST 4: Endurance énergétique ===
ClapTrap (10 energy): ...épuisé après 10 attaques
ScavTrap (50 energy): ...épuisé après 50 attaques
FragTrap (100 energy): ...épuisé après 100 attaques

=== TEST 9: Scénario de siège ===
Le gardien active son mode:
ScavTrap Gatekeeper is now in Gate keeper mode.

Les attaquants frappent:
ClapTrap Attacker1 attacks Gatekeeper, causing 30 points of damage!
ClapTrap Attacker2 attacks Gatekeeper, causing 30 points of damage!
ClapTrap Gatekeeper took 60 points of damage! Remaining HP: 40

Le gardien riposte:
ScavTrap Gatekeeper savagely attacks Attacker1, causing 20 points of damage!

=== Destruction de tous les robots ===
[30+ destructeurs appelés dans l'ordre LIFO]
```

### Tableau récapitulatif démontré

| Caractéristique | ClapTrap | ScavTrap | FragTrap |
|-----------------|----------|----------|----------|
| **HP** | 10 (meurt vite) | 100 (résistant) | 100 (résistant) |
| **Energy** | 10 (10 actions) | 50 (50 actions) | **100 (champion)** |
| **Damage** | 0 (inoffensif) | 20 (moyen) | **30 (le plus fort)** |
| **Message attack()** | "attacks" | "savagely attacks" | "attacks" |
| **Capacité spéciale** | ❌ | guardGate() | highFivesGuys() |

### Points clés démontrés

✅ **Hiérarchie complète** : 3 types de robots avec des spécialisations  
✅ **Override sélectif** : ScavTrap override attack(), FragTrap non  
✅ **Héritage** : takeDamage() et beRepaired() fonctionnent partout  
✅ **Capacités uniques** : Chaque type dérivé a sa spécialité  
✅ **Stats différenciées** : Équilibre entre HP, Energy et Damage  
✅ **Scénarios complexes** : Combats, sièges, armées  

**Total :** Plus de 30 robots testés dans des situations variées !

---

## 💡 Concepts clés

### 1. Override vs Héritage direct

| Classe | attack() | Comportement |
|--------|----------|--------------|
| **ClapTrap** | Définie | Message : "attacks" |
| **ScavTrap** | Override | Message : "savagely attacks" |
| **FragTrap** | Hérité | Message : "attacks" (de ClapTrap) |

**Choix de design :**
- ScavTrap change le message → Override
- FragTrap garde le message mais change les dégâts → Pas d'override

### 2. Hiérarchie plate

```
ClapTrap n'hérite de rien
    │
    ├── ScavTrap hérite de ClapTrap
    │
    └── FragTrap hérite de ClapTrap

ScavTrap et FragTrap sont frères (siblings)
```

**Pas d'héritage entre frères :**
```cpp
// ❌ FAUX
class FragTrap : public ScavTrap { ... }

// ✅ CORRECT
class FragTrap : public ClapTrap { ... }
```

### 3. Polymorphisme (aperçu)

```cpp
ClapTrap* robots[3];
robots[0] = new ClapTrap("Clap");
robots[1] = new ScavTrap("Scav");
robots[2] = new FragTrap("Frag");

// Tous peuvent être traités comme des ClapTrap !
for (int i = 0; i < 3; i++)
    robots[i]->attack("target");
```

**Note :** Le polymorphisme complet nécessite des fonctions `virtual` (CPP04).

---

## 🎨 Diagramme UML complet

```
┌──────────────────────────┐
│       ClapTrap           │
├──────────────────────────┤
│ # _name: string          │
│ # _hitPoints: uint       │ HP: 10
│ # _energyPoints: uint    │ Energy: 10
│ # _attackDamage: uint    │ Damage: 0
├──────────────────────────┤
│ + attack(target)         │ "attacks"
│ + takeDamage(amount)     │
│ + beRepaired(amount)     │
└───────────┬──────────────┘
            │
     ┌──────┴──────┐
     │             │
     ▼             ▼
┌─────────┐   ┌─────────┐
│ScavTrap │   │FragTrap │
├─────────┤   ├─────────┤
│HP: 100  │   │HP: 100  │
│En: 50   │   │En: 100  │
│Dmg: 20  │   │Dmg: 30  │
├─────────┤   ├─────────┤
│attack() │   │(hérite) │
│override │   │attack() │
│         │   │         │
│guardGate│   │highFives│
└─────────┘   └─────────┘
```

---

## 📊 Tableau récapitulatif complet

| Aspect | ClapTrap | ScavTrap | FragTrap |
|--------|----------|----------|----------|
| **Type** | Classe de base | Classe dérivée | Classe dérivée |
| **Hérite de** | Rien | ClapTrap | ClapTrap |
| **HP initial** | 10 | 100 | 100 |
| **Energy initial** | 10 | 50 | **100** ⭐ |
| **Damage initial** | 0 | 20 | **30** ⭐ |
| **attack() override** | N/A | ✅ Oui | ❌ Non |
| **Capacité spéciale** | ❌ | `guardGate()` | `highFivesGuys()` |
| **Rôle thématique** | Robot basique | Gardien | Destructeur |
| **Polyvalence** | Faible | Combat | Attaque pure |

---

## 🚨 Erreurs courantes

### 1. Copier-coller sans adapter

```cpp
// ❌ FAUX - Copié de ScavTrap sans changer les valeurs
FragTrap::FragTrap() : ClapTrap() {
    _hitPoints = 100;
    _energyPoints = 50;  // ❌ Devrait être 100 !
    _attackDamage = 20;  // ❌ Devrait être 30 !
}

// ✅ CORRECT
FragTrap::FragTrap() : ClapTrap() {
    _hitPoints = 100;
    _energyPoints = 100;  // ✅
    _attackDamage = 30;   // ✅
}
```

### 2. Oublier d'implémenter highFivesGuys()

```cpp
// ❌ FAUX - Déclaré mais pas défini
class FragTrap {
    void highFivesGuys(void);  // Déclaration
};
// Pas d'implémentation → Erreur de link

// ✅ CORRECT
void FragTrap::highFivesGuys(void) {
    std::cout << "High five!" << std::endl;
}
```

### 3. Redéfinir attack() inutilement

```cpp
// ⚠️ Pas nécessaire si le message reste le même
void FragTrap::attack(const std::string& target) {
    // Même code que ClapTrap::attack()
    // Juste le damage est différent (géré par _attackDamage)
}

// ✅ Pas besoin de redéfinir !
// L'héritage suffit
```

### 4. Confusion dans l'ordre de destruction

```cpp
// Construction :
ClapTrap → ScavTrap

// Destruction :
ScavTrap → ClapTrap
(Inverse automatique)
```

---

## ✅ Checklist de validation

- [ ] FragTrap hérite publiquement de ClapTrap
- [ ] Constructeurs de FragTrap appellent les constructeurs de ClapTrap
- [ ] FragTrap initialise HP=100, Energy=100, Damage=30
- [ ] FragTrap N'override PAS attack() (utilise celle de ClapTrap)
- [ ] highFivesGuys() est implémenté
- [ ] L'opérateur= de FragTrap appelle celui de ClapTrap
- [ ] Les messages de construction/destruction sont corrects
- [ ] takeDamage(), beRepaired(), attack() fonctionnent correctement
- [ ] Le main teste les 3 classes (ClapTrap, ScavTrap, FragTrap)
- [ ] Compilation sans erreur avec `-Wall -Wextra -Werror -std=c++98`

---

## 🎯 Objectif pédagogique

Cet exercice consolide :

1. ✅ La création de **plusieurs classes dérivées**
2. ✅ La différenciation entre **override et héritage direct**
3. ✅ La gestion de **hiérarchies de classes**
4. ✅ La compréhension des **ordres de construction/destruction**
5. ✅ Les **capacités spécifiques** par classe dérivée
6. ✅ La **réutilisation de code** via l'héritage

---

## 🔮 Pour aller plus loin

### Module CPP04 : Polymorphisme

Le prochain module introduira :
- **Fonctions virtuelles** (`virtual`)
- **Classes abstraites** (pure virtual)
- **Destructeurs virtuels**
- **Polymorphisme dynamique**

**Aperçu :**
```cpp
class ClapTrap {
    virtual void attack(...);  // Fonction virtuelle
    virtual ~ClapTrap();       // Destructeur virtuel
};

ClapTrap* robot = new ScavTrap("Scav");
robot->attack("enemy");  // Appelle ScavTrap::attack() (polymorphisme)
delete robot;            // Appelle ~ScavTrap() puis ~ClapTrap() (virtuel)
```

---

## 📚 Design patterns observés

### 1. Template Method Pattern

```
ClapTrap définit le comportement de base
    │
    ├── ScavTrap spécialise attack()
    └── FragTrap réutilise attack() mais change les stats
```

### 2. Specialization Pattern

Chaque classe dérivée se spécialise dans un rôle :
- **ClapTrap** : Générique
- **ScavTrap** : Gardien (moyenne stats, mode garde)
- **FragTrap** : Destructeur (haute stats, moral boost)

---

## 🎮 Tests supplémentaires suggérés

```cpp
// Test 1 : Combat entre robots
ScavTrap defender("Guardian");
FragTrap attacker("Destroyer");

attacker.attack("Guardian");
defender.takeDamage(30);  // Prend les dégâts de FragTrap

// Test 2 : Épuisement d'énergie
FragTrap fighter("Fighter");
for (int i = 0; i < 105; i++) {
    fighter.attack("dummy");  // Testera l'épuisement après 100 attaques
}

// Test 3 : Copie et affectation
FragTrap original("Original");
FragTrap copy(original);           // Constructeur de copie
FragTrap assigned("Temp");
assigned = original;               // Opérateur d'affectation

// Test 4 : Polymorphisme (sans virtual)
ClapTrap* robot = new FragTrap("Poly");
robot->attack("target");  // Appelle ClapTrap::attack() (pas polymorphe sans virtual)
delete robot;
```

---

## 📖 Récapitulatif du module CPP03

| Exercice | Classe(s) | Concept principal |
|----------|-----------|-------------------|
| **Ex00** | ClapTrap | Classe de base avec logique métier |
| **Ex01** | ScavTrap | Héritage, protected, override |
| **Ex02** | FragTrap | Hiérarchie, capacités spécifiques |

**Progression pédagogique :**
1. Créer une classe solide (ex00)
2. Apprendre l'héritage (ex01)
3. Consolider avec une seconde classe dérivée (ex02)

---

**Félicitations ! 🎉🎉🎉**

Vous avez terminé le module CPP03 et maîtrisez maintenant :
- ✅ L'héritage en C++
- ✅ Les modificateurs d'accès (private, protected, public)
- ✅ La redéfinition de méthodes (override)
- ✅ Les hiérarchies de classes
- ✅ La construction/destruction en chaîne

**Prochaine étape : CPP04 et le polymorphisme ! 🚀**

Le polymorphisme rendra vos hiérarchies vraiment puissantes avec les fonctions virtuelles et le dispatch dynamique !
