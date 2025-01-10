#include "SudokuForwardChecking.h"
#include <cstring>  // Para usar std::memcpy

namespace SudokuSolver {
// Inicializa la matriz de candidatos
void SudokuForwardChecking::inicializarCandidatos() {
    for (int fila = 0; fila < SIZE; ++fila) {
        for (int col = 0; col < SIZE; ++col) {
            if (grid[fila][col] == 0) {  // Si la celda está vacía
                for (int num = 1; num <= SIZE; ++num) {
                    if (isValid(fila, col, num)) {
                        candidatos[fila][col][num - 1] = true;
                    }
                }
            }
        }
    }
}

// Verifica si hay candidatos para la celda (fila, col)
bool SudokuForwardChecking::tieneCandidatos(int fila, int col) {
    for (int num = 0; num < SIZE; ++num) {
        if (candidatos[fila][col][num]) {
            return true;
        }
    }
    return false;
}

// Actualiza los candidatos al colocar un número en la celda (fila, col)
void SudokuForwardChecking::actualizarCandidatos(int fila, int col, int num) {
    // Desactiva el número como candidato en la fila, columna y región 3x3
    for (int i = 0; i < SIZE; ++i) {
        candidatos[fila][i][num - 1] = false;
        candidatos[i][col][num - 1] = false;
    }

    int startRow = fila - fila % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            candidatos[startRow + i][startCol + j][num - 1] = false;
        }
    }
}

// Método recursivo para resolver el Sudoku utilizando forward checking
bool SudokuForwardChecking::resolverRecursivo() {
    int fila = -1, col = -1;
    // Buscar la siguiente celda vacía
    for (int i = 0; i < SIZE && fila == -1; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] == 0) {
                fila = i;
                col = j;
                break;
            }
        }
    }
    if (fila == -1) return true;  // Si no hay celdas vacías, hemos resuelto el Sudoku

    // Intentar colocar cada número en la celda vacía
    for (int num = 1; num <= SIZE; ++num) {
        if (candidatos[fila][col][num - 1]) {
            grid[fila][col] = num;

            // Crear una copia de los candidatos antes de hacer modificaciones
            bool copiaCandidatos[SIZE][SIZE][SIZE];
            std::memcpy(copiaCandidatos, candidatos, sizeof(candidatos));

            // Actualizar los candidatos
            actualizarCandidatos(fila, col, num);

            // Llamar recursivamente para resolver el siguiente número
            if (resolverRecursivo()) {
                return true;  // Si se resuelve el Sudoku, retornar true
            }

            // Si no se puede resolver, restaurar los candidatos y deshacer el cambio
            std::memcpy(candidatos, copiaCandidatos, sizeof(candidatos));
            grid[fila][col] = 0;
        }
    }
    return false;  // Si no se pudo resolver con ningún número, retornar false
}

// Constructor de la clase SudokuForwardChecking
SudokuForwardChecking::SudokuForwardChecking(const std::string& filename) : Sudoku(filename) {}

// Método principal para resolver el Sudoku utilizando forward checking
bool SudokuForwardChecking::solve() {
    inicializarCandidatos();
    return resolverRecursivo();  // Llamar al algoritmo recursivo para resolver el Sudoku
}
}