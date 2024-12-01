#include "compilation_emsi.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor
CompilationEmsi::CompilationEmsi() : rows(0), cols(0) {}

// Load vocabulary from file
void CompilationEmsi::loadVocabulary(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open vocabulary file");
    }

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string symbol;

    vocabulary.clear();
    while (std::getline(ss, symbol, ',')) {
        if (!symbol.empty()) {
            vocabulary.push_back(symbol[0]);
        }
    }
    cols = vocabulary.size();
}

// Load matrix from file
int** CompilationEmsi::matrice_file(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open matrix file");
    }

    file >> rows >> cols;
    if (cols != vocabulary.size()) {
        throw std::runtime_error("Matrix columns don't match vocabulary size");
    }

    int** M = new int*[rows];
    for (int i = 0; i < rows; i++) {
        M[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            file >> M[i][j];
        }
    }

    return M;
}

// Create matrix from user input
int** CompilationEmsi::matrice() {
    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    cols = vocabulary.size();

    int** M = new int*[rows];
    for (int i = 0; i < rows; i++) {
        M[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            std::cout << "State " << i << " with symbol '" << vocabulary[j] << "': ";
            std::cin >> M[i][j];
        }
    }

    return M;
}

// Convert input word to symbol indices
int* CompilationEmsi::Mot(int taille) {
    int* T = new int[taille];
    char symbol;

    for (int i = 0; i < taille; i++) {
        bool validSymbol = false;
        do {
            std::cout << "Enter character #" << (i + 1) << ": ";
            std::cin >> symbol;

            // Find symbol in vocabulary
            for (size_t j = 0; j < vocabulary.size(); j++) {
                if (vocabulary[j] == symbol) {
                    T[i] = j;
                    validSymbol = true;
                    break;
                }
            }

            if (!validSymbol) {
                std::cout << "Invalid symbol. Please use: ";
                for (char c : vocabulary) {
                    std::cout << c << " ";
                }
                std::cout << std::endl;
            }
        } while (!validSymbol);
    }

    return T;
}

// Trace path in matrix
int CompilationEmsi::trace(int** M, int* T, int taille) {
    int currentState = 0;  // Start from state 0

    for (int i = 0; i < taille; i++) {
        currentState = M[currentState][T[i]];
        if (currentState == -1) {
            return -1;  // Return immediately if we hit a rejecting state
        }
    }

    return currentState;
}

// Check if word is accepted
void CompilationEmsi::reconaissance(int tr) {
    if (tr != -1) {
        std::cout << "Word is accepted" << std::endl;
    } else {
        std::cout << "Word is not accepted" << std::endl;
    }
}

// Display the transition matrix
void CompilationEmsi::displayMatrix(int** M) {
    std::cout << "\nTransition Matrix:" << std::endl;
    // Display vocabulary header
    std::cout << "   ";
    for (char c : vocabulary) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    // Display matrix content
    for (int i = 0; i < rows; i++) {
        std::cout << i << ": ";
        for (int j = 0; j < cols; j++) {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// List all valid words of length 3
void CompilationEmsi::lister_mot(int** M) {
    int count = 0;
    int* word = new int[3];

    for (int i = 0; i < cols; i++) {
        word[0] = i;
        for (int j = 0; j < cols; j++) {
            word[1] = j;
            for (int k = 0; k < cols; k++) {
                word[2] = k;
                int result = trace(M, word, 3);
                if (result != -1) {
                    count++;
                    std::cout << vocabulary[word[0]] << vocabulary[word[1]] << vocabulary[word[2]] << std::endl;
                }
            }
        }
    }

    std::cout << "\nTotal number of valid words of length 3: " << count << std::endl;
    delete[] word;
}