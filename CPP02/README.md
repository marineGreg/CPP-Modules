*This project has been created as part of the 42 curriculum by mgregoir*

# CPP Module 02 - Tout comprendre sur la Virgule Fixe

Ce module est une étape clé de l'apprentissage du C++. Il introduit la **Forme Canonique Orthodoxe**, la **Surcharge d'opérateurs** et la manipulation des **Nombres en Virgule Fixe**.

---

## 1. Le Concept : Pourquoi la Virgule Fixe ?

L'ordinateur est très rapide avec les **entiers** (`1`, `2`, `100`), mais plus lent et parfois imprécis avec les **nombres à virgule** (`float`). 

### L'analogie de la Tasse à Mesurer
Imagine que tu veux mesurer des **Litres** (ton `float`), mais que ton outil ne sait compter que des **Gouttes** (ton `int _value`).
*   **La Règle :** On décide qu'il y a exactement **256 gouttes** dans **1 Litre**.
*   **Le Zoom :** Pour stocker 0,5 Litre, on stocke $0,5 \times 256 = 128$ gouttes.
*   **L'illusion :** En mémoire, on a un entier (`128`), mais logiquement, on manipule un nombre à virgule (`0,5`).

C'est ce qu'on appelle la **Virgule Fixe** : on "fixe" la position de la virgule (ici à 8 bits du bord droit) pour transformer un nombre décimal en un entier "zoomé".

---

## 2. Le Moteur Technique : Les Décalages de Bits

Dans ce module, on utilise `_bits = 8`. Cela signifie que notre facteur de zoom est $2^8 = \mathbf{256}$.

| Fonction | Opération | Pourquoi ? |
| :--- | :--- | :--- |
| **`Fixed(int)`** | `n << 8` | On décale de 8 crans à gauche (multiplication par 256). |
| **`Fixed(float)`**| `roundf(n * 256)` | Multiplication par 256 + arrondi pour la précision. |
| **`toFloat()`** | `_value / 256.0` | On divise par 256 pour "dézoomer" et retrouver la virgule. |
| **`toInt()`** | `_value >> 8` | On décale à droite (division entière) pour jeter les décimales. |

---

## 3. La Forme Canonique Orthodoxe (OCF)

Pour être robuste, une classe C++ doit toujours implémenter ces 4 fonctions :

1.  **Constructeur par défaut** : Initialise l'objet (ex: `_value = 0`).
2.  **Constructeur de recopie** : Crée un jumeau d'un objet existant (`Fixed b(a)`).
3.  **Opérateur d'affectation (`=`)** : Met à jour un objet existant à partir d'un autre (`b = a`).
4.  **Destructeur** : Nettoie l'objet à sa disparition.

**Pourquoi ?** Pour garantir que chaque objet possède ses propres données (Deep Copy) et éviter les crashs mémoire (Double Free).

---

## 4. La Surcharge d'Opérateurs

La surcharge permet à notre classe d'utiliser les signes mathématiques classiques (`+`, `-`, `*`, `/`, `>`, `<`, etc.).

### L'incrémentation (`++a` vs `a++`)
*   **Pré-incrément (`++a`)** : On ajoute 1 à `_value` et on renvoie l'objet lui-même. C'est rapide.
*   **Post-incrément (`a++`)** : On prend une "photo" de l'objet (copie `tmp`), on augmente l'original, mais on renvoie la photo. C'est pour cela qu'on voit l'ancienne valeur avant le changement.

### Le "Petit Pas" (Epsilon)
La plus petite graduation de notre règle est **1** (la valeur brute). 
En nombre réel, cela vaut $1 / 256 = \mathbf{0,00390625}$. C'est le pas minimal de notre classe.

---

## 5. Questions Fréquentes (Préparation Soutenance)

**Q : Pourquoi `static const int _bits = 8` ?**  
*R : `static` signifie que la variable est partagée par tous les objets de la classe (elle n'est stockée qu'une seule fois). `const` signifie qu'elle ne change jamais. C'est notre règle de zoom commune.*

**Q : Pourquoi `roundf` dans le constructeur float ?**  
*R : Les floats sont imprécis. `roundf` permet d'arrondir à la graduation entière la plus proche après la multiplication, évitant ainsi de perdre de la précision (ex: transformer 0.9999 en 1).*

**Q : Pourquoi l'opérateur `<<` est-il en dehors de la classe ?**  
*R : Parce que le premier paramètre est `std::ostream` (le flux à gauche de `<<`) et non notre classe `Fixed`. On ne peut pas modifier la classe standard `std::ostream`, donc on crée une fonction amie/extérieure.*

**Q : C'est quoi la différence entre Virgule Fixe et Virgule Flottante ?**  
*R : En virgule fixe, la précision est la même partout (toujours 1/256ème). En virgule flottante (`float`), la virgule peut se déplacer pour représenter des nombres minuscules ou immenses, mais au prix d'une complexité de calcul plus grande.*

---
*Ce module permet de comprendre que les types de base (`int`, `float`) ne sont pas magiques : on peut recréer nos propres types numériques avec nos propres règles !*

***

 === Topo nombre virgule fixe ===

Deux infos stockees principalement : 
 un int (dont la taille en nb de bits peut etre limitee pour raison de perf)
 un int constant qui donne le nombre de bits dedies a la partie decimale du nombre

     Exemple:
      Int raw = 00001101 00101000 (16 bits)
      Int deci_bits = 8 (donc 8 pour la partie decimale)

      on peut parler de forme 16-bit (ou Q8.8)

    [Integer part] [Decimal part]
    |      8 bits |       8 bits   |
    --------------------------------
    |  00001101   |   00101000     |
    --------------------------------
        13 (int value)      40 (raw_deci)
                      
      Decimal part value  = raw_deci x (1/ 2^deci_bits)
                          = 40 x (1 / 2^8)
                          = 40 x 1/256
                          = 0.15625

    => Value = 13.15625