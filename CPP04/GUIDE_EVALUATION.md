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
cd ex00
make
./polymorphism
```

Le `main.cpp` contient **3 sections de tests** :

#### **Test 1 : TESTS DU SUJET (Polymorphisme de base)**

```cpp
std::cout << "\n=== TESTS DU SUJET ===" << std::endl;
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();

std::cout << j->getType() << " " << std::endl;
std::cout << i->getType() << " " << std::endl;
i->makeSound();    // Son du chat
j->makeSound();    // Son du chien
meta->makeSound(); // Son générique

delete meta;
delete j;
delete i;
```

**Sortie attendue** :
```
=== TESTS DU SUJET ===
Animal default constructor called
Animal default constructor called
Dog constructor called
Animal default constructor called
Cat constructor called
Dog 
Cat 
Meoowww !
Woooof !
Generic Animal sound...
Animal destructor called
Dog destructor called
Animal destructor called
Cat destructor called
Animal destructor called
```

**Ce que tu dois expliquer** :
- Bien que `j` et `i` soient des pointeurs `Animal*`, ils appellent les bonnes méthodes
- Grâce à `virtual`, le type **réel** de l'objet est utilisé (liaison dynamique)
- Les destructeurs sont appelés dans le bon ordre grâce à `virtual ~Animal()`
  - Pour `j` : Dog destructor → Animal destructor
  - Pour `i` : Cat destructor → Animal destructor

#### **Test 2 : TESTS SUPPLÉMENTAIRES (Stack & Copy)**

```cpp
std::cout << "\n=== TESTS SUPPLÉMENTAIRES (Stack & Copy) ===" << std::endl;

Dog originalDog;
std::cout << "Type de originalDog : " << originalDog.getType() << std::endl;

Dog copyDog(originalDog);  // Constructeur de copie
std::cout << "Type de copyDog : " << copyDog.getType() << std::endl;
copyDog.makeSound();

Cat stackCat;
stackCat.makeSound();
```

**Sortie attendue** :
```
=== TESTS SUPPLÉMENTAIRES (Stack & Copy) ===
Animal default constructor called
Dog constructor called
Type de originalDog : Dog
Animal copy constructor called
Animal assignment operator called
Dog copy constructor called
Type de copyDog : Dog
Woooof !
Animal default constructor called
Cat constructor called
Meoowww !
```

**Ce que tu dois expliquer** :
- Les objets peuvent être créés sur la **pile** (pas seulement avec `new`)
- Le constructeur de copie de `Dog` appelle d'abord celui d'`Animal(other)`
- L'ordre de construction : Animal → Dog
- À la fin du programme, l'ordre de destruction : Dog → Animal puis Cat → Animal

#### **Test 3 : TESTS WRONG ANIMAL (Sans polymorphisme)**

```cpp
std::cout << "\n=== TESTS WRONG ANIMAL (Pas de polymorphisme) ===" << std::endl;

const WrongAnimal* wrongMeta = new WrongAnimal();
const WrongAnimal* wrongCat = new WrongCat();

std::cout << "Type : " << wrongCat->getType() << std::endl;

// Malgré que ce soit un WrongCat, appelle WrongAnimal::makeSound()
wrongCat->makeSound(); 
wrongMeta->makeSound();

delete wrongMeta;
delete wrongCat;  // Attention : n'appellera pas le destructeur de WrongCat !
```

**Sortie attendue** :
```
=== TESTS WRONG ANIMAL (Pas de polymorphisme) ===
WrongAnimal default constructor called
WrongAnimal default constructor called
WrongCat constructor called
Type : WrongCat
WrongAnimal generic sound (shhh...)
WrongAnimal generic sound (shhh...)
WrongAnimal destructor called
WrongAnimal destructor called
```

**⚠️ POINT CRITIQUE** : Remarque que `WrongCat destructor called` n'apparaît **JAMAIS** !

**Ce que tu dois expliquer** :
- Sans `virtual`, c'est le type du **pointeur** qui compte (liaison statique)
- `wrongCat` est un `WrongAnimal*` → appelle `WrongAnimal::makeSound()`
- Le polymorphisme ne fonctionne PAS sans `virtual`
- Le destructeur de `WrongCat` n'est **jamais appelé** → risque de memory leak
- C'est une démonstration volontaire d'un mauvais design

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

## 🎯 Exercise 01: Brain & Deep Copy

### 📖 Explication du programme

Étend l'ex00 en ajoutant une classe `Brain` et en implémentant la **copie profonde (Deep Copy)** pour gérer correctement la mémoire dynamique.

**Structure des classes** :
```
Animal (avec virtual)
├── Dog (avec Brain*)
└── Cat (avec Brain*)

Brain (nouvelle classe)
└── ideas[100] (tableau de std::string)
```

### 🔑 Points clés à comprendre

#### 1. **Le problème de la Shallow Copy**

**Sans Deep Copy** :
```cpp
Dog original;           // Crée un Brain*
Dog copy = original;    // Copie le POINTEUR (pas le contenu)
// Les deux partagent le même Brain !
```
→ Quand `copy` est détruit, il `delete _brain`.  
→ Quand `original` est détruit, il essaie de `delete _brain` ENCORE → **CRASH**

**Avec Deep Copy** :
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    _brain = new Brain(*other._brain); // Nouvelle allocation
}
```
→ Chaque objet a son **propre** `Brain`.

#### 2. **La classe Brain**

```cpp
class Brain {
public:
    std::string ideas[100];
    
    Brain();
    Brain(const Brain& other);
    Brain& operator=(const Brain& other);
    ~Brain();
};
```

**Implémentation de l'opérateur d'assignation** :
```cpp
Brain& Brain::operator=(const Brain& other) {
    if (this != &other) {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = other.ideas[i];
    }
    return *this;
}
```

#### 3. **Orthodox Canonical Form avec mémoire dynamique**

**Dog.hpp** :
```cpp
class Dog : public Animal {
private:
    Brain* _brain;

public:
    Dog();
    Dog(const Dog& other);        // Deep Copy
    Dog& operator=(const Dog& other); // Deep Copy
    ~Dog();
    
    void makeSound() const;
};
```

**Dog.cpp - Les 4 méthodes critiques** :

**Constructeur** :
```cpp
Dog::Dog() : Animal() {
    std::cout << "Dog constructor called" << std::endl;
    _brain = new Brain(); // Allocation
}
```

**Constructeur de copie (DEEP COPY)** :
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
    _brain = new Brain(*other._brain); // Nouvelle allocation + copie
}
```

**Opérateur d'assignation** :
```cpp
Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        delete _brain;                     // Libère l'ancien
        _brain = new Brain(*other._brain); // Nouvelle allocation
    }
    return *this;
}
```

**Destructeur** :
```cpp
Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
    delete _brain; // Libération
}
```

### 🧪 Tests et analyse du main

#### **Test 1 : Tableau d'animaux avec Brain**

```cpp
const int count = 4;
Animal* animals[count];

std::cout << "=== CREATING ANIMALS ===" << std::endl;
for (int i = 0; i < count; i++) {
    if (i < count / 2)
        animals[i] = new Dog();
    else
        animals[i] = new Cat();
}

std::cout << "\n=== DELETING ANIMALS ===" << std::endl;
for (int i = 0; i < count; i++) {
    delete animals[i];
}
```

**Sortie attendue** :
```
=== CREATING ANIMALS ===
Animal default constructor called
Dog constructor called
Brain constructor called
Animal default constructor called
Dog constructor called
Brain constructor called
Animal default constructor called
Cat constructor called
Brain constructor called
Animal default constructor called
Cat constructor called
Brain constructor called

=== DELETING ANIMALS ===
Dog destructor called
Brain destructor called
Animal destructor called
Dog destructor called
Brain destructor called
Animal destructor called
Cat destructor called
Brain destructor called
Animal destructor called
Cat destructor called
Brain destructor called
Animal destructor called
```

**Ce que tu dois expliquer** :
- Pour chaque `new Dog()` : Animal → Dog → Brain
- Pour chaque `delete animals[i]` : Dog → Brain → Animal (grâce au destructeur virtuel)
- Si `~Animal()` n'était pas virtuel, les destructeurs de Dog/Cat et Brain ne seraient jamais appelés → **Memory leak**

#### **Test 2 : Deep Copy Test (LE TEST CRUCIAL)**

```cpp
std::cout << "\n=== DEEP COPY TEST ===" << std::endl;
Dog basic;
{
    Dog tmp = basic; // Constructeur de copie
} // tmp est détruit ici

std::cout << "Basic dog is still alive!" << std::endl;
```

**Sortie attendue** :
```
=== DEEP COPY TEST ===
Animal default constructor called
Dog constructor called
Brain constructor called
Animal copy constructor called
Animal assignment operator called
Dog copy constructor called
Brain copy constructor called
Brain assignment operator called
Dog destructor called
Brain destructor called
Animal destructor called
Basic dog is still alive!
Dog destructor called
Brain destructor called
Animal destructor called
```

**Ce que tu dois expliquer** :
1. `basic` est créé → alloue un `Brain`
2. `tmp` est créé par copie → alloue un **nouveau** `Brain` (deep copy)
3. À la fin du bloc `{}`, `tmp` est détruit → libère **son** `Brain`
4. `basic` reste vivant → a toujours **son propre** `Brain` intact
5. Pas de crash ! ✅

**Sans deep copy** : À l'étape 4, le programme crasherait car le `Brain` de `basic` aurait déjà été détruit.

### 📊 Points à démontrer

1. **Création du tableau** :
   - Montre que chaque animal crée son propre `Brain`
   - Compte les messages (4 créations → 4 Brain constructors)

2. **Destruction du tableau** :
   - Montre que les destructeurs sont appelés dans le bon ordre
   - Dog/Cat → Brain → Animal (grâce au destructeur virtuel)

3. **Deep Copy Test** :
   - **LE TEST LE PLUS IMPORTANT**
   - Prouve que la copie profonde fonctionne
   - `basic` survit à la destruction de `tmp`

### ❓ Questions attendues

**Q1 : "Quelle est la différence entre shallow copy et deep copy ?"**

**R1 :**
- **Shallow copy** : Copie les pointeurs → deux objets partagent la même mémoire
- **Deep copy** : Copie le contenu → chaque objet a sa propre mémoire
- Sans deep copy avec des pointeurs → crash lors de la destruction

**Q2 : "Pourquoi faut-il delete l'ancien _brain dans operator= ?"**

**R2 :**
- Si on ne le fait pas → **memory leak**
- L'ancien `Brain` devient inaccessible mais reste en mémoire
- À chaque assignation, on perd un `Brain`

**Q3 : "Que se passe-t-il si on oublie le destructeur virtuel dans Animal ?"**

**R3 :**
```cpp
Animal* ptr = new Dog(); // Crée un Dog avec un Brain
delete ptr;              // Sans virtual ~Animal()
                         // → Appelle seulement ~Animal()
                         // → ~Dog() n'est JAMAIS appelé
                         // → Le Brain n'est JAMAIS libéré
                         // → MEMORY LEAK
```

**Q4 : "Pourquoi utiliser new Brain(*other._brain) et pas new Brain() ?"**

**R4 :**
- `new Brain()` crée un `Brain` vide
- `new Brain(*other._brain)` crée un `Brain` et copie les 100 idées
- C'est ça la **deep copy** : copier la structure ET le contenu

### 🎯 Commandes de test

```bash
cd ex01

# Compilation
make

# Exécution
./polymorphism

# Test de memory leaks avec valgrind
valgrind --leak-check=full ./polymorphism

# Nettoyage
make fclean
```

**Avec valgrind, tu dois voir** :
```
All heap blocks were freed -- no leaks are possible
```

---

## 🎯 Exercise 02: Abstract Class

### 📖 Explication du programme

Transforme la classe `Animal` en **classe abstraite** en rendant `makeSound()` virtuelle pure. Cela empêche l'instanciation directe d'`Animal`.

**Différence avec ex01** :
- ex01 : `virtual void makeSound() const;` → Animal peut être instanciée
- ex02 : `virtual void makeSound() const = 0;` → Animal devient abstraite

### 🔑 Points clés à comprendre

#### 1. **Qu'est-ce qu'une classe abstraite ?**

Une **classe abstraite** contient au moins une **fonction virtuelle pure** (`= 0`) et ne peut pas être instanciée directement.

```cpp
class Animal {
public:
    virtual void makeSound() const = 0; // Fonction virtuelle pure
};

// INTERDIT (ne compile pas) :
Animal animal;           // Erreur : cannot declare variable 'animal' to be of abstract type
Animal* ptr = new Animal(); // Erreur : invalid new-expression of abstract class type

// AUTORISÉ :
Animal* ptr = new Dog(); // Pointeur vers classe dérivée concrète
```

#### 2. **Pourquoi rendre Animal abstraite ?**

**Raison conceptuelle** :
- Un "Animal" générique n'existe pas dans la réalité
- Seuls les animaux **concrets** existent (Dog, Cat, etc.)
- On veut **forcer** chaque animal à avoir son propre son

**Raison technique** :
- Évite les oublis : chaque classe dérivée **doit** implémenter `makeSound()`
- Si Dog ne définit pas `makeSound()`, Dog devient aussi abstraite
- Garantit un design cohérent

#### 3. **Fonction virtuelle pure**

**Syntaxe** :
```cpp
virtual void makeSound() const = 0;
```

**Signification** :
- `virtual` : Utilise le polymorphisme
- `= 0` : Pas d'implémentation dans la classe de base
- **Force** les classes dérivées à implémenter cette méthode

### 🔧 Modifications par rapport à ex01

#### **Animal.hpp - La seule ligne changée**

```cpp
class Animal {
protected:
    std::string type;

public:
    Animal();
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal();

    virtual void makeSound() const = 0; // ← Ajout du "= 0"
    std::string getType() const;
};
```

#### **Animal.cpp - Suppression de makeSound()**

```cpp
Animal::Animal() : type("Animal") {
    std::cout << "Animal default constructor called" << std::endl;
}

// ... autres méthodes ...

// makeSound() n'est PLUS défini ici

std::string Animal::getType() const {
    return this->type;
}
```

⚠️ **Point important** : On garde les constructeurs car les classes dérivées en ont besoin.

#### **Dog.cpp et Cat.cpp (inchangés)**

```cpp
void Dog::makeSound() const {
    std::cout << "Woooof !" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Meoowww !" << std::endl;
}
```

### 🧪 Tests et analyse du main

Les tests sont **identiques à ex01** car le comportement est le même :

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

Dog basic;
{
    Dog tmp = basic;
}
std::cout << "Basic dog is still alive!" << std::endl;
```

**Message ajouté** :
```
=== NOTE: Animal is now an abstract class ===
You cannot instantiate Animal directly anymore:
// Animal animal; <-- This would cause a compilation error!
Only Dog and Cat (concrete classes) can be instantiated.
```

### 🔬 Test de compilation (IMPORTANT)

Pour **prouver** qu'Animal est abstraite, tu peux tester en décommentant cette ligne dans `main.cpp` :

```cpp
// Animal animal; // Décommente cette ligne
```

**Résultat attendu** :
```
error: cannot declare variable 'animal' to be of abstract type 'Animal'
note: because the following virtual functions are pure within 'Animal':
note:     virtual void Animal::makeSound() const
```

### ❓ Questions attendues

**Q1 : "Quelle est la différence entre ex01 et ex02 ?"**

**R1 :**
- **ex01** : `Animal` peut être instanciée (`new Animal()` compile)
- **ex02** : `Animal` est abstraite (`new Animal()` ne compile pas)
- **Code changé** : `virtual void makeSound() const;` → `virtual void makeSound() const = 0;`

**Q2 : "Pourquoi Animal a-t-elle encore un constructeur si elle est abstraite ?"**

**R2 :**
- Les classes dérivées (`Dog`, `Cat`) appellent `Animal::Animal()`
- Même abstraite, `Animal` a besoin de son constructeur
- Le destructeur **doit** aussi être virtuel pour le polymorphisme

**Q3 : "Que se passe-t-il si Cat ne définit pas makeSound() ?"**

**R3 :**
- `Cat` devient **aussi abstraite**
- On ne peut plus faire `new Cat()`
- Le compilateur **force** l'implémentation

**Q4 : "Peut-on avoir des pointeurs vers Animal ?"**

**R4 :**
- **OUI** : `Animal* ptr = new Dog();` est valide
- On ne peut pas **instancier** Animal, mais on peut avoir des **pointeurs/références**
- C'est le principe du polymorphisme

**Q5 : "Quelle est la différence entre une classe abstraite et une interface ?"**

**R5 :**
- **Classe abstraite** : Peut avoir des méthodes concrètes ET des méthodes pures
  - Exemple : `Animal` (a `getType()` concrète et `makeSound()` pure)
- **Interface** : TOUTES les méthodes sont pures (voir ex03)

### 🆚 Comparaison ex01 vs ex02

| Aspect | ex01 | ex02 |
|--------|------|------|
| **Animal** | Concrète | Abstraite |
| `new Animal()` | ✅ Compile | ❌ Erreur |
| `Animal* ptr = new Dog()` | ✅ | ✅ |
| `makeSound()` dans Animal | Implémentée | Virtuelle pure (= 0) |
| **Brain** | ✅ | ✅ (inchangé) |
| **Deep Copy** | ✅ | ✅ (inchangé) |
| **Tests** | Identiques | Identiques |

### 🎯 Commandes de test

```bash
cd ex02

# Compilation
make

# Exécution
./polymorphism

# Test de memory leaks
valgrind --leak-check=full ./polymorphism

# Test de la classe abstraite (doit échouer)
# Décommente "Animal animal;" dans main.cpp
make
# → Erreur de compilation attendue

# Nettoyage
make fclean
```

---

## 🎯 Exercise 03: Interfaces & Materia

### 📖 Explication du programme

Implémente un système complexe d'**interfaces** et de **patterns de conception** :
- **Interfaces** pures (`ICharacter`, `IMateriaSource`)
- **Pattern Prototype** (méthode `clone()`)
- **Système d'inventaire** avec gestion avancée de la mémoire

**Structure des classes** :
```
AMateria (Abstraite)          ICharacter (Interface)      IMateriaSource (Interface)
├── Ice (Concrète)            └── Character (Concrète)    └── MateriaSource (Concrète)
└── Cure (Concrète)
```

### 🔑 Points clés à comprendre

#### 1. **Interface en C++**

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
- Pas d'attributs
- Définit un **contrat** que les classes concrètes doivent respecter

#### 2. **Pattern Prototype (clone())**

Le **pattern Prototype** permet de créer des copies d'objets sans connaître leur type exact :

```cpp
class AMateria {
public:
    virtual AMateria* clone() const = 0; // Virtuelle pure
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
AMateria* original = new Ice();
AMateria* copy = original->clone(); // On obtient une copie sans savoir que c'est un Ice
```

#### 3. **Gestion de la mémoire avec unequip**

**Problème** : Que faire de la Materia quand on l'unequip ?

**Solutions** :
1. ❌ `delete` directement → Risque de double-free
2. ✅ **Mettre sur le "floor"** (stockage temporaire) → Nettoyage dans le destructeur

```cpp
void Character::unequip(int idx) {
    if (_inventory[idx]) {
        _floor[_floorCount] = _inventory[idx]; // Ne pas delete !
        _floorCount++;
        _inventory[idx] = NULL;
    }
}
```

### 📁 Structure complète

```
ex03/
├── AMateria.hpp        # Classe abstraite pour toutes les materias
├── AMateria.cpp
├── Ice.hpp             # Materia concrète : Ice
├── Ice.cpp
├── Cure.hpp            # Materia concrète : Cure
├── Cure.cpp
├── ICharacter.hpp      # Interface pour les personnages
├── Character.hpp       # Implémentation concrète
├── Character.cpp
├── IMateriaSource.hpp  # Interface pour la source de materias
├── MateriaSource.hpp   # Implémentation concrète
├── MateriaSource.cpp
├── main.cpp
└── Makefile
```

### 🔧 Implémentation des composants clés

#### **AMateria (Classe abstraite de base)**

```cpp
class AMateria {
protected:
    std::string _type;

public:
    AMateria(std::string const & type);
    virtual ~AMateria();

    std::string const & getType() const;
    
    virtual AMateria* clone() const = 0; // Pattern Prototype
    virtual void use(ICharacter& target);
};
```

⚠️ **Important** : Dans `operator=`, le type n'est **jamais** copié (requis par le sujet).

#### **Ice et Cure (Materias concrètes)**

```cpp
// Ice.cpp
AMateria* Ice::clone() const {
    return new Ice(*this); // Nouvelle allocation
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}

// Cure.cpp
AMateria* Cure::clone() const {
    return new Cure(*this);
}

void Cure::use(ICharacter& target) {
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
```

#### **Character (Implémentation de ICharacter)**

```cpp
class Character : public ICharacter {
private:
    std::string _name;
    AMateria* _inventory[4];   // Max 4 Materias
    AMateria* _floor[100];     // Stockage des unequip
    int _floorCount;

public:
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};
```

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
    _floor[_floorCount++] = m;
}
```

**unequip()** :
```cpp
void Character::unequip(int idx) {
    if (idx >= 0 && idx < 4 && _inventory[idx]) {
        _floor[_floorCount++] = _inventory[idx]; // Stockage, pas delete !
        _inventory[idx] = NULL;
    }
}
```

**use()** :
```cpp
void Character::use(int idx, ICharacter& target) {
    if (idx >= 0 && idx < 4 && _inventory[idx]) {
        _inventory[idx]->use(target); // Polymorphisme
    }
}
```

#### **MateriaSource (Implémentation de IMateriaSource)**

```cpp
class MateriaSource : public IMateriaSource {
private:
    AMateria* _templates[4]; // Max 4 templates

public:
    void learnMateria(AMateria* m);
    AMateria* createMateria(std::string const & type);
};
```

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
    
    delete m; // Source pleine
}
```

**createMateria()** :
```cpp
AMateria* MateriaSource::createMateria(std::string const & type) {
    for (int i = 0; i < 4; i++) {
        if (_templates[i] && _templates[i]->getType() == type) {
            return _templates[i]->clone(); // Pattern Prototype
        }
    }
    return NULL; // Type inconnu
}
```

### 🧪 Tests et analyse du main

#### **Test 1 : Main du sujet**

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

me->use(0, *bob);
me->use(1, *bob);

delete bob;
delete me;
delete src;
```

**Sortie attendue** :
```
* shoots an ice bolt at bob *
* heals bob's wounds *
```

**Ce que tu dois expliquer** :
- `learnMateria()` stocke les templates
- `createMateria()` utilise `clone()` pour créer des copies
- `use()` appelle la bonne méthode grâce au polymorphisme

#### **Test 2 : Deep Copy**

```cpp
Character* original = new Character("Hero");
original->equip(new Ice());
original->equip(new Cure());

Character* copy = new Character(*original);

original->use(0, dummy); // Ice
copy->use(0, dummy);     // Ice (copie indépendante)

delete original; // Pas de crash
delete copy;     // Pas de crash
```

**Ce que tu dois expliquer** :
- Le constructeur de copie fait une deep copy de l'inventaire
- Chaque Character a ses propres Materias
- Pas de shared pointers

#### **Test 3 : Inventaire plein**

```cpp
Character* hero = new Character("Hero");
hero->equip(new Ice());
hero->equip(new Cure());
hero->equip(new Ice());
hero->equip(new Cure());
hero->equip(new Ice()); // 5ème materia
```

**Sortie attendue** :
```
Hero's inventory is full! Materia dropped on the floor.
```

#### **Test 4 : Unequip**

```cpp
hero->equip(new Ice());
hero->use(0, target);  // * shoots an ice bolt at Target *
hero->unequip(0);      // Retire sans delete
hero->use(0, target);  // No materia in slot 0!
```

#### **Test 5 : Type inconnu**

```cpp
IMateriaSource* src = new MateriaSource();
src->learnMateria(new Ice());

AMateria* tmp = src->createMateria("cure"); // Pas appris
// tmp == NULL
```

#### **Test 6 : Clone**

```cpp
AMateria* original = new Ice();
AMateria* cloned = original->clone();

std::cout << "Original type: " << original->getType() << std::endl; // ice
std::cout << "Cloned type: " << cloned->getType() << std::endl;     // ice

Character target("Target");
original->use(target); // * shoots an ice bolt at Target *
cloned->use(target);   // * shoots an ice bolt at Target *

delete original;
delete cloned;
```

### ❓ Questions attendues

**Q1 : "Quelle est la différence entre une classe abstraite et une interface ?"**

**R1 :**
- **Classe abstraite** : Peut avoir des méthodes concrètes ET des méthodes pures
  - Ex: `AMateria` (a `getType()` concrète et `clone()` pure)
- **Interface** : TOUTES les méthodes sont pures
  - Ex: `ICharacter`, `IMateriaSource`

**Q2 : "Pourquoi utiliser clone() au lieu d'un constructeur de copie ?"**

**R2 :**
- **Pattern Prototype** : On peut copier sans connaître le type exact
- `AMateria* copy = original->clone();` fonctionne même si on ne sait pas si c'est Ice ou Cure
- Très utile pour `MateriaSource::createMateria()`

**Q3 : "Pourquoi unequip() ne fait pas delete ?"**

**R3 :**
- On ne sait pas si quelqu'un d'autre a une référence
- Si on `delete`, risque de **double-free** ou **use-after-free**
- Solution : stocker sur le "floor", nettoyer dans le destructeur

**Q4 : "Que se passe-t-il si on appelle use() sur un slot vide ?"**

**R4 :**
```cpp
if (!_inventory[idx]) {
    std::cout << "No materia in slot " << idx << "!" << std::endl;
    return;
}
```
Rien ne crash, message informatif.

**Q5 : "Pourquoi le type n'est pas copié dans operator= d'AMateria ?"**

**R5 :**
- Requis par le sujet 42
- Conceptuellement : un Ice reste un Ice
- Assigner un Cure à un Ice ne change pas le type

### 🎯 Commandes de test

```bash
cd ex03

# Compilation
make

# Exécution
./materia

# Test de memory leaks (CRITIQUE)
valgrind --leak-check=full ./materia

# Doit afficher :
# All heap blocks were freed -- no leaks are possible

# Nettoyage
make fclean
```

### 📊 Diagramme des patterns

```
Pattern Prototype (clone):
  AMateria* template = new Ice();
  AMateria* copy = template->clone();

Pattern Factory (createMateria):
  MateriaSource* src = new MateriaSource();
  src->learnMateria(new Ice());
  AMateria* ice = src->createMateria("ice");

Pattern Interface (ICharacter):
  ICharacter* hero = new Character("Hero");
  hero->equip(ice);
```

### ⚠️ Pièges et erreurs courantes

1. **Delete dans unequip()** → Double-free
2. **Pas de floor** → Memory leak avec unequip
3. **Oublier clone() dans createMateria()** → Toutes les Materias partagent la même instance
4. **Ne pas vérifier NULL** → Segfault
5. **Oublier le destructeur virtuel dans les interfaces** → Memory leak

---

Bon courage pour ton évaluation ! 🎓
