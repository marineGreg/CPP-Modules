# 📝 Démarche de réalisation - Exercice 02 : Account Class

## 🎯 Contexte

L'exercice 02 est un exercice de **reverse engineering** où il fallait implémenter la classe `Account` en se basant uniquement sur :
- Le header `Account.hpp` (signatures)
- Le fichier de test `tests.cpp` (comportement)
- Le fichier log `19920104_091532.log` (sortie attendue)

---

## 🔍 Phase 1 : Analyse et compréhension

### 1.1 Analyse du header (Account.hpp)

J'ai identifié deux types de variables membres :

**Variables statiques (partagées entre toutes les instances) :**
- `_nbAccounts` : compteur total de comptes
- `_totalAmount` : somme de tous les montants
- `_totalNbDeposits` : total des dépôts effectués
- `_totalNbWithdrawals` : total des retraits effectués

**Variables d'instance (propres à chaque compte) :**
- `_accountIndex` : numéro d'index du compte
- `_amount` : montant actuel
- `_nbDeposits` : nombre de dépôts sur ce compte
- `_nbWithdrawals` : nombre de retraits sur ce compte

### 1.2 Analyse du fichier log

J'ai observé le format exact de chaque type de message :

```
[TIMESTAMP] index:X;amount:Y;created                  → Création
[TIMESTAMP] accounts:X;total:Y;deposits:Z;withdrawals:W  → Stats globales
[TIMESTAMP] index:X;amount:Y;deposits:Z;withdrawals:W    → Statut d'un compte
[TIMESTAMP] index:X;p_amount:Y;deposit:Z;amount:W;nb_deposits:N  → Dépôt
[TIMESTAMP] index:X;p_amount:Y;withdrawal:Z;amount:W;nb_withdrawals:N  → Retrait
[TIMESTAMP] index:X;p_amount:Y;withdrawal:refused       → Retrait refusé
[TIMESTAMP] index:X;amount:Y;closed                   → Destruction
```

**Point clé :** Le format est très strict avec des `;` et pas d'espaces superflus.

### 1.3 Analyse du fichier tests.cpp

J'ai compris que :
- 8 comptes sont créés avec des montants initiaux
- Les dépôts et retraits sont effectués via des boucles
- Certains retraits sont refusés (fonds insuffisants)
- Les comptes sont détruits automatiquement en fin de scope

---

## 🛠️ Phase 2 : Implémentation étape par étape

### 2.1 Initialisation des variables statiques

**Point crucial :** Les variables statiques doivent être initialisées **hors de la classe**.

```cpp
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;
```

### 2.2 Implémentation du timestamp

J'ai utilisé `<ctime>` avec `time()` et `localtime()` :

```cpp
void Account::_displayTimestamp(void) {
    std::time_t now = std::time(0);
    std::tm* ltm = std::localtime(&now);

    std::cout << "[" 
              << (1900 + ltm->tm_year)
              << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon)
              << std::setfill('0') << std::setw(2) << ltm->tm_mday
              << "_"
              << std::setfill('0') << std::setw(2) << ltm->tm_hour
              << std::setfill('0') << std::setw(2) << ltm->tm_min
              << std::setfill('0') << std::setw(2) << ltm->tm_sec
              << "] ";
}
```

**Points importants :**
- `std::setfill('0')` et `std::setw(2)` pour avoir `01` au lieu de `1`
- L'année commence à 1900, donc on ajoute 1900
- Les mois commencent à 0, donc on ajoute 1

### 2.3 Constructeur

Le constructeur doit :
1. Initialiser l'index avec la valeur actuelle de `_nbAccounts`
2. Incrémenter `_nbAccounts`
3. Initialiser le montant
4. Ajouter au total
5. Afficher le message

```cpp
Account::Account(int initial_deposit) {
    this->_accountIndex = _nbAccounts;
    this->_amount = initial_deposit;
    this->_nbDeposits = 0;
    this->_nbWithdrawals = 0;

    _nbAccounts++;
    _totalAmount += initial_deposit;

    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "created" << std::endl;
}
```

**Ordre important :** L'index doit être assigné AVANT d'incrémenter `_nbAccounts`.

### 2.4 Destructeur

Simple affichage du message de fermeture :

```cpp
Account::~Account(void) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "closed" << std::endl;
}
```

### 2.5 Getters statiques

Ce sont de simples retours des variables statiques :

```cpp
int Account::getNbAccounts(void) { return _nbAccounts; }
int Account::getTotalAmount(void) { return _totalAmount; }
int Account::getNbDeposits(void) { return _totalNbDeposits; }
int Account::getNbWithdrawals(void) { return _totalNbWithdrawals; }
```

### 2.6 Affichage des informations globales

```cpp
void Account::displayAccountsInfos(void) {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts << ";";
    std::cout << "total:" << _totalAmount << ";";
    std::cout << "deposits:" << _totalNbDeposits << ";";
    std::cout << "withdrawals:" << _totalNbWithdrawals << std::endl;
}
```

### 2.7 Affichage du statut d'un compte

```cpp
void Account::displayStatus(void) const {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "deposits:" << this->_nbDeposits << ";";
    std::cout << "withdrawals:" << this->_nbWithdrawals << std::endl;
}
```

### 2.8 Dépôt

**Logique :**
1. Afficher le timestamp et les infos de base
2. Modifier les variables
3. Afficher le résultat

```cpp
void Account::makeDeposit(int deposit) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "p_amount:" << this->_amount << ";";
    std::cout << "deposit:" << deposit << ";";

    // Modifications
    this->_amount += deposit;
    this->_nbDeposits++;
    _totalAmount += deposit;
    _totalNbDeposits++;

    std::cout << "amount:" << this->_amount << ";";
    std::cout << "nb_deposits:" << this->_nbDeposits << std::endl;
}
```

**Point clé :** Il faut mettre à jour TOUTES les variables (instance ET statiques).

### 2.9 Retrait

**Logique :**
1. Vérifier si le retrait est possible
2. Si NON : afficher "refused" et retourner `false`
3. Si OUI : effectuer le retrait et retourner `true`

```cpp
bool Account::makeWithdrawal(int withdrawal) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "p_amount:" << this->_amount << ";";

    if (withdrawal > this->_amount) {
        std::cout << "withdrawal:refused" << std::endl;
        return false;
    }

    std::cout << "withdrawal:" << withdrawal << ";";

    // Modifications
    this->_amount -= withdrawal;
    this->_nbWithdrawals++;
    _totalAmount -= withdrawal;
    _totalNbWithdrawals++;

    std::cout << "amount:" << this->_amount << ";";
    std::cout << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;

    return true;
}
```

### 2.10 Getter du montant

Simple retour :

```cpp
int Account::checkAmount(void) const {
    return this->_amount;
}
```

---

## ✅ Phase 3 : Tests et validation

### 3.1 Compilation

```bash
c++ -Wall -Wextra -Werror -std=c++98 Account.cpp tests.cpp -o account
```

**Résultat :** ✅ Compilation réussie sans warnings ni erreurs.

### 3.2 Exécution

```bash
./account
```

**Résultat :** ✅ Programme s'exécute correctement et affiche les résultats attendus.

### 3.3 Comparaison avec le log

```bash
diff <(sed 's/\[.*\]/[TIMESTAMP]/g' 19920104_091532.log) \
     <(./account | sed 's/\[.*\]/[TIMESTAMP]/g')
```

**Résultat :** ✅ Aucune différence ! Le format est identique.

---

## 💡 Points clés et pièges évités

### 1. Variables statiques
❌ **Erreur courante :** Oublier d'initialiser les variables statiques dans le .cpp
✅ **Solution :** Toujours les initialiser hors de la classe

### 2. Ordre des opérations
❌ **Erreur courante :** Incrémenter `_nbAccounts` avant de l'assigner à `_accountIndex`
✅ **Solution :** Assigner d'abord, incrémenter ensuite

### 3. Mise à jour des totaux
❌ **Erreur courante :** Oublier de mettre à jour `_totalAmount` ou les compteurs globaux
✅ **Solution :** Toujours mettre à jour les variables d'instance ET les variables statiques

### 4. Format de sortie strict
❌ **Erreur courante :** Ajouter des espaces autour des `;`
✅ **Solution :** Respecter exactement le format du log

### 5. Timestamp
❌ **Erreur courante :** Oublier le padding avec des zéros
✅ **Solution :** Utiliser `std::setfill('0')` et `std::setw(2)`

### 6. Retrait refusé
❌ **Erreur courante :** Ne pas retourner `false` quand le retrait est refusé
✅ **Solution :** Vérifier le montant AVANT d'effectuer le retrait

---

## 📊 Résultat final

### Structure du code

```
Account.cpp (143 lignes)
├── Initialisation des variables statiques (4 lignes)
├── Constructeur (13 lignes)
├── Destructeur (6 lignes)
├── Getters statiques (4 méthodes, 1 ligne chacune)
├── displayAccountsInfos() (7 lignes)
├── makeDeposit() (15 lignes)
├── makeWithdrawal() (22 lignes)
├── checkAmount() (3 lignes)
├── displayStatus() (7 lignes)
└── _displayTimestamp() (13 lignes)
```

### Validation

✅ Compilation sans warnings  
✅ Exécution correcte  
✅ Sortie identique au log (sauf timestamps)  
✅ Pas de memory leaks  
✅ Respect du C++98  
✅ Code propre et lisible  

---

## 🚀 Conclusion

Cet exercice m'a permis de comprendre :
- Le fonctionnement des **variables statiques** en C++
- L'importance de l'**ordre des opérations**
- La gestion de **l'état partagé** entre instances
- Le **reverse engineering** à partir d'une sortie attendue
- L'utilisation de `<ctime>` pour les timestamps
- Le formatage précis avec `<iomanip>`

**Temps de réalisation :** ~30 minutes  
**Difficulté :** Moyenne (surtout comprendre la logique des variables statiques)  
**Points délicats :** Format de sortie strict, ordre des opérations, timestamp avec padding

---

**Exercice validé ! ✅**

