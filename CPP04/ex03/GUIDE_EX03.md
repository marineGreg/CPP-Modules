# Guide CPP04 - Exercise 03 : Interfaces & Materia

## 📋 Objectif de l'exercice

Implémenter un système complexe d'**interfaces** en C++ avec :
- Interfaces pures (`AMateria`, `ICharacter`, `IMateriaSource`)
- Pattern **Prototype** (méthode `clone()`)
- Gestion avancée de la mémoire (éviter les leaks avec `unequip`)
- Système d'inventaire avec slots limités

## 🎯 Concepts clés

### 1. Interface en C++

Une **interface** est une classe abstraite avec **TOUTES** ses méthodes virtuelles pures :

```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual std::string const & getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

**Caractéristiques** :
- Aucune implémentation
- Pas d'attributs (sauf exceptions)
- Définit un **contrat** que les classes concrètes doivent respecter

### 2. Pattern Prototype (clone())

Le **pattern Prototype** permet de créer des copies d'objets sans connaître leur type exact :

```cpp
class AMateria {
public:
    virtual AMateria* clone() const = 0; // Retourne une copie de l'objet
};

class Ice : public AMateria {
public:
    AMateria* clone() const {
        return new Ice(*this); // Copie de soi-même
    }
};
```

**Usage** :
```cpp
AMateria* template = new Ice();
AMateria* copy = template->clone(); // On ne sait pas que c'est un Ice, mais on obtient une copie
```

### 3. Gestion de la mémoire avec unequip

**Problème** :
```cpp
character->unequip(0); // Que faire de la Materia ?
```

**Solutions possibles** :
1. ❌ `delete` directement → Peut causer des double-free si utilisée ailleurs
2. ✅ **Mettre sur le "floor"** (stockage temporaire) → Nettoyage dans le destructeur

## 📁 Structure de l'exercice

```
ex03/
├── AMateria.hpp        # Classe abstraite pour toutes les materias
├── AMateria.cpp
├── Ice.hpp             # Materia concrète : Ice
├── Ice.cpp
├── Cure.hpp            # Materia concrète : Cure
├── Cure.cpp
├── ICharacter.hpp      # Interface pour les personnages
├── Character.hpp       # Implémentation concrète de ICharacter
├── Character.cpp
├── IMateriaSource.hpp  # Interface pour la source de materias
├── MateriaSource.hpp   # Implémentation concrète de IMateriaSource
├── MateriaSource.cpp
├── main.cpp
└── Makefile
```

## 🔧 Implémentation

### 1. AMateria (Classe abstraite de base)

#### AMateria.hpp

```cpp
class ICharacter; // Forward declaration

class AMateria {
protected:
    std::string _type;

public:
    AMateria();
    AMateria(std::string const & type);
    AMateria(const AMateria& other);
    AMateria& operator=(const AMateria& other);
    virtual ~AMateria();

    std::string const & getType() const;
    
    virtual AMateria* clone() const = 0; // Pattern Prototype
    virtual void use(ICharacter& target);
};
```

**Points clés** :
- `clone()` est **virtuelle pure** → chaque Materia doit l'implémenter
- `use()` a une implémentation par défaut (peut être override)
- `_type` est `protected` pour être accessible aux classes dérivées

#### AMateria.cpp

```cpp
AMateria& AMateria::operator=(const AMateria& other) {
    if (this != &other) {
        // On ne copie PAS le type selon le sujet 42
        (void)other;
    }
    return *this;
}
```

⚠️ **Important** : Le type n'est **jamais** copié dans l'opérateur d'assignation (requis par le sujet).

### 2. Ice et Cure (Materias concrètes)

#### Ice.cpp

```cpp
Ice::Ice() : AMateria("ice") {
}

AMateria* Ice::clone() const {
    return new Ice(*this); // Nouvelle allocation + copie
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
```

#### Cure.cpp

```cpp
Cure::Cure() : AMateria("cure") {
}

AMateria* Cure::clone() const {
    return new Cure(*this);
}

void Cure::use(ICharacter& target) {
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
```

**Pattern Prototype en action** :
- Chaque classe concrète sait comment se copier elle-même
- On peut créer des copies sans connaître le type exact

### 3. ICharacter et Character

#### ICharacter.hpp (Interface)

```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}
    
    virtual std::string const & getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

#### Character.hpp

```cpp
class Character : public ICharacter {
private:
    std::string _name;
    AMateria* _inventory[4];   // Max 4 Materias
    AMateria* _floor[100];     // Stockage des Materias unequip
    int _floorCount;

public:
    Character();
    Character(std::string const & name);
    Character(const Character& other);
    Character& operator=(const Character& other);
    ~Character();

    std::string const & getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};
```

**Attributs clés** :
- `_inventory[4]` : 4 slots maximum
- `_floor[100]` : Stockage temporaire pour éviter les leaks lors de `unequip`

#### Character.cpp - Méthodes critiques

**equip()** :
```cpp
void Character::equip(AMateria* m) {
    if (!m) return;
    
    for (int i = 0; i < 4; i++) {
        if (!_inventory[i]) {
            _inventory[i] = m;
            return;
        }
    }
    
    // Inventaire plein : on met sur le floor
    if (_floorCount < 100) {
        _floor[_floorCount] = m;
        _floorCount++;
    } else {
        delete m; // Floor plein aussi
    }
}
```

**unequip()** :
```cpp
void Character::unequip(int idx) {
    if (idx < 0 || idx >= 4 || !_inventory[idx])
        return;
    
    // On met sur le floor au lieu de delete
    if (_floorCount < 100) {
        _floor[_floorCount] = _inventory[idx];
        _floorCount++;
        _inventory[idx] = NULL;
    }
}
```

⚠️ **Crucial** : `unequip` ne `delete` **JAMAIS** la Materia, sinon memory leak ou double-free.

**use()** :
```cpp
void Character::use(int idx, ICharacter& target) {
    if (idx < 0 || idx >= 4 || !_inventory[idx])
        return;
    
    _inventory[idx]->use(target); // Polymorphisme
}
```

**Destructeur** :
```cpp
Character::~Character() {
    // Nettoyage de l'inventaire
    for (int i = 0; i < 4; i++) {
        if (_inventory[i])
            delete _inventory[i];
    }
    
    // Nettoyage du floor
    for (int i = 0; i < _floorCount; i++) {
        if (_floor[i])
            delete _floor[i];
    }
}
```

### 4. IMateriaSource et MateriaSource

#### IMateriaSource.hpp (Interface)

```cpp
class IMateriaSource {
public:
    virtual ~IMateriaSource() {}
    
    virtual void learnMateria(AMateria*) = 0;
    virtual AMateria* createMateria(std::string const & type) = 0;
};
```

#### MateriaSource.cpp

**learnMateria()** :
```cpp
void MateriaSource::learnMateria(AMateria* m) {
    if (!m) return;
    
    for (int i = 0; i < 4; i++) {
        if (!_templates[i]) {
            _templates[i] = m; // Stocke le template
            return;
        }
    }
    
    delete m; // Source pleine, évite le leak
}
```

**createMateria()** :
```cpp
AMateria* MateriaSource::createMateria(std::string const & type) {
    for (int i = 0; i < 4; i++) {
        if (_templates[i] && _templates[i]->getType() == type) {
            return _templates[i]->clone(); // Utilise le pattern Prototype
        }
    }
    return NULL; // Type inconnu
}
```

**Pattern utilisé** :
1. On "apprend" une Materia (template)
2. On peut ensuite en créer des copies à la demande via `clone()`

## 🧪 Tests dans main.cpp

### Test 1 : Main du sujet

```cpp
IMateriaSource* src = new MateriaSource();
src->learnMateria(new Ice());
src->learnMateria(new Cure());

ICharacter* me = new Character("me");

AMateria* tmp;
tmp = src->createMateria("ice");
me->equip(tmp);
tmp = src->createMateria("cure");
me->equip(tmp);

ICharacter* bob = new Character("bob");

me->use(0, *bob); // * shoots an ice bolt at bob *
me->use(1, *bob); // * heals bob's wounds *

delete bob;
delete me;
delete src;
```

### Test 2 : Deep Copy

```cpp
Character* original = new Character("Hero");
original->equip(new Ice());
original->equip(new Cure());

Character* copy = new Character(*original);

// Les inventaires sont indépendants
original->use(0, dummy); // Ice
copy->use(0, dummy);     // Ice (copie)

delete original; // Pas de crash
delete copy;     // Pas de crash
```

### Test 3 : Inventaire plein

```cpp
Character* hero = new Character("Hero");
hero->equip(new Ice());
hero->equip(new Cure());
hero->equip(new Ice());
hero->equip(new Cure());
hero->equip(new Ice()); // "Inventory is full! Materia dropped on the floor."
```

### Test 4 : Unequip

```cpp
hero->equip(new Ice());
hero->use(0, target);  // Ice
hero->unequip(0);      // Retire sans delete
hero->use(0, target);  // "No materia in slot 0!"
```

### Test 5 : Type inconnu

```cpp
IMateriaSource* src = new MateriaSource();
src->learnMateria(new Ice());

AMateria* tmp = src->createMateria("cure"); // Pas appris
// tmp == NULL
```

## 🎓 Points clés pour l'évaluation

### Question 1 : "Quelle est la différence entre une classe abstraite et une interface ?"

**Réponse** :
- **Classe abstraite** : Peut avoir des méthodes concrètes ET des méthodes pures
  - Exemple : `AMateria` (a `getType()` concrète et `clone()` pure)
- **Interface** : TOUTES les méthodes sont pures
  - Exemple : `ICharacter`, `IMateriaSource`

### Question 2 : "Pourquoi utiliser clone() au lieu d'un constructeur de copie ?"

**Réponse** :
- **Pattern Prototype** : On peut copier un objet sans connaître son type exact
- `AMateria* copy = original->clone();` fonctionne même si on ne sait pas si c'est un Ice ou Cure
- Très utile pour `MateriaSource::createMateria()`

### Question 3 : "Pourquoi unequip() ne fait pas delete ?"

**Réponse** :
- On ne sait pas si quelqu'un d'autre a une référence vers cette Materia
- Si on `delete`, on risque un **double-free** ou un **use-after-free**
- Solution : stocker sur le "floor" et nettoyer dans le destructeur

### Question 4 : "Que se passe-t-il si on appelle use() sur un slot vide ?"

**Réponse** :
```cpp
if (!_inventory[idx]) {
    std::cout << "No materia in slot " << idx << "!" << std::endl;
    return;
}
```
Rien ne crash, on affiche juste un message.

### Question 5 : "Pourquoi le type n'est pas copié dans operator= d'AMateria ?"

**Réponse** :
- Le sujet 42 l'exige
- Conceptuellement : une fois qu'un Ice est créé, il reste un Ice
- Assigner un Cure à un Ice ne change pas le type de l'Ice

## 🔄 Diagramme de classes

```
         ┌─────────────┐
         │  AMateria   │ (Abstraite)
         │  - _type    │
         │  + clone()* │
         │  + use()    │
         └──────┬──────┘
                │
        ┌───────┴───────┐
        │               │
   ┌────▼───┐      ┌───▼────┐
   │  Ice   │      │  Cure  │
   └────────┘      └────────┘

   ┌──────────────┐
   │ ICharacter   │ (Interface)
   │  + getName() │
   │  + equip()   │
   │  + unequip() │
   │  + use()     │
   └──────┬───────┘
          │
    ┌─────▼──────┐
    │ Character  │
    │ - _name    │
    │ - _inv[4]  │
    │ - _floor   │
    └────────────┘

   ┌─────────────────┐
   │ IMateriaSource  │ (Interface)
   │ + learnMateria()│
   │ + createMateria│
   └───────┬─────────┘
           │
    ┌──────▼──────┐
    │MateriaSource│
    │ - _templ[4] │
    └─────────────┘
```

## ⚠️ Pièges et erreurs courantes

1. **Delete dans unequip()** → Double-free
2. **Pas de floor** → Memory leak avec unequip
3. **Oublier clone() dans createMateria()** → Toutes les Materias partagent la même instance
4. **Ne pas vérifier NULL** → Segfault
5. **Oublier le destructeur virtuel dans les interfaces** → Memory leak

## ✅ Points de vérification

- [ ] `AMateria::clone()` est virtuelle pure
- [ ] `Ice` et `Cure` implémentent `clone()` correctement
- [ ] `Character::unequip()` ne fait PAS `delete`
- [ ] Le destructeur de `Character` nettoie l'inventaire ET le floor
- [ ] `MateriaSource::createMateria()` utilise `clone()`
- [ ] Pas de memory leak (tester avec `valgrind`)
- [ ] Les tests de deep copy fonctionnent
- [ ] Les interfaces (`I*`) n'ont que des méthodes virtuelles pures

## 📚 Patterns utilisés

1. **Interface Pattern** : `ICharacter`, `IMateriaSource`
2. **Prototype Pattern** : `clone()`
3. **Factory Pattern** : `MateriaSource::createMateria()`

---

**Résumé** : Cet exercice combine plusieurs concepts avancés de C++ (interfaces, patterns, gestion mémoire) pour créer un système flexible et extensible. C'est l'exercice le plus complexe du module CPP04. 🧙‍♂️✨
