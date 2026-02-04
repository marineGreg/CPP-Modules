# Guide CPP02 - Exercice 00 : My First Class in Orthodox Canonical Form

## 📋 Objectif de l'exercice

Créer une classe `Fixed` qui représente un nombre à **virgule fixe** (fixed-point number) en respectant la **Forme Canonique Orthodoxe** (Orthodox Canonical Form). Cet exercice introduit les concepts fondamentaux de la gestion de classe en C++.

---

## 🎯 Qu'est-ce qu'un nombre à virgule fixe ?

### Différence avec les nombres flottants

| Type | Description | Exemple |
|------|-------------|---------|
| **Float/Double** | Virgule **flottante** - précision variable | 3.14159, 0.0001 |
| **Fixed-point** | Virgule **fixe** - nombre de décimales constant | 42.25 (toujours 8 bits fractionnaires) |

### Représentation interne

Un nombre à virgule fixe stocke :
- Une partie **entière**
- Une partie **fractionnaire**

Le tout dans un **seul entier** !

**Exemple avec 8 bits fractionnaires :**
```
Nombre: 42.25
Représentation: 42.25 × 2^8 = 42.25 × 256 = 10816

En binaire:
  42      .     25
101010  .  01000000
  ↓           ↓
partie     partie
entière    fractionnaire
```

---

## 🏗️ La Forme Canonique Orthodoxe (OCF)

### Les 4 piliers obligatoires

Toute classe bien conçue en C++ doit implémenter :

1. **Constructeur par défaut** : `Fixed()`
2. **Constructeur de recopie** : `Fixed(const Fixed &src)`
3. **Opérateur d'affectation** : `Fixed &operator=(const Fixed &rhs)`
4. **Destructeur** : `~Fixed()`

### Pourquoi c'est important ?

Sans ces éléments, le compilateur génère des versions par défaut qui peuvent causer :
- ❌ Fuites mémoire
- ❌ Double free
- ❌ Copies superficielles (shallow copy)

---

## 📝 Structure de la classe Fixed

### Fixed.hpp

```cpp
class Fixed
{
    private:
        int                 _value;      // Valeur brute du nombre fixe
        static const int    _bits = 8;   // Nombre de bits fractionnaires

    public:
        // --- Forme Canonique Orthodoxe ---
        Fixed();                            // Constructeur par défaut
        Fixed(const Fixed &src);            // Constructeur de recopie
        Fixed &operator=(const Fixed &rhs); // Opérateur d'affectation
        ~Fixed();                           // Destructeur

        // --- Fonctions membres ---
        int     getRawBits(void) const;     // Getter
        void    setRawBits(int const raw);  // Setter
};
```

**Points clés :**
- `_value` : Stocke la valeur brute (raw value)
- `_bits` : Constante statique (8 bits = 256 positions fractionnaires)
- `const` après `getRawBits()` : fonction ne modifie pas l'objet

---

## 🔍 Implémentation détaillée

### 1. Constructeur par défaut

```cpp
Fixed::Fixed() : _value(0) {
    std::cout << "Default constructor called" << std::endl;
}
```

**Rôle :**
- Initialise `_value` à 0
- Liste d'initialisation : `: _value(0)` (plus efficace que `_value = 0;` dans le corps)
- Affiche un message pour tracer les appels

**Utilisation :**
```cpp
Fixed a;  // Appelle le constructeur par défaut
```

---

### 2. Constructeur de recopie

```cpp
Fixed::Fixed(const Fixed &src) {
    std::cout << "Copy constructor called" << std::endl;
    *this = src;  // Utilise l'opérateur d'affectation
}
```

**Rôle :**
- Crée une **copie** d'un objet existant
- `*this = src` : délègue la copie à l'opérateur `=`

**Utilisation :**
```cpp
Fixed a;
Fixed b(a);    // Appelle le constructeur de recopie
Fixed c = a;   // Appelle aussi le constructeur de recopie !
```

**⚠️ Attention :**
```cpp
Fixed c = a;  // ≠ opérateur d'affectation
              // C'est une INITIALISATION → constructeur de recopie
```

---

### 3. Opérateur d'affectation

```cpp
Fixed &Fixed::operator=(const Fixed &rhs) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs) {                    // Protection auto-affectation
        this->_value = rhs.getRawBits();   // Copie la valeur
    }
    return *this;                          // Retourne *this pour chaînage
}
```

**Rôle :**
- Copie les données d'un objet vers un autre **déjà existant**
- `if (this != &rhs)` : évite l'auto-affectation (`a = a;`)
- `return *this` : permet le chaînage (`a = b = c;`)

**Utilisation :**
```cpp
Fixed a;
Fixed b;
b = a;  // Appelle l'opérateur d'affectation
```

**Différence avec le constructeur de recopie :**

```cpp
Fixed b(a);   // Construction → Constructeur de recopie
Fixed b = a;  // Construction → Constructeur de recopie

Fixed b;
b = a;        // Affectation → Opérateur d'affectation
```

---

### 4. Destructeur

```cpp
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}
```

**Rôle :**
- Libère les ressources (ici, rien à libérer)
- Appelé automatiquement à la fin de vie de l'objet
- Ordre d'appel : inverse de la construction (LIFO)

**Utilisation automatique :**
```cpp
{
    Fixed a;  // Constructeur appelé
    Fixed b;  // Constructeur appelé
}  // Destructeurs appelés : b puis a
```

---

### 5. Getter et Setter

```cpp
int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return this->_value;
}

void Fixed::setRawBits(int const raw) {
    std::cout << "setRawBits member function called" << std::endl;
    this->_value = raw;
}
```

**Rôle :**
- **getRawBits()** : retourne la valeur brute
  - `const` après la fonction : ne modifie pas l'objet
- **setRawBits()** : modifie la valeur brute

---

## 🧪 Test et analyse du main

### Code du main

```cpp
int main(void)
{
    Fixed   a;          // 1. Constructeur par défaut
    Fixed   b(a);       // 2. Constructeur de recopie
    Fixed   c;          // 3. Constructeur par défaut
    
    c = b;              // 4. Opérateur d'affectation

    std::cout << a.getRawBits() << std::endl;  // 5. Getter
    std::cout << b.getRawBits() << std::endl;  // 6. Getter
    std::cout << c.getRawBits() << std::endl;  // 7. Getter

    return 0;           // 8. Destructeurs de c, b, a
}
```

### Sortie attendue

```
Default constructor called           ← a
Copy constructor called              ← b(a)
Default constructor called           ← c
Copy assignment operator called      ← c = b
getRawBits member function called    ← a.getRawBits()
0                                    ← valeur de a
getRawBits member function called    ← b.getRawBits()
0                                    ← valeur de b
getRawBits member function called    ← c.getRawBits()
0                                    ← valeur de c
Destructor called                    ← ~c
Destructor called                    ← ~b
Destructor called                    ← ~a
```

### Analyse détaillée

| Ligne | Action | Fonction appelée |
|-------|--------|------------------|
| `Fixed a;` | Création de `a` | Constructeur par défaut |
| `Fixed b(a);` | Copie de `a` dans `b` | Constructeur de recopie |
| `Fixed c;` | Création de `c` | Constructeur par défaut |
| `c = b;` | Affectation de `b` à `c` | Opérateur `=` |
| `a.getRawBits()` | Lecture de `a` | Getter (affiche 0) |
| `b.getRawBits()` | Lecture de `b` | Getter (affiche 0) |
| `c.getRawBits()` | Lecture de `c` | Getter (affiche 0) |
| `}` | Fin du scope | Destructeurs (c, b, a) |

---

## 💡 Concepts clés

### 1. Liste d'initialisation vs Corps du constructeur

```cpp
// ✅ PRÉFÉRÉ : Liste d'initialisation
Fixed::Fixed() : _value(0) {
    // Corps vide
}

// ⚠️ Moins efficace : Affectation dans le corps
Fixed::Fixed() {
    _value = 0;  // Initialisation par défaut puis affectation
}
```

**Pourquoi ?**
- Liste d'initialisation = initialisation directe
- Corps = initialisation par défaut + affectation

### 2. Protection contre l'auto-affectation

```cpp
Fixed &Fixed::operator=(const Fixed &rhs) {
    if (this != &rhs) {  // ← IMPORTANT !
        // copie
    }
    return *this;
}
```

**Sans cette protection :**
```cpp
Fixed a;
a = a;  // Sans protection, comportement indéfini si ressources dynamiques !
```

### 3. Retour par référence de l'opérateur =

```cpp
Fixed &operator=(const Fixed &rhs);  // Retourne Fixed&
```

**Permet le chaînage :**
```cpp
Fixed a, b, c;
a = b = c;  // Équivaut à : a = (b = c);
```

### 4. Const correctness

```cpp
int getRawBits(void) const;  // ← const = ne modifie pas l'objet
```

**Permet :**
```cpp
const Fixed a;
a.getRawBits();  // ✅ OK : fonction const
a.setRawBits(5); // ❌ ERREUR : fonction non-const
```

---

## 🔧 Attribut statique

### Déclaration et utilisation

```cpp
class Fixed {
    static const int _bits = 8;  // Initialisé dans la déclaration (C++11)
};
```

**Caractéristiques :**
- **Statique** : partagé par toutes les instances
- **const** : ne peut pas être modifié
- Accessible via `Fixed::_bits` ou `this->_bits`

**Avant C++11 :**
```cpp
// Fixed.hpp
class Fixed {
    static const int _bits;
};

// Fixed.cpp
const int Fixed::_bits = 8;  // Définition obligatoire
```

---

## 🎓 Différences importantes

### Constructeur de recopie vs Opérateur d'affectation

| Critère | Constructeur de recopie | Opérateur d'affectation |
|---------|-------------------------|-------------------------|
| **Quand ?** | Création d'un nouvel objet | Objet déjà existant |
| **Syntaxe** | `Fixed b(a);` ou `Fixed b = a;` | `b = a;` |
| **Retour** | Rien (constructeur) | `*this` (référence) |
| **Ancienne valeur** | Pas d'ancienne valeur | Doit gérer l'ancienne valeur |

### Exemple complet

```cpp
Fixed a;           // Constructeur par défaut
Fixed b(a);        // Constructeur de recopie
Fixed c = a;       // Constructeur de recopie (pas opérateur =)
Fixed d;           // Constructeur par défaut
d = a;             // Opérateur d'affectation
```

---

## 📚 Vocabulaire C++

| Terme | Anglais | Description |
|-------|---------|-------------|
| Forme Canonique Orthodoxe | Orthodox Canonical Form (OCF) | 4 fonctions essentielles |
| Constructeur de recopie | Copy constructor | Crée copie d'un objet |
| Opérateur d'affectation | Copy assignment operator | Assigne valeur d'un objet |
| Liste d'initialisation | Initialization list | `: _value(0)` |
| Auto-affectation | Self-assignment | `a = a;` |
| Const correctness | Const correctness | Bon usage de `const` |
| Virgule fixe | Fixed-point | Nombre avec décimales fixes |

---

## ✅ Checklist de validation

- [ ] La classe Fixed est définie dans Fixed.hpp
- [ ] Les 4 fonctions de la forme canonique orthodoxe sont présentes
- [ ] Le constructeur par défaut initialise `_value` à 0
- [ ] Le constructeur de recopie utilise l'opérateur d'affectation
- [ ] L'opérateur d'affectation protège contre l'auto-affectation
- [ ] L'opérateur d'affectation retourne `*this`
- [ ] getRawBits() est déclaré `const`
- [ ] Tous les constructeurs/destructeurs affichent un message
- [ ] La sortie du programme correspond exactement à celle attendue
- [ ] Compilation sans erreur avec `-Wall -Wextra -Werror -std=c++98`

---

## 🚨 Erreurs courantes

### 1. Oublier le const dans getRawBits

```cpp
// ❌ FAUX
int getRawBits(void);

// ✅ CORRECT
int getRawBits(void) const;
```

### 2. Ne pas protéger contre l'auto-affectation

```cpp
// ❌ DANGEREUX
Fixed &operator=(const Fixed &rhs) {
    _value = rhs.getRawBits();  // OK ici mais dangereux avec pointeurs
    return *this;
}
```

### 3. Oublier de retourner *this

```cpp
// ❌ FAUX - empêche le chaînage
void operator=(const Fixed &rhs) {
    // ...
}

// ✅ CORRECT
Fixed &operator=(const Fixed &rhs) {
    // ...
    return *this;
}
```

### 4. Confondre initialisation et affectation

```cpp
Fixed a;
Fixed b = a;  // ← Constructeur de recopie, PAS opérateur =
Fixed c;
c = a;        // ← Opérateur d'affectation
```

---

## 🎯 Objectif pédagogique

Cet exercice vous apprend à :

1. ✅ Implémenter la **Forme Canonique Orthodoxe**
2. ✅ Comprendre la différence entre constructeur de recopie et opérateur d'affectation
3. ✅ Utiliser les **listes d'initialisation**
4. ✅ Protéger contre l'**auto-affectation**
5. ✅ Comprendre le concept de **virgule fixe**
6. ✅ Maîtriser la **const correctness**
7. ✅ Utiliser les attributs **statiques**

---

## 🔮 Pour aller plus loin

### Pourquoi 8 bits fractionnaires ?

Avec 8 bits fractionnaires (2^8 = 256) :

```
0.00390625 = 1/256     → précision minimale
42.25 × 256 = 10816    → valeur stockée

Pour convertir :
  int → fixed: valeur × 256
  fixed → int: valeur / 256
```

### Exercices suivants

- **ex01** : Ajout de constructeurs avec conversions (int, float)
- **ex02** : Surcharge des opérateurs arithmétiques et de comparaison

---

## 📖 Ressources

- **Orthodox Canonical Form** : Standard C++ pour classes bien conçues
- **Fixed-point arithmetic** : Alternative aux nombres flottants
- **Const correctness** : Principe de conception C++
- **Copy semantics** : Gestion des copies en C++

---

**Bon courage ! 🚀**

Ce premier exercice pose les bases essentielles pour tous les modules suivants. Prenez le temps de bien comprendre chaque concept !
