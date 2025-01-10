#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>  // Para std::memset
#include <string>   // Para std::string

const int SIZE = 9;  // Tamaño del Sudoku

class Sudoku {
protected:
    int grid[SIZE][SIZE];  // Matriz para el Sudoku

    bool isValid(int fila, int col, int num); // Método para verificar si un número es válido en una celda (fila, col)

public:
    Sudoku();  // Constructor por defecto
    explicit Sudoku(const std::string& filename);  // Constructor para cargar desde archivo
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);  // Sobrecarga del operador de salida
    void saveToFile(const std::string& filename) const;  // Método para guardar en archivo
    virtual bool solve() = 0;  // Método virtual puro (abstracto) para resolver
    virtual ~Sudoku();  // Destructor virtual

    int (&getGrid())[SIZE][SIZE]{   // Método para devolver la matriz
        return grid;
    }
};

#endif
