#ifndef SUDOKUCROSSHATCHING_H
#define SUDOKUCROSSHATCHING_H

#include "Sudoku.h"

namespace SudokuSolver {
class SudokuCrossHatching : public Sudoku {
private:
    bool candidatos[SIZE][SIZE][SIZE] = {{{false}}};               // Matriz de candidatos
    bool candidatosPrevios[SIZE][SIZE][SIZE] = {{{false}}};        // Matriz para guardar el estado previo de los candidatos

    void inicializarCandidatos();                                   // Inicializa los candidatos
    void actualizarCandidatos(int fila, int col, int num);          // Actualiza los candidatos al colocar un número
    void restaurarCandidatos(int fila, int col, int num);           // Restaura los candidatos al asignar un numero que conduce a una no solución
    bool resolverConCandidatos();                                   // Inicia la resolución con cross-hatching
    bool solveRec(int row, int col);                                // Resuelve el sudoku de forma recursiva

public:
    explicit SudokuCrossHatching(const std::string& filename);  // Constructor
    bool solve() override;  // Método para resolver el Sudoku
};
}
#endif
