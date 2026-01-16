# 📚 Guide - Exercice 02 : Account Class

## 🎯 Objectif de l'exercice

C'est un exercice de **reverse engineering** ! Vous devez implémenter la classe `Account` en analysant :
- Les signatures dans `Account.hpp`
- Le comportement dans `tests.cpp`
- La sortie attendue dans `19920104_091532.log`

---

## 📁 Fichiers fournis

| Fichier | Description | À modifier ? |
|---------|-------------|--------------|
| `Account.hpp` | Header avec toutes les signatures | ❌ NON |
| `tests.cpp` | Programme de test | ❌ NON |
| `19920104_091532.log` | Sortie attendue | ❌ NON |
| `Account.cpp` | **À CRÉER** | ✅ OUI |

---

## 🔍 Analyse de la classe Account

### Variables membres statiques (partagées entre toutes les instances)

```cpp
static int _nbAccounts;           // Nombre total de comptes créés
static int _totalAmount;          // Montant total de tous les comptes
static int _totalNbDeposits;      // Total des dépôts effectués
static int _totalNbWithdrawals;   // Total des retraits effectués
```

⚠️ **Important** : Ces variables doivent être **initialisées dans Account.cpp** :
```cpp
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;
```

### Variables membres d'instance (propres à chaque compte)

```cpp
int _accountIndex;      // Index du compte (auto-incrémenté)
int _amount;            // Montant actuel du compte
int _nbDeposits;        // Nombre de dépôts sur ce compte
int _nbWithdrawals;     // Nombre de retraits sur ce compte
```

---

## 📊 Format de sortie (selon le log)

### 1. Timestamp
```
[19920104_091532]
```
Format : `[YYYYMMDD_HHMMSS]`

### 2. Création d'un compte
```
[19920104_091532] index:0;amount:42;created
```

### 3. Affichage des stats globales
```
[19920104_091532] accounts:8;total:20049;deposits:0;withdrawals:0
```

### 4. Affichage du statut d'un compte
```
[19920104_091532] index:0;amount:42;deposits:0;withdrawals:0
```

### 5. Dépôt réussi
```
[19920104_091532] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
```
- `p_amount` = previous amount (montant avant)
- `amount` = nouveau montant
- `nb_deposits` = nombre total de dépôts sur ce compte

### 6. Retrait réussi
```
[19920104_091532] index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1
```

### 7. Retrait refusé (fonds insuffisants)
```
[19920104_091532] index:0;p_amount:47;withdrawal:refused
```

### 8. Fermeture d'un compte
```
[19920104_091532] index:0;amount:47;closed
```

---

## 🛠️ Méthodes à implémenter

### Méthodes statiques publiques

```cpp
static int getNbAccounts(void);        // Retourne _nbAccounts
static int getTotalAmount(void);       // Retourne _totalAmount
static int getNbDeposits(void);        // Retourne _totalNbDeposits
static int getNbWithdrawals(void);     // Retourne _totalNbWithdrawals
static void displayAccountsInfos(void); // Affiche les stats globales
```

### Méthode statique privée

```cpp
static void _displayTimestamp(void);   // Affiche [YYYYMMDD_HHMMSS]
```

💡 **Astuce pour le timestamp** : Utilisez `<ctime>` avec `time()` et `localtime()`

### Constructeur et destructeur

```cpp
Account(int initial_deposit);
~Account(void);
```

**Le constructeur doit :**
- Initialiser `_accountIndex` avec la valeur actuelle de `_nbAccounts`
- Incrémenter `_nbAccounts`
- Initialiser `_amount` avec `initial_deposit`
- Ajouter `initial_deposit` à `_totalAmount`
- Initialiser `_nbDeposits` et `_nbWithdrawals` à 0
- Afficher le message de création

**Le destructeur doit :**
- Afficher le message de fermeture

### Méthodes d'instance

```cpp
void makeDeposit(int deposit);
bool makeWithdrawal(int withdrawal);
int checkAmount(void) const;
void displayStatus(void) const;
```

**`makeDeposit(int deposit)`** :
- Afficher l'ancien montant, le dépôt, le nouveau montant
- Incrémenter `_amount`
- Incrémenter `_nbDeposits`
- Incrémenter `_totalAmount`
- Incrémenter `_totalNbDeposits`

**`makeWithdrawal(int withdrawal)`** :
- Vérifier si `withdrawal <= _amount`
- Si OUI : effectuer le retrait et retourner `true`
- Si NON : afficher "refused" et retourner `false`

**`checkAmount(void) const`** :
- Retourne `_amount` (getter simple)

**`displayStatus(void) const`** :
- Affiche l'état complet du compte

---

## 🚀 Ordre d'implémentation recommandé

1. ✅ **Initialiser les variables statiques** dans `Account.cpp`
2. ✅ **Implémenter `_displayTimestamp()`**
3. ✅ **Implémenter le constructeur** `Account(int initial_deposit)`
4. ✅ **Implémenter les getters statiques** (getNbAccounts, etc.)
5. ✅ **Implémenter `displayAccountsInfos()`**
6. ✅ **Implémenter `displayStatus()`**
7. ✅ **Implémenter `makeDeposit()`**
8. ✅ **Implémenter `makeWithdrawal()`**
9. ✅ **Implémenter `checkAmount()`**
10. ✅ **Implémenter le destructeur** `~Account()`

---

## 🧪 Comment tester

### Compilation
```bash
c++ -Wall -Wextra -Werror -std=c++98 Account.cpp tests.cpp -o account
```

### Exécution
```bash
./account > my_output.log
```

### Comparaison avec le log attendu
```bash
diff 19920104_091532.log my_output.log
```

⚠️ **Note** : Le timestamp sera différent, donc utilisez cette commande pour ignorer les timestamps :
```bash
diff <(sed 's/\[.*\]/[TIMESTAMP]/g' 19920104_091532.log) \
     <(sed 's/\[.*\]/[TIMESTAMP]/g' my_output.log)
```

Ou simplement comparez visuellement les formats de sortie.

---

## 💡 Points importants

1. **Variables statiques** : Doivent être initialisées **hors de la classe** dans le .cpp
2. **Format exact** : Respectez exactement les `;` et les noms des champs
3. **Pas d'espaces superflus** : Le format est très strict
4. **Ordre des opérations** : Affichage → Modification des variables
5. **Timestamp** : Utilisez `time()` et `localtime()` de `<ctime>`

---

## 📝 Exemple de structure Account.cpp

```cpp
#include "Account.hpp"
#include <iostream>
#include <ctime>

// Initialisation des variables statiques
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

// Implémentation du timestamp
void Account::_displayTimestamp(void) {
    // Obtenir l'heure actuelle
    std::time_t now = std::time(0);
    std::tm* ltm = std::localtime(&now);
    
    // Afficher au format [YYYYMMDD_HHMMSS]
    std::cout << "[" 
              << (1900 + ltm->tm_year)
              << ...
              << "] ";
}

// ... reste des implémentations
```

---

## ✅ Checklist finale

- [ ] Toutes les variables statiques sont initialisées
- [ ] Le timestamp s'affiche au bon format
- [ ] Les messages de création/destruction s'affichent
- [ ] Les dépôts fonctionnent et mettent à jour les totaux
- [ ] Les retraits refusent si fonds insuffisants
- [ ] Les stats globales sont correctes
- [ ] Le format de sortie est identique au log (sauf timestamp)
- [ ] Pas de memory leaks
- [ ] Compilation avec `-std=c++98`

---

**Bon courage ! 🚀**

