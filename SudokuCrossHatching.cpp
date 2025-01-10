#include "SudokuCrossHatching.h"

namespace SudokuSolver {
// Inicializar la matriz de candidatos
void SudokuCrossHatching::inicializarCandidatos() {
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

// Actualizar los candidatos y guardar su estado anterior
void SudokuCrossHatching::actualizarCandidatos(int fila, int col, int num) {
    // Guardar el estado previo de los candidatos
    for (int i = 0; i < SIZE; ++i) {
        candidatosPrevios[fila][i][num - 1] = candidatos[fila][i][num - 1];
        candidatosPrevios[i][col][num - 1] = candidatos[i][col][num - 1];
    }

    int startRow = fila - fila % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            candidatosPrevios[startRow + i][startCol + j][num - 1] = candidatos[startRow + i][startCol + j][num - 1];
        }
    }

    // Actualizar los candidatos
    for (int i = 0; i < SIZE; ++i) {
        candidatos[fila][i][num - 1] = false;
        candidatos[i][col][num - 1] = false;
    }

    int startRow2 = fila - fila % 3;
    int startCol2 = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            candidatos[startRow2 + i][startCol2 + j][num - 1] = false;
        }
    }
}

// Restaurar los candidatos a su estado previo
void SudokuCrossHatching::restaurarCandidatos(int fila, int col, int num) {
    for (int i = 0; i < SIZE; ++i) {
        candidatos[fila][i][num - 1] = candidatosPrevios[fila][i][num - 1];
        candidatos[i][col][num - 1] = candidatosPrevios[i][col][num - 1];
    }

    int startRow = fila - fila % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            candidatos[startRow + i][startCol + j][num - 1] = candidatosPrevios[startRow + i][startCol + j][num - 1];
        }
    }
}

// Resolver utilizando los candidatos, al estilo de "cross-hatching"
bool SudokuCrossHatching::resolverConCandidatos() {
    for (int fila = 0; fila < SIZE; ++fila) {
        for (int col = 0; col < SIZE; ++col) {
            if (grid[fila][col] == 0) {
                int cuenta = 0, unicoCandidato = 0;
                for (int num = 0; num < SIZE; ++num) {
                    if (candidatos[fila][col][num]) {
                        ++cuenta;
                        unicoCandidato = num + 1;
                    }
                }
                if (cuenta == 1) {
                    grid[fila][col] = unicoCandidato;
                    actualizarCandidatos(fila, col, unicoCandidato);
                    return true;
                }
            }
        }
    }
    return false;
}

// Método recursivo para resolver el Sudoku utilizando backtracking
bool SudokuCrossHatching::solveRec(int row, int col) {
    if (row == SIZE - 1 && col == SIZE) {
        return true;  // Solución encontrada
    }

    if (col == SIZE) {
        row++;
        col = 0;
    }

    if (grid[row][col] != 0) {
        return solveRec(row, col + 1);  // Ir a la siguiente celda
    }

    for (int num = 1; num <= SIZE; ++num) {
        if (candidatos[row][col][num - 1]) {
            grid[row][col] = num;  // Colocar el número
            actualizarCandidatos(row, col, num);  // Actualizar los candidatos

            if (solveRec(row, col + 1)) {
                return true;  // Continuar con la siguiente celda
            }

            // Si no se pudo resolver, deshacer los cambios
            grid[row][col] = 0;
            restaurarCandidatos(row, col, num);  // Restaurar los candidatos
        }
    }

    return false;  // No se pudo resolver con ningún número
}

// Constructor de la clase SudokuCrossHatching
SudokuCrossHatching::SudokuCrossHatching(const std::string& filename) : Sudoku(filename) {}

// Método principal para resolver el Sudoku
bool SudokuCrossHatching::solve() {
    inicializarCandidatos();
    while (resolverConCandidatos()) {
        // Continuar aplicando la técnica de cross-hatching hasta que no haya más cambios
    }

    return solveRec(0, 0);  // Llamar a la función recursiva para resolver el Sudoku
}
}