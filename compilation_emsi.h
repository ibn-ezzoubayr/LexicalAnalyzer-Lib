#pragma once
#include <vector>
#include <string>

class CompilationEmsi {
private:
    int rows;
    int cols;
    std::vector<char> vocabulary;

public:
    // Constructor
    CompilationEmsi();

    // Core matrix functions
    int** matrice_file(const char* filename);  // Load matrix from file
    int** matrice();                          // Create matrix from user input

    // Word processing functions
    int* Mot(int taille);                     // Convert input to symbol indices
    int trace(int** M, int* T, int taille);   // Trace path in matrix
    void reconaissance(int tr);               // Check if word is accepted
    void lister_mot(int** M);                 // List all valid words of length 3

    // Utility functions
    void loadVocabulary(const char* filename); // Load vocabulary from file
    void displayMatrix(int** M);              // Display the transition matrix
};