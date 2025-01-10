#ifndef SUDOKUFORWARDCHECKING_H
#define SUDOKUFORWARDCHECKING_H

#include "Sudoku.h"

namespace SudokuSolver {
class SudokuForwardChecking : public Sudoku {
private:
    bool candidatos[SIZE][SIZE][SIZE] = {{{false}}};  // Matriz de candidatos

    void inicializarCandidatos();  // Inicializa los candidatos
    bool tieneCandidatos(int fila, int col);  // Verifica si hay candidatos en una celda
    void actualizarCandidatos(int fila, int col, int num);  // Actualiza los candidatos al colocar un número
    bool resolverRecursivo();  // Resuelve el Sudoku de forma recursiva con backtracking

public:
    explicit SudokuForwardChecking(const std::string& filename);  // Constructor
    bool solve() override;  // Método para resolver el Sudoku
};
}
#endif
