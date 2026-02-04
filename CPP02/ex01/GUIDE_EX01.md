# Guide CPP02 - Exercice 01 : Towards a more useful fixed-point number class

## 📋 Objectif de l'exercice

Améliorer la classe `Fixed` en ajoutant des **constructeurs de conversion** (int, float) et des **fonctions de conversion** (toFloat, toInt), ainsi que la surcharge de l'**opérateur d'insertion** `<<` pour faciliter l'affichage.

---

## 🎯 Nouveautés par rapport à l'ex00

| Fonctionnalité | Ex00 | Ex01 |
|----------------|------|------|
| **Constructeur par défaut** | ✅ | ✅ |
| **Constructeur de recopie** | ✅ | ✅ |
| **Opérateur d'affectation** | ✅ | ✅ |
| **Destructeur** | ✅ | ✅ |
| **Constructeur(int)** | ❌ | ✅ **NOUVEAU** |
| **Constructeur(float)** | ❌ | ✅ **NOUVEAU** |
| **toFloat()** | ❌ | ✅ **NOUVEAU** |
| **toInt()** | ❌ | ✅ **NOUVEAU** |
| **operator<<** | ❌ | ✅ **NOUVEAU** |

---

## 🏗️ Structure de la classe Fixed

### Fixed.hpp

```cpp
#include <iostream>
#include <cmath>  // Pour roundf()

class Fixed {
    private:
        int                 _value;      // Valeur brute
        static const int    _bits = 8;   // 8 bits fractionnaires

    public:
        // --- Forme Canonique Orthodoxe ---
        Fixed();
        Fixed(const Fixed &src);
        Fixed &operator=(const Fixed &rhs);
        ~Fixed();

        // --- Constructeurs de conversion (NOUVEAU) ---
        Fixed(const int n);       // int → Fixed
        Fixed(const float n);     // float → Fixed

        // --- Fonctions membres ---
        int     getRawBits(void) const;
        void    setRawBits(int const raw);
        
        // --- Conversions (NOUVEAU) ---
        float   toFloat(void) const;    // Fixed → float
        int     toInt(void) const;      // Fixed → int
};

// --- Surcharge opérateur << (NOUVEAU) ---
std::ostream &operator<<(std::ostream &o, Fixed const &i);
```

---

## 🔍 Implémentation détaillée

### 1. Constructeur Fixed(int)

```cpp
Fixed::Fixed(const int n) {
    std::cout << "Int constructor called" << std::endl;
    this->_value = n << _bits;  // Décalage de 8 bits = multiplication par 256
}
```

**Explication :**
- Convertit un entier en nombre à virgule fixe
- `n << 8` équivaut à `n * 256` (décalage binaire)
- Exemple : `42` → `42 × 256 = 10752`

**Détail binaire :**
```
42 en binaire :     00101010
42 << 8 :           00101010 00000000  (10752 en décimal)
                        ↑       ↑
                    partie   partie
                    entière  fractionnaire
```

**Utilisation :**
```cpp
Fixed a(42);        // Appelle Fixed(int)
Fixed b = 10;       // Appelle aussi Fixed(int)
```

---

### 2. Constructeur Fixed(float)

```cpp
Fixed::Fixed(const float n) {
    std::cout << "Float constructor called" << std::endl;
    this->_value = roundf(n * (1 << _bits));  // n * 256 avec arrondi
}
```

**Explication :**
- Convertit un float en nombre à virgule fixe
- `(1 << _bits)` = `1 << 8` = 256
- `roundf()` arrondit au plus proche (évite les erreurs de troncature)
- Exemple : `42.42f` → `42.42 × 256 = 10859.52` → `10860` (arrondi)

**Pourquoi roundf() ?**
```cpp
// Sans arrondi (troncature)
42.99 * 256 = 11005.44 → 11005  ❌ perd 0.44

// Avec arrondi
42.99 * 256 = 11005.44 → 11005  ✅ (arrondi au plus proche)
```

**Utilisation :**
```cpp
Fixed a(42.42f);    // Appelle Fixed(float)
Fixed b = 3.14f;    // Appelle aussi Fixed(float)
```

---

### 3. Fonction toFloat()

```cpp
float Fixed::toFloat(void) const {
    return (float)this->_value / (1 << _bits);  // Division par 256
}
```

**Explication :**
- Convertit la valeur brute en float
- `/ (1 << 8)` = `/ 256`
- Cast en `(float)` pour avoir un résultat décimal
- Exemple : `10860` → `10860 / 256.0 = 42.421875`

**Détail :**
```cpp
_value = 10860
(1 << _bits) = 256
10860 / 256 = 42.421875
```

---

### 4. Fonction toInt()

```cpp
int Fixed::toInt(void) const {
    return this->_value >> _bits;  // Décalage = division entière par 256
}
```

**Explication :**
- Convertit la valeur brute en int (partie entière)
- `>> 8` équivaut à `/= 256` (division entière)
- Exemple : `10860` → `10860 >> 8 = 42`

**Détail binaire :**
```
10860 en binaire :  00101010 01101100
10860 >> 8 :               00101010  (42 en décimal)
                               ↑
                          partie entière
```

---

### 5. Surcharge de l'opérateur <<

```cpp
std::ostream &operator<<(std::ostream &o, Fixed const &i) {
    o << i.toFloat();  // Affiche la représentation float
    return o;          // Retourne le flux pour chaînage
}
```

**Points importants :**
- **Fonction externe** (pas membre de la classe)
- `std::ostream &o` : flux de sortie (std::cout par exemple)
- `Fixed const &i` : objet Fixed à afficher (par référence constante)
- `return o` : permet le chaînage (`std::cout << a << b << c;`)

**Utilisation :**
```cpp
Fixed a(42.42f);
std::cout << a;           // Affiche : 42.4219
std::cout << a << "\n";   // Chaînage possible
```

**Pourquoi externe ?**
```cpp
// ❌ Si membre de classe :
a.operator<<(std::cout);  // Syntaxe bizarre !

// ✅ Fonction externe :
std::cout << a;           // Syntaxe naturelle !
```

---

## 🧪 Test et analyse du main

### Code du main

```cpp
int main(void)
{
    Fixed       a;                  // 1. Constructeur par défaut
    Fixed const b(10);              // 2. Constructeur(int) avec 10
    Fixed const c(42.42f);          // 3. Constructeur(float) avec 42.42
    Fixed const d(b);               // 4. Constructeur de recopie
    
    a = Fixed(1234.4321f);          // 5. Constructeur(float) + opérateur=

    std::cout << "a is " << a << std::endl;  // 6. operator<<
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    std::cout << "a is " << a.toInt() << " as an integer" << std::endl;  // 7. toInt()
    std::cout << "b is " << b.toInt() << " as an integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as an integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as an integer" << std::endl;

    return 0;
}
```

### Sortie attendue

```
Default constructor called              ← a
Int constructor called                  ← b(10)
Float constructor called                ← c(42.42f)
Copy constructor called                 ← d(b)
Float constructor called                ← Fixed(1234.4321f) temporaire
Copy assignment operator called         ← a = ...
Destructor called                       ← ~temporaire
a is 1234.43                            ← a.toFloat()
b is 10                                 ← b.toFloat()
c is 42.4219                            ← c.toFloat()
d is 10                                 ← d.toFloat()
a is 1234 as an integer                 ← a.toInt()
b is 10 as an integer                   ← b.toInt()
c is 42 as an integer                   ← c.toInt()
d is 10 as an integer                   ← d.toInt()
Destructor called                       ← ~d
Destructor called                       ← ~c
Destructor called                       ← ~b
Destructor called                       ← ~a
```

### Analyse détaillée

| Ligne | Explication | Fonction appelée |
|-------|-------------|------------------|
| `Fixed a;` | Création par défaut | Constructeur par défaut |
| `Fixed const b(10);` | Conversion int → Fixed | Constructeur(int) |
| `Fixed const c(42.42f);` | Conversion float → Fixed | Constructeur(float) |
| `Fixed const d(b);` | Copie de b | Constructeur de recopie |
| `a = Fixed(1234.4321f);` | Objet temporaire + affectation | Constructeur(float) + opérateur= + destructeur |
| `std::cout << a` | Affichage via toFloat() | operator<< + toFloat() |
| `a.toInt()` | Conversion en int | toInt() |

---

## 💡 Concepts clés

### 1. Décalage binaire vs multiplication

```cpp
// Ces deux lignes sont équivalentes :
_value = n << 8;        // Décalage de 8 bits (RAPIDE)
_value = n * 256;       // Multiplication (plus lent)
```

**Avantages du décalage :**
- ⚡ Plus rapide (une seule instruction CPU)
- 💯 Utilisé pour les puissances de 2

**Table de correspondance :**
```
1 << 0 = 1
1 << 1 = 2
1 << 2 = 4
1 << 3 = 8
...
1 << 8 = 256
1 << 16 = 65536
```

### 2. Arrondi vs Troncature

```cpp
// AVEC arrondi (roundf)
42.99f * 256 = 11005.44 → 11005 (arrondi vers 11005)
43.01f * 256 = 11010.56 → 11011 (arrondi vers 11011)

// SANS arrondi (cast direct)
42.99f * 256 = 11005.44 → 11005 (troncature, perd 0.44)
43.01f * 256 = 11010.56 → 11010 (troncature, perd 0.56)
```

**Pourquoi c'est important ?**
```cpp
Fixed a(42.99f);
a.toFloat();  // Avec roundf: 42.99 (précis) ✅
              // Sans roundf: 42.98 (imprécis) ❌
```

### 3. Opérateur externe vs membre

| Type | Syntaxe déclaration | Syntaxe utilisation |
|------|---------------------|---------------------|
| **Membre** | `class A { void f(); };` | `a.f();` |
| **Externe** | `void f(A &a);` | `f(a);` |
| **Opérateur membre** | `class A { A operator+(A); };` | `a + b` → `a.operator+(b)` |
| **Opérateur externe** | `A operator+(A, A);` | `a + b` → `operator+(a, b)` |

**Pour operator<< :**
```cpp
// ❌ Impossible en membre car std::cout serait à droite
class Fixed {
    void operator<<(std::ostream &o);  // Donnerait: a << std::cout (bizarre!)
};

// ✅ En externe :
std::ostream &operator<<(std::ostream &o, Fixed const &f);  // std::cout << a
```

### 4. const correctness

```cpp
Fixed const b(10);  // Objet constant

b.toFloat();   // ✅ OK : toFloat() est const
b.toInt();     // ✅ OK : toInt() est const
b.setRawBits(5);  // ❌ ERREUR : setRawBits() n'est pas const
```

---

## 🧮 Conversions en détail

### Tableau de conversion

| Type | Valeur | Valeur brute (_value) | Calcul |
|------|--------|----------------------|--------|
| **int** | 42 | 10752 | 42 × 256 = 10752 |
| **float** | 42.42 | 10860 | 42.42 × 256 ≈ 10859.52 → 10860 |
| **float** | 1234.4321 | 316014 | 1234.4321 × 256 ≈ 316014.62 → 316015 |

### Précision

Avec 8 bits fractionnaires :
- **Précision minimale** : 1/256 = 0.00390625
- **Partie entière** : 24 bits (jusqu'à ±8 millions environ)
- **Partie fractionnaire** : 8 bits (256 positions)

**Exemple de précision :**
```cpp
Fixed a(42.123f);
a.toFloat();  // Résultat: 42.1211 (pas exactement 42.123)
              // Car 256 positions fractionnaires = précision limitée
```

---

## 🎨 Différences entre constructeurs

### Quand chaque constructeur est appelé

```cpp
Fixed a;               // Constructeur par défaut
Fixed b(42);           // Constructeur(int)
Fixed c = 42;          // Constructeur(int) aussi !
Fixed d(42.42f);       // Constructeur(float)
Fixed e = 42.42f;      // Constructeur(float) aussi !
Fixed f(b);            // Constructeur de recopie
Fixed g = b;           // Constructeur de recopie aussi !

Fixed h;
h = b;                 // Opérateur d'affectation (h existe déjà)
```

### Initialisation vs Affectation

```cpp
// INITIALISATION (= constructeur)
Fixed a = 42;          // Appelle Fixed(int), PAS operator=

// AFFECTATION (= operator=)
Fixed a;
a = 42;                // 1. Appelle Fixed(int) pour créer temporaire
                       // 2. Appelle operator= pour copier
                       // 3. Détruit le temporaire
```

---

## 🚨 Erreurs courantes

### 1. Oublier l'arrondi dans Fixed(float)

```cpp
// ❌ FAUX - perte de précision
Fixed::Fixed(const float n) {
    _value = n * (1 << _bits);  // Troncature !
}

// ✅ CORRECT
Fixed::Fixed(const float n) {
    _value = roundf(n * (1 << _bits));  // Arrondi
}
```

### 2. Oublier le cast en float dans toFloat()

```cpp
// ❌ FAUX - division entière
float Fixed::toFloat(void) const {
    return _value / (1 << _bits);  // Résultat entier !
}

// ✅ CORRECT
float Fixed::toFloat(void) const {
    return (float)_value / (1 << _bits);  // Division décimale
}
```

### 3. Retourner void dans operator<<

```cpp
// ❌ FAUX - empêche le chaînage
void operator<<(std::ostream &o, Fixed const &i) {
    o << i.toFloat();
}

// ✅ CORRECT - permet le chaînage
std::ostream &operator<<(std::ostream &o, Fixed const &i) {
    o << i.toFloat();
    return o;  // Important !
}
```

### 4. Oublier #include <cmath>

```cpp
// ❌ FAUX
#include <iostream>
// Erreur: roundf() non déclaré

// ✅ CORRECT
#include <iostream>
#include <cmath>  // Pour roundf()
```

---

## ✅ Checklist de validation

- [ ] La classe Fixed compile sans erreur
- [ ] Le constructeur Fixed(int) utilise le décalage `<<`
- [ ] Le constructeur Fixed(float) utilise `roundf()`
- [ ] toFloat() retourne un float (avec cast)
- [ ] toInt() utilise le décalage `>>`
- [ ] operator<< est une fonction externe (pas membre)
- [ ] operator<< retourne `std::ostream&` pour permettre le chaînage
- [ ] operator<< appelle toFloat() pour l'affichage
- [ ] `#include <cmath>` est présent dans Fixed.hpp
- [ ] La sortie du programme correspond exactement à celle attendue
- [ ] Compilation sans erreur avec `-Wall -Wextra -Werror -std=c++98`

---

## 🎯 Objectif pédagogique

Cet exercice vous apprend à :

1. ✅ Créer des **constructeurs de conversion** (int, float)
2. ✅ Implémenter des **fonctions de conversion** (toFloat, toInt)
3. ✅ Utiliser les **opérateurs de décalage** (`<<`, `>>`)
4. ✅ Comprendre l'**arrondi vs troncature** (`roundf()`)
5. ✅ Surcharger l'**opérateur d'insertion** (`operator<<`)
6. ✅ Différencier **fonction membre vs externe**
7. ✅ Maîtriser les **conversions implicites**

---

## 📊 Comparaison Ex00 vs Ex01

| Aspect | Ex00 | Ex01 |
|--------|------|------|
| **Utilité** | Forme canonique uniquement | Classe utilisable ! |
| **Initialisation** | `setRawBits()` | `Fixed a(42);` |
| **Affichage** | `getRawBits()` | `std::cout << a;` |
| **Conversion** | Aucune | int ↔ Fixed ↔ float |
| **Complexité** | Basique | Pratique |

---

## 🔮 Pour aller plus loin

### Exercice suivant (ex02)

L'exercice 02 ajoutera :
- Opérateurs de comparaison (`<`, `>`, `<=`, `>=`, `==`, `!=`)
- Opérateurs arithmétiques (`+`, `-`, `*`, `/`)
- Opérateurs d'incrémentation (`++`, `--`)
- Fonctions min/max

### Opérateurs de conversion implicites (C++11)

```cpp
// Conversion implicite (moderne)
operator float() const { return toFloat(); }
operator int() const { return toInt(); }

// Utilisation
Fixed a(42.42f);
float f = a;  // Appelle operator float() automatiquement
```

---

**Bon courage ! 🚀**

Vous avez maintenant une classe Fixed fonctionnelle et utilisable !
