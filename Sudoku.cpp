#include "Sudoku.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>

// Constructor por defecto, inicializa la matriz a 0
Sudoku::Sudoku() {
    std::memset(grid, 0, sizeof(grid));  // Inicializa el grid a ceros
}

// Constructor que carga el Sudoku desde un archivo
Sudoku::Sudoku(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Error al abrir el archivo: " + filename);
    }

    // Cargar los valores del archivo al grid
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            file >> grid[i][j];
            if (file.fail()) {
                throw std::runtime_error("Error al leer los datos del archivo: " + filename);
            }
        }
    }
}

// Sobrecarga del operador de salida para imprimir el Sudoku
std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            os << sudoku.grid[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

// Método para guardar el Sudoku en un archivo
void Sudoku::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Error al guardar el archivo: " + filename);
    }

    // Guardar el grid en el archivo
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            file << grid[i][j] << " ";
        }
        file << std::endl;
    }
}

// Método para saber si el número en la celda es válido
bool Sudoku::isValid(int fila, int col, int num) {
    // Verificar fila y columna
    for (int x = 0; x < SIZE; ++x) {
        if (grid[fila][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Verificar subcuadro 3x3
    int startRow = fila - fila % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Destructor virtual (puede ser necesario si se agregan recursos dinámicos en futuras clases derivadas)
Sudoku::~Sudoku() = default;
