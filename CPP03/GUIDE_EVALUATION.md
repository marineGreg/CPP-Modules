cd# Guide d'Évaluation - CPP Module 03

## 📋 Vue d'ensemble du module

**Thème principal** : Héritage (Inheritance)

**Concepts clés** :
- Héritage simple
- Constructeurs et destructeurs dans l'héritage
- Redéfinition de méthodes (method overriding)
- Spécificateurs d'accès (`public`, `protected`, `private`)
- Héritage multiple
- Problème du diamant (Diamond Problem)

---

## 🎯 Exercise 00: Aaaaand... OPEN!

### 📖 Explication du programme

Implémente la classe de base `ClapTrap` : un robot de combat avec des points de vie, d'énergie et d'attaque.

**Attributs** :
```cpp
class ClapTrap {
private:
    std::string _name;
    unsigned int _hitPoints;      // Points de vie (10 par défaut)
    unsigned int _energyPoints;   // Points d'énergie (10 par défaut)
    unsigned int _attackDamage;   // Dégâts d'attaque (0 par défaut)
};
```

**Méthodes publiques** :
- `attack(const std::string& target)` : Attaque une cible (coûte 1 énergie)
- `takeDamage(unsigned int amount)` : Subit des dégâts
- `beRepaired(unsigned int amount)` : Se répare (coûte 1 énergie)

### 🔑 Points clés à comprendre

#### 1. **Logique des méthodes**

**Attack** :
```cpp
void ClapTrap::attack(const std::string& target) {
    if (_energyPoints == 0) {
        std::cout << _name << " has no energy to attack!" << std::endl;
        return;
    }
    if (_hitPoints == 0) {
        std::cout << _name << " is dead and cannot attack!" << std::endl;
        return;
    }
    _energyPoints--;
    std::cout << "ClapTrap " << _name << " attacks " << target 
              << ", causing " << _attackDamage << " points of damage!" << std::endl;
}
```

**TakeDamage** :
```cpp
void ClapTrap::takeDamage(unsigned int amount) {
    if (_hitPoints == 0) {
        std::cout << _name << " is already dead!" << std::endl;
        return;
    }
    if (amount >= _hitPoints) {
        _hitPoints = 0;
        std::cout << _name << " takes " << amount << " damage and dies!" << std::endl;
    } else {
        _hitPoints -= amount;
        std::cout << _name << " takes " << amount << " damage! (" 
                  << _hitPoints << " HP left)" << std::endl;
    }
}
```

**BeRepaired** :
```cpp
void ClapTrap::beRepaired(unsigned int amount) {
    if (_energyPoints == 0) {
        std::cout << _name << " has no energy to repair!" << std::endl;
        return;
    }
    if (_hitPoints == 0) {
        std::cout << _name << " is dead and cannot repair!" << std::endl;
        return;
    }
    _energyPoints--;
    _hitPoints += amount;
    std::cout << _name << " repairs itself for " << amount 
              << " HP! (" << _hitPoints << " HP total)" << std::endl;
}
```

#### 2. **Orthodox Canonical Form**

N'oublie pas d'implémenter :
- Constructeur par défaut
- Constructeur de copie
- Opérateur d'assignation
- Destructeur

**Constructeur avec paramètre** :
```cpp
ClapTrap::ClapTrap(std::string name) 
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap Name constructor called for " << _name << std::endl;
}
```

### 🧪 Tests à démontrer

```bash
cd ex00
make
./claptrap
```

Le main contient **4 tests** qui correspondent exactement au code :

**Test 1 : Construction et actions**
```cpp
ClapTrap clap("Clappy");
clap.attack("enemy");
clap.takeDamage(3);
clap.beRepaired(5);
```

**Sortie attendue** :
```
=== TEST 1: Construction et actions ===
ClapTrap Name constructor called for Clappy
ClapTrap Clappy attacks enemy, causing 0 points of damage!
ClapTrap Clappy took 3 points of damage! Remaining HP: 7
ClapTrap Clappy repairs itself by 5 points! Current HP: 12
```

**Ce que tu dois expliquer** :
- Le constructeur initialise : HP=10, Energy=10, Damage=0
- `attack()` coûte 1 énergie (il reste 9)
- `takeDamage(3)` réduit les HP de 10 à 7
- `beRepaired(5)` coûte 1 énergie et ajoute 5 HP (12 HP total)

**Test 2 : Constructeur de copie**
```cpp
ClapTrap copy(clap);
copy.attack("target");
```

**Sortie attendue** :
```
=== TEST 2: Constructeur de copie ===
ClapTrap Copy constructor called
ClapTrap Assignment operator called
ClapTrap Clappy attacks target, causing 0 points of damage!
```

**Ce que tu dois expliquer** :
- Le constructeur de copie délègue à l'opérateur d'assignation
- `copy` est une copie indépendante de `clap`
- Les deux objets peuvent agir séparément

**Test 3 : Épuisement d'énergie**
```cpp
ClapTrap tired("Exhausted");
for (int i = 0; i < 12; i++)
    tired.attack("dummy");
```

**Sortie attendue** :
```
=== TEST 3: Épuisement d'énergie ===
ClapTrap Name constructor called for Exhausted
ClapTrap Exhausted attacks dummy, causing 0 points of damage!
[... 9 fois de plus ...]
ClapTrap Exhausted is out of energy and cannot attack!
ClapTrap Exhausted is out of energy and cannot attack!
```

**Ce que tu dois expliquer** :
- ClapTrap commence avec 10 points d'énergie
- Chaque attaque coûte 1 énergie
- Après 10 attaques, plus d'énergie
- Les attaques 11 et 12 échouent

**Test 4 : Mort par dégâts**
```cpp
ClapTrap victim("Victim");
victim.takeDamage(15);
victim.attack("ghost");
```

**Sortie attendue** :
```
=== TEST 4: Mort par dégâts ===
ClapTrap Name constructor called for Victim
ClapTrap Victim took 15 points of damage! Remaining HP: 0
ClapTrap Victim is dead and cannot attack!
```

**Ce que tu dois expliquer** :
- ClapTrap commence avec 10 HP
- `takeDamage(15)` met les HP à 0 (pas négatif car `unsigned int`)
- Un ClapTrap mort ne peut plus agir

### ⚠️ Erreurs courantes

1. **Ne pas vérifier si le robot est mort** avant d'agir
2. **Ne pas vérifier l'énergie** avant d'attaquer/réparer
3. **Underflow** : `_hitPoints` devient négatif (utilise `unsigned int`)
4. **Ne pas décrémenter l'énergie** après une action
5. **Oublier les messages constructeur/destructeur**

### 💡 Conseils de présentation

- Montre que tu gères les cas limites (mort, plus d'énergie)
- Explique le choix de `unsigned int` pour éviter les valeurs négatives
- Discute de l'ordre d'exécution des vérifications (mort > énergie > action)

---

## 🎯 Exercise 01: Serena, my love!

### 📖 Explication du programme

Implémente `ScavTrap`, une classe qui **hérite** de `ClapTrap`.

**Différences avec ClapTrap** :
- HP : `100` (au lieu de 10)
- Energy : `50` (au lieu de 10)
- Attack Damage : `20` (au lieu de 0)
- Méthode spéciale : `guardGate()`
- Message d'attaque différent

### 🔑 Points clés à comprendre

#### 1. **Syntaxe de l'héritage**

```cpp
class ScavTrap : public ClapTrap {
public:
    ScavTrap();
    ScavTrap(std::string name);
    ScavTrap(const ScavTrap& other);
    ScavTrap& operator=(const ScavTrap& other);
    ~ScavTrap();

    void attack(const std::string& target);  // Redéfinition
    void guardGate();                         // Nouvelle méthode
};
```

**`public` héritage** :
- Les membres `public` de `ClapTrap` restent `public` dans `ScavTrap`
- Les membres `protected` de `ClapTrap` restent `protected` dans `ScavTrap`

#### 2. **Constructeur de la classe dérivée**

```cpp
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "ScavTrap Name constructor called for " << name << std::endl;
}
```

**Ordre d'exécution** :
1. Constructeur de `ClapTrap` (classe de base)
2. Initialisation des attributs de `ScavTrap`
3. Corps du constructeur de `ScavTrap`

#### 3. **Destructeur de la classe dérivée**

```cpp
ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap Destructor called" << std::endl;
}
```

**Ordre d'exécution** :
1. Corps du destructeur de `ScavTrap`
2. Destructeur de `ClapTrap` (automatique)

**Sortie attendue** :
```
ScavTrap Destructor called
ClapTrap Destructor called for X
```

#### 4. **Redéfinition de méthode (Overriding)**

```cpp
void ScavTrap::attack(const std::string& target) {
    if (_energyPoints == 0 || _hitPoints == 0) {
        std::cout << "ScavTrap " << _name << " can't attack!" << std::endl;
        return;
    }
    _energyPoints--;
    std::cout << "ScavTrap " << _name << " savagely attacks " << target 
              << ", causing " << _attackDamage << " points of damage!" << std::endl;
}
```

**Important** : 
- Ce n'est **pas** du polymorphisme (pas de `virtual`)
- `ScavTrap::attack()` **remplace** `ClapTrap::attack()` pour les objets `ScavTrap`

#### 5. **Nouvelle méthode : guardGate()**

```cpp
void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << _name << " is now in Gate keeper mode." << std::endl;
}
```

### 🧪 Tests à démontrer

```bash
cd ex01
make
./claptrap
```

**Test 1 : Construction**
```cpp
ScavTrap scav("Guardian");
// Sortie:
// ClapTrap Guardian is born!
// ScavTrap Guardian is constructed!
```

**Test 2 : Attaque différente**
```cpp
ClapTrap clap("Basic");
ScavTrap scav("Advanced");
clap.attack("target");  // Message ClapTrap
scav.attack("target");  // Message ScavTrap (différent)
```

**Test 3 : Capacité spéciale**
```cpp
ScavTrap scav("Gatekeeper");
scav.guardGate();
```

**Test 4 : Endurance (50 energy)**
```cpp
ScavTrap energetic("Energetic");
for (int i = 0; i < 52; i++) {
    energetic.attack("fly");  // Fonctionne 50 fois, puis échec
}
```

**Test 5 : Résistance (100 HP)**
```cpp
ScavTrap tank("Tank");
tank.takeDamage(90);    // Survit
tank.beRepaired(10);
tank.takeDamage(20);    // Meurt
```

**Test 6 : Destruction**
```cpp
{
    ScavTrap scav("Temporary");
}
// Sortie:
// ScavTrap Temporary is destructed!
// ClapTrap Temporary is destructed!
```

### ⚠️ Erreurs courantes

1. **Ne pas appeler le constructeur de base** : `ScavTrap() : ClapTrap() { ... }`
2. **Accéder aux membres privés de ClapTrap** → Utilise `protected` ou des getters
3. **Oublier de redéfinir `attack()`** → Le message ne change pas
4. **Mauvais ordre des destructeurs** dans les messages

### 💡 Conseils de présentation

- Explique l'ordre constructeur/destructeur avec un schéma
- Montre la différence entre `ClapTrap::attack()` et `ScavTrap::attack()`
- Discute du choix `protected` vs `private` pour les attributs de `ClapTrap`
- Compare les stats : HP, Energy, Damage

---

## 🎯 Exercise 02: Repetitive work

### 📖 Explication du programme

Implémente `FragTrap`, une **autre** classe héritant de `ClapTrap`.

**Différences** :
- HP : `100`
- Energy : `100` (plus que ScavTrap !)
- Attack Damage : `30` (plus que ScavTrap !)
- Méthode spéciale : `highFivesGuys()`

### 🔑 Points clés à comprendre

#### 1. **Structure similaire à ScavTrap**

```cpp
class FragTrap : public ClapTrap {
public:
    FragTrap();
    FragTrap(std::string name);
    FragTrap(const FragTrap& other);
    FragTrap& operator=(const FragTrap& other);
    ~FragTrap();

    void highFivesGuys(void);  // Nouvelle méthode
};
```

**Pas besoin de redéfinir `attack()`** :
- On peut garder le message de `ClapTrap`
- Ou créer un message spécifique `FragTrap`

#### 2. **Comparaison des trois classes**

| Classe | HP | Energy | Attack Damage | Méthode spéciale |
|--------|-----|--------|---------------|------------------|
| ClapTrap | 10 | 10 | 0 | - |
| ScavTrap | 100 | 50 | 20 | `guardGate()` |
| FragTrap | 100 | 100 | 30 | `highFivesGuys()` |

#### 3. **Méthode highFivesGuys()**

```cpp
void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << _name << " says: \"High five, anyone?\"" << std::endl;
}
```

### 🧪 Tests à démontrer

```bash
cd ex02
make
./claptrap
```

**Test 1 : Construction des 3 types**
```cpp
ClapTrap clap("Basic");
ScavTrap scav("Guardian");
FragTrap frag("Destroyer");
```

**Test 2 : Comparaison des attaques**
```cpp
clap.attack("target");  // 0 dégâts
scav.attack("target");  // 20 dégâts
frag.attack("target");  // 30 dégâts
```

**Test 3 : Capacités spéciales**
```cpp
scav.guardGate();
frag.highFivesGuys();
```

**Test 4 : Endurance (100 energy)**
```cpp
FragTrap energyFrag("EnergyFrag");
for (int i = 0; i < 102; i++) {
    energyFrag.attack("dummy");  // Fonctionne 100 fois
}
```

**Test 5 : Comparaison HP**
```cpp
ClapTrap weakClap("Weak");
FragTrap strongFrag("Strong");
weakClap.takeDamage(10);   // Meurt
strongFrag.takeDamage(90); // Survit
```

### ⚠️ Erreurs courantes

1. **Confondre les stats de ScavTrap et FragTrap**
2. **Dupliquer du code** au lieu de factoriser dans ClapTrap
3. **Ne pas tester les 3 types ensemble** pour montrer les différences

### 💡 Conseils de présentation

- Compare les 3 classes côte à côte
- Montre que FragTrap est le plus résistant ET le plus puissant
- Explique pourquoi on n'utilise pas de polymorphisme ici (pas de `virtual`)

---

## 🎯 Exercise 03: Now it's weird!

### 📖 Explication du programme

Implémente `DiamondTrap`, qui hérite de **ScavTrap ET FragTrap** (héritage multiple).

**Le problème du diamant** :
```
       ClapTrap
       /      \
  ScavTrap  FragTrap
       \      /
     DiamondTrap
```

`DiamondTrap` hérite indirectement de `ClapTrap` **deux fois** → Ambiguïté !

### 🔑 Points clés à comprendre

#### 1. **Héritage multiple**

```cpp
class DiamondTrap : public ScavTrap, public FragTrap {
private:
    std::string _name;  // Son propre nom (ClapTrap aura name + "_clap_name")
public:
    DiamondTrap();
    DiamondTrap(std::string name);
    DiamondTrap(const DiamondTrap& other);
    DiamondTrap& operator=(const DiamondTrap& other);
    ~DiamondTrap();

    void whoAmI();  // Affiche les deux noms
    using ScavTrap::attack;  // Utilise l'attaque de ScavTrap
};
```

#### 2. **Résolution de l'ambiguïté**

**Problème** : `DiamondTrap` a deux `ClapTrap` en lui !

**Solutions** :

**A) Héritage virtuel** (Recommandé mais complexe) :
```cpp
class ScavTrap : virtual public ClapTrap { ... };
class FragTrap : virtual public ClapTrap { ... };
```
→ Une seule instance de `ClapTrap` partagée

**B) Sans héritage virtuel** (Plus simple pour 42) :
- Initialiser explicitement les deux classes parentes
- Gérer les attributs dupliqués

#### 3. **Constructeur de DiamondTrap**

```cpp
DiamondTrap::DiamondTrap(std::string name) 
    : ClapTrap(name + "_clap_name"), FragTrap(), ScavTrap() {
    this->_name = name;
    this->_hitPoints = 100;      // Provient de FragTrap
    this->_energyPoints = 50;    // Provient de ScavTrap
    this->_attackDamage = 30;    // Provient de FragTrap
    std::cout << "DiamondTrap Name constructor called for " << name << std::endl;
}
```

**Stats de DiamondTrap** :
- HP : de `FragTrap` (100)
- Energy : de `ScavTrap` (50)
- Attack Damage : de `FragTrap` (30)
- Name : propre nom + nom ClapTrap suffixé

#### 4. **Méthode whoAmI()**

```cpp
void DiamondTrap::whoAmI() {
    std::cout << "I am DiamondTrap: " << this->_name 
              << " and my ClapTrap name is: " << ClapTrap::_name << std::endl;
}
```

#### 5. **Using ScavTrap::attack**

```cpp
class DiamondTrap : public ScavTrap, public FragTrap {
public:
    using ScavTrap::attack;  // Résout l'ambiguïté attack()
};
```

Sans cette ligne, appeler `diamond.attack()` serait ambigu (ScavTrap ou FragTrap ?).

### 🧪 Tests à démontrer

```bash
cd ex03
make
./claptrap
```

**Test 1 : Construction**
```cpp
DiamondTrap diamond("Diamond");
// Sortie:
// ClapTrap Name constructor called for Diamond_clap_name
// FragTrap Default constructor called
// ScavTrap Default constructor called
// DiamondTrap Name constructor called for Diamond
```

**Test 2 : whoAmI()**
```cpp
DiamondTrap diamond("Ultron");
diamond.whoAmI();
// Sortie: I am DiamondTrap: Ultron and my ClapTrap name is: Ultron_clap_name
```

**Test 3 : Attack de ScavTrap**
```cpp
diamond.attack("enemy");  // Utilise ScavTrap::attack()
```

**Test 4 : Capacités héritées**
```cpp
diamond.guardGate();       // De ScavTrap
diamond.highFivesGuys();   // De FragTrap
diamond.takeDamage(30);    // De ClapTrap
diamond.beRepaired(10);    // De ClapTrap
```

**Test 5 : Stats combinées**
```cpp
DiamondTrap ultimate("Ultimate");
// HP: 100 (FragTrap)
// Energy: 50 (ScavTrap)
// Damage: 30 (FragTrap)
ultimate.attack("target");  // 30 dégâts, message ScavTrap
```

**Test 6 : Destruction**
```cpp
{
    DiamondTrap diamond("Temp");
}
// Sortie (ordre inverse de construction):
// DiamondTrap Destructor called
// ScavTrap Destructor called
// FragTrap Destructor called
// ClapTrap Destructor called for Temp_clap_name
```

### ⚠️ Erreurs courantes

1. **Ne pas gérer le double héritage de ClapTrap**
2. **Ne pas utiliser `using ScavTrap::attack;`** → Ambiguïté
3. **Mauvais nom ClapTrap** (doit avoir le suffixe `_clap_name`)
4. **Mauvaises stats** (mix HP/Energy/Damage de FragTrap et ScavTrap)
5. **Ordre des destructeurs incorrect**

### 💡 Conseils de présentation

- **Dessine le diagramme du diamant** pour expliquer le problème
- Explique pourquoi on a deux `ClapTrap` (ou un seul avec `virtual`)
- Montre comment `using` résout l'ambiguïté
- Compare avec/sans héritage virtuel
- Discute des stats : pourquoi HP de FragTrap et Energy de ScavTrap ?

---

## 🎁 Bonus : Questions anticipées

### Q1 : "Qu'est-ce que le Diamond Problem ?"

**Réponse** :
```
       A
      / \
     B   C
      \ /
       D
```

- `D` hérite de `B` et `C`
- `B` et `C` héritent tous deux de `A`
- **Problème** : `D` a **deux copies** de `A` !

**Conséquences** :
- Ambiguïté : `d.methodFromA()` → quelle version ? (via B ou C ?)
- Duplication : Attributs de A présents deux fois

**Solution** : Héritage virtuel
```cpp
class B : virtual public A { };
class C : virtual public A { };
```
→ Une seule instance de `A` partagée

### Q2 : "Quelle est la différence entre `protected` et `private` ?"

**Réponse** :

| Accès | `private` | `protected` | `public` |
|-------|-----------|-------------|----------|
| Même classe | ✅ Oui | ✅ Oui | ✅ Oui |
| Classe dérivée | ❌ Non | ✅ Oui | ✅ Oui |
| Extérieur | ❌ Non | ❌ Non | ✅ Oui |

**Exemple** :
```cpp
class ClapTrap {
private:
    std::string _name;  // Inaccessible dans ScavTrap
protected:
    int _hitPoints;     // Accessible dans ScavTrap
public:
    void attack();      // Accessible partout
};
```

**Conseil** : Utilise `protected` pour les attributs dont les classes dérivées ont besoin.

### Q3 : "Pourquoi l'ordre constructeur/destructeur est-il important ?"

**Réponse** :

**Construction** : De la **base** vers le **dérivé**
```
ClapTrap → ScavTrap → DiamondTrap
```

**Destruction** : Du **dérivé** vers la **base** (ordre inverse)
```
DiamondTrap → ScavTrap → ClapTrap
```

**Raison** :
- Le constructeur dérivé peut utiliser les membres de la base
- Le destructeur dérivé doit nettoyer avant que la base ne soit détruite

### Q4 : "C'est quoi l'overriding vs overloading ?"

**Réponse** :

**Overriding** (Redéfinition) :
- Même signature dans classe dérivée
- Remplace la méthode de la classe de base
- Exemple : `ScavTrap::attack()` vs `ClapTrap::attack()`

**Overloading** (Surcharge) :
- Même nom, signatures différentes
- Dans la même classe ou classes différentes
- Exemple : `Fixed::Fixed(int)` vs `Fixed::Fixed(float)`

### Q5 : "Pourquoi pas de `virtual` dans ce module ?"

**Réponse** :
- Le module 03 se concentre sur l'**héritage de base**
- Le `virtual` (polymorphisme runtime) est dans le **module 04**

**Différence** :
```cpp
// Sans virtual (module 03)
ClapTrap* ptr = new ScavTrap("Scav");
ptr->attack("target");  // Appelle ClapTrap::attack()

// Avec virtual (module 04)
class ClapTrap {
    virtual void attack(...);
};
ClapTrap* ptr = new ScavTrap("Scav");
ptr->attack("target");  // Appelle ScavTrap::attack() ✅
```

---

## 📝 Checklist finale

Avant l'évaluation, assure-toi de pouvoir :

### Compétences techniques
- [ ] Implémenter l'héritage simple (`class B : public A`)
- [ ] Appeler le constructeur de base dans la liste d'initialisation
- [ ] Redéfinir une méthode (overriding)
- [ ] Utiliser `protected` pour partager des attributs avec les dérivées
- [ ] Implémenter l'héritage multiple
- [ ] Résoudre l'ambiguïté avec `using`

### Concepts théoriques
- [ ] Expliquer le Diamond Problem
- [ ] Expliquer l'ordre constructeur/destructeur
- [ ] Expliquer `private` vs `protected` vs `public`
- [ ] Expliquer overriding vs overloading
- [ ] Expliquer l'héritage virtuel (au moins conceptuellement)

### Tests pratiques
- [ ] Compiler tous les exercices sans warnings
- [ ] Démontrer les différences entre ClapTrap/ScavTrap/FragTrap
- [ ] Montrer les deux noms de DiamondTrap
- [ ] Vérifier l'ordre des messages constructeur/destructeur
- [ ] Tester les cas limites (mort, énergie épuisée)

### Makefile
- [ ] `make` compile tout
- [ ] `make clean` supprime les `.o`
- [ ] `make fclean` supprime les `.o` et l'exécutable
- [ ] `make re` fait un clean + recompile
- [ ] Flags : `-Wall -Wextra -Werror -std=c++98`

---

## 🚀 Conseils généraux de présentation

1. **Dessine des schémas** : L'héritage est visuel, un diagramme UML aide énormément
2. **Compare les classes** : Montre les stats et différences côte à côte
3. **Trace l'exécution** : Explique l'ordre constructeur/destructeur avec un exemple concret
4. **Anticipe le module 04** : Mentionne que le `virtual` arrive bientôt
5. **Reste confiant** : L'héritage peut sembler complexe, mais tu maîtrises les bases !

Bonne chance ! 🍀
