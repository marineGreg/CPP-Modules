# Guide CPP01 - Exercice 06 : harlFilter

## 📋 Objectif de l'exercice

Créer un programme **harlFilter** qui filtre les messages de Harl en fonction d'un niveau passé en argument de ligne de commande. L'exercice introduit l'utilisation du **switch** avec le comportement de **fall-through** pour afficher tous les messages à partir d'un certain niveau de priorité.

---

## 🎯 Différences avec l'exercice 05

| Aspect | Exercice 05 | Exercice 06 |
|--------|-------------|-------------|
| **Nom du programme** | `harl` | `harlFilter` |
| **Arguments** | Aucun | 1 argument (niveau) |
| **Comportement** | Affiche **un seul** message | Affiche **tous** les messages >= niveau |
| **Structure de contrôle** | Pointeurs de fonctions | **Switch avec fall-through** |
| **Utilisation** | `./harl` | `./harlFilter WARNING` |

---

## 🎓 Concepts clés

### 1. Le switch en C++

Le `switch` est une structure de contrôle qui permet de comparer une variable à plusieurs valeurs constantes.

**Syntaxe de base :**
```cpp
switch (variable) {
    case valeur1:
        // code
        break;
    case valeur2:
        // code
        break;
    default:
        // code si aucun cas ne correspond
}
```

### 2. Le fall-through

Le **fall-through** est un comportement du `switch` où l'exécution continue dans les cases suivantes si on **omet le `break`**.

**Exemple :**
```cpp
switch (level) {
    case 0:
        std::cout << "DEBUG" << std::endl;
        // PAS DE BREAK = fall-through
    case 1:
        std::cout << "INFO" << std::endl;
        // PAS DE BREAK = fall-through
    case 2:
        std::cout << "WARNING" << std::endl;
        break;
}
```

Si `level = 0`, on affichera :
```
DEBUG
INFO
WARNING
```

### 3. Arguments de ligne de commande

```cpp
int main(int argc, char **argv)
```

- **argc** : Nombre d'arguments (y compris le nom du programme)
- **argv** : Tableau de chaînes de caractères (les arguments)
- **argv[0]** : Nom du programme
- **argv[1]** : Premier argument

**Exemple :**
```bash
./harlFilter WARNING
# argc = 2
# argv[0] = "./harlFilter"
# argv[1] = "WARNING"
```

---

## 🏗️ Structure du projet

```
ex06/
├── Harl.hpp       // Déclaration de la classe
├── Harl.cpp       // Implémentation des méthodes
├── main.cpp       // Programme principal avec switch
└── Makefile       // Compilation
```

---

## 📝 Implémentation détaillée

### Harl.hpp

Identique à l'exercice 05 :

```cpp
class Harl {
    private:
        void debug(void);
        void info(void);
        void warning(void);
        void error(void);

    public:
        Harl();
        ~Harl();
        void complain(std::string level);
};
```

### Harl.cpp

Légèrement modifié pour un meilleur affichage :

```cpp
void Harl::debug(void) {
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese..." << std::endl;
    std::cout << "I really do !" << std::endl;
    std::cout << std::endl;  // Ligne vide pour la lisibilité
}

// Même structure pour info(), warning(), error()
```

**Différence avec ex05 :** Ajout d'un `std::endl` à la fin pour séparer visuellement les messages.

### main.cpp - Fonction auxiliaire

```cpp
int getLevel(std::string level)
{
    std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    
    for (int i = 0; i < 4; i++)
    {
        if (levels[i] == level)
            return (i);  // Retourne l'index (0, 1, 2, ou 3)
    }
    return (-1);  // Niveau invalide
}
```

**Rôle :** Convertir le string en entier pour le switch.

### main.cpp - Le cœur du programme

```cpp
int main(int argc, char **argv)
{
    // 1. Vérification du nombre d'arguments
    if (argc != 2)
    {
        std::cout << "Usage: ./harlFilter [DEBUG|INFO|WARNING|ERROR]" << std::endl;
        return (1);
    }

    // 2. Création de l'objet Harl
    Harl harl;
    
    // 3. Conversion du niveau en entier
    int level = getLevel(argv[1]);

    // 4. Switch avec fall-through
    switch (level)
    {
        case 0:  // DEBUG
            harl.complain("DEBUG");
            // fall through (pas de break)
        case 1:  // INFO
            harl.complain("INFO");
            // fall through
        case 2:  // WARNING
            harl.complain("WARNING");
            // fall through
        case 3:  // ERROR
            harl.complain("ERROR");
            break;  // Arrêt ici
        default:  // Niveau invalide
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }

    return (0);
}
```

---

## 🔍 Analyse du comportement

### Comportement du fall-through

| Argument | Cases exécutées | Messages affichés |
|----------|----------------|-------------------|
| `DEBUG` | 0 → 1 → 2 → 3 | DEBUG, INFO, WARNING, ERROR |
| `INFO` | 1 → 2 → 3 | INFO, WARNING, ERROR |
| `WARNING` | 2 → 3 | WARNING, ERROR |
| `ERROR` | 3 | ERROR |
| `UNKNOWN` | default | Message par défaut |

### Pourquoi le fall-through ?

C'est une métaphore de **filtrage par niveau de priorité** :

1. **DEBUG** = Niveau le plus bas → Affiche TOUT
2. **INFO** = Niveau moyen-bas → Affiche INFO et plus grave
3. **WARNING** = Niveau moyen-haut → Affiche WARNING et plus grave
4. **ERROR** = Niveau le plus haut → Affiche seulement ERROR

C'est comme un **système de logs** : si on filtre sur WARNING, on veut voir WARNING + ERROR (les messages importants), mais pas DEBUG ni INFO.

---

## 🧪 Tests et résultats

### Compilation

```bash
make
```

### Test 1 : Niveau DEBUG

```bash
./harlFilter DEBUG
```

**Résultat attendu :**
```
[ DEBUG ]
I love having extra bacon for my 7XL-double-cheese-triple-pickle-special ketchup burger.
I really do !

[ INFO ]
I cannot believe adding extra bacon costs more money.
You didn't put enough bacon in my burger ! If you did, I wouldn't be asking for more !

[ WARNING ]
I think I deserve to have some extra bacon for free.
I've been coming for years whereas you started working here since last month.

[ ERROR ]
This is unacceptable ! I want to speak to the manager now.

```

### Test 2 : Niveau WARNING

```bash
./harlFilter WARNING
```

**Résultat attendu :**
```
[ WARNING ]
I think I deserve to have some extra bacon for free.
I've been coming for years whereas you started working here since last month.

[ ERROR ]
This is unacceptable ! I want to speak to the manager now.

```

### Test 3 : Niveau ERROR

```bash
./harlFilter ERROR
```

**Résultat attendu :**
```
[ ERROR ]
This is unacceptable ! I want to speak to the manager now.

```

### Test 4 : Niveau invalide

```bash
./harlFilter CRITICAL
```

**Résultat attendu :**
```
[ Probably complaining about insignificant problems ]
```

### Test 5 : Sans argument

```bash
./harlFilter
```

**Résultat attendu :**
```
Usage: ./harlFilter [DEBUG|INFO|WARNING|ERROR]
```

### Test 6 : Trop d'arguments

```bash
./harlFilter DEBUG INFO
```

**Résultat attendu :**
```
Usage: ./harlFilter [DEBUG|INFO|WARNING|ERROR]
```

---

## 💡 Points techniques importants

### 1. Pourquoi convertir en int ?

Le `switch` en C++ ne peut pas comparer directement des `std::string`. Il faut :
- Soit utiliser des `if/else` (pas l'objectif de l'exercice)
- Soit convertir les strings en entiers via une fonction auxiliaire

### 2. Le commentaire "fall through"

```cpp
case 0:
    harl.complain("DEBUG");
    // fall through
```

Ce commentaire est une **bonne pratique** :
- Il indique clairement que l'absence de `break` est **intentionnelle**
- Certains compilateurs émettent des warnings si le fall-through n'est pas documenté
- Il améliore la lisibilité du code

### 3. Gestion des erreurs

```cpp
if (argc != 2)
{
    std::cout << "Usage: ..." << std::endl;
    return (1);  // Code de sortie d'erreur
}
```

Toujours vérifier les arguments avant de les utiliser !

### 4. La fonction getLevel()

```cpp
int getLevel(std::string level)
{
    std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    
    for (int i = 0; i < 4; i++)
    {
        if (levels[i] == level)
            return (i);
    }
    return (-1);
}
```

**Avantages :**
- Code réutilisable et lisible
- Séparation des responsabilités
- Facile à modifier si on ajoute des niveaux

---

## 🎨 Comparaison des approches

### ❌ Approche avec if/else (non demandée)

```cpp
if (level == "DEBUG") {
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
}
else if (level == "INFO") {
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
}
// ... très répétitif
```

**Problèmes :**
- Code extrêmement répétitif
- Difficile à maintenir
- Ne démontre pas la maîtrise du switch

### ✅ Approche avec switch + fall-through (demandée)

```cpp
switch (getLevel(level)) {
    case 0:
        harl.complain("DEBUG");
        // fall through
    case 1:
        harl.complain("INFO");
        // fall through
    case 2:
        harl.complain("WARNING");
        // fall through
    case 3:
        harl.complain("ERROR");
        break;
    default:
        std::cout << "Invalid level" << std::endl;
}
```

**Avantages :**
- Utilisation intelligente du fall-through
- Code élégant et concis
- Facile à comprendre et maintenir
- Démontre la maîtrise du switch

---

## 🔄 Schéma du flux d'exécution

```
Programme lancé avec argument "INFO"
           |
           v
   argc == 2 ? ────NO────> Affiche Usage
           |
          YES
           |
           v
    level = getLevel("INFO")
           |
           v
       level = 1
           |
           v
     switch (1)
           |
           v
    case 0: SKIP (car 1 != 0)
           |
           v
    case 1: EXECUTE harl.complain("INFO")
           |
           v
    case 2: EXECUTE harl.complain("WARNING")  (fall-through)
           |
           v
    case 3: EXECUTE harl.complain("ERROR")    (fall-through)
           |
           v
        break
           |
           v
      return (0)
```

---

## 📚 Concepts C++ utilisés

| Concept | Description | Utilisation dans l'exercice |
|---------|-------------|----------------------------|
| **Switch** | Structure de contrôle multi-cas | Filtrage des niveaux |
| **Fall-through** | Omission du break dans switch | Affichage cascadé des messages |
| **argc/argv** | Arguments de ligne de commande | Lecture du niveau souhaité |
| **Fonction auxiliaire** | `getLevel()` | Conversion string → int |
| **Validation d'entrée** | Vérification argc | Gestion des erreurs |
| **return codes** | 0 = succès, 1 = erreur | Code de sortie du programme |

---

## 🚨 Erreurs courantes à éviter

### 1. Oublier le fall-through

```cpp
// ❌ FAUX
case 1:
    harl.complain("INFO");
    break;  // Oups ! On arrête trop tôt
case 2:
    harl.complain("WARNING");
```

### 2. Utiliser argv sans vérifier argc

```cpp
// ❌ FAUX - Segfault si pas d'argument !
int main(int argc, char **argv) {
    Harl harl;
    harl.complain(argv[1]);  // argv[1] peut ne pas exister !
}
```

### 3. Oublier le case default

```cpp
// ❌ FAUX - Pas de gestion des niveaux invalides
switch (level) {
    case 0:
        harl.complain("DEBUG");
    // ... pas de default
}
```

### 4. Comparer directement des strings dans le switch

```cpp
// ❌ NE COMPILE PAS !
switch (level) {  // level est std::string
    case "DEBUG":  // Erreur : case doit être une constante entière
        // ...
}
```

---

## 🎯 Améliorations possibles (hors sujet)

### Version avec enum

```cpp
enum Level { DEBUG = 0, INFO, WARNING, ERROR, INVALID = -1 };

Level getLevel(std::string level) {
    if (level == "DEBUG") return DEBUG;
    if (level == "INFO") return INFO;
    if (level == "WARNING") return WARNING;
    if (level == "ERROR") return ERROR;
    return INVALID;
}
```

### Version avec map (C++98 compatible)

```cpp
#include <map>

int getLevel(std::string level) {
    std::map<std::string, int> levels;
    levels["DEBUG"] = 0;
    levels["INFO"] = 1;
    levels["WARNING"] = 2;
    levels["ERROR"] = 3;
    
    if (levels.find(level) != levels.end())
        return levels[level];
    return -1;
}
```

---

## ✅ Checklist de validation

- [ ] Le programme se nomme `harlFilter`
- [ ] Il prend **exactement 1 argument** en ligne de commande
- [ ] Le switch utilise le **fall-through** (pas de break entre les cases 0-2)
- [ ] Les 4 niveaux (DEBUG, INFO, WARNING, ERROR) fonctionnent correctement
- [ ] Un niveau invalide affiche le message par défaut
- [ ] Aucun argument ou trop d'arguments affiche le message d'usage
- [ ] Le code compile avec `-Wall -Wextra -Werror -std=c++98`
- [ ] Pas de fuite mémoire (vérifier avec valgrind si nécessaire)
- [ ] Les commentaires `// fall through` sont présents

---

## 🎓 Objectifs pédagogiques

Cet exercice vous apprend à :

1. ✅ Utiliser le **switch** efficacement en C++
2. ✅ Comprendre et exploiter le **fall-through**
3. ✅ Gérer les **arguments de ligne de commande** (argc/argv)
4. ✅ Valider les entrées utilisateur
5. ✅ Convertir des strings en valeurs numériques pour le switch
6. ✅ Créer des fonctions auxiliaires pour améliorer la lisibilité
7. ✅ Gérer les cas d'erreur proprement

---

## 📖 Comparaison Ex05 vs Ex06

| Critère | Ex05 (Harl) | Ex06 (harlFilter) |
|---------|-------------|-------------------|
| **Structure** | Pointeurs de fonctions | Switch avec fall-through |
| **Objectif pédagogique** | Pointeurs membres | Switch et arguments CLI |
| **Comportement** | Un seul message | Messages cascadés |
| **Complexité** | Moyenne | Facile |
| **Réutilisabilité** | Haute (tableau de fonctions) | Moyenne (switch statique) |

---

## 🏆 Astuce pour briller

Ajoutez des commentaires explicatifs dans votre code :

```cpp
switch (level)
{
    case 0:  // DEBUG: affiche tous les niveaux
        harl.complain("DEBUG");
        // fall through intentionnel
    case 1:  // INFO: affiche INFO, WARNING, ERROR
        harl.complain("INFO");
        // fall through intentionnel
    case 2:  // WARNING: affiche WARNING, ERROR
        harl.complain("WARNING");
        // fall through intentionnel
    case 3:  // ERROR: affiche uniquement ERROR
        harl.complain("ERROR");
        break;
    default:  // Niveau non reconnu
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
}
```

---

## 🎉 Conclusion

L'exercice 06 est une excellente démonstration de l'utilisation du **fall-through** du switch, un comportement souvent considéré comme un piège mais qui, utilisé intentionnellement, devient un outil puissant pour créer des comportements cascadés élégants.

Cette approche simule parfaitement un **système de logging avec niveaux de priorité**, où demander les logs WARNING implique aussi d'afficher les ERROR (plus graves).

**Bon courage ! 🚀**
