#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "sudoku.h"
#include <vector>

class OneDefaultSudokuObject{
	public:
	Sudoku sudoku;
};

//tests for solver
TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 1 for easy"){
	sudoku.fieldwithgasps={{0, 0, 4, 0, 0, 0, 0, 6, 0}, {1, 9, 6, 4, 7, 5, 0, 2, 8}, {8, 0, 5, 0, 0, 6, 4, 9, 7}, 
	{0, 3, 1, 6, 8, 0, 7, 5, 2}, {9, 0, 0, 3, 5, 0, 0, 1, 4}, {0, 0, 0, 7, 1, 4, 0, 3, 6}, 
	{7, 0, 0, 0, 0, 0, 5, 0, 9}, {0, 4, 3, 0, 9, 0, 2, 0, 0}, {0, 5, 0, 0, 0, 0, 0, 0, 0}};
	CHECK(sudoku.Solver() == true);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 2 for easy"){
	sudoku.fieldwithgasps={{7, 0, 0, 0, 0, 5, 9, 0, 0}, {9, 6, 0, 1, 0, 3, 7, 0, 5}, {3, 5, 0, 0, 7, 9, 0, 0, 6}, 
	{0, 3, 7, 0, 0, 0, 6, 9, 2}, {5, 0, 9, 7, 2, 0, 0, 0, 4}, {0, 1, 2, 0, 0, 0, 0, 5, 0}, 
	{8, 7, 0, 0, 9, 0, 0, 0, 0}, {2, 0, 0, 3, 1, 8, 5, 7, 0}, {1, 9, 0, 6, 0, 0, 0, 8, 3}};
	CHECK(sudoku.Solver() == true);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 1 for normal"){
	sudoku.fieldwithgasps={{0, 0, 0, 6, 0, 0, 9, 7, 3}, {0, 0, 0, 0, 4, 0, 0, 0, 0}, {6, 2, 0, 9, 0, 0, 0, 0, 0}, 
	{0, 0, 6, 0, 0, 0, 1, 0, 0}, {2, 8, 0, 4, 6, 0, 0, 0, 7}, {4, 0, 5, 7, 1, 8, 0, 0, 0}, 
	{0, 0, 8, 0, 7, 0, 2, 0, 4}, {0, 0, 0, 2, 0, 6, 0, 0, 5}, {7, 0, 2, 5, 0, 0, 8, 0, 0}};
	CHECK(sudoku.Solver() == true);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 2 for normal"){
	sudoku.fieldwithgasps={{0, 8, 1, 0, 4, 0, 0, 0, 0}, {0, 7, 0, 8, 0, 0, 0, 9, 0}, {4, 0, 9, 7, 0, 0, 0, 1, 3}, 
	{9, 0, 0, 0, 0, 0, 4, 0, 8}, {0, 0, 0, 6, 0, 8, 9, 3, 0}, {0, 1, 6, 0, 0, 9, 0, 7, 5}, 
	{1, 0, 0, 2, 0, 7, 3, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 7}, {2, 0, 0, 5, 9, 0, 0, 0, 0}};
	CHECK(sudoku.Solver() == true);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 1 for hard"){
	sudoku.fieldwithgasps={{0, 0, 0, 6, 0, 0, 9, 7, 3}, {0, 0, 0, 0, 4, 0, 0, 0, 0}, {6, 2, 0, 9, 0, 0, 0, 0, 0}, 
	{0, 0, 6, 0, 0, 0, 1, 0, 0}, {2, 8, 0, 4, 6, 0, 0, 0, 7}, {4, 0, 5, 7, 1, 8, 0, 0, 0}, 
	{0, 0, 8, 0, 7, 0, 2, 0, 4}, {0, 0, 0, 2, 0, 6, 0, 0, 5}, {7, 0, 2, 5, 0, 0, 8, 0, 0}};
	CHECK(sudoku.Solver() == true);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 2 for hard"){
	sudoku.fieldwithgasps={{0, 0, 0, 0, 8, 0, 0, 2, 6}, {0, 0, 0, 4, 1, 0, 0, 7, 0}, {7, 0, 0, 0, 0, 5, 0, 0, 0}, 
	{4, 0, 0, 0, 0, 1, 0, 3, 0}, {0, 0, 6, 2, 0, 4, 0, 0, 0}, {0, 9, 5, 7, 3, 0, 0, 0, 1}, 
	{0, 0, 4, 3, 0, 0, 0, 0, 9}, {0, 0, 0, 0, 4, 9, 6, 0, 0}, {0, 0, 0, 0, 0, 0, 5, 0, 0}};
	CHECK(sudoku.Solver() == true);
}


TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 1 without unic"){
	sudoku.fieldwithgasps={{6, 3, 5, 1, 7, 9, 0, 0, 8}, {7, 4, 2, 3, 8, 5, 1, 6, 9}, {8, 9, 1, 2, 4, 6, 3, 7, 5}, 
	{5, 7, 8, 0, 1, 3, 0, 0, 6}, {2, 6, 3, 0, 5, 7, 0, 8, 1}, {9, 1, 4, 6, 2, 8, 5, 3, 7}, 
	{3, 8, 7, 5, 9, 4, 6, 1, 2}, {1, 5, 6, 7, 3, 2, 8, 9, 4}, {4, 2, 9, 8, 6, 1, 7, 5, 3}};
	CHECK(sudoku.Solver() == false);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 2 without unic"){
	sudoku.fieldwithgasps={{6, 8, 9, 4, 0, 1, 0, 7, 3}, {5, 3, 2, 6, 7, 8, 9, 4, 1}, {7, 4, 1, 3, 0, 9, 0, 6, 8}, 
	{2, 7, 3, 1, 8, 4, 6, 9, 5}, {4, 1, 5, 2, 9, 6, 8, 3, 7}, {9, 6, 8, 5, 3, 7, 4, 1, 2}, 
	{8, 2, 4, 7, 6, 3, 1, 5, 9}, {3, 5, 6, 9, 1, 2, 7, 8, 4}, {1, 9, 7, 8, 4, 5, 3, 2, 6}};
	CHECK(sudoku.Solver() == false);
}
TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 3 without unic"){
	sudoku.fieldwithgasps={{8, 3, 4, 0, 2, 0, 9, 1, 7}, {7, 6, 5, 1, 4, 9, 3, 2, 8}, {1, 9, 2, 8, 7, 3, 4, 5, 6}, 
	{0, 0, 3, 0, 0, 0, 0, 8, 1}, {0, 7, 1, 2, 8, 0, 6, 9, 3}, {0, 8, 9, 0, 3, 1, 0, 4, 2}, 
	{0, 1, 6, 0, 5, 2, 8, 7, 9}, {0, 0, 7, 0, 0, 8, 0, 3, 5}, {0, 5, 8, 0, 0, 7, 0, 6, 4}};
	CHECK(sudoku.Solver() == false);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 4 without unic"){
	sudoku.fieldwithgasps={{8, 3, 6, 4, 1, 2, 0, 5, 0}, {9, 5, 2, 0, 0, 0, 4, 8, 1}, {7, 4, 1, 5, 0, 8, 0, 3, 0}, 
	{5, 6, 7, 0, 4, 1, 0, 2, 0}, {2, 1, 3, 0, 5, 0, 0, 0, 4}, {4, 9, 8, 3, 2, 0, 0, 1, 0}, 
	{1, 2, 0, 0, 0, 0, 0, 0, 0}, {6, 0, 0, 2, 0, 0, 1, 4, 0}, {3, 0, 0, 1, 0, 0, 0, 6, 0}};
	CHECK(sudoku.Solver() == false);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 5 without unic"){
	sudoku.fieldwithgasps={{9, 3, 1, 5, 7, 6, 8, 2, 4}, {4, 2, 7, 3, 0, 0, 1, 6, 5}, {6, 5, 8, 2, 1, 4, 7, 9, 3}, 
	{0, 9, 6, 8, 4, 0, 0, 1, 7}, {1, 4, 0, 7, 6, 0, 0, 8, 9}, {8, 7, 2, 0, 5, 0, 4, 3, 6}, 
	{2, 1, 9, 4, 3, 5, 6, 7, 8}, {0, 8, 0, 6, 2, 7, 9, 4, 1}, {7, 6, 4, 0, 0, 0, 3, 5, 2}};
	CHECK(sudoku.Solver() == false);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 6 without unic"){
	sudoku.fieldwithgasps={{6, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 3, 0, 0, 4, 0, 0, 0, 0}, {0, 9, 0, 3, 0, 0, 0, 6, 0}, 
	{5, 0, 0, 0, 0, 7, 0, 3, 8}, {0, 7, 0, 8, 0, 3, 0, 1, 0}, {0, 0, 3, 2, 6, 0, 0, 0, 9}, 
	{7, 0, 0, 0, 0, 5, 0, 0, 0}, {0, 5, 0, 6, 2, 0, 0, 0, 0}, {3, 0, 0, 0, 0, 0, 8, 5, 0}};
	CHECK(sudoku.Solver() == false);
}

//tests for createfield with unic solution
TEST_CASE("Case 1 for easy with generation"){
	Sudoku easysudoku = Sudoku('e');
	easysudoku.CreateField();
	CHECK(easysudoku.Solver() == true);
}

TEST_CASE("Case 2 for normal with generation"){
	Sudoku normalsudoku = Sudoku('n');
	normalsudoku.CreateField();
	CHECK(normalsudoku.Solver() == true);
}

TEST_CASE("Case 3 for hard with generation"){
	Sudoku hardsudoku = Sudoku('h');
	hardsudoku.CreateField();
	CHECK(hardsudoku.Solver() == true);
}

// tests for findgasps
TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 1 for serching gasps with gasps"){
	sudoku.fieldwithgasps={{0, 0, 4, 0, 0, 0, 0, 6, 0}, {1, 9, 6, 4, 7, 5, 0, 2, 8}, {8, 0, 5, 0, 0, 6, 4, 9, 7}, 
	{0, 3, 1, 6, 8, 0, 7, 5, 2}, {9, 0, 0, 3, 5, 0, 0, 1, 4}, {0, 0, 0, 7, 1, 4, 0, 3, 6}, 
	{7, 0, 0, 0, 0, 0, 5, 0, 9}, {0, 4, 3, 0, 9, 0, 2, 0, 0}, {0, 5, 0, 0, 0, 0, 0, 0, 0}};
	CHECK(sudoku.isFindGasps(sudoku.fieldwithgasps) == true);
}

TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 2 for serching gasps without gasps"){
	sudoku.field={{1, 2, 3, 4, 5, 6, 7, 8, 9}, {2, 3, 4, 5, 6, 7, 8, 9, 1}, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 
	{4, 5, 6, 7, 8, 9, 1, 2, 3}, {5, 6, 7, 8, 9, 1, 2, 3, 4}, {6, 7, 8, 9, 1, 2, 3, 4, 5}, 
	{7, 8, 9, 1, 2, 3, 4, 5, 6}, {8, 9, 1, 2, 3, 4, 5, 6, 7}, {9, 1, 2, 3, 4, 5, 6, 7, 8}};
	CHECK(sudoku.isFindGasps(sudoku.field) == false);
}
// tests for checkrow
TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 1 for checkrow"){
	sudoku.field={{1, 2, 3, 7, 5, 6, 7, 8, 9}, {2, 3, 4, 5, 6, 7, 8, 9, 1}, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 
	{4, 5, 6, 7, 8, 9, 1, 1, 3}, {5, 6, 7, 8, 9, 1, 2, 3, 4}, {6, 9, 8, 9, 1, 2, 3, 4, 5}, 
	{7, 8, 9, 1, 2, 3, 4, 5, 6}, {9, 9, 1, 2, 9, 4, 5, 6, 7}, {9, 1, 2, 3, 4, 5, 6, 7, 8}};
	CHECK(sudoku.isCheckRow(0, 6) == false);
	CHECK(sudoku.isCheckRow(5, 1) == true);
	CHECK(sudoku.isCheckRow(5, 3) == false);
	CHECK(sudoku.isCheckRow(7, 4) == false);
	CHECK(sudoku.isCheckRow(3, 7) == false);
}
// tests for checkcol
TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 2 for checkrow"){
	sudoku.field={{1, 2, 3, 8, 5, 6, 7, 8, 9}, {1, 3, 4, 5, 6, 7, 8, 9, 1}, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 
	{4, 5, 6, 7, 8, 9, 1, 2, 3}, {5, 6, 7, 8, 9, 1, 2, 3, 4}, {6, 7, 8, 9, 1, 2, 3, 4, 5}, 
	{7, 8, 9, 1, 2, 3, 4, 5, 6}, {8, 9, 1, 2, 3, 4, 5, 6, 7}, {9, 1, 2, 3, 4, 5, 9, 7, 8}};
	CHECK(sudoku.isCheckCol(1, 0) == false);
	CHECK(sudoku.isCheckCol(0, 3) == true);
	CHECK(sudoku.isCheckCol(4, 3) == false);
	CHECK(sudoku.isCheckCol(8, 6) == false);
}
//tests for checksqr
TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 3 for checksquare"){
	sudoku.field={{1, 2, 3, 4, 5, 6, 7, 8, 9}, {2, 3, 4, 5, 6, 7, 8, 9, 1}, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 
	{4, 5, 6, 7, 8, 9, 1, 2, 3}, {5, 6, 7, 8, 9, 1, 2, 3, 4}, {6, 7, 8, 9, 1, 2, 3, 4, 5}, 
	{7, 8, 9, 1, 2, 3, 4, 5, 6}, {8, 9, 1, 2, 3, 4, 5, 6, 7}, {9, 1, 2, 3, 4, 5, 6, 7, 8}};
	CHECK(sudoku.isCheckSquare(1, 1) == false);
	CHECK(sudoku.isCheckSquare(2, 2) == true);
	CHECK(sudoku.isCheckSquare(0, 1) == true);
	CHECK(sudoku.isCheckSquare(8, 1) == false);
}
//tests for checkFillCell
TEST_CASE_FIXTURE(OneDefaultSudokuObject, "Case 1 for checkFillCell"){
	sudoku.field={{5, 1, 3, 6, 2, 9, 4, 7, 8}, {7, 2, 9, 4, 8, 1, 3, 6, 5}, {6, 8, 4, 7, 3, 5, 9, 1, 2}, 
	{4, 6, 1, 9, 5, 2, 8, 3, 7}, {9, 3, 5, 8, 6, 7, 2, 4, 1}, {2, 7, 8, 1, 4, 3, 6, 5, 9}, 
	{8, 5, 2, 3, 1, 6, 7, 9, 4}, {1, 9, 6, 2, 7, 4, 5, 8, 3}, {3, 4, 7, 5, 9, 8, 1, 2, 6}};
	sudoku.fieldwithgasps={{0, 0, 7, 6, 2, 0, 0, 0, 8}, {0, 2, 0, 0, 8, 1, 0, 0, 0}, {6, 8, 4, 7, 0, 0, 0, 1, 0}, 
	{4, 6, 0, 0, 5, 2, 8, 3, 7}, {0, 0, 5, 0, 6, 7, 2, 4, 1}, {0, 0, 8, 0, 4, 3, 6, 5, 0}, 
	{8, 0, 2, 3, 1, 6, 0, 0, 4}, {1, 9, 0, 0, 7, 0, 0, 0, 3}, {0, 4, 0, 0, 9, 0, 0, 0, 0}};
	CHECK(sudoku.isCheckFillCell(0, 0) == false);
	CHECK(sudoku.isCheckFillCell(5, 2) == true);
	CHECK(sudoku.isCheckFillCell(0, 2) == false);
	CHECK(sudoku.isCheckFillCell(8, 1) == true);
}
