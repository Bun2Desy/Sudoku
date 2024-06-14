/**
*\file form.cpp
* The file with gui of sudoku game
*/

#include "form.h"
#include "ui_form.h"
#include "sudoku.h"
#include "network.h"

#include <iostream>
#include <fstream>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <vector>
#include <boost/thread.hpp>

Server servObj{Server()};
Client clientObj{Client()};
boost::thread_group threads;

std::vector<boost::thread*> threads_array;

/**
* Constructor for new form object
*\param[in] parent reference on gui window
*/
Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    tmr = new QTimer();
    ui->setupUi(this);
    ui->sudokuTable->close();
    ChangeButtonsVisible(false);
    ui->winLabel->close();
    ui->loseLabel->close();
    ui->errorCountLabel->close();
    ui->timerLabel->close();
    ui->backButton->close();
    ui->bestTimeLabel->close();
    ui->lastGameTimeLabel->close();
}

Form::~Form()
{
    delete ui;
}

/**
* Set state of game buttons
*\param[in] flag show or hide buttons state
*/
void Form::ChangeButtonsVisible(bool flag)
{
    ui->button1->setVisible(flag);
    ui->button2->setVisible(flag);
    ui->button3->setVisible(flag);
    ui->button4->setVisible(flag);
    ui->button5->setVisible(flag);
    ui->button6->setVisible(flag);
    ui->button7->setVisible(flag);
    ui->button8->setVisible(flag);
    ui->button9->setVisible(flag);
}

/**
* Set number to cell
*\param[in] row row of cell
*\param[in] column column of cell
*\param[in] cellValue value of cell
*/
void Form::SetNumberToCell(int row, int column, QString cellValue)
{
    QTableWidgetItem * cell{new QTableWidgetItem()};
    cell->setText(cellValue);
    cell->setFont(QFont(cellValue, 16));
    cell->setTextAlignment(4);
    if(!sudokuObj.isCheckFillCell(row, column)){
        sudokuObj.fieldwithgasps[row][column] = cellValue.toInt();
        if(sudokuObj.fieldwithgasps[row][column] != sudokuObj.field[row][column]){
            cell->setForeground(QBrush(QColor(255, 0, 0)));
            errorsCount += 1;
            std::string errorsCountStringFormat = std::to_string(errorsCount) + "/3";
            ui->errorCountLabel->setText(QString::fromStdString(errorsCountStringFormat));
            if(errorsCount == 3)
                emit GameEndLose();
        } else
            cell->setForeground(QBrush(QColor(0, 0, 150)));
        ui->sudokuTable->setItem(row, column, cell);
    }
    bool sudokuIsSolved = true;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(sudokuObj.fieldwithgasps[i][j] != sudokuObj.field[i][j]){
                sudokuIsSolved = false;
                break;
            }
        }
    }
    if(sudokuIsSolved)
        emit GameEndWin();
}

/**
* Get string information of all cells of sudoku table
*/
void Form::GetSudokuTable()
{
    std::string cellsOfSudokuInformationString;
    std::string cellsOfSolvedSudokuInformationString;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(sudokuObj.fieldwithgasps[i][j] != 0){
                int compileSudokuTableInformation = i * 100 + j * 10 + sudokuObj.fieldwithgasps[i][j];
                if((compileSudokuTableInformation / 10) == 0){
                    cellsOfSudokuInformationString += "00";
                } else if((compileSudokuTableInformation / 100) == 0){
                    cellsOfSudokuInformationString += "0";
                }
                cellsOfSudokuInformationString += std::to_string(compileSudokuTableInformation);
            }
        }
    }
    cellsOfSudokuInformationString += ".";
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            int compileSudokuTableInformation = i * 100 + j * 10 + sudokuObj.field[i][j];
            if((compileSudokuTableInformation / 10) == 0){
                cellsOfSudokuInformationString += "00";
            } else if((compileSudokuTableInformation / 100) == 0){
                cellsOfSudokuInformationString += "0";
            }
            cellsOfSudokuInformationString += std::to_string(compileSudokuTableInformation);
        }
    }
    emit SendMessageSignal(cellsOfSudokuInformationString);
}

/**
* Fill sudoku game field
*/
void Form::FillSudokuTable()
{
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            QTableWidgetItem * cell{new QTableWidgetItem()};
            QString cellValue;
            cell->setText(QString::fromStdString(""));
            ui->sudokuTable->setItem(i, j, cell);
            if(sudokuObj.fieldwithgasps[i][j] != 0){
                cellValue.setNum(sudokuObj.fieldwithgasps[i][j]);
                cell->setText(cellValue);
                cell->setTextAlignment(4);
                cell->setFont(QFont(cellValue, 16));
                ui->sudokuTable->setItem(i, j, cell);
            }
        }
    }
}

/**
* Parse information of cell
*\param[in] compileMessage information of cell from buffer
*/
void Form::PlayerStepInformationParser(std::string compileMessage)
{
    int compileNum{std::stoi(compileMessage)};
    int row{compileNum / 100};
    compileNum = compileNum % 100;
    int column{compileNum / 10};
    QString cellValue;
    cellValue.setNum(compileNum % 10);
    if(compileNum % 10 != 0)
        SetNumberToCell(row, column, cellValue);
}

/**
* Compile message from buffer for filling sudoku game field 
*\param[in] compileMessage information of sudoku table from buffer
*/
void Form::CompileMessageToSudokuArray(std::string compileMessage)
{
    int i = 0;
    while(compileMessage[i] != '.'){
        int compileNum{std::stoi(compileMessage.substr(i, 3))};
        int row{compileNum / 100};
        compileNum = compileNum % 100;
        int column{compileNum / 10};
        sudokuObj.fieldwithgasps[row][column] = compileNum % 10;
        i += 3;
    }
    i += 1;
    while(i < compileMessage.length()){
        int compileNum{std::stoi(compileMessage.substr(i, 3))};
        int row{compileNum / 100};
        compileNum = compileNum % 100;
        int column{compileNum / 10};
        sudokuObj.field[row][column] = compileNum % 10;
        i += 3;
    }
    emit SudokuIsReadyToFill();
}

void Form::CompileMessageToSolvedSudokuArray(std::string compileMessage)
{
    for(int i = 0; i < compileMessage.length(); i += 3){
        int compileNum{std::stoi(compileMessage.substr(i, 3))};
        int row{compileNum / 100};
        compileNum = compileNum % 100;
        int column{compileNum / 10};
        sudokuObj.field[row][column] = compileNum % 10;
    }
}

/**
* Open a game window
*/
void Form::OpenGameMenu()
{
    FillSudokuTable();
    ui->sudokuTable->show();
    ChangeButtonsVisible(true);
}

/**
* Open a winner window
*/
void Form::WinnerGameWindow()
{
    std::ofstream out;
    std::ifstream in;
    if(sudokuObj.dif == 'e')
        in.open("file_easy.txt");
    else if(sudokuObj.dif == 'n')
        in.open("file_normal.txt");
    else if(sudokuObj.dif == 'h')
        in.open("file_hard.txt");
    std::string bestTime;
    in >> bestTime;
    in.close();
    int bestTimeInt = std::stoi(bestTime);
    if(currentTimeSeconds < bestTimeInt){
        if(sudokuObj.dif == 'e')
            out.open("file_easy.txt");
        else if(sudokuObj.dif == 'n')
            out.open("file_normal.txt");
        else if(sudokuObj.dif == 'h')
            out.open("file_hard.txt");
        out << currentTimeSeconds;
        out.close();
        std::string bestTimeFormat = TransformToTimeFormat(currentTimeSeconds);
        ui->bestTimeLabel->setText(QString::fromStdString("The best time: " + bestTimeFormat));
        ui->lastGameTimeLabel->setText(QString::fromStdString("Last game: " + bestTimeFormat));
    } else{
        std::string currentTimeFormat = TransformToTimeFormat(currentTimeSeconds);
        std::string bestTimeFormat = TransformToTimeFormat(bestTimeInt);
        ui->bestTimeLabel->setText(QString::fromStdString("The best time: " + bestTimeFormat));
        ui->lastGameTimeLabel->setText(QString::fromStdString("Last game: " + currentTimeFormat));
    }
    resize(400, 300);
    ui->bestTimeLabel->show();
    ui->lastGameTimeLabel->show();
    ui->backButton->show();
    ui->sudokuTable->close();
    ChangeButtonsVisible(false);
    if(!servObj.sessions.empty())
        tmr->stop();
    ui->timerLabel->close();
    ui->errorCountLabel->close();
    ui->winLabel->show();
    ui->bestTimeLabel->show();
    ui->lastGameTimeLabel->show();
}

/**
* Open a lose window
*/
void Form::LoserGameWindow()
{
    resize(400, 300);
    ui->backButton->show();
    ui->sudokuTable->close();
    ChangeButtonsVisible(false);
    if(!servObj.sessions.empty())
        tmr->stop();
    ui->timerLabel->close();
    ui->errorCountLabel->close();
    ui->loseLabel->show();
}

/**
* Update timer on game window
*\param[in] currentTimeSeconds The current time in seconds
*/
void Form::UpdateTimer(int currentTimeSeconds)
{
    std::string timeMinutes = std::to_string(currentTimeSeconds / 60);
    this->currentTimeSeconds = currentTimeSeconds;
    if(timeMinutes.length() == 1)
        timeMinutes = "0" + timeMinutes;
    std::string timeSeconds = std::to_string(currentTimeSeconds - (std::stoi(timeMinutes) * 60));
    if(timeSeconds.length() == 1)
        timeSeconds = "0" + timeSeconds;
    std::string compileTime = timeMinutes + ":" + timeSeconds;
    ui->timerLabel->setText(QString::fromStdString(compileTime));
}

/**
* Increment second
*/
void Form::IncrementTime()
{
    currentTimeSeconds += 1;
    if(secondClientIsConnect)
        emit SendMessageSignal("t" + std::to_string(currentTimeSeconds) + ".");
    UpdateTimer(currentTimeSeconds);
}

/**
* Set state of second client connect on true
*/
void Form::ClientConnected()
{
    secondClientIsConnect = true;
}

/**
* Called when create game button clicked
*/
void Form::on_createGameButton_clicked()
{
    servObj.playerMode = 2;
    StartGame();
}

/**
* Create multiplayer game
*/
void Form::StartGame()
{
    ui->createGameButton->close();
    ui->joinGameButton->close();
    ui->difficultyBox->close();
    ui->ipv4EditFirstOctate->close();
    ui->ipv4EditSecondOctate->close();
    ui->ipv4EditThirdOctate->close();
    ui->ipv4EditFourthOctate->close();
    ui->nameLabel->close();
    ui->playGame->close();
    QString difficulty{ui->difficultyBox->currentText()};
    if(difficulty == "Easy")
        sudokuObj.dif = 'e';
    else if(difficulty == "Normal")
        sudokuObj.dif = 'n';
    else if(difficulty == "Hard")
        sudokuObj.dif = 'h';
    QObject::connect(&clientObj, &Client::UpdateSomeData, this, &Form::PlayerStepInformationParser);
    QObject::connect(this, &Form::SendMessageSignal, &clientObj, &Client::TransferFromGUIToBuffer);
    QObject::connect(&servObj, &Server::SecondClientConnect, this, &Form::GetSudokuTable);
    QObject::connect(&servObj, &Server::SecondClientConnect, this, &Form::ClientConnected);
    QObject::connect(this, &Form::GameEndWin, this, &Form::WinnerGameWindow);
    QObject::connect(this, &Form::GameEndLose, this, &Form::LoserGameWindow);
    QObject::connect(tmr, &QTimer::timeout, this, &Form::IncrementTime);
    UpServer(threads_array, threads, &servObj);
    clientObj.ConnectClient(threads_array, threads, "127.0.0.1");
    sudokuObj.CreateField();
    FillSudokuTable();
    resize(575, 300);
    ui->sudokuTable->show();
    ChangeButtonsVisible(true);
    tmr->start(1000);
    ui->errorCountLabel->show();
    ui->timerLabel->show();
}

/**
* Called when button 1 clicked
*/
void Form::on_button1_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 1};
    cellValue.setNum(1);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when sudoku table cell pressed
*\param[in] row row of selected cell
*\param[in] column column of selected cell
*/
void Form::on_sudokuTable_cellPressed(int row, int column)
{
    lastSelectedCellRow = row;
    lastSelectedCellColumn = column;
}

/**
* Called when button 2 clicked
*/
void Form::on_button2_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 2};
    cellValue.setNum(2);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when button 3 clicked
*/
void Form::on_button3_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 3};
    cellValue.setNum(3);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when button 4 clicked
*/
void Form::on_button4_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 4};
    cellValue.setNum(4);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when button 5 clicked
*/
void Form::on_button5_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 5};
    cellValue.setNum(5);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when button 6 clicked
*/
void Form::on_button6_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 6};
    cellValue.setNum(6);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when button 7 clicked
*/
void Form::on_button7_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 7};
    cellValue.setNum(7);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when button 8 clicked
*/
void Form::on_button8_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 8};
    cellValue.setNum(8);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when button 9 clicked
*/
void Form::on_button9_clicked()
{
    QString cellValue;
    int compilePlayerStepInformation{lastSelectedCellRow * 100 + lastSelectedCellColumn * 10 + 9};
    cellValue.setNum(9);
    SetNumberToCell(lastSelectedCellRow, lastSelectedCellColumn, cellValue);
    std::string compilePlayerStepInformationStringFormat;
    if((compilePlayerStepInformation / 10) == 0){
        compilePlayerStepInformationStringFormat += "00";
    } else if((compilePlayerStepInformation / 100) == 0){
        compilePlayerStepInformationStringFormat += "0";
    }
    compilePlayerStepInformationStringFormat += std::to_string(compilePlayerStepInformation);
    emit SendMessageSignal(compilePlayerStepInformationStringFormat);
}

/**
* Called when join game button clicked
*/
void Form::on_joinGameButton_clicked()
{
    ui->createGameButton->close();
    ui->joinGameButton->close();
    ui->difficultyBox->close();
    ui->ipv4EditFirstOctate->close();
    ui->ipv4EditSecondOctate->close();
    ui->ipv4EditThirdOctate->close();
    ui->ipv4EditFourthOctate->close();
    ui->playGame->close();
    ui->nameLabel->close();
    QString ipv4FirstOctate{ui->ipv4EditFirstOctate->text()};
    QString ipv4SecondOctate{ui->ipv4EditSecondOctate->text()};
    QString ipv4ThirdOctate{ui->ipv4EditThirdOctate->text()};
    QString ipv4FourthOctate{ui->ipv4EditFourthOctate->text()};
    int firstOctateNum{ipv4FirstOctate.toInt()};
    int secondOctateNum{ipv4SecondOctate.toInt()};
    int thirdOctateNum{ipv4ThirdOctate.toInt()};
    int fourthOctateNum{ipv4FourthOctate.toInt()};
    std::string ipv4String{std::to_string(firstOctateNum) + "." + std::to_string(secondOctateNum) + "." + std::to_string(thirdOctateNum) + "." + std::to_string(fourthOctateNum)};
    QObject::connect(&clientObj, &Client::SudokuTableInBuffer, this, &Form::CompileMessageToSudokuArray);
    QObject::connect(&clientObj, &Client::UpdateSomeData, this, &Form::PlayerStepInformationParser);
    QObject::connect(this, &Form::SendMessageSignal, &clientObj, &Client::TransferFromGUIToBuffer);
    QObject::connect(this, &Form::SudokuIsReadyToFill, this, &Form::OpenGameMenu);
    QObject::connect(&clientObj, &Client::SolvedSudokuTableInBuffer, this, &Form::CompileMessageToSolvedSudokuArray);
    QObject::connect(this, &Form::GameEndWin, this, &Form::WinnerGameWindow);
    QObject::connect(this, &Form::GameEndLose, this, &Form::LoserGameWindow);
    QObject::connect(&clientObj, &Client::GetTimerInfo, this, &Form::UpdateTimer);
    clientObj.ConnectClient(threads_array, threads, ipv4String);
    resize(575, 300);
    ui->errorCountLabel->show();
    ui->timerLabel->show();
}

/**
* Called when back button clicked
*/
void Form::on_backButton_clicked()
{
    if(!clientObj.gameIsEnd)
        emit SendMessageSignal("end");
    threads.join_all();
    //std::cout << "debug1" << std::endl;
    for(int i = 0; i < threads_array.size(); i++){
        threads.remove_thread(threads_array[i]);
    }
    //std::cout << "debug2" << std::endl;
    if(!servObj.sessions.empty()){
        servObj.sessions.clear();
        QObject::disconnect(&clientObj, &Client::UpdateSomeData, this, &Form::PlayerStepInformationParser);
        QObject::disconnect(this, &Form::SendMessageSignal, &clientObj, &Client::TransferFromGUIToBuffer);
        QObject::disconnect(&servObj, &Server::SecondClientConnect, this, &Form::GetSudokuTable);
        QObject::disconnect(&servObj, &Server::SecondClientConnect, this, &Form::ClientConnected);
        QObject::disconnect(this, &Form::GameEndWin, this, &Form::WinnerGameWindow);
        QObject::disconnect(this, &Form::GameEndLose, this, &Form::LoserGameWindow);
        QObject::disconnect(tmr, &QTimer::timeout, this, &Form::IncrementTime);
    } else{
        QObject::disconnect(&clientObj, &Client::SudokuTableInBuffer, this, &Form::CompileMessageToSudokuArray);
        QObject::disconnect(&clientObj, &Client::UpdateSomeData, this, &Form::PlayerStepInformationParser);
        QObject::disconnect(this, &Form::SendMessageSignal, &clientObj, &Client::TransferFromGUIToBuffer);
        QObject::disconnect(this, &Form::SudokuIsReadyToFill, this, &Form::OpenGameMenu);
        QObject::disconnect(&clientObj, &Client::SolvedSudokuTableInBuffer, this, &Form::CompileMessageToSolvedSudokuArray);
        QObject::disconnect(this, &Form::GameEndWin, this, &Form::WinnerGameWindow);
        QObject::disconnect(this, &Form::GameEndLose, this, &Form::LoserGameWindow);
        QObject::disconnect(&clientObj, &Client::GetTimerInfo, this, &Form::UpdateTimer);
        sudokuObj.field = { 9, std::vector<int>(9, 0) };
        sudokuObj.fieldwithgasps = { 9, std::vector<int>(9, 0) };
    }
    //std::cout << "debug3" << std::endl;
    currentTimeSeconds = 0;
    threads_array.clear();
    clientObj.gameIsEnd = false;
    secondClientIsConnect = false;
    if(errorsCount != 0){
        errorsCount = 0;
        std::string errorsCountStringFormat = std::to_string(errorsCount) + "/3";
        ui->errorCountLabel->setText(QString::fromStdString(errorsCountStringFormat));
    }
    //std::cout << "debug4" << std::endl;
    ui->sudokuTable->reset();
    clientObj.socket.close();
    ui->loseLabel->close();
    ui->winLabel->close();
    ui->backButton->close();
    ui->bestTimeLabel->close();
    ui->lastGameTimeLabel->close();
    ui->createGameButton->show();
    ui->joinGameButton->show();
    ui->difficultyBox->show();
    ui->ipv4EditFirstOctate->show();
    ui->ipv4EditSecondOctate->show();
    ui->ipv4EditThirdOctate->show();
    ui->ipv4EditFourthOctate->show();
    ui->playGame->show();
    ui->nameLabel->show();
    //std::cout << "debug5" << std::endl;
}

/**
* Transform seconds int format to minutes and seconds format
*\param[in] time time in seconds
*\return time format in minutes and seconds
*/
std::string Form::TransformToTimeFormat(int time)
{
    int timeMinutes = time / 60;
    int timeSeconds = time - (timeMinutes * 60);
    std::string timeFormat = "";
    if(timeMinutes < 10){
        timeFormat = "0" + std::to_string(timeMinutes) + ":";
    } else{
        timeFormat = std::to_string(timeMinutes) + ":";
    }
    if(timeSeconds < 10){
        timeFormat = timeFormat + "0" + std::to_string(timeSeconds);
    } else{
        timeFormat = timeFormat + std::to_string(timeSeconds);
    }
    return timeFormat;
}

/**
* Called when play game clicked
*/
void Form::on_playGame_clicked()
{
    servObj.playerMode = 1;
    StartGame();
}

