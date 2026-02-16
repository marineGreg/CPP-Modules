# Guide d'Évaluation - CPP Module 04

## 📋 Vue d'ensemble du module

**Thème principal** : Polymorphisme de sous-type, classes abstraites et interfaces

**Concepts clés** :
- Polymorphisme avec `virtual`
- Destructeurs virtuels
- Fonctions virtuelles pures (classes abstraites)
- Interfaces en C++
- Liaison dynamique (dynamic binding) vs liaison statique (static binding)

---

## 🎯 Exercise 00: Polymorphism

### 📖 Explication du programme

Implémente le **polymorphisme de sous-type** avec des classes `Animal`, `Dog`, `Cat` et démontre l'importance du mot-clé `virtual` avec des contre-exemples (`WrongAnimal`, `WrongCat`).

**Structure des classes** :
```
Animal (avec virtual)
├── Dog
└── Cat

WrongAnimal (SANS virtual)
└── WrongCat
```

### 🔑 Points clés à comprendre

#### 1. **Qu'est-ce que le Polymorphisme ?**

Le polymorphisme permet à un objet d'une classe dérivée d'être traité comme un objet de sa classe de base, **tout en conservant son comportement spécifique**.

**Exemple concret** :
```cpp
const Animal* cat = new Cat();  // Pointeur Animal vers un objet Cat
cat->makeSound();  // Appelle Cat::makeSound() (pas Animal::makeSound())
```

**Pourquoi c'est utile ?**
- Permet d'écrire du code générique qui fonctionne avec tous les types dérivés
- Facilite l'extensibilité (ajouter de nouveaux animaux sans modifier le code existant)
- Base de la programmation orientée objet moderne

#### 2. **Le mot-clé `virtual`**

Le mot-clé `virtual` active la **liaison dynamique** (résolution à l'exécution).

**Sans `virtual` (liaison statique)** :
```cpp
class WrongAnimal {
    void makeSound() const;  // Pas de virtual
};

const WrongAnimal* cat = new WrongCat();
cat->makeSound();  // Appelle WrongAnimal::makeSound() ❌
```
→ Le **type du pointeur** détermine quelle méthode est appelée

**Avec `virtual` (liaison dynamique)** :
```cpp
class Animal {
    virtual void makeSound() const;  // Avec virtual
};

const Animal* cat = new Cat();
cat->makeSound();  // Appelle Cat::makeSound() ✅
```
→ Le **type réel de l'objet** détermine quelle méthode est appelée

#### 3. **Destructeur virtuel (CRITIQUE)**

⚠️ **RÈGLE D'OR** : Si une classe a au moins une méthode `virtual`, son destructeur **DOIT** être `virtual` !

```cpp
class Animal {
public:
    virtual ~Animal();  // OBLIGATOIRE
};
```

**Pourquoi ?**
```cpp
Animal* ptr = new Dog();
delete ptr;

// Sans virtual ~Animal() :
// → Seulement ~Animal() est appelé
// → ~Dog() n'est JAMAIS appelé
// → Memory leak si Dog alloue de la mémoire !

// Avec virtual ~Animal() :
// → ~Dog() est appelé d'abord
// → Puis ~Animal() est appelé
// → Destruction correcte ✅
```

#### 4. **Implémentation de la classe Animal**

**Animal.hpp** :
```cpp
class Animal {
protected:
    std::string type;  // Protected pour accès des dérivées

public:
    Animal();
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal();  // ✅ Virtuel pour destruction polymorphique

    virtual void makeSound() const;  // ✅ Virtuel pour override
    std::string getType() const;
};
```

**Animal.cpp** :
```cpp
Animal::Animal() : type("Animal") {
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound() const {
    std::cout << "Generic Animal sound..." << std::endl;
}

std::string Animal::getType() const {
    return this->type;
}
```

#### 5. **Implémentation d'une classe dérivée (Dog)**

**Dog.hpp** :
```cpp
class Dog : public Animal {
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();  // Pas besoin de virtual ici (hérité de Animal)

    void makeSound() const;  // Override (pas besoin de re-spécifier virtual)
};
```

**Dog.cpp** :
```cpp
Dog::Dog() {
    this->type = "Dog";  // Modifie le type hérité
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other)
        Animal::operator=(other);  // Appelle l'opérateur du parent
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "Woooof !" << std::endl;
}
```

**Points importants** :
- Le constructeur de copie appelle `Animal(other)` pour copier la partie Animal
- L'opérateur d'assignation appelle `Animal::operator=(other)`
- `makeSound()` **override** la méthode virtuelle du parent

### 🧪 Tests à démontrer

```bash
./polymorphism
```

#### **Test 1 : Polymorphisme de base (du sujet)**

```cpp
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();

std::cout << j->getType() << std::endl;  // "Dog"
std::cout << i->getType() << std::endl;  // "Cat"
i->makeSound();  // "Meoowww !" (son du chat)
j->makeSound();  // "Woooof !" (son du chien)
meta->makeSound();  // "Generic Animal sound..."

delete meta;
delete j;
delete i;
```

**Ce que tu dois expliquer** :
- Bien que `j` et `i` soient des pointeurs `Animal*`, ils appellent les bonnes méthodes
- Grâce à `virtual`, le type **réel** de l'objet est utilisé
- Les destructeurs sont appelés dans le bon ordre grâce à `virtual ~Animal()`

#### **Test 2 : WrongAnimal (sans virtual)**

```cpp
const WrongAnimal* wrongMeta = new WrongAnimal();
const WrongAnimal* wrongCat = new WrongCat();

std::cout << wrongCat->getType() << std::endl;  // "WrongCat"
wrongCat->makeSound();  // "WrongAnimal generic sound" ❌ Pas le son du chat !
wrongMeta->makeSound();  // "WrongAnimal generic sound"

delete wrongMeta;
delete wrongCat;
```

**Ce que tu dois expliquer** :
- Sans `virtual`, c'est le type du **pointeur** qui compte
- `wrongCat` est un `WrongAnimal*` → appelle `WrongAnimal::makeSound()`
- Le polymorphisme ne fonctionne PAS sans `virtual`
- C'est une démonstration volontaire d'un mauvais design

#### **Test 3 : Constructeur de copie**

```cpp
Dog originalDog;
Dog copiedDog(originalDog);

std::cout << "Original type: " << originalDog.getType() << std::endl;
std::cout << "Copied type: " << copiedDog.getType() << std::endl;
```

**Sortie attendue** :
```
Animal default constructor called
Dog constructor called
Animal copy constructor called
Animal assignment operator called
Dog copy constructor called
Original type: Dog
Copied type: Dog
```

**Ce que tu dois expliquer** :
- Le constructeur de copie de Dog appelle d'abord celui d'Animal
- L'ordre de construction : Animal → Dog
- L'ordre de destruction : Dog → Animal (inverse)

#### **Test 4 : Opérateur d'assignation**

```cpp
Cat cat1;
Cat cat2;
cat2 = cat1;
cat1.makeSound();
cat2.makeSound();
```

**Ce que tu dois expliquer** :
- L'opérateur d'assignation vérifie l'auto-assignation (`if (this != &other)`)
- Appelle l'opérateur d'assignation du parent (`Animal::operator=`)
- Les deux objets peuvent ensuite fonctionner indépendamment

#### **Test 5 : Tableau polymorphe**

```cpp
const Animal* animals[4];
animals[0] = new Dog();
animals[1] = new Cat();
animals[2] = new Dog();
animals[3] = new Cat();

for (int idx = 0; idx < 4; idx++) {
    std::cout << "Animal " << idx << " est un " << animals[idx]->getType() 
              << " qui fait: ";
    animals[idx]->makeSound();
}

for (int idx = 0; idx < 4; idx++) {
    delete animals[idx];
}
```

**Sortie attendue** :
```
Animal 0 est un Dog qui fait: Woooof !
Animal 1 est un Cat qui fait: Meoowww !
Animal 2 est un Dog qui fait: Woooof !
Animal 3 est un Cat qui fait: Meoowww !
```

**Ce que tu dois expliquer** :
- Tableau de pointeurs vers la classe de base
- Chaque élément peut pointer vers un type dérivé différent
- Le polymorphisme permet de traiter tous les animaux uniformément
- La destruction appelle les bons destructeurs grâce à `virtual`

#### **Test 6 : Comparaison Animal vs WrongAnimal**

```cpp
// Avec virtual (Animal):
const Animal* cat = new Cat();
cat->makeSound();  // "Meoowww !" ✅
delete cat;

// Sans virtual (WrongAnimal):
const WrongAnimal* wrongCat = new WrongCat();
wrongCat->makeSound();  // "WrongAnimal generic sound" ❌
delete wrongCat;
```

**Ce que tu dois expliquer** :
- Comparaison côte à côte pour montrer la différence
- Avec `virtual` : le bon son est produit
- Sans `virtual` : le son générique est produit (mauvais comportement)

### ⚠️ Erreurs courantes

1. **Oublier `virtual` sur le destructeur**
   - Conséquence : Fuites mémoire, destructeurs dérivés non appelés
   - Solution : Toujours mettre `virtual ~ClassName()` dans la classe de base

2. **Oublier `virtual` sur les méthodes à override**
   - Conséquence : Pas de polymorphisme, mauvaise méthode appelée
   - Solution : Marquer toutes les méthodes polymorphes avec `virtual`

3. **Ne pas appeler le constructeur parent dans le constructeur de copie**
   ```cpp
   // ❌ MAUVAIS
   Dog::Dog(const Dog& other) {
       *this = other;
   }
   
   // ✅ BON
   Dog::Dog(const Dog& other) : Animal(other) {
       std::cout << "Dog copy constructor called" << std::endl;
   }
   ```

4. **Ne pas appeler l'opérateur d'assignation parent**
   ```cpp
   // ❌ MAUVAIS
   Dog& Dog::operator=(const Dog& other) {
       if (this != &other)
           this->type = other.type;  // Oublie les autres attributs d'Animal
       return *this;
   }
   
   // ✅ BON
   Dog& Dog::operator=(const Dog& other) {
       if (this != &other)
           Animal::operator=(other);  // Délègue au parent
       return *this;
   }
   ```

5. **Utiliser des objets au lieu de pointeurs pour le polymorphisme**
   ```cpp
   // ❌ Pas de polymorphisme (object slicing)
   Animal animal = Dog();
   animal.makeSound();  // "Generic Animal sound..."
   
   // ✅ Polymorphisme avec pointeur
   Animal* animal = new Dog();
   animal->makeSound();  // "Woooof !"
   delete animal;
   ```

### 💡 Conseils de présentation

1. **Dessine un schéma** de l'héritage :
   ```
   Animal (virtual)          WrongAnimal (pas virtual)
      ↑      ↑                     ↑
      |      |                     |
    Dog    Cat               WrongCat
   ```

2. **Explique la vtable** (table virtuelle) :
   - Chaque classe avec `virtual` a une vtable (tableau de pointeurs de fonctions)
   - Chaque objet a un pointeur vers sa vtable
   - Lors d'un appel de fonction virtuelle, le programme consulte la vtable
   - C'est ainsi que le bon `makeSound()` est appelé

3. **Montre l'ordre de construction/destruction** :
   ```
   Construction : Animal → Dog
   Destruction :  Dog → Animal
   ```

4. **Compare le coût** :
   - Sans `virtual` : appel direct (plus rapide)
   - Avec `virtual` : indirection via vtable (légèrement plus lent)
   - En pratique : différence négligeable, la clarté du code prime

5. **Donne des exemples concrets** :
   - Zoo avec différents animaux
   - Système de paiement avec différentes méthodes (Carte, PayPal, etc.)
   - Interface graphique avec différents widgets (Button, TextBox, etc.)

---

## 🎁 Questions anticipées

### Q1 : "Pourquoi utiliser des pointeurs pour le polymorphisme ?"

**Réponse** :
Parce que le polymorphisme en C++ nécessite une **indirection** (pointeur ou référence).

Avec un objet direct, il y a **object slicing** :
```cpp
Dog dog;
Animal animal = dog;  // Coupe la partie Dog !
animal.makeSound();   // Appelle Animal::makeSound() ❌
```

Avec un pointeur ou référence :
```cpp
Dog dog;
Animal* animal = &dog;  // Garde le type réel
animal->makeSound();    // Appelle Dog::makeSound() ✅
```

### Q2 : "Quelle est la différence entre override et overload ?"

**Réponse** :
- **Override** (redéfinition) : Même signature dans classe dérivée
  ```cpp
  class Animal {
      virtual void makeSound() const;
  };
  class Dog : public Animal {
      void makeSound() const;  // Override
  };
  ```

- **Overload** (surcharge) : Même nom, signature différente
  ```cpp
  void print(int n);
  void print(std::string s);  // Overload
  ```

### Q3 : "Pourquoi `type` est `protected` et pas `private` ?"

**Réponse** :
- `private` : Accessible uniquement dans la classe elle-même
- `protected` : Accessible dans la classe ET ses dérivées
- Les classes dérivées (Dog, Cat) ont besoin de modifier `type`
- Donc `protected` est le bon choix

### Q4 : "Peut-on avoir une classe avec seulement des méthodes virtuelles ?"

**Réponse** :
Oui ! C'est ce qu'on appelle une **classe abstraite** ou **interface**.

En C++, on utilise des **fonctions virtuelles pures** :
```cpp
class IAnimal {
public:
    virtual ~IAnimal() {}
    virtual void makeSound() const = 0;  // Pure virtual
    virtual std::string getType() const = 0;
};
```

Le `= 0` signifie "pas d'implémentation, les dérivées DOIVENT l'implémenter".
On ne peut pas instancier directement une classe abstraite.

### Q5 : "Que se passe-t-il si on oublie d'implémenter une méthode virtuelle ?"

**Réponse** :
Si la méthode est **virtuelle pure** (`= 0`) : Erreur de compilation
Si la méthode est **virtuelle simple** : La classe dérivée hérite de l'implémentation du parent

```cpp
class Animal {
    virtual void makeSound() const { std::cout << "Animal sound"; }
};

class Dog : public Animal {
    // N'implémente pas makeSound()
};

Dog dog;
dog.makeSound();  // Appelle Animal::makeSound() (hérité)
```

### Q6 : "Pourquoi WrongCat hérite de WrongAnimal ?"

**Réponse** :
C'est un **contre-exemple pédagogique** pour démontrer ce qui se passe **sans** `virtual`.

Ça montre que :
- L'héritage seul ne suffit pas pour le polymorphisme
- Le mot-clé `virtual` est essentiel
- Sans `virtual`, on perd les avantages du polymorphisme

---

## ✅ Checklist finale avant l'évaluation

- [ ] Je comprends la différence entre liaison statique et dynamique
- [ ] Je sais expliquer pourquoi le destructeur doit être virtuel
- [ ] Je peux expliquer comment fonctionne la vtable
- [ ] Je comprends le contre-exemple WrongAnimal/WrongCat
- [ ] Je sais démontrer le polymorphisme avec un tableau d'animaux
- [ ] Je peux expliquer la différence entre override et overload
- [ ] Je comprends l'ordre de construction/destruction avec l'héritage
- [ ] Mon code compile sans warnings avec `-Wall -Wextra -Werror`
- [ ] Tous mes tests passent et affichent les bons messages
- [ ] J'ai vérifié les fuites mémoire (valgrind)

---

## 🚀 Commandes utiles

```bash
# Compilation
make

# Exécution
./polymorphism

# Vérification des fuites mémoire
valgrind --leak-check=full ./polymorphism

# Nettoyage
make fclean
```

---

Bon courage pour ton évaluation ! 🎓
