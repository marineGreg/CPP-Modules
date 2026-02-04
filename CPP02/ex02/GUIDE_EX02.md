# Guide CPP02 - Exercice 02 : Now we're talking

## 📋 Objectif de l'exercice

Compléter la classe `Fixed` avec la surcharge de **tous les opérateurs essentiels** : comparaisons, arithmétiques, incrémentation/décrémentation, et fonctions statiques min/max. C'est l'exercice qui rend la classe Fixed vraiment utilisable comme un type natif !

---

## 🎯 Nouveautés par rapport à l'ex01

| Catégorie | Opérateurs ajoutés |
|-----------|-------------------|
| **Comparaison** | `>` `<` `>=` `<=` `==` `!=` |
| **Arithmétique** | `+` `-` `*` `/` |
| **Incrémentation** | `++a` `a++` `--a` `a--` |
| **Fonctions statiques** | `min()` `max()` (versions const et non-const) |

**Résultat** : La classe Fixed se comporte maintenant comme un type natif (int, float) !

---

## 🏗️ Structure complète de la classe

### Fixed.hpp

```cpp
class Fixed {
private:
    int                 _value;
    static const int    _bits = 8;

public:
    // Forme Canonique Orthodoxe
    Fixed();
    Fixed(const int n);
    Fixed(const float n);
    Fixed(const Fixed &src);
    Fixed &operator=(const Fixed &rhs);
    ~Fixed();

    // Conversions
    int     getRawBits(void) const;
    void    setRawBits(int const raw);
    float   toFloat(void) const;
    int     toInt(void) const;

    // ✨ NOUVEAUX : Comparaisons
    bool operator>(const Fixed &rhs) const;
    bool operator<(const Fixed &rhs) const;
    bool operator>=(const Fixed &rhs) const;
    bool operator<=(const Fixed &rhs) const;
    bool operator==(const Fixed &rhs) const;
    bool operator!=(const Fixed &rhs) const;

    // ✨ NOUVEAUX : Arithmétiques
    Fixed operator+(const Fixed &rhs) const;
    Fixed operator-(const Fixed &rhs) const;
    Fixed operator*(const Fixed &rhs) const;
    Fixed operator/(const Fixed &rhs) const;

    // ✨ NOUVEAUX : Incrément / Décrément
    Fixed &operator++(void);       // Pré-incrément : ++a
    Fixed operator++(int);         // Post-incrément : a++
    Fixed &operator--(void);       // Pré-décrément : --a
    Fixed operator--(int);         // Post-décrément : a--

    // ✨ NOUVEAUX : Min / Max (Statiques)
    static Fixed &min(Fixed &a, Fixed &b);
    static const Fixed &min(const Fixed &a, const Fixed &b);
    static Fixed &max(Fixed &a, Fixed &b);
    static const Fixed &max(const Fixed &a, const Fixed &b);
};
```

---

## 🔍 Implémentation détaillée

### 1. Opérateurs de comparaison

```cpp
bool Fixed::operator>(const Fixed &rhs) const  { 
    return this->_value > rhs._value; 
}

bool Fixed::operator<(const Fixed &rhs) const  { 
    return this->_value < rhs._value; 
}

bool Fixed::operator>=(const Fixed &rhs) const { 
    return this->_value >= rhs._value; 
}

bool Fixed::operator<=(const Fixed &rhs) const { 
    return this->_value <= rhs._value; 
}

bool Fixed::operator==(const Fixed &rhs) const { 
    return this->_value == rhs._value; 
}

bool Fixed::operator!=(const Fixed &rhs) const { 
    return this->_value != rhs._value; 
}
```

**Points clés :**
- ✅ Comparent directement `_value` (valeur brute) → Efficace !
- ✅ `const` après la fonction : n'altère pas l'objet
- ✅ Retournent `bool`
- ✅ Peuvent accéder à `rhs._value` car fonction membre

**Utilisation :**
```cpp
Fixed a(42.42f);
Fixed b(10);

if (a > b)    // true
if (a == b)   // false
if (a != b)   // true
```

---

### 2. Opérateurs arithmétiques

```cpp
Fixed Fixed::operator+(const Fixed &rhs) const { 
    return Fixed(this->toFloat() + rhs.toFloat()); 
}

Fixed Fixed::operator-(const Fixed &rhs) const { 
    return Fixed(this->toFloat() - rhs.toFloat()); 
}

Fixed Fixed::operator*(const Fixed &rhs) const { 
    return Fixed(this->toFloat() * rhs.toFloat()); 
}

Fixed Fixed::operator/(const Fixed &rhs) const { 
    return Fixed(this->toFloat() / rhs.toFloat()); 
}
```

**Stratégie :**
1. Convertir les deux Fixed en float
2. Effectuer l'opération arithmétique
3. Créer un nouveau Fixed avec le résultat

**Pourquoi convertir en float ?**
```cpp
// ❌ APPROCHE DIRECTE (compliquée)
// Pour a * b en virgule fixe :
// result._value = (a._value * b._value) / 256  // Risque d'overflow !

// ✅ APPROCHE PAR CONVERSION (simple)
// Fixed(a.toFloat() * b.toFloat())  // Gère automatiquement la précision
```

**Utilisation :**
```cpp
Fixed a(5.05f);
Fixed b(2);

Fixed c = a + b;   // 7.05
Fixed d = a * b;   // 10.1
Fixed e = a / b;   // 2.525
```

---

### 3. Pré-incrémentation (++a)

```cpp
Fixed &Fixed::operator++(void) {
    this->_value++;    // Incrémente de 1 (la plus petite unité)
    return *this;      // Retourne la référence à l'objet modifié
}
```

**Caractéristiques :**
- Incrémente **puis** retourne la valeur
- Retourne une **référence** (`Fixed &`)
- Pas de paramètre
- Incrémente `_value` de 1 = ajoute 1/256 (≈ 0.00390625)

**Utilisation :**
```cpp
Fixed a(5);
Fixed b = ++a;   // a = 5.00390625, b = 5.00390625
```

---

### 4. Post-incrémentation (a++)

```cpp
Fixed Fixed::operator++(int) {
    Fixed tmp(*this);   // 1. Copie l'état actuel
    this->_value++;     // 2. Incrémente l'original
    return tmp;         // 3. Retourne l'ancienne valeur
}
```

**Caractéristiques :**
- Retourne la valeur **puis** incrémente
- Retourne une **copie** (pas de référence)
- Paramètre `int` factice (pour différencier de ++a)
- Moins efficace (crée une copie)

**Utilisation :**
```cpp
Fixed a(5);
Fixed b = a++;   // b = 5, a = 5.00390625
```

**Différence pré/post :**
```cpp
Fixed a(5);

std::cout << ++a;  // Affiche 5.00390625 (incrémente puis retourne)
std::cout << a++;  // Affiche 5.00390625 (retourne puis incrémente)
std::cout << a;    // Affiche 5.0078125
```

---

### 5. Décrém

entation (--a et a--)

```cpp
// Pré-décrément
Fixed &Fixed::operator--(void) {
    this->_value--;
    return *this;
}

// Post-décrément
Fixed Fixed::operator--(int) {
    Fixed tmp(*this);
    this->_value--;
    return tmp;
}
```

Même logique que `++`, mais décrémente au lieu d'incrémenter.

---

### 6. Fonctions statiques min et max

```cpp
// Version non-const
Fixed &Fixed::min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

// Version const
const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}

// Version non-const
Fixed &Fixed::max(Fixed &a, Fixed &b) {
    return (a > b) ? a : b;
}

// Version const
const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}
```

**Points clés :**
- **Statiques** : appelées via `Fixed::min(a, b)` (pas via objet)
- **Deux versions** : const et non-const
- Retournent une **référence** (pas de copie)
- Utilisent l'opérateur ternaire `? :`

**Pourquoi deux versions ?**
```cpp
Fixed a(5);
Fixed b(10);
const Fixed c(15);
const Fixed d(20);

Fixed::min(a, b);      // Version non-const ✅
Fixed::min(c, d);      // Version const ✅

// Sans la version const, Fixed::min(c, d) ne compilerait pas !
```

**Utilisation :**
```cpp
Fixed a(42);
Fixed b(10);

Fixed &smaller = Fixed::min(a, b);  // Référence à b
Fixed &larger = Fixed::max(a, b);   // Référence à a

smaller.setRawBits(100);  // Modifie b !
```

---

## 🧪 Test et analyse du main

### Code du main

```cpp
int main(void)
{
    Fixed       a;                              // a = 0
    Fixed const b(Fixed(5.05f) * Fixed(2));     // b = 10.1

    std::cout << a << std::endl;                // 0
    std::cout << ++a << std::endl;              // 0.00390625
    std::cout << a << std::endl;                // 0.00390625
    std::cout << a++ << std::endl;              // 0.00390625
    std::cout << a << std::endl;                // 0.0078125
    
    std::cout << b << std::endl;                // 10.1
    std::cout << Fixed::max(a, b) << std::endl; // 10.1

    return 0;
}
```

### Sortie attendue

```
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
```

### Analyse détaillée

| Ligne | Valeur de a | Valeur affichée | Explication |
|-------|-------------|-----------------|-------------|
| `Fixed a;` | 0 | - | Constructeur par défaut |
| `std::cout << a` | 0 | 0 | Affiche 0 |
| `++a` | 0.00390625 | 0.00390625 | Pré-incrémente puis affiche |
| `std::cout << a` | 0.00390625 | 0.00390625 | Affiche la valeur actuelle |
| `a++` | 0.0078125 | 0.00390625 | Affiche puis post-incrémente |
| `std::cout << a` | 0.0078125 | 0.0078125 | Affiche la valeur actuelle |
| `b` | 10.1016 | 10.1016 | 5.05 × 2 |
| `Fixed::max(a, b)` | - | 10.1016 | Retourne b (le plus grand) |

---

## 💡 Concepts clés

### 1. Pré-incrémentation vs Post-incrémentation

| Aspect | ++a (pré) | a++ (post) |
|--------|-----------|------------|
| **Ordre** | Incrémente puis retourne | Retourne puis incrémente |
| **Retour** | Référence (`Fixed &`) | Copie (`Fixed`) |
| **Efficacité** | ⚡ Rapide (pas de copie) | 🐌 Lent (copie temporaire) |
| **Paramètre** | `void` | `int` (factice) |
| **Utilisation** | `Fixed b = ++a;` | `Fixed b = a++;` |

**Recommandation :** Préférer `++a` quand possible (plus efficace).

### 2. Paramètre int factice

```cpp
Fixed &operator++(void);    // Pré-incrémentation
Fixed operator++(int);      // Post-incrémentation (int non utilisé !)
```

Le paramètre `int` n'est **jamais utilisé**. Il sert uniquement à différencier les signatures.

### 3. Fonctions statiques

```cpp
// Fonction membre classique
a.min(b);  // ❌ Bizarre syntaxiquement

// Fonction statique
Fixed::min(a, b);  // ✅ Naturel
```

**Caractéristiques :**
- Pas d'accès à `this`
- Appelées via le nom de la classe
- Souvent utilisées pour fonctions utilitaires

### 4. Opérateur ternaire

```cpp
return (a < b) ? a : b;
// Équivaut à :
if (a < b)
    return a;
else
    return b;
```

---

## 🎨 Techniques avancées

### 1. Arithmétique directe vs conversion

```cpp
// ✅ Approche simple (utilisée ici)
Fixed operator+(const Fixed &rhs) const {
    return Fixed(this->toFloat() + rhs.toFloat());
}

// 🔧 Approche optimale (plus complexe)
Fixed operator+(const Fixed &rhs) const {
    Fixed result;
    result._value = this->_value + rhs._value;
    return result;
}
```

**Avantages de la conversion :**
- Simple et lisible
- Évite les problèmes d'overflow
- Suffisant pour cet exercice

**Avantages de l'arithmétique directe :**
- Plus rapide
- Pas de perte de précision
- Utilisé en production

### 2. Chaînage d'opérateurs

```cpp
Fixed a(1), b(2), c(3);

Fixed result = a + b + c;  // Fonctionne car operator+ retourne Fixed
// Équivaut à : ((a + b) + c)
```

### 3. Retour par référence vs copie

```cpp
// Référence : modification possible
Fixed &min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

Fixed a(5), b(10);
Fixed::min(a, b) = Fixed(99);  // Modifie a ! (car retourne référence)

// Copie : protection contre modification
Fixed min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

Fixed::min(a, b) = Fixed(99);  // ❌ Erreur de compilation
```

---

## 🚨 Erreurs courantes

### 1. Confondre pré et post incrémentation

```cpp
// ❌ FAUX - Inversé !
Fixed &operator++(int) {  // Post devrait retourner copie
    _value++;
    return *this;
}

Fixed operator++(void) {  // Pré devrait retourner référence
    Fixed tmp(*this);
    _value++;
    return tmp;
}
```

### 2. Oublier le paramètre int factice

```cpp
// ❌ FAUX - Signatures identiques !
Fixed &operator++(void);
Fixed operator++(void);  // Erreur : redéfinition !

// ✅ CORRECT
Fixed &operator++(void);     // Pré
Fixed operator++(int);       // Post
```

### 3. Ne pas créer de version const pour min/max

```cpp
// ❌ Incomplet
static Fixed &min(Fixed &a, Fixed &b);

const Fixed a(5), b(10);
Fixed::min(a, b);  // ❌ Erreur : pas de version const !

// ✅ CORRECT
static Fixed &min(Fixed &a, Fixed &b);
static const Fixed &min(const Fixed &a, const Fixed &b);
```

### 4. Arithmétique sur _value sans ajuster

```cpp
// ❌ FAUX - Double décalage !
Fixed operator+(const Fixed &rhs) const {
    Fixed result;
    result._value = this->_value + rhs._value;
    // Problème : _value est déjà décalé !
    // Si a = 5 (5 × 256 = 1280) et b = 3 (3 × 256 = 768)
    // result._value = 2048 = 8 × 256 (pas 8 !)
    return result;
}

// ✅ CORRECT (approche par conversion)
Fixed operator+(const Fixed &rhs) const {
    return Fixed(this->toFloat() + rhs.toFloat());
}
```

---

## ✅ Checklist de validation

- [ ] Tous les opérateurs de comparaison fonctionnent
- [ ] Tous les opérateurs arithmétiques fonctionnent
- [ ] Pré-incrémentation retourne une référence
- [ ] Post-incrémentation retourne une copie
- [ ] Post-incrémentation a un paramètre `int` factice
- [ ] min/max ont deux versions (const et non-const)
- [ ] min/max sont statiques
- [ ] min/max retournent des références
- [ ] Les messages de constructeurs/destructeurs sont supprimés (pour ex02)
- [ ] Compilation sans erreur avec `-Wall -Wextra -Werror -std=c++98`

---

## 🎯 Objectif pédagogique

Cet exercice vous apprend à :

1. ✅ Surcharger les **opérateurs de comparaison**
2. ✅ Surcharger les **opérateurs arithmétiques**
3. ✅ Différencier **pré-incrémentation** et **post-incrémentation**
4. ✅ Créer des **fonctions statiques**
5. ✅ Gérer les **versions const/non-const**
6. ✅ Comprendre le **retour par référence vs copie**
7. ✅ Maîtriser la surcharge d'opérateurs en C++

---

## 📊 Comparaison Ex00 → Ex01 → Ex02

| Fonctionnalité | Ex00 | Ex01 | Ex02 |
|----------------|------|------|------|
| **Forme canonique** | ✅ | ✅ | ✅ |
| **Constructeurs conversion** | ❌ | ✅ | ✅ |
| **toFloat/toInt** | ❌ | ✅ | ✅ |
| **operator<<** | ❌ | ✅ | ✅ |
| **Comparaisons** | ❌ | ❌ | ✅ |
| **Arithmétiques** | ❌ | ❌ | ✅ |
| **Incrémentation** | ❌ | ❌ | ✅ |
| **min/max** | ❌ | ❌ | ✅ |

---

## 🔮 Pour aller plus loin

### Opérateurs composés

```cpp
Fixed &operator+=(const Fixed &rhs) {
    *this = *this + rhs;
    return *this;
}

// Utilisation :
a += b;  // Équivaut à : a = a + b;
```

### Opérateur de négation

```cpp
Fixed operator-() const {
    return Fixed(-this->toFloat());
}

// Utilisation :
Fixed a(5);
Fixed b = -a;  // b = -5
```

---

**Félicitations ! 🎉**

Vous avez maintenant une classe Fixed **complète et utilisable** qui se comporte comme un type natif C++ ! Cette classe peut être utilisée dans des projets réels pour des calculs à virgule fixe (embarqué, finance, etc.).

**Bon courage pour CPP03 ! 🚀**
