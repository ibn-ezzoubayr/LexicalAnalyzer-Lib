# Bibliothèque d'Analyse Lexicale

## Introduction
بسم الله الرحمن الرحيم، الحمد لله الذي أنشأ و برى، و خلق الماء و الثرى، و أبدع كل شيء و ذرى، لا يغيب عن بصره صغير النمل في الليل إذا سرى، و لا يعزب عن علمه مثقال ذرة في الأرض و لا في السماء، الرحمن على العرش استوى، له ما في السماوات و ما في الأرض و ما بينهما و ما تحت الثرى، و إن تجهر بالقول فإنه يعلم السر و أخفى، الله لا إله إلا هو له الأسماء الحسنى، خلق آدم فابتلاه ثم اجتباه فتاب عليه و هدى، و بعث نوحا فصنع الفلك بأمر الله و جرى، و نجا الخليل من النار فصار حرها بردا و سلاما عليه فاعتبروا بما جرى، و آتى موسى تسع آيات فما سمع فرعون و مرعوى، و أيد عيسى بآيات تبهر الورى، و أنزل الكتاب على محمد فيه البينات و الهدى، نحمده على نعمه التي لا تزال تترى، و نصلي و نسلم على المبعوث في أم القرى، صلى الله عليه و على صاحبه أبي بكر في الغار بلا مرى، و على عمر الملهم برأيه فهو بنور الله يرى، و على عثمان زوج ابنتيه ما كان حديثا يفترى، و على علي ابن عمه بدر العلوم و أسد الشرى، و على جميع آله و صحابته الذين انتشر فضلهم في الورى، و سلم تسليما كثيرا.

هدية متواضعة لطلبة المدرسة المغربية لعلوم المهندسة السنة الرابعة شعبة المعلوميات

*Lire dans d'autres langues: [English](README.md), [العربية](README_AR.md)*

Une bibliothèque C++ pour l'analyse lexicale et la simulation d'automates finis. Cette bibliothèque permet de créer et de travailler avec des matrices de transition pour les automates finis, de traiter des chaînes d'entrée et de vérifier l'acceptation des mots selon des règles définies.

## Fonctionnalités

- Chargement et création de matrices de transition
- Traitement des mots d'entrée selon un vocabulaire défini
- Traçage des chemins dans la matrice de transition
- Vérification de l'acceptation des mots
- Liste de tous les mots valides d'une longueur spécifique
- Chargement de vocabulaires personnalisés à partir de fichiers

## Installation

C'est une bibliothèque header-only. Pour l'utiliser dans votre projet :

1. Copiez `compilation_emsi.h` et `compilation_emsi.cpp` dans votre répertoire de projet
2. Incluez le fichier d'en-tête dans votre code :
```cpp
#include "compilation_emsi.h"
```

## Utilisation

### Configuration de Base

```cpp
// Créer une instance de l'analyseur lexical
CompilationEmsi lexer;

// Charger le vocabulaire depuis un fichier
lexer.loadVocabulary("vocabulary.txt");
```

### Chargement d'une Matrice de Transition

Vous pouvez charger une matrice de transition soit depuis un fichier, soit la créer de manière interactive :

```cpp
// Chargement depuis un fichier
int** matrice = lexer.matrice_file("matrix.txt");

// Ou création interactive
int** matrice = lexer.matrice();
```

### Traitement des Mots

```cpp
// Traiter un mot d'une longueur spécifique
int longueur = 3;
int* mot = lexer.Mot(longueur);

// Tracer le mot dans la matrice
int resultat = lexer.trace(matrice, mot, longueur);

// Vérifier si le mot est accepté
lexer.reconaissance(resultat);
```

### Fonctions Utilitaires

```cpp
// Afficher la matrice de transition
lexer.displayMatrix(matrice);

// Lister tous les mots valides de longueur 3
lexer.lister_mot(matrice);
```

## Formats de Fichiers

### Fichier de Vocabulaire (vocabulary.txt)
- Une seule ligne contenant des symboles séparés par des virgules
- Exemple :
```
a,b,c
```

### Fichier de Matrice (matrix.txt)
- Première ligne : nombre de lignes et de colonnes
- Lignes suivantes : valeurs de la matrice de transition
- Exemple :
```
3 3
1 0 2
2 1 0
0 2 1
```

## Documentation des Méthodes

### `loadVocabulary(const char* filename)`
Charge le vocabulaire (alphabet) depuis un fichier.
- **Paramètres** : `filename` - Chemin vers le fichier de vocabulaire
- **Exceptions** : `std::runtime_error` si le fichier ne peut pas être ouvert

### `matrice_file(const char* filename)`
Charge une matrice de transition depuis un fichier.
- **Paramètres** : `filename` - Chemin vers le fichier de matrice
- **Retourne** : Tableau 2D représentant la matrice de transition
- **Exceptions** : `std::runtime_error` si le fichier ne peut pas être ouvert ou si les dimensions de la matrice ne correspondent pas au vocabulaire

### `matrice()`
Crée une matrice de transition via l'entrée utilisateur.
- **Retourne** : Tableau 2D représentant la matrice de transition

### `Mot(int taille)`
Convertit un mot d'entrée en indices de symboles basés sur le vocabulaire.
- **Paramètres** : `taille` - Longueur du mot
- **Retourne** : Tableau d'indices correspondant aux symboles d'entrée

### `trace(int** M, int* T, int taille)`
Trace un chemin dans la matrice de transition pour un mot donné.
- **Paramètres** :
  - `M` - Matrice de transition
  - `T` - Tableau d'indices de symboles
  - `taille` - Longueur du mot
- **Retourne** : État final (-1 si rejeté)

### `reconaissance(int tr)`
Affiche si un mot est accepté en fonction du résultat du traçage.
- **Paramètres** : `tr` - État final de la fonction trace

### `displayMatrix(int** M)`
Affiche la matrice de transition avec les en-têtes de vocabulaire.
- **Paramètres** : `M` - Matrice de transition à afficher

### `lister_mot(int** M)`
Liste tous les mots valides de longueur 3 qui sont acceptés par l'automate.
- **Paramètres** : `M` - Matrice de transition

## Gestion des Erreurs

La bibliothèque inclut une gestion basique des erreurs :
- Les opérations sur les fichiers lèvent des exceptions lorsque les fichiers ne peuvent pas être ouverts
- Validation des entrées pour les symboles du vocabulaire
- Validation des dimensions de la matrice

## Gestion de la Mémoire

N'oubliez pas de libérer correctement la mémoire des matrices une fois terminé :
```cpp
// Nettoyage de la matrice
for (int i = 0; i < rows; i++) {
    delete[] matrice[i];
}
delete[] matrice;
```

## Exemple

Voici un exemple complet d'utilisation de la bibliothèque :

```cpp
#include "compilation_emsi.h"
#include <iostream>

int main() {
    try {
        CompilationEmsi lexer;
        
        // Charger le vocabulaire
        lexer.loadVocabulary("vocabulary.txt");
        
        // Charger la matrice de transition
        int** matrice = lexer.matrice_file("matrix.txt");
        
        // Afficher la matrice
        lexer.displayMatrix(matrice);
        
        // Traiter un mot de longueur 3
        int* mot = lexer.Mot(3);
        
        // Vérifier si le mot est accepté
        int resultat = lexer.trace(matrice, mot, 3);
        lexer.reconaissance(resultat);
        
        // Lister tous les mots valides
        lexer.lister_mot(matrice);
        
        // Nettoyage
        for (int i = 0; i < lexer.rows; i++) {
            delete[] matrice[i];
        }
        delete[] matrice;
        delete[] mot;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```
