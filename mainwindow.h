#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include <QTextStream>
#include "Sudoku.h"
#include "SudokuDFS.h"
#include "SudokuForwardChecking.h"
#include "SudokuCrossHatching.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadSudoku();
    void solveSudoku();
private:
    Ui::MainWindow *ui;
    int sudoku[9][9];
    QString fileName;
    //Sudoku* sudoku = new SudokuSolver::SudokuDFS(fileName.toStdString());

    void displaySudoku();
    void displaySolution();
};
#endif // MAINWINDOW_H
