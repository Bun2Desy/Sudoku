/**
*\file sudoku.h
* The header file for sudoku generation
*/
/*!
	\brief class Sudoku
	\details This class is aimed at creating Sudoku fields with different levels of difficulty with a unique solution
*/
#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <ctime>

class Sudoku {
public:
    const size_t SIZE = 9;///< constant field size
    std::vector<std::vector<int>> field{ SIZE, std::vector<int>(SIZE, 0) };///< solved field
    std::vector<std::vector<int>> fieldwithgasps{ SIZE, std::vector<int>(SIZE, 0) };///< field with gasps
    char dif = 'e';///< level of difficulty
public:
    Sudoku()=default;///< Default constructor
    Sudoku(char difficulty);
	bool isCheckFillCell(int, int);
    void CreateField();
    bool isCheckRow(int, int);
    bool isCheckCol(int, int);
    bool isCheckSquare(int, int);
    void CreateGasps();
    bool Solver();
    void UpdateSets(std::vector<std::vector<int>>&, std::vector < std::vector < std::set<int>>>&);
    bool isFindGasps(std::vector<std::vector<int>>&);
};

#endif