# Guide CPP03 - Exercice 03 : Now it's weird!

## 📋 Objectif de l'exercice

Créer une classe `DiamondTrap` qui utilise l'**héritage multiple** en héritant à la fois de `ScavTrap` ET de `FragTrap`. Cet exercice introduit le fameux **"Diamond Problem"** et démontre comment le résoudre en C++.

---

## 🎯 Le Diamond Problem (Problème du diamant)

### Schéma de la hiérarchie

```
           ClapTrap
          /        \
     ScavTrap    FragTrap
          \        /
         DiamondTrap
```

**Problème :** DiamondTrap hérite de ClapTrap **deux fois** (via ScavTrap et FragTrap) !

### Conséquences

Sans précautions :
- ❌ Deux copies des attributs de ClapTrap
- ❌ Ambiguïté : quel `_name` utiliser ?
- ❌ Gaspillage mémoire
- ❌ Comportements imprévisibles

---

## 🏗️ Structure de DiamondTrap

### DiamondTrap.hpp

```cpp
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap {
    private:
        std::string _name;  // Nom propre du DiamondTrap

    public:
        DiamondTrap();
        DiamondTrap(std::string name);
        DiamondTrap(const DiamondTrap& other);
        DiamondTrap& operator=(const DiamondTrap& other);
        ~DiamondTrap();

        // Utilise l'attaque de ScavTrap explicitement
        using ScavTrap::attack;

        // Capacité spéciale unique
        void whoAmI();
};
```

**Points clés :**
- Hérite de **2 classes** : `FragTrap` ET `ScavTrap`
- Attribut `_name` propre au DiamondTrap
- `using ScavTrap::attack` : résout l'ambiguïté d'attack()
- `whoAmI()` : méthode unique à DiamondTrap

---

## 🔍 Caractéristiques de DiamondTrap

### Tableau des stats

| Attribut | Valeur | Provenance |
|----------|--------|------------|
| **Hit Points** | 100 | FragTrap |
| **Energy Points** | 50 | ScavTrap |
| **Attack Damage** | 30 | FragTrap |
| **attack()** | ScavTrap | `using ScavTrap::attack` |
| **Noms** | 2 noms | `_name` + `ClapTrap::_name` |

### Capacités héritées

```
DiamondTrap a accès à :
    ├── ClapTrap
    │   ├── attack() [via ScavTrap]
    │   ├── takeDamage()
    │   └── beRepaired()
    │
    ├── ScavTrap
    │   ├── attack() (redéfini) ✅ Utilisé
    │   └── guardGate()
    │
    ├── FragTrap
    │   └── highFivesGuys()
    │
    └── DiamondTrap
        └── whoAmI() (unique)
```

---

## 🔍 Implémentation détaillée

### 1. Constructeur avec nom

```cpp
DiamondTrap::DiamondTrap(std::string name) 
    : ClapTrap(name + "_clap_name"),  // Nom de ClapTrap avec suffixe
      FragTrap(),                      // Constructeur par défaut
      ScavTrap()                       // Constructeur par défaut
{
    this->_name = name;                // Nom propre du DiamondTrap
    
    // Stats hybrides
    this->_hitPoints = 100;            // De FragTrap
    this->_energyPoints = 50;          // De ScavTrap
    this->_attackDamage = 30;          // De FragTrap
    
    std::cout << "DiamondTrap Name constructor called for " << name << std::endl;
}
```

**Ordre d'exécution :**
1. `ClapTrap(name + "_clap_name")`
2. `FragTrap()` (qui appelle aussi ClapTrap)
3. `ScavTrap()` (qui appelle aussi ClapTrap)
4. Corps de `DiamondTrap(name)`

**Deux noms :**
- `_name` : "Monster"
- `ClapTrap::_name` : "Monster_clap_name"

---

### 2. Méthode whoAmI()

```cpp
void DiamondTrap::whoAmI() {
    std::cout << "I am DiamondTrap: " << this->_name 
              << " and my ClapTrap name is: " << ClapTrap::_name << std::endl;
}
```

**Exemple de sortie :**
```
I am DiamondTrap: Monster and my ClapTrap name is: Monster_clap_name
```

**Points clés :**
- `this->_name` : Nom DiamondTrap
- `ClapTrap::_name` : Nom ClapTrap (avec suffixe)
- Résolution d'ambiguïté avec `ClapTrap::`

---

### 3. Résolution de l'ambiguïté d'attack()

```cpp
// Dans DiamondTrap.hpp
using ScavTrap::attack;
```

**Sans `using` :**
```cpp
DiamondTrap dt("Monster");
dt.attack("enemy");  // ❌ ERREUR : Ambiguïté !
                     // Utiliser FragTrap::attack() ou ScavTrap::attack() ?
```

**Avec `using` :**
```cpp
DiamondTrap dt("Monster");
dt.attack("enemy");  // ✅ OK : Utilise ScavTrap::attack()
```

---

### 4. Constructeur de copie

```cpp
DiamondTrap::DiamondTrap(const DiamondTrap& other) 
    : ClapTrap(other),   // Copie via ClapTrap
      FragTrap(other),   // Copie via FragTrap
      ScavTrap(other)    // Copie via ScavTrap
{
    *this = other;       // Délègue à l'opérateur=
    std::cout << "DiamondTrap Copy constructor called" << std::endl;
}
```

---

### 5. Opérateur d'affectation

```cpp
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    if (this != &other) {
        this->_name = other._name;                    // Nom DiamondTrap
        this->ClapTrap::_name = other.ClapTrap::_name; // Nom ClapTrap
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return *this;
}
```

**Important :** Copie les **deux noms** !

---

## 🧪 Test et analyse du main

### Vue d'ensemble des tests

Le main.cpp contient **7 tests** qui démontrent l'héritage multiple :

| Test | Objectif |
|------|----------|
| **1** | Construction DiamondTrap |
| **2** | whoAmI() (les deux noms) |
| **3** | attack() de ScavTrap |
| **4** | Capacités héritées des 3 parents |
| **5** | Constructeur de copie |
| **6** | Endurance (50 energy) |
| **7** | Comparaison avec les 4 types |

### Code du main

```cpp
int main() {
    // TEST 1: Construction
    DiamondTrap diamond("Monster");

    // TEST 2: whoAmI()
    diamond.whoAmI();
    // Sortie: "I am DiamondTrap: Monster and my ClapTrap name is: Monster_clap_name"

    // TEST 3: Attack (de ScavTrap)
    diamond.attack("enemy");

    // TEST 4: Capacités héritées
    diamond.guardGate();       // De ScavTrap
    diamond.highFivesGuys();   // De FragTrap
    diamond.takeDamage(30);    // De ClapTrap
    diamond.beRepaired(15);    // De ClapTrap

    // TEST 5: Constructeur de copie
    DiamondTrap copy(diamond);
    copy.whoAmI();

    // TEST 6: Endurance (50 energy)
    DiamondTrap marathon("Marathon");
    for (int i = 0; i < 52; i++)
        marathon.attack("dummy");

    // TEST 7: Comparaison
    ClapTrap clap("Clap");
    ScavTrap scav("Scav");
    FragTrap frag("Frag");
    DiamondTrap ultimate("Ultimate");
    
    clap.attack("target");
    scav.attack("target");
    frag.attack("target");
    ultimate.attack("target");
    ultimate.whoAmI();

    return 0;
}
```

### Ordre de construction/destruction

```
Construction de DiamondTrap("Monster") :
    1. ClapTrap("Monster_clap_name")   ← Base
    2. FragTrap()                      ← Parent 1
       └─> ClapTrap()                  ← (ClapTrap encore!)
    3. ScavTrap()                      ← Parent 2
       └─> ClapTrap()                  ← (Et encore!)
    4. DiamondTrap("Monster")          ← Enfant

Destruction (ordre inverse) :
    1. DiamondTrap destructor
    2. ScavTrap destructor → ClapTrap destructor
    3. FragTrap destructor → ClapTrap destructor
    4. ClapTrap destructor
```

**⚠️ Sans virtual inheritance : ClapTrap construit/détruit 3 fois !**

### Sortie attendue (extrait)

```
=== TEST 1: Construction ===
ClapTrap Name constructor called for Monster_clap_name
FragTrap Default constructor called
ScavTrap Default constructor called
DiamondTrap Name constructor called for Monster

=== TEST 2: whoAmI() ===
I am DiamondTrap: Monster and my ClapTrap name is: Monster_clap_name

=== TEST 3: Attack (de ScavTrap) ===
ScavTrap Monster savagely attacks enemy, causing 30 points of damage!

=== TEST 4: Capacités héritées ===
ScavTrap Monster is now in Gate keeper mode.
FragTrap Monster says: "High five, anyone?"
ClapTrap Monster took 30 points of damage! Remaining HP: 70
ClapTrap Monster repairs itself by 15 points! Current HP: 85

=== TEST 7: Comparaison ===
ClapTrap Clap attacks target, causing 0 points of damage!
ScavTrap Scav savagely attacks target, causing 20 points of damage!
ClapTrap Frag attacks target, causing 30 points of damage!
ScavTrap Ultimate savagely attacks target, causing 30 points of damage!
I am DiamondTrap: Ultimate and my ClapTrap name is: Ultimate_clap_name
```

---

## 💡 Concepts clés

### 1. Héritage multiple

```cpp
class Enfant : public Parent1, public Parent2 {
    // Hérite des deux parents
};
```

**Avantages :**
- ✅ Combine fonctionnalités de plusieurs classes
- ✅ Réutilisation maximale du code

**Inconvénients :**
- ❌ Complexité accrue
- ❌ Diamond Problem
- ❌ Ambiguïtés potentielles

### 2. using pour résoudre l'ambiguïté

```cpp
class DiamondTrap : public FragTrap, public ScavTrap {
    using ScavTrap::attack;  // Choisit attack() de ScavTrap
};
```

**Alternatives :**
```cpp
// Appel explicite (sans using)
diamond.ScavTrap::attack("enemy");  // Explicite mais lourd
```

### 3. Résolution de scope (::)

```cpp
this->_name                 // Nom DiamondTrap
ClapTrap::_name            // Nom ClapTrap
ScavTrap::attack("enemy")  // Méthode de ScavTrap
```

### 4. Virtual Inheritance (solution au Diamond Problem)

**Ce que le sujet devrait avoir (mais n'a peut-être pas) :**

```cpp
class ScavTrap : virtual public ClapTrap { };
class FragTrap : virtual public ClapTrap { };
```

**Effet :**
- Une seule instance de ClapTrap dans DiamondTrap
- Pas de duplication d'attributs
- Résout le Diamond Problem proprement

---

## 🎨 Diagramme UML complet

```
┌──────────────────┐
│    ClapTrap      │
│  HP:10 E:10 D:0  │
└────────┬─────────┘
         │
    ┌────┴────┐
    │         │
    ▼         ▼
┌────────┐ ┌────────┐
│ScavTrap│ │FragTrap│
│HP:100  │ │HP:100  │
│E:50    │ │E:100   │
│D:20    │ │D:30    │
└───┬────┘ └───┬────┘
    │          │
    └────┬─────┘
         ▼
   ┌────────────┐
   │DiamondTrap │
   │  HP: 100   │ ← FragTrap
   │  E:  50    │ ← ScavTrap
   │  D:  30    │ ← FragTrap
   │            │
   │ attack()   │ ← ScavTrap
   │ guardGate()│ ← ScavTrap
   │highFives() │ ← FragTrap
   │ whoAmI()   │ ← Unique
   └────────────┘
```

---

## 🚨 Erreurs courantes

### 1. Oublier `using` pour attack()

```cpp
// ❌ ERREUR : Ambiguïté
class DiamondTrap : public FragTrap, public ScavTrap {
    // Pas de using
};

DiamondTrap dt("Test");
dt.attack("enemy");  // ❌ ERREUR de compilation : ambiguë
```

### 2. Confondre les deux noms

```cpp
// ❌ FAUX
void whoAmI() {
    std::cout << _name << " and " << _name << std::endl;
    //           ^^^^^              ^^^^^ (même nom !)
}

// ✅ CORRECT
void whoAmI() {
    std::cout << _name << " and " << ClapTrap::_name << std::endl;
    //           ^^^^^              ^^^^^^^^^^^^^^^ (nom ClapTrap)
}
```

### 3. Ne pas initialiser ClapTrap avec suffixe

```cpp
// ❌ FAUX
DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name) {
    // ClapTrap::_name sera "Monster" au lieu de "Monster_clap_name"
}

// ✅ CORRECT
DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name") {
    // ClapTrap::_name sera "Monster_clap_name"
}
```

### 4. Oublier de copier les deux noms

```cpp
// ❌ FAUX - N'assigne qu'un seul nom
DiamondTrap& operator=(const DiamondTrap& other) {
    _name = other._name;  // Oublie ClapTrap::_name !
    return *this;
}

// ✅ CORRECT
DiamondTrap& operator=(const DiamondTrap& other) {
    _name = other._name;
    ClapTrap::_name = other.ClapTrap::_name;  // Les deux !
    return *this;
}
```

---

## ✅ Checklist de validation

- [ ] DiamondTrap hérite de FragTrap ET ScavTrap
- [ ] DiamondTrap a son propre attribut `_name`
- [ ] `using ScavTrap::attack` est présent
- [ ] whoAmI() affiche les deux noms
- [ ] ClapTrap::_name se termine par "_clap_name"
- [ ] Stats : HP=100, Energy=50, Damage=30
- [ ] attack() utilise celle de ScavTrap
- [ ] guardGate() fonctionne (de ScavTrap)
- [ ] highFivesGuys() fonctionne (de FragTrap)
- [ ] takeDamage() et beRepaired() fonctionnent
- [ ] Constructeurs appellent tous les parents
- [ ] Compilation sans erreur avec `-Wall -Wextra -Werror -std=c++98`

---

## 🎯 Objectif pédagogique

Cet exercice vous apprend à :

1. ✅ Utiliser l'**héritage multiple**
2. ✅ Comprendre le **Diamond Problem**
3. ✅ Résoudre les **ambiguïtés** avec `using`
4. ✅ Utiliser la **résolution de scope** (`::`)
5. ✅ Gérer **plusieurs noms** dans une hiérarchie
6. ✅ Combiner les **caractéristiques** de plusieurs classes
7. ✅ Maîtriser la **construction/destruction** en héritage multiple

---

## 📊 Tableau récapitulatif complet

| Robot | HP | Energy | Damage | Capacités spéciales |
|-------|-----|--------|--------|---------------------|
| **ClapTrap** | 10 | 10 | 0 | ❌ Aucune |
| **ScavTrap** | 100 | 50 | 20 | guardGate() |
| **FragTrap** | 100 | 100 | 30 | highFivesGuys() |
| **DiamondTrap** | 100 | 50 | 30 | guardGate() + highFivesGuys() + whoAmI() |

**DiamondTrap = Meilleur équilibre !**
- HP de FragTrap (résistant)
- Energy de ScavTrap (équilibré)
- Damage de FragTrap (le plus fort)
- Toutes les capacités spéciales

---

## 🔮 Pour aller plus loin

### Virtual Inheritance (C++98)

```cpp
// Solution propre au Diamond Problem
class ScavTrap : virtual public ClapTrap { };
class FragTrap : virtual public ClapTrap { };

// Résultat :
// - Une seule instance de ClapTrap dans DiamondTrap
// - Pas de duplication
// - Construction/destruction une seule fois
```

### Héritage multiple dans d'autres langages

- **Java** : Interdit (interfaces seulement)
- **C#** : Interdit (interfaces seulement)  
- **Python** : Autorisé (MRO = Method Resolution Order)
- **C++** : Autorisé mais complexe

---

## 📚 Vocabulaire

| Terme | Description |
|-------|-------------|
| **Héritage multiple** | Hériter de plusieurs classes |
| **Diamond Problem** | Ambiguïté avec ancêtre commun |
| **Virtual Inheritance** | Solution au Diamond Problem |
| **using** | Choisir quelle méthode utiliser |
| **Scope resolution (::)** | Spécifier quelle classe |
| **Ambiguïté** | Compilateur ne sait pas quoi choisir |

---

**Félicitations ! 🎉**

Vous avez terminé le module CPP03 et maîtrisez maintenant :
- ✅ L'héritage simple
- ✅ L'héritage multiple
- ✅ Le Diamond Problem
- ✅ La résolution d'ambiguïtés

**Module CPP03 : COMPLET ! 🚀**

L'héritage multiple est puissant mais complexe. Utilisez-le avec précaution en production !
