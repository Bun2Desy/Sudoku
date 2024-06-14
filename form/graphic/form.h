/**
 * \file form.h
 * The header file with gui of sudoku game
 */
#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include <QObject>
#include "ui_form.h"
#include "sudoku.h"
#include <iostream>

namespace Ui {
class Form;
}
/*!
    \brief class Form
    \details This class needed to create graphical interface of game
*/
class Form : public QWidget
{
    Q_OBJECT

public:
    //QTableWidgetItem * lastSelectedCell;
    int lastSelectedCellRow;///< last selected cell row
    int lastSelectedCellColumn;///< last selected cell column
    int currentTimeSeconds{0};///< current time in seconds for game
    int errorsCount{0};///< current count of errors per game
    bool secondClientIsConnect = false; ///< connection status of second client 
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void ChangeButtonsVisible(bool flag);
    void SetNumberToCell(int row, int column, QString cellValue);
    void FillSudokuTable();
    void GetSudokuTable();
    void UpdateTimer(int currentTimeSeconds);
    void StartGame();
    std::string TransformToTimeFormat(int time);
signals:
    void SendMessageSignal(std::string messageNum);
    void SudokuIsReadyToFill();
    void GameEndWin();
    void GameEndLose();
    void CloseServer();
public slots:
    void OpenGameMenu();
    void PlayerStepInformationParser(std::string compileMessage);
    void CompileMessageToSudokuArray(std::string compileMessage);
    void CompileMessageToSolvedSudokuArray(std::string compileMessage);
    void IncrementTime();
    void WinnerGameWindow();
    void ClientConnected();
    void LoserGameWindow();

private slots:
    void on_createGameButton_clicked();

    void on_button1_clicked();

    void on_sudokuTable_cellPressed(int row, int column);

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void on_button5_clicked();

    void on_button6_clicked();

    void on_button7_clicked();

    void on_button8_clicked();

    void on_button9_clicked();

    void on_joinGameButton_clicked();

    void on_backButton_clicked();

    void on_playGame_clicked();

private:
    Ui::Form *ui;///< pointer for work with widgets
    Sudoku sudokuObj{Sudoku('e')};///< sudoku object
    QTimer *tmr;///< timer pointer
};

#endif // FORM_H