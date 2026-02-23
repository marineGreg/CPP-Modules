# Guide CPP04 - Exercise 01 : Brain et Deep Copy

## 📋 Objectif de l'exercice

Comprendre et implémenter la **copie profonde (Deep Copy)** en C++ avec gestion de la mémoire dynamique :
- Allocation dynamique de ressources (`Brain*`)
- Constructeur de copie et opérateur d'assignation corrects
- Éviter les **shallow copies** qui causent des crashs

## 🎯 Concepts clés

### 1. Le problème de la Shallow Copy

**Sans copie profonde** :
```cpp
class Dog {
    Brain* _brain;
public:
    Dog() { _brain = new Brain(); }
    ~Dog() { delete _brain; }
    // Pas de constructeur de copie personnalisé
};

Dog original;
Dog copy = original; // Shallow copy : les deux pointent vers le même Brain
// Quand copy est détruit -> delete _brain
// Quand original est détruit -> delete _brain ENCORE -> CRASH !
```

### 2. La Deep Copy (Copie profonde)

**Avec copie profonde** :
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    _brain = new Brain(*other._brain); // Nouvelle allocation !
}
```
→ Chaque objet a son **propre** `Brain`, ils sont indépendants.

### 3. La classe Brain

```cpp
class Brain {
    std::string ideas[100]; // 100 idées
};
```

- Chaque `Dog` et `Cat` possède un `Brain*`
- Le `Brain` est alloué dynamiquement (`new Brain()`)
- Le `Brain` doit être correctement copié et détruit

## 📁 Structure de l'exercice

```
ex01/
├── Animal.hpp          # Classe de base (inchangée depuis ex00)
├── Animal.cpp
├── Dog.hpp             # Dog avec Brain*
├── Dog.cpp
├── Cat.hpp             # Cat avec Brain*
├── Cat.cpp
├── Brain.hpp           # Nouvelle classe Brain
├── Brain.cpp
├── WrongAnimal.hpp     # Gardés pour comparaison
├── WrongAnimal.cpp
├── WrongCat.hpp
├── WrongCat.cpp
├── main.cpp            # Tests de deep copy
└── Makefile
```

## 🔧 Implémentation

### Brain.hpp

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

### Brain.cpp

```cpp
Brain::Brain() {
    std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain& other) {
    std::cout << "Brain copy constructor called" << std::endl;
    *this = other;
}

Brain& Brain::operator=(const Brain& other) {
    std::cout << "Brain assignment operator called" << std::endl;
    if (this != &other) {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = other.ideas[i];
    }
    return *this;
}

Brain::~Brain() {
    std::cout << "Brain destructor called" << std::endl;
}
```

### Dog.hpp

```cpp
class Dog : public Animal {
	private:
    	Brain* _brain; // Pointeur vers Brain

	public:
    	Dog();
    	Dog(const Dog& other);
    	Dog& operator=(const Dog& other);
    	~Dog();

    	void makeSound() const;
};
```

### Dog.cpp - Les points critiques

**Constructeur** :
```cpp
Dog::Dog() : Animal() {
    std::cout << "Dog constructor called" << std::endl;
    _brain = new Brain(); // Allocation dynamique
}
```

**Constructeur de copie** (DEEP COPY) :
```cpp
Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
    _brain = new Brain(*other._brain); // Nouvelle allocation + copie du contenu
}
```
⚠️ **CRITIQUE** : On crée un **nouveau** `Brain`, on ne copie pas le pointeur !

**Opérateur d'assignation** :
```cpp
Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        delete _brain;                    // Libère l'ancien Brain
        _brain = new Brain(*other._brain); // Nouvelle allocation
    }
    return *this;
}
```
⚠️ **CRITIQUE** : On **delete** l'ancien avant d'allouer le nouveau.

**Destructeur** :
```cpp
Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
    delete _brain; // Libération de la mémoire
}
```

## 🧪 Tests dans main.cpp

### Test 1 : Création et destruction d'un tableau

```cpp
const int count = 4;
Animal* animals[count];

for (int i = 0; i < count; i++) {
    if (i < count / 2)
        animals[i] = new Dog();
    else
        animals[i] = new Cat();
}

for (int i = 0; i < count; i++) {
    delete animals[i]; // Doit appeler les destructeurs Dog/Cat ET Brain
}
```

**Vérifications** :
- Les destructeurs de `Dog`/`Cat` sont appelés (polymorphisme)
- Les destructeurs de `Brain` sont appelés (pas de memory leak)

### Test 2 : Deep Copy Test (Le plus important)

```cpp
Dog basic;
{
    Dog tmp = basic; // Constructeur de copie
} // tmp est détruit ici

std::cout << "Basic dog is still alive!" << std::endl; // Pas de crash !
```

**Ce qui se passe** :
1. `basic` est créé → alloue un `Brain`
2. `tmp` est créé par copie → alloue un **nouveau** `Brain` (deep copy)
3. `tmp` est détruit → libère **son** `Brain`
4. `basic` reste vivant → a toujours **son propre** `Brain`

**Sans deep copy** : Crash à l'étape 4 car le `Brain` de `basic` a déjà été détruit.

## 🎓 Points clés pour l'évaluation

### Question 1 : "Pourquoi a-t-on besoin d'une deep copy ici ?"

**Réponse** :
- `Dog` et `Cat` possèdent un `Brain*` (pointeur)
- Si on fait une shallow copy, les deux objets partagent le même `Brain`
- Quand un objet est détruit, il `delete _brain`
- L'autre objet a maintenant un **pointeur dangling** → crash

### Question 2 : "Que se passe-t-il si on oublie de delete _brain dans l'opérateur d'assignation ?"

**Réponse** :
- **Memory leak** : l'ancien `Brain` n'est jamais libéré
- À chaque assignation, on perd la référence vers l'ancien `Brain`

### Question 3 : "Pourquoi utilise-t-on new Brain(*other._brain) et pas new Brain() ?"

**Réponse** :
- `new Brain()` crée un `Brain` vide
- `new Brain(*other._brain)` crée un `Brain` et copie le contenu (les 100 idées)
- C'est ça la **deep copy** : on copie la structure ET le contenu

## 🔄 Ordre d'exécution

**Création d'un Dog** :
```
1. Animal default constructor
2. Dog constructor
3. Brain constructor
```

**Copie d'un Dog** :
```
1. Animal copy constructor
2. Animal assignment operator
3. Dog copy constructor
4. Brain copy constructor
5. Brain assignment operator
```

**Destruction d'un Dog** :
```
1. Dog destructor
2. Brain destructor
3. Animal destructor
```

## ⚠️ Erreurs courantes

1. **Oublier le destructeur virtuel dans Animal** → Memory leak
2. **Faire une shallow copy** → Crash
3. **Ne pas appeler Animal::operator= dans Dog::operator=** → Perte de données
4. **Oublier de delete l'ancien _brain dans operator=** → Memory leak

## ✅ Points de vérification

- [ ] Tous les destructeurs sont appelés dans le bon ordre
- [ ] Le test de deep copy ne crash pas
- [ ] Pas de memory leak (utiliser `valgrind`)
- [ ] Les constructeurs de copie font des deep copies
- [ ] Les opérateurs d'assignation gèrent l'auto-assignation

---

**Résumé** : Cet exercice enseigne la gestion correcte de la mémoire dynamique en C++ avec le polymorphisme. La **deep copy** est essentielle pour éviter les crashs et les memory leaks. 🧠
