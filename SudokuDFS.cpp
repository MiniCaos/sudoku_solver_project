#include "SudokuDFS.h"

namespace SudokuSolver {
// Método recursivo para resolver el Sudoku usando backtracking
bool SudokuDFS::solveRec(int row, int col) {
    if (row == SIZE - 1 && col == SIZE) {
        return true;  // Solución encontrada
    }

    if (col == SIZE) {
        row++;
        col = 0;
    }

    if (grid[row][col] != 0) {
        return solveRec(row, col + 1);  // Pasar a la siguiente celda
    }

    for (int num = 1; num <= SIZE; ++num) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;
            if (solveRec(row, col + 1)) {
                return true;  // Continuar si se encontró una solución
            }
            grid[row][col] = 0;  // Deshacer el cambio (backtrack)
        }
    }

    return false;  // Si no se pudo resolver, devolver false
}

// Constructor de SudokuDFS
SudokuDFS::SudokuDFS(const std::string& filename) : Sudoku(filename) {}

// Método principal para resolver el Sudoku
bool SudokuDFS::solve() {
    return solveRec(0, 0);  // Comenzamos desde la primera celda
}
}