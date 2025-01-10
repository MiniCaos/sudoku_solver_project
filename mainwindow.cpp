#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sudoku.h"
#include "SudokuDFS.h"
#include "SudokuCrossHatching.h"
#include "SudokuForwardChecking.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnLoadSudoku, &QPushButton::clicked, this, &MainWindow::loadSudoku);
    connect(ui->btnSolve, &QPushButton::clicked, this, &MainWindow::solveSudoku);

    ui->comboAlgorithm->addItem("DFS");
    ui->comboAlgorithm->addItem("Forward Checking");
    ui->comboAlgorithm->addItem("Cross Hatching");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSudoku(){
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccionar archivo Sudoku", "", "Archivos de text  (*.txt)");
    if (fileName.isEmpty()) return;

    qDebug() << "archivo cargado" << fileName;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }

    QTextStream in(&file);
    for (int i = 0; i < 9; ++i) {
        QString line = in.readLine().trimmed();
        QStringList numbers = line.split(' ', Qt::SkipEmptyParts);
        for (int j = 0; j < 9; ++j) {
            sudoku[i][j] = numbers[j].toInt();
        }
    }
    file.close();

    displaySudoku();

    this->fileName = fileName;
    qDebug() << "Archivo asignado a fileName:" << this->fileName;
}

void MainWindow::displaySudoku(){
    //ui->tableSudoku->clear();
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (sudoku[i][j] != 0){
                ui->tableSudoku->setItem(i, j, new QTableWidgetItem(QString::number(sudoku[i][j])));
                QTableWidgetItem *item = ui->tableSudoku->item(i, j);
                item->setForeground(QBrush(Qt::red));
            } else {
                ui->tableSudoku->setItem(i, j, new QTableWidgetItem(""));
            }
        }
    }
}

void MainWindow::solveSudoku(){
    qDebug() << "Archivo en solveSudoku: " << fileName;
    if (fileName.isEmpty()){
        QMessageBox::warning(this, "Error", "No se  ha cargado  ningún archivo");
        return;
    }
    QString selectedAlgorithm = ui->comboAlgorithm->currentText();

    /*int sudokuGrid[SIZE][SIZE];
    for (int i = 0; i < SIZE;  ++i){
        for (int j = 0; j < SIZE; ++j) {
            sudokuGrid[i][j] = ui->tableSudoku->item(i, j)->text().toInt();
        }
    }*/

    bool solved = false;   
    if  (selectedAlgorithm == "DFS"){
        SudokuSolver::SudokuDFS solver(fileName.toStdString());
        solved = solver.solve();
        int (&solverGrid)[SIZE][SIZE] = solver.getGrid();
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                ui->tableSudoku->setItem(i, j, new QTableWidgetItem(QString::number(solverGrid[i][j])));
                solverGrid[i][j] = sudoku[i][j];
            }
        }
    } else if (selectedAlgorithm == "Forward Checking"){
        SudokuSolver::SudokuForwardChecking solver(fileName.toStdString());
        solved = solver.solve();
        int (&solverGrid)[SIZE][SIZE] = solver.getGrid();
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                ui->tableSudoku->setItem(i, j, new QTableWidgetItem(QString::number(solverGrid[i][j])));
                solverGrid[i][j] = sudoku[i][j];
            }
        }
    } else if (selectedAlgorithm == "Cross Hatching"){
        SudokuSolver::SudokuCrossHatching solver(fileName.toStdString());
        solved = solver.solve();
        int (&solverGrid)[SIZE][SIZE] = solver.getGrid();
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                ui->tableSudoku->setItem(i, j, new QTableWidgetItem(QString::number(solverGrid[i][j])));
                solverGrid[i][j] = sudoku[i][j];
            }
        }
    }

    if (!solved){
        QMessageBox::warning(this, "Error", "No se pudo reolver el Sudoku");
    }
}

/*void MainWindow::displaySolution(){
    SudokuSolver::SudokuDFS solver(fileName.toStdString());
    if (solver.solve()){
        int (&grid)[SIZE][SIZE] = solver.getGrid();

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (ui->tableSudoku->item(i, j)->text().isEmpty()){
                    ui->tableSudoku->item(i, j)->setText(QString::number(grid[i][j]));
                }
            }
        }
    } else{
        QMessageBox::warning(this, "Error", "No se pudo resolver el sudoku");
    }


}*/
