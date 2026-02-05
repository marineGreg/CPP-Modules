# Guide CPP04 - Exercise 00 : Polymorphisme

## 📋 Objectif de l'exercice

Comprendre et implémenter le **polymorphisme de sous-type** en C++, en particulier :
- L'utilisation du mot-clé `virtual` pour les méthodes et destructeurs
- Le comportement polymorphique avec des pointeurs vers la classe de base
- La différence entre polymorphisme avec et sans `virtual`

## 🎯 Concepts clés

### 1. Le Polymorphisme

Le **polymorphisme** permet à un objet d'une classe dérivée d'être traité comme un objet de sa classe de base, tout en conservant son comportement spécifique.

```cpp
const Animal* cat = new Cat();  // Pointeur Animal vers un objet Cat
cat->makeSound();  // Appelle Cat::makeSound() grâce au virtual
```

### 2. Le mot-clé `virtual`

Le mot-clé `virtual` indique au compilateur d'utiliser la **liaison dynamique** (dynamic binding) au lieu de la liaison statique.

**Sans `virtual` :**
```cpp
class WrongAnimal {
    void makeSound() const;  // Pas de virtual
};
```
→ Le type du **pointeur** détermine quelle méthode est appelée (WrongAnimal::makeSound)

**Avec `virtual` :**
```cpp
class Animal {
    virtual void makeSound() const;  // Avec virtual
};
```
→ Le type **réel de l'objet** détermine quelle méthode est appelée (Cat::makeSound ou Dog::makeSound)

### 3. Destructeur virtuel

⚠️ **CRITIQUE** : Quand on utilise le polymorphisme, le destructeur de la classe de base **DOIT** être virtuel !

```cpp
class Animal {
    virtual ~Animal();  // OBLIGATOIRE
};
```

**Pourquoi ?**
```cpp
Animal* ptr = new Dog();
delete ptr;  // Sans destructeur virtuel → seulement ~Animal() est appelé
             // Avec destructeur virtuel → ~Dog() puis ~Animal() sont appelés
```

Sans destructeur virtuel = **memory leak** si la classe dérivée alloue de la mémoire !

## 📁 Structure de l'exercice

```
ex00/
├── Animal.hpp          # Classe de base avec virtual
├── Animal.cpp
├── Dog.hpp             # Classe dérivée
├── Dog.cpp
├── Cat.hpp             # Classe dérivée
├── Cat.cpp
├── WrongAnimal.hpp     # Classe de base SANS virtual (contre-exemple)
├── WrongAnimal.cpp
├── WrongCat.hpp        # Classe dérivée (pour démontrer le problème)
├── WrongCat.cpp
├── main.cpp
└── Makefile
```

## 💻 Implémentation

### Animal.hpp - La classe de base (AVEC virtual)

```cpp
class Animal {
protected:
    std::string type;

public:
    Animal();
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal();  // ✅ VIRTUEL pour permettre le polymorphisme

    virtual void makeSound() const;  // ✅ VIRTUEL pour override
    std::string getType() const;
};
```

**Points importants :**
- `type` est **protected** pour être accessible aux classes dérivées
- Destructeur **virtual** pour la destruction polymorphique correcte
- `makeSound()` est **virtual** pour permettre l'override dans les classes dérivées

### Dog.hpp et Cat.hpp - Classes dérivées

```cpp
class Dog : public Animal {
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();  // Pas besoin de "virtual" ici (hérité)

    void makeSound() const;  // Override de Animal::makeSound()
};
```

**Implémentation dans Dog.cpp :**
```cpp
Dog::Dog() {
    this->type = "Dog";  // Initialise le type
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
    // Appelle le constructeur de copie de Animal
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other)
        Animal::operator=(other);  // Appelle l'opérateur de Animal
    return *this;
}

void Dog::makeSound() const {
    std::cout << "Woooof !" << std::endl;
}
```

**Points importants :**
- Le constructeur de copie appelle `Animal(other)` pour initialiser la partie `Animal`
- L'opérateur d'assignation appelle `Animal::operator=(other)`
- Pas besoin de `virtual` dans la déclaration de `makeSound()` (mais on peut le mettre)

### WrongAnimal.hpp - Le contre-exemple (SANS virtual)

```cpp
class WrongAnimal {
protected:
    std::string type;

public:
    WrongAnimal();
    WrongAnimal(const WrongAnimal& other);
    WrongAnimal& operator=(const WrongAnimal& other);
    ~WrongAnimal();  // ❌ PAS de virtual

    void makeSound() const;  // ❌ PAS de virtual
    std::string getType() const;
};
```

**Conséquence :**
```cpp
const WrongAnimal* ptr = new WrongCat();
ptr->makeSound();  // Appelle WrongAnimal::makeSound() au lieu de WrongCat::makeSound()
```

## 🧪 Tests et analyse du main

### Test 1 : Polymorphisme de base (du sujet)

```cpp
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();

i->makeSound(); // "Meoowww !" (polymorphisme fonctionne)
j->makeSound(); // "Woooof !" (polymorphisme fonctionne)
meta->makeSound(); // "Generic Animal sound..."
```

**Résultat attendu :** Chaque animal fait son propre son grâce au `virtual`.

### Test 2 : WrongAnimal (sans virtual)

```cpp
const WrongAnimal* wrongCat = new WrongCat();
wrongCat->makeSound(); // "WrongAnimal generic sound (shhh...)"
```

**Résultat :** Le son de `WrongAnimal` est joué au lieu de celui de `WrongCat` car `makeSound()` n'est **pas virtuel**.

### Test 3 : Constructeur de copie

```cpp
Dog originalDog;
Dog copiedDog(originalDog);
```

**Affichage :**
```
Animal default constructor called
Dog constructor called
Animal copy constructor called
Animal assignment operator called
Dog copy constructor called
```

**Analyse :** Le constructeur de copie de `Dog` appelle d'abord le constructeur de copie d'`Animal`.

### Test 4 : Opérateur d'assignation

```cpp
Cat cat1;
Cat cat2;
cat2 = cat1;
```

**Affichage :**
```
Cat assignment operator called
Animal assignment operator called
```

**Analyse :** L'opérateur d'assignation de `Cat` délègue à `Animal::operator=`.

### Test 5 : Tableau d'animaux polymorphe

```cpp
const Animal* animals[4];
animals[0] = new Dog();
animals[1] = new Cat();
animals[2] = new Dog();
animals[3] = new Cat();

for (int idx = 0; idx < 4; idx++) {
    animals[idx]->makeSound();  // Chaque animal fait son propre son
}
```

**Résultat :**
```
Animal 0 est un Dog qui fait: Woooof !
Animal 1 est un Cat qui fait: Meoowww !
Animal 2 est un Dog qui fait: Woooof !
Animal 3 est un Cat qui fait: Meoowww !
```

**Analyse :** Le polymorphisme permet de traiter différents types d'animaux de manière uniforme tout en conservant leur comportement spécifique.

### Test 6 : Comparaison directe

```cpp
// Avec virtual
const Animal* cat = new Cat();
cat->makeSound();  // "Meoowww !"

// Sans virtual
const WrongAnimal* wrongCat = new WrongCat();
wrongCat->makeSound();  // "WrongAnimal generic sound (shhh...)"
```

**Analyse :** Démontre clairement la différence entre polymorphisme avec et sans `virtual`.

## 📊 Schéma du polymorphisme

```
┌─────────────────────────────────────────────────────────┐
│                    AVEC virtual                         │
├─────────────────────────────────────────────────────────┤
│  const Animal* ptr = new Cat();                         │
│  ptr->makeSound();                                      │
│                                                         │
│  Appelle Cat::makeSound() ✅                            │
│  (liaison dynamique = runtime)                          │
└─────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────┐
│                   SANS virtual                          │
├─────────────────────────────────────────────────────────┤
│  const WrongAnimal* ptr = new WrongCat();               │
│  ptr->makeSound();                                      │
│                                                         │
│  Appelle WrongAnimal::makeSound() ❌                    │
│  (liaison statique = compile time)                      │
└─────────────────────────────────────────────────────────┘
```

## 🔍 Fonctionnement interne

### Table de méthodes virtuelles (vtable)

Quand une classe a des méthodes `virtual`, le compilateur crée une **vtable** (table de pointeurs de fonctions) :

```
Animal vtable:
├─ makeSound → Animal::makeSound
└─ ~Animal   → Animal::~Animal

Dog vtable:
├─ makeSound → Dog::makeSound
└─ ~Animal   → Dog::~Dog (puis Animal::~Animal)

Cat vtable:
├─ makeSound → Cat::makeSound
└─ ~Animal   → Cat::~Cat (puis Animal::~Animal)
```

Chaque objet contient un **pointeur caché vers sa vtable** (vptr) :

```cpp
Animal* ptr = new Dog();
// ptr pointe vers un objet Dog qui contient un vptr vers la Dog vtable
ptr->makeSound();  // Regarde dans la Dog vtable → appelle Dog::makeSound()
```

**Coût :** Un pointeur supplémentaire par objet (8 bytes sur 64-bit) + indirection lors des appels.

## ⚠️ Erreurs courantes

### 1. Oublier le destructeur virtuel

```cpp
class Animal {
    ~Animal();  // ❌ Pas virtual
};

Animal* ptr = new Dog();
delete ptr;  // Seulement ~Animal() appelé, ~Dog() jamais appelé → leak
```

**Solution :** Toujours mettre `virtual ~Animal();`

### 2. Ne pas appeler le constructeur de la classe de base

```cpp
Dog::Dog(const Dog& other) {  // ❌ Ne pas appeler Animal(other)
    std::cout << "Dog copy constructor" << std::endl;
}
```

**Solution :**
```cpp
Dog::Dog(const Dog& other) : Animal(other) {  // ✅ Appeler Animal(other)
    std::cout << "Dog copy constructor" << std::endl;
}
```

### 3. Faire du slicing

```cpp
Animal animal = Dog();  // ❌ SLICING ! L'objet Dog est "coupé"
animal.makeSound();     // Appelle Animal::makeSound() même avec virtual
```

**Explication :** L'objet est copié dans une variable de type `Animal`, donc la partie `Dog` est perdue.

**Solution :** Utiliser des **pointeurs** ou **références** :
```cpp
Animal* animal = new Dog();  // ✅
Animal& animal = dog;        // ✅
```

### 4. Oublier `const` dans l'override

```cpp
class Animal {
    virtual void makeSound() const;
};

class Dog : public Animal {
    void makeSound();  // ❌ Pas le même const → pas un override !
};
```

**Solution :** Respecter la signature exacte :
```cpp
void makeSound() const;  // ✅
```

En C++11+, on peut utiliser `override` pour détecter ce genre d'erreur :
```cpp
void makeSound() const override;  // Le compilateur vérifie que c'est un override
```

## 🎓 Points importants à retenir

1. ✅ **Toujours déclarer le destructeur `virtual`** dans une classe de base polymorphique
2. ✅ **Utiliser `virtual`** pour les méthodes qu'on veut pouvoir override
3. ✅ **Utiliser des pointeurs ou références** pour bénéficier du polymorphisme
4. ✅ **Appeler les constructeurs de la classe de base** dans les constructeurs de copie
5. ✅ **Déléguer aux opérateurs de la classe de base** dans les opérateurs d'assignation
6. ⚠️ Le polymorphisme a un **coût en performance** (indirection via vtable)
7. ⚠️ Le polymorphisme fonctionne uniquement avec des **pointeurs ou références**

## 🧩 Hiérarchie des classes

```
        ┌──────────┐              ┌──────────────┐
        │  Animal  │              │ WrongAnimal  │
        │ (virtual)│              │(pas virtual) │
        └────┬─────┘              └──────┬───────┘
             │                           │
      ┌──────┴──────┐                    │
      │             │                    │
┌─────▼────┐  ┌────▼─────┐        ┌─────▼────────┐
│   Dog    │  │   Cat    │        │  WrongCat    │
│          │  │          │        │              │
└──────────┘  └──────────┘        └──────────────┘

Polymorphisme: ✅              Polymorphisme: ❌
```

## 📚 Compilation et exécution

```bash
make
./polymorphism
```

**Flags de compilation :**
```makefile
FLAGS = -Wall -Wextra -Werror -std=c++98
```

## ✅ Checklist de validation

- [ ] La classe `Animal` a un destructeur **virtuel**
- [ ] La méthode `makeSound()` est **virtuelle** dans `Animal`
- [ ] Les classes `Dog` et `Cat` héritent de `Animal`
- [ ] Les types sont correctement initialisés ("Dog", "Cat")
- [ ] Le polymorphisme fonctionne : `cat->makeSound()` appelle `Cat::makeSound()`
- [ ] Les constructeurs de copie appellent le constructeur de copie de la classe de base
- [ ] Les opérateurs d'assignation délèguent à la classe de base
- [ ] `WrongAnimal` et `WrongCat` démontrent le problème sans `virtual`
- [ ] Le `main` contient des tests variés et complets
- [ ] Tous les destructeurs sont appelés dans le bon ordre
- [ ] Aucune fuite mémoire (vérifier avec `valgrind`)
- [ ] La compilation passe avec `-Wall -Wextra -Werror -std=c++98`

## 🚀 Pour aller plus loin

### Méthodes purement virtuelles (exercices suivants)

```cpp
class Animal {
    virtual void makeSound() const = 0;  // Méthode pure virtuelle
};
```

Une méthode pure virtuelle = **classe abstraite** (impossible de l'instancier).

### Le mot-clé `override` (C++11)

```cpp
class Dog : public Animal {
    void makeSound() const override;  // Vérifie qu'on override bien
};
```

### Le mot-clé `final` (C++11)

```cpp
class Dog : public Animal {
    void makeSound() const final;  // Ne peut plus être override
};
```

---

**Exercice validé !** Tu comprends maintenant le polymorphisme et l'importance du mot-clé `virtual` en C++. 🎉
