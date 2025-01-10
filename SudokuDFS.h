// SudokuDFS.h
#ifndef SUDOKUDFS_H
#define SUDOKUDFS_H

#include "Sudoku.h"
namespace SudokuSolver {

class SudokuDFS : public Sudoku {
private:
    bool solveRec(int row, int col);

public:
    explicit SudokuDFS(const std::string& filename);  // Constructor
    bool solve() override;  // Sobrescribir el método solve
};

}
#endif // SUDOKUDFS_H
