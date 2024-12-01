# Lexical Analyzer Library

## Introduction

بسم الله الرحمن الرحيم، الحمد لله الذي أنشأ و برى، و خلق الماء و الثرى، و أبدع كل شيء و ذرى، لا يغيب عن بصره صغير النمل في الليل إذا سرى، و لا يعزب عن علمه مثقال ذرة في الأرض و لا في السماء، الرحمن على العرش استوى، له ما في السماوات و ما في الأرض و ما بينهما و ما تحت الثرى، و إن تجهر بالقول فإنه يعلم السر و أخفى، الله لا إله إلا هو له الأسماء الحسنى، خلق آدم فابتلاه ثم اجتباه فتاب عليه و هدى، و بعث نوحا فصنع الفلك بأمر الله و جرى، و نجا الخليل من النار فصار حرها بردا و سلاما عليه فاعتبروا بما جرى، و آتى موسى تسع آيات فما سمع فرعون و مرعوى، و أيد عيسى بآيات تبهر الورى، و أنزل الكتاب على محمد فيه البينات و الهدى، نحمده على نعمه التي لا تزال تترى، و نصلي و نسلم على المبعوث في أم القرى، صلى الله عليه و على صاحبه أبي بكر في الغار بلا مرى، و على عمر الملهم برأيه فهو بنور الله يرى، و على عثمان زوج ابنتيه ما كان حديثا يفترى، و على علي ابن عمه بدر العلوم و أسد الشرى، و على جميع آله و صحابته الذين انتشر فضلهم في الورى، و سلم تسليما كثيرا.

هدية متواضعة لطلبة المدرسة المغربية لعلوم المهندسة السنة الرابعة شعبة المعلوميات

*Read this in other languages: [Français](README_FR.md), [العربية](README_AR.md)*

A C++ library for lexical analysis and finite state machine simulation. This library allows you to create and work with transition matrices for finite state automata, process input strings, and verify word acceptance based on defined rules.

## Features

- Load and create transition matrices
- Process input words using defined vocabulary
- Trace paths through the transition matrix
- Verify word acceptance
- List all valid words of a specific length
- Load custom vocabularies from files

## Installation

This is a header-only library. To use it in your project:

1. Copy `compilation_emsi.h` and `compilation_emsi.cpp` to your project directory
2. Include the header file in your code:
```cpp
#include "compilation_emsi.h"
```

## Usage

### Basic Setup

```cpp
// Create an instance of the lexical analyzer
CompilationEmsi lexer;

// Load vocabulary from a file
lexer.loadVocabulary("vocabulary.txt");
```

### Loading a Transition Matrix

You can load a transition matrix either from a file or create it interactively:

```cpp
// Load from file
int** matrix = lexer.matrice_file("matrix.txt");

// Or create interactively
int** matrix = lexer.matrice();
```

### Processing Words

```cpp
// Process a word of specific length
int length = 3;
int* word = lexer.Mot(length);

// Trace the word through the matrix
int result = lexer.trace(matrix, word, length);

// Check if the word is accepted
lexer.reconaissance(result);
```

### Utility Functions

```cpp
// Display the transition matrix
lexer.displayMatrix(matrix);

// List all valid words of length 3
lexer.lister_mot(matrix);
```

## File Formats

### Vocabulary File (vocabulary.txt)
- Single line containing comma-separated symbols
- Example:
```
a,b,c
```

### Matrix File (matrix.txt)
- First line: number of rows and columns
- Following lines: transition matrix values
- Example:
```
3 3
1 0 2
2 1 0
0 2 1
```

## Method Documentation

### `loadVocabulary(const char* filename)`
Loads the vocabulary (alphabet) from a file.
- **Parameters**: `filename` - Path to the vocabulary file
- **Throws**: `std::runtime_error` if file cannot be opened

### `matrice_file(const char* filename)`
Loads a transition matrix from a file.
- **Parameters**: `filename` - Path to the matrix file
- **Returns**: 2D array representing the transition matrix
- **Throws**: `std::runtime_error` if file cannot be opened or if matrix dimensions don't match vocabulary

### `matrice()`
Creates a transition matrix through user input.
- **Returns**: 2D array representing the transition matrix

### `Mot(int taille)`
Converts an input word to symbol indices based on the vocabulary.
- **Parameters**: `taille` - Length of the word
- **Returns**: Array of indices corresponding to input symbols

### `trace(int** M, int* T, int taille)`
Traces a path through the transition matrix for a given word.
- **Parameters**:
  - `M` - Transition matrix
  - `T` - Array of symbol indices
  - `taille` - Length of the word
- **Returns**: Final state (-1 if rejected)

### `reconaissance(int tr)`
Prints whether a word is accepted based on the trace result.
- **Parameters**: `tr` - Final state from trace function

### `displayMatrix(int** M)`
Displays the transition matrix with vocabulary headers.
- **Parameters**: `M` - Transition matrix to display

### `lister_mot(int** M)`
Lists all valid words of length 3 that are accepted by the automaton.
- **Parameters**: `M` - Transition matrix

## Error Handling

The library includes basic error handling:
- File operations throw exceptions when files cannot be opened
- Input validation for vocabulary symbols
- Matrix dimension validation

## Memory Management

Remember to properly deallocate memory for matrices when you're done:
```cpp
// Cleanup matrix
for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
}
delete[] matrix;
```

## Example

Here's a complete example of using the library:

```cpp
#include "compilation_emsi.h"
#include <iostream>

int main() {
    try {
        CompilationEmsi lexer;
        
        // Load vocabulary
        lexer.loadVocabulary("vocabulary.txt");
        
        // Load transition matrix
        int** matrix = lexer.matrice_file("matrix.txt");
        
        // Display the matrix
        lexer.displayMatrix(matrix);
        
        // Process a word of length 3
        int* word = lexer.Mot(3);
        
        // Check if word is accepted
        int result = lexer.trace(matrix, word, 3);
        lexer.reconaissance(result);
        
        // List all valid words
        lexer.lister_mot(matrix);
        
        // Cleanup
        for (int i = 0; i < lexer.rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] word;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```
