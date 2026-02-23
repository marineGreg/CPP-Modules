# Guide CPP04 - Exercise 02 : Classes Abstraites

## 📋 Objectif de l'exercice

Comprendre et implémenter les **classes abstraites** en C++ :
- Fonctions virtuelles pures (`= 0`)
- Rendre une classe non-instanciable
- Forcer les classes dérivées à implémenter certaines méthodes

## 🎯 Concepts clés

### 1. Qu'est-ce qu'une classe abstraite ?

Une **classe abstraite** est une classe qui contient au moins une **fonction virtuelle pure** et qui **ne peut pas être instanciée** directement.

```cpp
class Animal {
public:
    virtual void makeSound() const = 0; // Fonction virtuelle pure
};

// INTERDIT (ne compile pas) :
Animal animal; // Erreur : cannot declare variable 'animal' to be of abstract type 'Animal'

// AUTORISÉ :
Animal* ptr = new Dog(); // Pointeur vers une classe dérivée concrète
```

### 2. Fonction virtuelle pure

Syntaxe : `virtual void makeSound() const = 0;`

**Signification** :
- `virtual` : Utilise le polymorphisme
- `= 0` : Pas d'implémentation dans la classe de base
- **Force** les classes dérivées à implémenter cette méthode

### 3. Pourquoi rendre Animal abstraite ?

**Raison conceptuelle** :
- Un "Animal" générique n'existe pas dans la réalité
- Seuls les animaux **concrets** (Dog, Cat, etc.) existent
- On veut **forcer** chaque animal à avoir son propre son

**Raison technique** :
- Évite les oublis : chaque classe dérivée **doit** implémenter `makeSound()`
- Garantit que tous les animaux ont un comportement spécifique

## 📁 Structure de l'exercice

```
ex02/
├── Animal.hpp          # Animal ABSTRAIT (makeSound = 0)
├── Animal.cpp          # Pas d'implémentation de makeSound
├── Dog.hpp             # Dog avec Brain* (comme ex01)
├── Dog.cpp
├── Cat.hpp             # Cat avec Brain* (comme ex01)
├── Cat.cpp
├── Brain.hpp           # Brain (comme ex01)
├── Brain.cpp
├── WrongAnimal.hpp
├── WrongAnimal.cpp
├── WrongCat.hpp
├── WrongCat.cpp
├── main.cpp            # Tests (sans instanciation directe d'Animal)
└── Makefile
```

## 🔧 Implémentation

### Animal.hpp - La modification clé

**AVANT (ex01)** :
```cpp
class Animal {
public:
    virtual void makeSound() const;
};
```

**APRÈS (ex02)** :
```cpp
class Animal {
public:
    virtual void makeSound() const = 0; // Fonction virtuelle pure
};
```

### Animal.cpp - Pas d'implémentation de makeSound

```cpp
#include "Animal.hpp"

Animal::Animal() : type("Animal") {
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const Animal& other) {
    std::cout << "Animal copy constructor called" << std::endl;
    *this = other;
}

Animal& Animal::operator=(const Animal& other) {
    std::cout << "Animal assignment operator called" << std::endl;
    if (this != &other)
        this->type = other.type;
    return *this;
}

Animal::~Animal() {
    std::cout << "Animal destructor called" << std::endl;
}

// makeSound() n'est PAS défini ici car c'est une fonction virtuelle pure

std::string Animal::getType() const {
    return this->type;
}
```

⚠️ **Point important** : On garde les constructeurs et le destructeur car les classes dérivées en ont besoin.

### Dog.cpp et Cat.cpp (inchangés depuis ex01)

```cpp
void Dog::makeSound() const {
    std::cout << "Woooof !" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Meoowww !" << std::endl;
}
```

Les classes dérivées **doivent** implémenter `makeSound()` sinon elles deviennent aussi abstraites.

## 🧪 Tests dans main.cpp

### Test 1 : Tableau d'animaux (fonctionne toujours)

```cpp
const int count = 4;
Animal* animals[count];

for (int i = 0; i < count; i++) {
    if (i < count / 2)
        animals[i] = new Dog(); // OK : Dog est concrète
    else
        animals[i] = new Cat(); // OK : Cat est concrète
}

for (int i = 0; i < count; i++) {
    delete animals[i];
}
```

### Test 2 : Deep Copy Test (fonctionne toujours)

```cpp
Dog basic;
{
    Dog tmp = basic;
}
std::cout << "Basic dog is still alive!" << std::endl;
```

### Test 3 : Ce qui ne compile PAS

Si on décommente ces lignes, la compilation échoue :

```cpp
// Animal animal; // ERREUR : cannot declare variable 'animal' to be of abstract type 'Animal'
// Animal* ptr = new Animal(); // ERREUR : invalid new-expression of abstract class type 'Animal'
```

## 🎓 Points clés pour l'évaluation

### Question 1 : "Quelle est la différence entre ex01 et ex02 ?"

**Réponse** :
- **ex01** : `Animal` peut être instanciée directement (`new Animal()`)
- **ex02** : `Animal` est **abstraite**, on ne peut créer que des `Dog` ou `Cat`
- **Code changé** : `virtual void makeSound() const;` → `virtual void makeSound() const = 0;`

### Question 2 : "Pourquoi Animal a-t-elle encore un constructeur ?"

**Réponse** :
- Les classes dérivées (`Dog`, `Cat`) appellent le constructeur d'`Animal`
- Même si `Animal` est abstraite, elle a besoin de son constructeur
- Le destructeur **doit** aussi être virtuel pour le polymorphisme

### Question 3 : "Que se passe-t-il si Cat ne définit pas makeSound() ?"

**Réponse** :
- `Cat` devient **aussi abstraite**
- On ne pourrait pas faire `new Cat()`
- Le compilateur force l'implémentation

### Question 4 : "Peut-on avoir des pointeurs vers Animal ?"

**Réponse** :
- **OUI** : `Animal* ptr = new Dog();` est valide
- On ne peut pas **instancier** Animal, mais on peut avoir des **pointeurs/références**
- C'est le principe du polymorphisme

## 🔄 Hiérarchie de classes

```
Animal (ABSTRAITE)
├── Dog (CONCRÈTE) → makeSound() implémentée
└── Cat (CONCRÈTE) → makeSound() implémentée
```

## ⚠️ Erreurs courantes

1. **Oublier le = 0** → Animal reste concrète
2. **Définir makeSound() dans Animal.cpp** → Ne compile pas (fonction pure définie)
3. **Ne pas implémenter makeSound() dans Dog/Cat** → Dog/Cat deviennent abstraites
4. **Oublier le destructeur virtuel** → Memory leaks avec polymorphisme

## 🆚 Comparaison ex01 vs ex02

| Aspect | ex01 | ex02 |
|--------|------|------|
| **Animal** | Concrète | Abstraite |
| `new Animal()` | ✅ Compile | ❌ Erreur |
| `Animal* ptr = new Dog()` | ✅ | ✅ |
| `makeSound()` dans Animal | Implémentée | Virtuelle pure (= 0) |
| **Brain** | ✅ | ✅ (inchangé) |
| **Deep Copy** | ✅ | ✅ (inchangé) |

## ✅ Points de vérification

- [ ] Animal contient `virtual void makeSound() const = 0;`
- [ ] Animal.cpp ne définit PAS makeSound()
- [ ] Dog et Cat implémentent makeSound()
- [ ] `new Animal()` ne compile pas
- [ ] `Animal* ptr = new Dog()` compile et fonctionne
- [ ] Tous les tests de deep copy fonctionnent toujours
- [ ] Pas de memory leak

## 📚 Concepts avancés

### Interface vs Classe abstraite

**Interface** (C++) :
```cpp
class IAnimal {
public:
    virtual ~IAnimal() {}
    virtual void makeSound() const = 0;
    virtual std::string getType() const = 0;
};
```
→ Toutes les méthodes sont virtuelles pures

**Classe abstraite** (C++) :
```cpp
class Animal {
protected:
    std::string type; // Attribut
public:
    Animal(); // Constructeur
    virtual void makeSound() const = 0; // Méthode pure
    std::string getType() const; // Méthode concrète
};
```
→ Mélange de méthodes pures et concrètes

---

**Résumé** : Cet exercice enseigne les **classes abstraites**, un concept fondamental de la POO qui force un design cohérent en empêchant l'instanciation de classes "trop génériques". 🚫🐾
