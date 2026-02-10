# Guide d'Évaluation - CPP Module 02

## 📋 Vue d'ensemble du module

**Thème principal** : Polymorphisme ad-hoc, surcharge d'opérateurs et forme canonique orthodoxe

**Concepts clés** :
- Forme Canonique Orthodoxe (Orthodox Canonical Form)
- Surcharge d'opérateurs
- Nombres à virgule fixe (Fixed-point numbers)
- Conversions de types
- Opérateurs d'incrémentation/décrémentation

---

## 🎯 Exercise 00: My First Class in Orthodox Canonical Form

### 📖 Explication du programme

Implémente une classe `Fixed` représentant un **nombre à virgule fixe** (fixed-point number).

**Qu'est-ce qu'un nombre à virgule fixe ?**
- Alternative aux `float`/`double` (virgule flottante)
- Utilise un `int` pour stocker la valeur
- Une partie des bits = partie entière, reste = partie fractionnaire
- Exemple : si 8 bits pour la fraction, `256` en interne = `1.0` en réel

**Attributs** :
```cpp
class Fixed {
private:
    int _rawBits;                    // Valeur brute (entier)
    static const int _fractionalBits = 8;  // Nombre de bits pour la fraction
};
```

### 🔑 Points clés à comprendre

#### 1. **Forme Canonique Orthodoxe (OCF)**

Toute classe doit implémenter les **4 fonctions essentielles** :

```cpp
class Fixed {
public:
    Fixed();                           // 1. Constructeur par défaut
    Fixed(const Fixed& other);         // 2. Constructeur de copie
    Fixed& operator=(const Fixed& other);  // 3. Opérateur d'assignation
    ~Fixed();                          // 4. Destructeur
};
```

**Pourquoi ?**
- Sans ces fonctions, le compilateur les génère automatiquement
- Le comportement par défaut est souvent incorrect (shallow copy)
- Pour les classes gérant des ressources, c'est crucial

#### 2. **Implémentation de chaque fonction**

**Constructeur par défaut** :
```cpp
Fixed::Fixed() : _rawBits(0) {
    std::cout << "Default constructor called" << std::endl;
}
```

**Constructeur de copie** :
```cpp
Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other;  // Utilise l'opérateur d'assignation
    // OU : this->_rawBits = other.getRawBits();
}
```

**Opérateur d'assignation** :
```cpp
Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {  // Protection contre l'auto-assignation
        this->_rawBits = other.getRawBits();
    }
    return *this;  // Retourne *this pour permettre a = b = c
}
```

**Destructeur** :
```cpp
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}
```

#### 3. **Getters et Setters**

```cpp
int getRawBits(void) const;       // Retourne _rawBits
void setRawBits(int const raw);   // Modifie _rawBits
```

### 🧪 Tests à démontrer

```bash
./fixed
```

**Ce que tu dois montrer** :
1. Création d'un objet `Fixed a;` → Constructeur par défaut
2. Copie d'un objet `Fixed b(a);` → Constructeur de copie
3. Assignation `Fixed c = a;` → Constructeur de copie (pas opérateur d'assignation !)
4. Assignation `c = b;` → Opérateur d'assignation
5. Destruction des objets en fin de scope → Destructeur

**Sortie attendue** (ordre des messages) :
```
Default constructor called
Copy constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
setRawBits member function called
getRawBits member function called
Destructor called
Destructor called
Destructor called
```

### ⚠️ Erreurs courantes

1. **Oublier la protection contre l'auto-assignation** : `if (this != &other)`
2. **Ne pas retourner `*this`** dans l'opérateur d'assignation
3. **Confondre initialisation et assignation** :
   - `Fixed b = a;` → Constructeur de copie (initialisation)
   - `b = a;` → Opérateur d'assignation (b existe déjà)
4. **Appeler `getRawBits()` au lieu d'accéder directement** dans les méthodes membres

### 💡 Conseils de présentation

- Explique chacune des 4 fonctions de l'OCF et leur rôle
- Montre la différence entre constructeur de copie et opérateur d'assignation
- Explique pourquoi `operator=` retourne une référence
- Discute du concept de "shallow copy" vs "deep copy" (même si pas pertinent ici)

---

## 🎯 Exercise 01: Towards a more useful fixed-point number class

### 📖 Explication du programme

Ajoute des **constructeurs de conversion** et des **méthodes de conversion** à la classe `Fixed`.

**Nouveautés** :
1. Constructeur à partir d'un `int`
2. Constructeur à partir d'un `float`
3. Conversion vers `int` : `toInt()`
4. Conversion vers `float` : `toFloat()`
5. Surcharge de `operator<<` pour afficher un `Fixed`

### 🔑 Points clés à comprendre

#### 1. **Constructeur int → Fixed**

```cpp
Fixed::Fixed(const int value) {
    std::cout << "Int constructor called" << std::endl;
    _rawBits = value << _fractionalBits;  // Décalage de 8 bits vers la gauche
}
```

**Exemple** :
- Valeur : `42`
- Après décalage : `42 << 8 = 42 * 256 = 10752`
- Stockage interne : `10752` (représente `42.0` en virgule fixe)

#### 2. **Constructeur float → Fixed**

```cpp
Fixed::Fixed(const float value) {
    std::cout << "Float constructor called" << std::endl;
    _rawBits = roundf(value * (1 << _fractionalBits));  // Multiplication par 2^8
}
```

**Exemple** :
- Valeur : `42.42`
- Après multiplication : `42.42 * 256 = 10859.52`
- Après arrondi : `10860`
- Stockage interne : `10860` (représente `~42.42` en virgule fixe)

#### 3. **Conversion Fixed → int**

```cpp
int Fixed::toInt(void) const {
    return _rawBits >> _fractionalBits;  // Décalage de 8 bits vers la droite
}
```

**Exemple** :
- Valeur interne : `10752`
- Après décalage : `10752 >> 8 = 42`
- Résultat : `42`

#### 4. **Conversion Fixed → float**

```cpp
float Fixed::toFloat(void) const {
    return (float)_rawBits / (1 << _fractionalBits);  // Division par 2^8
}
```

**Exemple** :
- Valeur interne : `10860`
- Après division : `10860 / 256 = 42.421875`
- Résultat : `42.421875`

#### 5. **Surcharge de operator<<**

```cpp
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}
```

**Important** :
- Fonction **non-membre** (friend ou avec getter public)
- Retourne `std::ostream&` pour permettre le chaînage : `cout << a << b`

### 🧪 Tests à démontrer

```bash
./fixed
```

**Ce que tu dois montrer** (selon le main du sujet) :
```cpp
Fixed a;
Fixed const b(10);
Fixed const c(42.42f);
Fixed const d(b);

a = Fixed(1234.4321f);

std::cout << "a is " << a << std::endl;
std::cout << "b is " << b << std::endl;
std::cout << "c is " << c << std::endl;
std::cout << "d is " << d << std::endl;

std::cout << "a is " << a.toInt() << " as integer" << std::endl;
std::cout << "b is " << b.toInt() << " as integer" << std::endl;
std::cout << "c is " << c.toInt() << " as integer" << std::endl;
std::cout << "d is " << d.toInt() << " as integer" << std::endl;
```

**Sortie attendue** :
```
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Destructor called
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
```

### ⚠️ Erreurs courantes

1. **Ne pas arrondir** dans le constructeur float → `roundf()` est nécessaire
2. **Oublier d'inclure `<cmath>`** pour `roundf()`
3. **Mauvais sens des décalages** : `<<` pour multiplier, `>>` pour diviser
4. **operator<< mal implémenté** : doit retourner `ostream&`, pas `void`
5. **Perte de précision** : c'est normal avec les fixed-point, ne pas paniquer

### 💡 Conseils de présentation

- Explique comment fonctionne la représentation en virgule fixe
- Montre les calculs de conversion sur un exemple concret
- Compare avec les `float` : avantages (vitesse, déterminisme) et inconvénients (précision limitée)
- Explique pourquoi `operator<<` est une fonction non-membre

---

## 🎯 Exercise 02: Now we're talking

### 📖 Explication du programme

Ajoute une **surcharge complète des opérateurs** à la classe `Fixed`.

**Opérateurs à implémenter** :

1. **Comparaison** : `>`, `<`, `>=`, `<=`, `==`, `!=`
2. **Arithmétiques** : `+`, `-`, `*`, `/`
3. **Incrémentation/Décrémentation** : `++a`, `a++`, `--a`, `a--`
4. **Fonctions statiques** : `min()`, `max()`

### 🔑 Points clés à comprendre

#### 1. **Opérateurs de comparaison**

```cpp
bool Fixed::operator>(const Fixed& other) const {
    return this->_rawBits > other._rawBits;
}

bool Fixed::operator<(const Fixed& other) const {
    return this->_rawBits < other._rawBits;
}

bool Fixed::operator>=(const Fixed& other) const {
    return this->_rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed& other) const {
    return this->_rawBits <= other._rawBits;
}

bool Fixed::operator==(const Fixed& other) const {
    return this->_rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed& other) const {
    return this->_rawBits != other._rawBits;
}
```

**Astuce** : On compare directement `_rawBits` (pas besoin de convertir en float)

#### 2. **Opérateurs arithmétiques**

**Addition** :
```cpp
Fixed Fixed::operator+(const Fixed& other) const {
    return Fixed(this->toFloat() + other.toFloat());
}
```

**Soustraction** :
```cpp
Fixed Fixed::operator-(const Fixed& other) const {
    return Fixed(this->toFloat() - other.toFloat());
}
```

**Multiplication** :
```cpp
Fixed Fixed::operator*(const Fixed& other) const {
    return Fixed(this->toFloat() * other.toFloat());
}
```

**Division** :
```cpp
Fixed Fixed::operator/(const Fixed& other) const {
    return Fixed(this->toFloat() / other.toFloat());
}
```

**Alternative plus efficace** (sans passer par float) :
```cpp
Fixed Fixed::operator+(const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->_rawBits + other._rawBits);
    return result;
}
```

#### 3. **Pré-incrémentation vs Post-incrémentation**

**Pré-incrémentation** (`++a`) :
```cpp
Fixed& Fixed::operator++() {
    this->_rawBits++;  // Incrémente de 1/256 (plus petite valeur représentable)
    return *this;      // Retourne la nouvelle valeur
}
```

**Post-incrémentation** (`a++`) :
```cpp
Fixed Fixed::operator++(int) {  // Le 'int' est un dummy parameter
    Fixed temp(*this);  // Copie de la valeur actuelle
    this->_rawBits++;   // Incrémentation
    return temp;        // Retourne l'ancienne valeur
}
```

**Différence clé** :
- `++a` : retourne une **référence** (plus efficace)
- `a++` : retourne une **copie** (nécessaire pour retourner l'ancienne valeur)

**Décrémentation** : Même logique avec `--`

#### 4. **Fonctions statiques min/max**

```cpp
static Fixed& min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

static const Fixed& min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

static Fixed& max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

static const Fixed& max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}
```

**Pourquoi deux versions ?**
- Une pour les objets **non-const** (retourne référence modifiable)
- Une pour les objets **const** (retourne référence const)

### 🧪 Tests à démontrer

```bash
./fixed
```

**Test 1 : Comparaison**
```cpp
Fixed a(10);
Fixed b(5);
std::cout << (a > b) << std::endl;   // 1 (true)
std::cout << (a < b) << std::endl;   // 0 (false)
std::cout << (a == b) << std::endl;  // 0 (false)
```

**Test 2 : Arithmétique**
```cpp
Fixed a(10);
Fixed b(5);
std::cout << a + b << std::endl;  // 15
std::cout << a - b << std::endl;  // 5
std::cout << a * b << std::endl;  // 50
std::cout << a / b << std::endl;  // 2
```

**Test 3 : Incrémentation**
```cpp
Fixed a(5.5f);
Fixed b = a++;  // b = 5.5, a = 5.50391
Fixed c = ++a;  // c = 5.50781, a = 5.50781
std::cout << a << std::endl;  // 5.50781
std::cout << b << std::endl;  // 5.5
std::cout << c << std::endl;  // 5.50781
```

**Test 4 : Min/Max**
```cpp
Fixed a(10);
Fixed b(20);
std::cout << Fixed::min(a, b) << std::endl;  // 10
std::cout << Fixed::max(a, b) << std::endl;  // 20
```

### ⚠️ Erreurs courantes

1. **Confondre pré et post-incrémentation** : signature différente !
2. **Retourner `void`** au lieu de `Fixed` ou `Fixed&`
3. **Ne pas gérer les deux versions const/non-const** de min/max
4. **Division par zéro** : pas forcément géré, mais bon à mentionner
5. **Oublier le `const`** après les méthodes qui ne modifient pas l'objet

### 💡 Conseils de présentation

- Explique la différence entre `++a` et `a++` avec un exemple concret
- Montre que tu comprends pourquoi on retourne une référence vs une copie
- Discute des choix d'implémentation (conversion en float vs manipulation directe de rawBits)
- Explique le concept de surcharge d'opérateurs et son utilité

---

## 🎁 Bonus : Questions anticipées

### Q1 : "Pourquoi utiliser des fixed-point au lieu de float ?"

**Réponse** :
1. **Performance** : Opérations entières plus rapides que flottantes (surtout sur vieux hardware)
2. **Déterminisme** : Résultats identiques sur toutes les plateformes (important en jeux vidéo)
3. **Précision contrôlée** : On sait exactement combien de décimales on a

**Inconvénients** :
- Plage de valeurs limitée
- Perte de précision sur les grandes valeurs
- Plus complexe à manipuler

### Q2 : "Pourquoi le paramètre `int` dans `operator++(int)` ?"

**Réponse** :
- C'est une **convention du C++** pour différencier pré et post-incrémentation
- Le paramètre n'est **jamais utilisé**, c'est un "dummy parameter"
- Le compilateur passe automatiquement `0` quand on écrit `a++`

**Syntaxe** :
```cpp
Fixed& operator++();      // Pré-incrémentation (++a)
Fixed operator++(int);    // Post-incrémentation (a++)
```

### Q3 : "Pourquoi deux versions de `min()` et `max()` ?"

**Réponse** :
- Une pour les objets **const**, une pour les **non-const**
- Permet de retourner une référence du bon type

**Exemple** :
```cpp
const Fixed a(10);
const Fixed b(20);
const Fixed& minVal = Fixed::min(a, b);  // Version const

Fixed c(10);
Fixed d(20);
Fixed& minVal2 = Fixed::min(c, d);       // Version non-const
minVal2 = Fixed(5);  // Modifiable !
```

### Q4 : "Qu'est-ce que le polymorphisme ad-hoc ?"

**Réponse** :
- **Polymorphisme ad-hoc** = Surcharge de fonctions/opérateurs
- Plusieurs fonctions avec le **même nom** mais des **signatures différentes**

**Exemples** :
```cpp
void print(int x);      // Version int
void print(float x);    // Version float
void print(string x);   // Version string
```

**Différence avec polymorphisme subtyping** :
- Ad-hoc : Résolu à la **compilation** (static)
- Subtyping : Résolu à l'**exécution** (dynamic, avec `virtual`)

### Q5 : "Pourquoi `operator<<` n'est pas membre de la classe ?"

**Réponse** :
- `operator<<` doit être appelé comme : `cout << fixed`
- `cout` est de type `std::ostream`, pas `Fixed`
- On ne peut pas modifier la classe `std::ostream`

**Solutions** :
1. **Fonction non-membre** (préféré) :
   ```cpp
   std::ostream& operator<<(std::ostream& out, const Fixed& fixed);
   ```

2. **Fonction friend** (si besoin d'accéder aux membres privés) :
   ```cpp
   class Fixed {
       friend std::ostream& operator<<(std::ostream& out, const Fixed& fixed);
   };
   ```

---

## 📝 Checklist finale

Avant l'évaluation, assure-toi de pouvoir :

### Compétences techniques
- [ ] Implémenter les 4 fonctions de l'Orthodox Canonical Form
- [ ] Surcharger tous les opérateurs demandés
- [ ] Expliquer la différence entre pré et post-incrémentation
- [ ] Implémenter des conversions int/float ↔ Fixed
- [ ] Utiliser les bit shifts (`<<`, `>>`) correctement

### Concepts théoriques
- [ ] Expliquer l'Orthodox Canonical Form et son importance
- [ ] Expliquer le polymorphisme ad-hoc
- [ ] Expliquer les nombres à virgule fixe
- [ ] Expliquer shallow copy vs deep copy
- [ ] Expliquer pourquoi `operator<<` est non-membre

### Tests pratiques
- [ ] Compiler tous les exercices sans warnings
- [ ] Démontrer chaque opérateur surchargé
- [ ] Tester les cas limites (division par zéro, très grandes valeurs)
- [ ] Vérifier avec `valgrind` (pas de leaks)

### Makefile
- [ ] `make` compile tout
- [ ] `make clean` supprime les `.o`
- [ ] `make fclean` supprime les `.o` et l'exécutable
- [ ] `make re` fait un clean + recompile
- [ ] Flags : `-Wall -Wextra -Werror -std=c++98`

---

## 🚀 Conseils généraux de présentation

1. **Maîtrise l'OCF** : C'est la base du module, tu dois pouvoir l'expliquer les yeux fermés
2. **Prépare des exemples** : Montre des cas concrets d'utilisation des opérateurs
3. **Compare avec C** : Explique pourquoi C++ offre plus de flexibilité
4. **Discute des choix d'implémentation** : Pourquoi convertir en float vs manipuler rawBits ?
5. **Reste précis** : "Retourne une référence" ≠ "Retourne une copie"

Bonne chance ! 🍀
