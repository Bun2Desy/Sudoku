/**
*\file sudoku.cpp
* The file with sudoku generation functions
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <ctime>
#include "sudoku.h"
/**
* Constructor for new object
*\param[in] difficulty level of difficulty
*/
Sudoku::Sudoku(char difficulty)
	:dif(difficulty)
{
}
/**
* The main function to create field
*/
void Sudoku::CreateField() 
{
    field = { SIZE, std::vector<int>(SIZE, 0) };
    int i; 
	int j;
    std::srand(unsigned(std::time(0)));
    std::vector<int> valueVector;

    // set some values:
    for (int i = 1; i < 10; ++i){
		valueVector.push_back(i); // 1 2 3 4 5 6 7 8 9
	}
    // using built-in random generator:
    i = 0;
    while (i < 9) {
        bool flag = true;
        clock_t startShuffle = clock();
        while (flag) {
            clock_t endShuffle = clock();
            int check = 0;
            std::random_shuffle(valueVector.begin(), valueVector.end());
            field[i] = valueVector;
            for (j = 0; j < 9; j++) {
                if (isCheckSquare(i, j) && isCheckRow(i, j) && isCheckCol(i, j))
                    check++;
            }
            if (check == 9)
                flag = false;
            if(((double)(endShuffle - startShuffle) / CLOCKS_PER_SEC) > 1){
                i -= 2;
                break;
            }
        }
        i++;
    }
    CreateGasps();
}
/**
* A simplified version of checking the correctness of the inserted number in cell
*\param[in] x row number
*\param[in] y column number
*\return true if number is correct or false otherwise
*/
bool Sudoku::isCheckFillCell(int x, int y)
{
    if (fieldwithgasps[x][y] == 0 || fieldwithgasps[x][y] != field[x][y])
        return false;
    return true;
}
/**
* Сompares the values of the current cell and cells in the same row before it
*\param[in] x row number
*\param[in] y column number
*\return true if no matches or false otherwise
*/
bool Sudoku::isCheckRow(int x, int y)
{
    for (int i = 0; i < y; i++){
        if (field[x][i] == field[x][y])
            return false;
	}
    return true;
}
/**
* Сompares the values of the current cell and cells in the same column before it
*\param[in] x row number
*\param[in] y column number
*\return true if no matches or false otherwise
*/
bool Sudoku::isCheckCol(int x, int y)
{
    for (int i = 0; i < x; i++){
        if (field[i][y] == field[x][y])
            return false;
	}
    return true;
}
/**
* Сompares the values of the current cell and cells in the same square before it
*\param[in] x row number
*\param[in] y column number
*\return true if no matches or false otherwise
*/
bool Sudoku::isCheckSquare(int x, int y)
{
    int first_row = (x / 3) * 3;
    int first_col = (y / 3) * 3;
    for (int current_row = first_row; current_row < first_row + 3; current_row++){
        for (int current_col = first_col; current_col < first_col + 3; current_col++) {
            if (current_row == x && current_col == y)
                return true;
            if (field[current_row][current_col] == field[x][y])
                return false;
        }
	}
    return true;
}
/**
* The function to create field with gasps
*/
void Sudoku::CreateGasps()
{
    int max = 0;
    if (dif == 'e')
        max = 40;
    else if(dif == 'n')
        max = 50;
    else if (dif == 'h')
        max = 55;
    fieldwithgasps = field;
    int n = 0;
    int i;
    int j;
    bool run = true;
    clock_t start = clock();
    clock_t end{};
    double seconds{};
    while (n != max) {
        i = rand() % 9;
        j = rand() % 9;
        if (fieldwithgasps[i][j] == 0) {
            continue;
        }
        fieldwithgasps[i][j] = 0;
        if (Solver() == false) {
            fieldwithgasps[i][j] = field[i][j];
        }else
            n++;
        end = clock();
        seconds = (double)(end - start) / CLOCKS_PER_SEC;
        if (seconds > 1.5) {
            //std::cout << seconds << std::endl;
            run = false;
            break;
        }
    }
    //std::cout << seconds << std::endl;
    if (run == false)
        CreateField();

}
/**
* Updates possible values for each cell
*\param[in] solvefield field that is used to check solutions
*\param[in] zones data of possible values for each cell
*/
void Sudoku::UpdateSets(std::vector<std::vector<int>>& solvefield, std::vector < std::vector < std::set<int>>>& zones) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (solvefield[i][j] != 0)
                zones[i][j] = { 0 };
            else {
                std::set<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
                for (int col = 0; col < 9; col++)
                    numbers.erase(solvefield[i][col]);
                for (int row = 0; row < 9; row++)
                    numbers.erase(solvefield[row][j]);
                for (int first_row = (i / 3) * 3; first_row < (i / 3) * 3 + 3; first_row++)
                    for (int first_col = (j / 3) * 3; first_col < (j / 3) * 3 + 3; first_col++)
                        numbers.erase(solvefield[first_row][first_col]);
                zones[i][j] = numbers;
            }
        }
    }
}
/**
* Search for cells with zero value
*\param[in] solvefield field that is used to check solutions
*\return true if the number of non-zero values is not zero or false otherwise
*/
bool Sudoku::isFindGasps(std::vector<std::vector<int>>& solvefield) {
    int count = 0;//search for zero
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (solvefield[i][j] == 0)
                count++;
        }
    }
    if (count == 0)
        return false;
    else
        return true;
}
/**
* Check fields for unique solutions
*\return true if the field have unique solution or false otherwise
*/
bool Sudoku::Solver()
{
    std::vector<std::vector<int>> solvefield(SIZE, std::vector<int>(SIZE, 0));
    solvefield = fieldwithgasps;
    std::vector < std::vector < std::set<int>>> zones(SIZE, std::vector < std::set<int>>(SIZE));
    bool run = true;
    bool stop = false;
    while (run == true) {
        if (stop == true)
            return false;
        stop = true;
        UpdateSets(solvefield, zones);
        for (int i = 0; i < 9; i++) { 
            for (int j = 0; j < 9; j++) {
                if (solvefield[i][j] != 0)
                    continue;
                else {
                    for (int n : zones[i][j]){
                        int k = 0;
                        for (int col = 0; col < 9; col++)//checkcol
                            if (zones[i][col].count(n) == 1 && col != j)
                                k++;
                        if (k == 0) {
                            solvefield[i][j] = n;
                            zones[i][j].clear();
                            stop = false;
                            break;
                        }
                    }
                }
            }
        }
        UpdateSets(solvefield, zones);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (solvefield[i][j] != 0)
                    continue;
                else {
                    for (int n : zones[i][j]){
                        int k = 0;
                        for (int row = 0; row < 9; row++)//checkrow
                            if (zones[row][j].count(n) == 1 && row != i)
                                k++;
                        if (k == 0) {
                            solvefield[i][j] = n;
                            zones[i][j].clear();
                            stop = false;
                            break;
                        }

                    }
                }
            }
        }
        UpdateSets(solvefield, zones);
        for (int i = 0; i < 9; i++) {//checksquare
            for (int j = 0; j < 9; j++) {
                if (solvefield[i][j] != 0)
                    continue;
                else {
                    if (zones[i][j].size() == 1) {
                        for (int n : zones[i][j])
                            solvefield[i][j] = n;
                        stop = false;
                        zones[i][j].clear();
                    }
                }
            }
        }
        run = isFindGasps(solvefield);
    }
    if (run == false)
        return true;
}