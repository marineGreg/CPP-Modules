# 📖 Guide Explicatif - CPP01 ex04 : Sed is for losers

## 📋 Table des matières
1. [Vue d'ensemble](#vue-densemble)
2. [Structure du projet](#structure-du-projet)
3. [Fonction main](#fonction-main)
4. [Fonction run_replace](#fonction-run_replace)
5. [Manipulation de fichiers](#manipulation-de-fichiers)
6. [Manipulation de chaînes](#manipulation-de-chaînes)
7. [Concepts C++ utilisés](#concepts-c-utilisés)
8. [Exemples d'utilisation](#exemples-dutilisation)
9. [Points clés](#points-clés)

---

## 🎯 Vue d'ensemble

Cet exercice implémente un **programme de remplacement de texte** similaire à la commande `sed` d'Unix.

### Objectif
Créer un programme qui :
1. Lit un fichier
2. Remplace toutes les occurrences d'une chaîne `s1` par `s2`
3. Écrit le résultat dans un nouveau fichier `<filename>.replace`

### Utilisation
```bash
./replace <filename> <s1> <s2>
```

**Exemple :**
```bash
./replace test.txt "Hello" "Bonjour"
# Crée test.txt.replace avec "Hello" remplacé par "Bonjour"
```

### Particularités
- ✅ Pas d'utilisation de `std::string::replace()` (interdit)
- ✅ Manipulation manuelle des chaînes avec `find()` et `substr()`
- ✅ Gestion complète des erreurs
- ✅ Travail avec les flux de fichiers (`ifstream`, `ofstream`)

---

## 📁 Structure du projet

```
ex04/
├── main.cpp         # Point d'entrée et validation des arguments
├── Replace.cpp      # Logique de remplacement
└── Makefile         # Fichier de compilation
```

**Note :** Pas de header `.hpp` car l'exercice est simple et ne nécessite qu'une déclaration de fonction.

---

## 🚀 Fonction main

### Fichier : main.cpp

```cpp
#include <iostream>

void run_replace(std::string filename, std::string s1, std::string s2);

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
        return (1);
    }
    std::string filename = av[1];
    std::string s1 = av[2];
    std::string s2 = av[3];

    if (s1.empty()) {
        std::cerr << "Error: s1 cannot be empty" << std::endl;
        return (1);
    }
    run_replace(filename, s1, s2);
    return (0);
}
```

---

### 📝 Analyse détaillée

#### Étape 1 : Validation du nombre d'arguments

```cpp
if (ac != 4) {
    std::cerr << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
    return (1);
}
```

**Explication :**
- `ac` (argument count) : Nombre d'arguments
- Attendu : exactement 4 arguments
  - `av[0]` : Nom du programme (`./replace`)
  - `av[1]` : Nom du fichier
  - `av[2]` : Chaîne à rechercher (`s1`)
  - `av[3]` : Chaîne de remplacement (`s2`)

**`std::cerr` vs `std::cout` :**
```cpp
std::cout  // Sortie standard (résultats normaux)
std::cerr  // Sortie d'erreur (messages d'erreur)
```

**💡 Bonnes pratiques :**
- Messages d'erreur → `std::cerr`
- Permet de rediriger les erreurs séparément : `./replace ... 2> errors.txt`

**Exemple d'utilisation incorrecte :**
```bash
./replace test.txt "Hello"
# Erreur : seulement 3 arguments (s2 manquant)
# Sortie : Usage: ./replace <filename> <s1> <s2>
```

---

#### Étape 2 : Conversion des arguments

```cpp
std::string filename = av[1];
std::string s1 = av[2];
std::string s2 = av[3];
```

**Explication :**
- `av[1]`, `av[2]`, `av[3]` sont de type `char*`
- Conversion automatique en `std::string` pour faciliter la manipulation
- `std::string` offre des méthodes puissantes (`find()`, `substr()`, etc.)

**💡 Pourquoi std::string ?**
```cpp
// Avec char*
char* s1 = av[2];
int len = strlen(s1);       // Longueur
char* found = strstr(...);  // Recherche

// Avec std::string
std::string s1 = av[2];
size_t len = s1.length();   // Longueur
size_t found = s1.find(...);// Recherche
```
→ Plus simple, plus sûr, plus lisible !

---

#### Étape 3 : Validation de s1

```cpp
if (s1.empty()) {
    std::cerr << "Error: s1 cannot be empty" << std::endl;
    return (1);
}
```

**Pourquoi cette vérification ?**
- Une chaîne vide `s1` causerait une **boucle infinie**
- `line.find("")` retournerait toujours `0`
- Le programme remplacerait à chaque position

**Exemple problématique :**
```cpp
// Si s1 est vide :
line = "Hello";
found = line.find("");  // Retourne 0
// Remplacement infini à la position 0 !
```

**💡 Note :** `s2` peut être vide (suppression de `s1`)

---

#### Étape 4 : Appel de la fonction de remplacement

```cpp
run_replace(filename, s1, s2);
return (0);
```

**Passage par valeur :**
- `std::string` est copié (pas de référence ici)
- Acceptable car ce sont de petites chaînes
- Pour des gros fichiers, on pourrait utiliser `const std::string&`

---

## 🔄 Fonction run_replace

### Fichier : Replace.cpp

```cpp
#include <iostream>
#include <fstream>
#include <string>

void run_replace(std::string filename, std::string s1, std::string s2)
{
    // 1. Ouverture du fichier d'entrée
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return;
    }

    // 2. Ouverture du fichier de sortie
    std::ofstream ofs((filename + ".replace").c_str());
    if (!ofs.is_open())
    {
        std::cerr << "Error: could not create output file" << std::endl;
        ifs.close();
        return;
    }
    
    // 3. Traitement ligne par ligne
    std::string line;
    while (std::getline(ifs, line))
    {
        size_t pos = 0;
        std::string newLine;
        
        // 4. Remplacement dans chaque ligne
        while (true)
        {
            size_t found = line.find(s1, pos);
            if (found == std::string::npos)
            {
                newLine += line.substr(pos);
                break;
            }
            newLine += line.substr(pos, found - pos);
            newLine += s2;
            pos = found + s1.length();
        }
        
        // 5. Écriture dans le fichier de sortie
        ofs << newLine;
        if (ifs.eof())
            ofs << std::endl;
    }
    
    // 6. Fermeture des fichiers
    ifs.close();
    ofs.close();
}
```

---

### 📝 Analyse détaillée

#### Étape 1 : Ouverture du fichier d'entrée

```cpp
std::ifstream ifs(filename.c_str());
if (!ifs.is_open())
{
    std::cerr << "Could not open file" << std::endl;
    return;
}
```

**Décomposition :**

##### `std::ifstream`
- **i**nput **f**ile **stream** : Flux de fichier en lecture
- Permet de lire depuis un fichier

##### `.c_str()`
```cpp
filename.c_str()
```
- **C++98** : `ifstream` prend un `const char*`, pas un `std::string`
- `.c_str()` convertit `std::string` → `const char*`

**💡 En C++11 et supérieur :**
```cpp
std::ifstream ifs(filename);  // Accepte directement std::string
```

##### Vérification d'ouverture
```cpp
if (!ifs.is_open())
```
- `.is_open()` retourne `true` si le fichier est ouvert
- `!ifs.is_open()` → échec d'ouverture

**Causes d'échec :**
- Fichier n'existe pas
- Pas de permissions de lecture
- Chemin invalide

---

#### Étape 2 : Ouverture du fichier de sortie

```cpp
std::ofstream ofs((filename + ".replace").c_str());
if (!ofs.is_open())
{
    std::cerr << "Error: could not create output file" << std::endl;
    ifs.close();  // ⚠️ Important : fermer le fichier d'entrée !
    return;
}
```

**Décomposition :**

##### `std::ofstream`
- **o**utput **f**ile **stream** : Flux de fichier en écriture
- Permet d'écrire dans un fichier

##### Nom du fichier de sortie
```cpp
filename + ".replace"
```
- Concatène `.replace` au nom du fichier
- Exemple : `"test.txt"` → `"test.txt.replace"`

##### Gestion d'erreur
```cpp
ifs.close();
return;
```
- **Important :** Fermer le fichier d'entrée avant de quitter
- Évite les fuites de ressources

**Causes d'échec :**
- Pas de permissions d'écriture
- Disque plein
- Chemin invalide

---

#### Étape 3 : Traitement ligne par ligne

```cpp
std::string line;
while (std::getline(ifs, line))
{
    // Traitement de chaque ligne
}
```

**Décomposition :**

##### `std::getline(ifs, line)`
```cpp
while (std::getline(ifs, line))
```

**Comportement :**
1. Lit une ligne du fichier `ifs`
2. Stocke la ligne dans `line`
3. Retourne le flux (`ifs`)
4. Continue tant qu'il reste des lignes

**💡 Note :** `std::getline()` **enlève** le `\n` de fin de ligne

**Exemple :**
```
Fichier :
Hello\n
World\n

Première itération : line = "Hello"  (sans \n)
Deuxième itération : line = "World"  (sans \n)
```

---

#### Étape 4 : Remplacement dans chaque ligne

```cpp
size_t pos = 0;
std::string newLine;

while (true)
{
    size_t found = line.find(s1, pos);
    if (found == std::string::npos)
    {
        newLine += line.substr(pos);
        break;
    }
    newLine += line.substr(pos, found - pos);
    newLine += s2;
    pos = found + s1.length();
}
```

**Algorithme de remplacement :**

##### Variables
```cpp
size_t pos = 0;         // Position actuelle dans la ligne
std::string newLine;    // Ligne reconstruite avec remplacements
```

##### Boucle de recherche
```cpp
size_t found = line.find(s1, pos);
```

**Méthode `.find()` :**
```cpp
line.find(s1, pos)
```
- Cherche `s1` dans `line` à partir de la position `pos`
- Retourne la position de la première occurrence
- Retourne `std::string::npos` si non trouvé

**`std::string::npos` :**
- Constante spéciale (généralement `-1` ou `SIZE_MAX`)
- Signifie "non trouvé" ou "position invalide"

---

##### Cas 1 : s1 non trouvé

```cpp
if (found == std::string::npos)
{
    newLine += line.substr(pos);
    break;
}
```

**Explication :**
- `s1` n'est plus présent dans le reste de la ligne
- `line.substr(pos)` : Extrait depuis `pos` jusqu'à la fin
- Ajoute le reste à `newLine` et termine

**Visualisation :**
```
line = "Hello World"
s1 = "foo" (non trouvé)
pos = 0

line.substr(0) = "Hello World"
newLine = "Hello World"
```

---

##### Cas 2 : s1 trouvé

```cpp
newLine += line.substr(pos, found - pos);
newLine += s2;
pos = found + s1.length();
```

**Étapes :**

1. **Ajouter le texte avant s1**
   ```cpp
   newLine += line.substr(pos, found - pos);
   ```
   - `line.substr(pos, found - pos)` : Texte entre `pos` et `found`
   - Ajoute le texte qui précède l'occurrence de `s1`

2. **Ajouter s2 (le remplacement)**
   ```cpp
   newLine += s2;
   ```

3. **Avancer pos après s1**
   ```cpp
   pos = found + s1.length();
   ```
   - Saute `s1` pour éviter de le traiter à nouveau
   - Continue la recherche après

---

##### Exemple complet de remplacement

```
Ligne originale : "Hello World Hello"
s1 = "Hello"
s2 = "Bonjour"

Itération 1 :
  pos = 0
  found = 0 (première occurrence à position 0)
  newLine += line.substr(0, 0) = ""     (rien avant)
  newLine += "Bonjour"                  (remplacement)
  pos = 0 + 5 = 5                       (après "Hello")
  newLine = "Bonjour"

Itération 2 :
  pos = 5
  found = 12 (deuxième occurrence à position 12)
  newLine += line.substr(5, 12-5) = " World "  (texte entre)
  newLine += "Bonjour"                         (remplacement)
  pos = 12 + 5 = 17                            (après deuxième "Hello")
  newLine = "Bonjour World Bonjour"

Itération 3 :
  pos = 17
  found = npos (plus d'occurrence)
  newLine += line.substr(17) = ""       (rien après)
  break
  
Résultat : "Bonjour World Bonjour"
```

---

#### Étape 5 : Écriture dans le fichier de sortie

```cpp
ofs << newLine;
if (ifs.eof())
    ofs << std::endl;
```

**Décomposition :**

##### Écriture de la ligne
```cpp
ofs << newLine;
```
- Écrit la ligne modifiée dans le fichier de sortie
- **Sans** retour à la ligne automatique

##### Gestion du retour à la ligne
```cpp
if (ifs.eof())
    ofs << std::endl;
```

**⚠️ Bug potentiel dans le code !**

Ce code est **incorrect**. Il devrait être :
```cpp
if (!ifs.eof())
    ofs << std::endl;
```

**Explication :**
- `ifs.eof()` retourne `true` après avoir lu la dernière ligne
- On veut un `\n` **après chaque ligne sauf la dernière**
- Le code actuel fait l'inverse

**Correction :**
```cpp
ofs << newLine;
if (!ifs.eof())  // Si ce N'EST PAS la dernière ligne
    ofs << std::endl;
```

---

#### Étape 6 : Fermeture des fichiers

```cpp
ifs.close();
ofs.close();
```

**Pourquoi fermer explicitement ?**
- **Bonne pratique** : Libérer les ressources immédiatement
- Les destructeurs ferment automatiquement, mais c'est mieux de le faire explicitement
- Permet de gérer les erreurs de fermeture (disque plein, etc.)

**💡 Note :**
```cpp
// Fermeture automatique à la fin de la portée
{
    std::ifstream ifs("file.txt");
    // ...
}  // ← ifs.close() appelé automatiquement ici
```

---

## 📂 Manipulation de fichiers

### Flux de fichiers en C++

#### Hiérarchie des classes

```
ios_base
    ↓
   ios
    ↓
  ┌───┴───┐
  │       │
istream ostream
  │       │
  ↓       ↓
ifstream ofstream
```

---

### `std::ifstream` (Input File Stream)

**Utilisation :**
```cpp
std::ifstream ifs("file.txt");

// Vérifier si ouvert
if (ifs.is_open()) {
    // Lecture ligne par ligne
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << std::endl;
    }
    ifs.close();
}
```

**Méthodes principales :**

| Méthode | Description |
|---------|-------------|
| `.is_open()` | Vérifie si le fichier est ouvert |
| `.eof()` | Vérifie si fin de fichier atteinte |
| `.close()` | Ferme le fichier |
| `std::getline(ifs, line)` | Lit une ligne complète |
| `ifs >> variable` | Lit un mot/nombre |

---

### `std::ofstream` (Output File Stream)

**Utilisation :**
```cpp
std::ofstream ofs("output.txt");

// Vérifier si ouvert
if (ofs.is_open()) {
    // Écriture
    ofs << "Hello" << std::endl;
    ofs << "World" << std::endl;
    ofs.close();
}
```

**Méthodes principales :**

| Méthode | Description |
|---------|-------------|
| `.is_open()` | Vérifie si le fichier est ouvert |
| `.close()` | Ferme le fichier |
| `ofs << data` | Écrit des données |
| `.flush()` | Force l'écriture sur disque |

---

### Modes d'ouverture (avancé)

```cpp
// Modes disponibles
std::ios::in     // Lecture
std::ios::out    // Écriture (écrase)
std::ios::app    // Ajout à la fin
std::ios::trunc  // Tronque le fichier
std::ios::binary // Mode binaire

// Exemples
std::ofstream ofs("file.txt", std::ios::app);  // Ajoute à la fin
std::ifstream ifs("data.bin", std::ios::binary);  // Mode binaire
```

---

## 🔤 Manipulation de chaînes

### Méthodes `std::string` utilisées

#### 1. `.find()`

**Syntaxe :**
```cpp
size_t pos = str.find(substr, start_pos);
```

**Paramètres :**
- `substr` : Sous-chaîne à chercher
- `start_pos` : Position de départ (optionnel, défaut = 0)

**Retour :**
- Position de la première occurrence
- `std::string::npos` si non trouvé

**Exemples :**
```cpp
std::string str = "Hello World Hello";

size_t pos1 = str.find("Hello");      // 0
size_t pos2 = str.find("Hello", 1);   // 12
size_t pos3 = str.find("Goodbye");    // std::string::npos
```

---

#### 2. `.substr()`

**Syntaxe :**
```cpp
std::string sub = str.substr(pos, len);
```

**Paramètres :**
- `pos` : Position de départ
- `len` : Longueur (optionnel, défaut = jusqu'à la fin)

**Retour :**
- Sous-chaîne extraite

**Exemples :**
```cpp
std::string str = "Hello World";

str.substr(0, 5)    // "Hello"
str.substr(6, 5)    // "World"
str.substr(6)       // "World" (jusqu'à la fin)
str.substr(0, 100)  // "Hello World" (tronqué automatiquement)
```

---

#### 3. `.length()` / `.size()`

**Syntaxe :**
```cpp
size_t len = str.length();  // ou str.size()
```

**Retour :**
- Nombre de caractères

**Exemples :**
```cpp
std::string str = "Hello";
str.length()  // 5
str.size()    // 5 (identique)
```

---

#### 4. `.empty()`

**Syntaxe :**
```cpp
bool is_empty = str.empty();
```

**Retour :**
- `true` si la chaîne est vide
- `false` sinon

**Exemples :**
```cpp
std::string str1 = "";
std::string str2 = "Hello";

str1.empty()  // true
str2.empty()  // false
```

---

#### 5. `.c_str()`

**Syntaxe :**
```cpp
const char* c_string = str.c_str();
```

**Retour :**
- Pointeur vers une chaîne C (`const char*`)
- Terminée par `\0`

**Usage :**
```cpp
std::string str = "Hello";
std::ifstream ifs(str.c_str());  // C++98
printf("%s\n", str.c_str());     // Fonctions C
```

---

#### 6. Concaténation (`+` et `+=`)

**Syntaxe :**
```cpp
std::string result = str1 + str2;
str1 += str2;
```

**Exemples :**
```cpp
std::string hello = "Hello";
std::string world = "World";

hello + " " + world  // "Hello World"
hello += " World"    // hello devient "Hello World"
```

---

## 🎓 Concepts C++ utilisés

### 1. Arguments de ligne de commande

```cpp
int main(int ac, char **av)
```

**Paramètres :**
- `ac` (argument count) : Nombre d'arguments
- `av` (argument vector) : Tableau de chaînes C

**Structure :**
```cpp
./replace file.txt "old" "new"
   ↓        ↓        ↓      ↓
 av[0]    av[1]   av[2]  av[3]
 
ac = 4
```

---

### 2. Flux de fichiers

**Headers nécessaires :**
```cpp
#include <fstream>   // ifstream, ofstream
#include <iostream>  // cout, cerr
#include <string>    // std::string
```

**Principe :**
- `std::ifstream` : Lecture de fichiers
- `std::ofstream` : Écriture de fichiers
- Similaire à `std::cin` et `std::cout`

---

### 3. Type `size_t`

```cpp
size_t pos = str.find("Hello");
```

**Caractéristiques :**
- Type **non signé** (pas de valeurs négatives)
- Suffisamment grand pour représenter toute taille possible
- Utilisé pour les tailles et positions

**Équivalent :**
```cpp
// Sur système 64 bits :
typedef unsigned long size_t;

// Sur système 32 bits :
typedef unsigned int size_t;
```

---

### 4. `std::string::npos`

```cpp
if (found == std::string::npos)
```

**Définition :**
```cpp
static const size_t npos = -1;  // Valeur maximale de size_t
```

**Usage :**
- Indique "non trouvé"
- Valeur spéciale pour les fonctions de recherche

**💡 Comparaison :**
```cpp
// Correct
if (found == std::string::npos)

// Incorrect (mais fonctionne souvent)
if (found == -1)  // Dépend de l'implémentation
```

---

### 5. Gestion d'erreurs avec `std::cerr`

```cpp
std::cerr << "Error: " << message << std::endl;
```

**Différence avec `std::cout` :**

| Stream | Usage | Redirigeable |
|--------|-------|--------------|
| `std::cout` | Sortie normale | `./prog > output.txt` |
| `std::cerr` | Messages d'erreur | `./prog 2> errors.txt` |

**Exemple :**
```bash
./replace file.txt "a" "b" > results.txt 2> errors.txt
# Sortie normale → results.txt
# Erreurs → errors.txt
```

---

## 💻 Exemples d'utilisation

### Exemple 1 : Remplacement simple

**Fichier test.txt :**
```
Hello World
Hello everyone
```

**Commande :**
```bash
./replace test.txt "Hello" "Bonjour"
```

**Fichier test.txt.replace :**
```
Bonjour World
Bonjour everyone
```

---

### Exemple 2 : Remplacements multiples

**Fichier test.txt :**
```
foo bar foo baz foo
```

**Commande :**
```bash
./replace test.txt "foo" "XXX"
```

**Fichier test.txt.replace :**
```
XXX bar XXX baz XXX
```

---

### Exemple 3 : Remplacement par chaîne vide (suppression)

**Fichier test.txt :**
```
Hello World
```

**Commande :**
```bash
./replace test.txt "Hello " ""
```

**Fichier test.txt.replace :**
```
World
```

---

### Exemple 4 : Cas limites

#### Chaîne non trouvée

**Fichier test.txt :**
```
Hello World
```

**Commande :**
```bash
./replace test.txt "Goodbye" "Bye"
```

**Fichier test.txt.replace :**
```
Hello World
```
(Aucun changement)

---

#### Remplacement avec chevauchement

**Fichier test.txt :**
```
aaa
```

**Commande :**
```bash
./replace test.txt "aa" "b"
```

**Fichier test.txt.replace :**
```
ba
```

**Explication :**
1. Première occurrence : "aa" (positions 0-1) → "b"
2. `pos` avance à 2
3. Plus d'occurrence (le "aa" aux positions 1-2 est ignoré)

---

### Exemple 5 : Erreurs

#### Fichier inexistant

```bash
./replace nonexistent.txt "a" "b"
```
**Sortie :**
```
Could not open file
```

---

#### Nombre d'arguments incorrect

```bash
./replace test.txt "Hello"
```
**Sortie :**
```
Usage: ./replace <filename> <s1> <s2>
```

---

#### s1 vide

```bash
./replace test.txt "" "new"
```
**Sortie :**
```
Error: s1 cannot be empty
```

---

## 💡 Points clés à retenir

### ✅ Bonnes pratiques

#### 1. Toujours vérifier l'ouverture des fichiers

```cpp
std::ifstream ifs("file.txt");
if (!ifs.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return;
}
```

---

#### 2. Fermer les fichiers en cas d'erreur

```cpp
if (!ofs.is_open()) {
    ifs.close();  // ⚠️ Important !
    return;
}
```

---

#### 3. Utiliser `std::cerr` pour les erreurs

```cpp
std::cerr << "Error: " << message << std::endl;
```

---

#### 4. Valider les arguments

```cpp
if (s1.empty()) {
    std::cerr << "Error: s1 cannot be empty" << std::endl;
    return 1;
}
```

---

### ⚠️ Pièges courants

#### 1. Oublier `.c_str()` en C++98

```cpp
// ❌ C++98 : Erreur de compilation
std::ifstream ifs(filename);

// ✅ C++98 : Correct
std::ifstream ifs(filename.c_str());

// ✅ C++11+ : Les deux fonctionnent
```

---

#### 2. Boucle infinie avec s1 vide

```cpp
// ❌ DANGER : Boucle infinie
if (s1.empty()) {
    std::cerr << "Error: s1 cannot be empty" << std::endl;
    return 1;
}
```

---

#### 3. Chevauchement de remplacements

```cpp
// "aaa" avec s1="aa", s2="b"
// Résultat : "ba" (pas "bba")
// La recherche avance après chaque remplacement
```

---

#### 4. Gestion des retours à la ligne

```cpp
// ⚠️ Bug dans le code fourni
if (ifs.eof())      // Devrait être !ifs.eof()
    ofs << std::endl;
```

---

### 🎯 Algorithme de remplacement

**Pseudocode :**
```
Pour chaque ligne :
    pos = 0
    newLine = ""
    
    Tant que vrai :
        found = chercher s1 dans line à partir de pos
        
        Si s1 non trouvé :
            Ajouter le reste de line à newLine
            Sortir de la boucle
        
        Sinon :
            Ajouter le texte avant s1 à newLine
            Ajouter s2 à newLine
            pos = position après s1
    
    Écrire newLine dans le fichier
```

---

### 📊 Complexité

**Temps :**
- `O(n * m)` où :
  - `n` = taille du fichier
  - `m` = nombre d'occurrences de s1

**Espace :**
- `O(n)` : Une ligne en mémoire à la fois

---

## 🎯 Résumé

### Ce que cet exercice enseigne

1. **Manipulation de fichiers** avec `ifstream` et `ofstream`
2. **Manipulation de chaînes** avec `find()` et `substr()`
3. **Gestion d'erreurs** robuste
4. **Arguments de ligne de commande**
5. **Algorithme de remplacement** sans `std::string::replace()`

### Architecture

```
main()
  ↓
  1. Validation des arguments
  2. Vérification de s1 non vide
  ↓
run_replace()
  ↓
  1. Ouverture des fichiers
  2. Traitement ligne par ligne
     ↓
     a. Recherche de s1
     b. Construction de la nouvelle ligne
     c. Écriture dans le fichier
  3. Fermeture des fichiers
```

### Message clé

**Cet exercice démontre comment manipuler des fichiers et des chaînes en C++ de manière robuste, avec une gestion d'erreurs complète et un algorithme efficace de remplacement de texte.** 📝✨

### Améliorations possibles

1. **Gérer les fichiers binaires**
2. **Supporter les expressions régulières**
3. **Mode interactif** (confirmation avant remplacement)
4. **Statistiques** (nombre de remplacements effectués)
5. **Backup** automatique du fichier original

**C'est une excellente base pour comprendre la manipulation de fichiers en C++ !** 🚀

