/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *createGameButton;
    QPushButton *joinGameButton;
    QComboBox *difficultyBox;
    QTableWidget *sudokuTable;
    QWidget *gridLayoutWidget;
    QGridLayout *numbersLayout;
    QPushButton *button2;
    QPushButton *button1;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button7;
    QPushButton *button8;
    QPushButton *button9;
    QPushButton *button6;
    QPushButton *button3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *ipv4EditFirstOctate;
    QLineEdit *ipv4EditSecondOctate;
    QLineEdit *ipv4EditThirdOctate;
    QLineEdit *ipv4EditFourthOctate;
    QLabel *winLabel;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *timerLabel;
    QLabel *errorCountLabel;
    QPushButton *backButton;
    QLabel *loseLabel;
    QPushButton *playGame;
    QLabel *nameLabel;
    QLabel *bestTimeLabel;
    QLabel *lastGameTimeLabel;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Form->sizePolicy().hasHeightForWidth());
        Form->setSizePolicy(sizePolicy);
        createGameButton = new QPushButton(Form);
        createGameButton->setObjectName("createGameButton");
        createGameButton->setGeometry(QRect(190, 140, 111, 21));
        joinGameButton = new QPushButton(Form);
        joinGameButton->setObjectName("joinGameButton");
        joinGameButton->setGeometry(QRect(190, 180, 111, 21));
        difficultyBox = new QComboBox(Form);
        difficultyBox->addItem(QString());
        difficultyBox->addItem(QString());
        difficultyBox->addItem(QString());
        difficultyBox->setObjectName("difficultyBox");
        difficultyBox->setGeometry(QRect(70, 120, 101, 22));
        sudokuTable = new QTableWidget(Form);
        if (sudokuTable->columnCount() < 9)
            sudokuTable->setColumnCount(9);
        if (sudokuTable->rowCount() < 9)
            sudokuTable->setRowCount(9);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        QFont font;
        font.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        __qtablewidgetitem->setBackground(brush1);
        __qtablewidgetitem->setForeground(brush);
        sudokuTable->setItem(0, 0, __qtablewidgetitem);
        sudokuTable->setObjectName("sudokuTable");
        sudokuTable->setEnabled(true);
        sudokuTable->setGeometry(QRect(30, 10, 271, 271));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sudokuTable->sizePolicy().hasHeightForWidth());
        sudokuTable->setSizePolicy(sizePolicy1);
        sudokuTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sudokuTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sudokuTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        sudokuTable->setRowCount(9);
        sudokuTable->setColumnCount(9);
        sudokuTable->horizontalHeader()->setVisible(false);
        sudokuTable->horizontalHeader()->setMinimumSectionSize(0);
        sudokuTable->horizontalHeader()->setDefaultSectionSize(30);
        sudokuTable->horizontalHeader()->setStretchLastSection(true);
        sudokuTable->verticalHeader()->setVisible(false);
        sudokuTable->verticalHeader()->setMinimumSectionSize(0);
        sudokuTable->verticalHeader()->setDefaultSectionSize(30);
        sudokuTable->verticalHeader()->setHighlightSections(true);
        sudokuTable->verticalHeader()->setStretchLastSection(true);
        gridLayoutWidget = new QWidget(Form);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(319, 40, 250, 71));
        numbersLayout = new QGridLayout(gridLayoutWidget);
        numbersLayout->setObjectName("numbersLayout");
        numbersLayout->setSizeConstraint(QLayout::SetMinimumSize);
        numbersLayout->setContentsMargins(0, 0, 0, 0);
        button2 = new QPushButton(gridLayoutWidget);
        button2->setObjectName("button2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(button2->sizePolicy().hasHeightForWidth());
        button2->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button2, 0, 1, 1, 1);

        button1 = new QPushButton(gridLayoutWidget);
        button1->setObjectName("button1");
        sizePolicy2.setHeightForWidth(button1->sizePolicy().hasHeightForWidth());
        button1->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button1, 0, 0, 1, 1);

        button4 = new QPushButton(gridLayoutWidget);
        button4->setObjectName("button4");
        sizePolicy2.setHeightForWidth(button4->sizePolicy().hasHeightForWidth());
        button4->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button4, 1, 0, 1, 1);

        button5 = new QPushButton(gridLayoutWidget);
        button5->setObjectName("button5");
        sizePolicy2.setHeightForWidth(button5->sizePolicy().hasHeightForWidth());
        button5->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button5, 1, 1, 1, 1);

        button7 = new QPushButton(gridLayoutWidget);
        button7->setObjectName("button7");
        sizePolicy2.setHeightForWidth(button7->sizePolicy().hasHeightForWidth());
        button7->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button7, 3, 0, 1, 1);

        button8 = new QPushButton(gridLayoutWidget);
        button8->setObjectName("button8");
        sizePolicy2.setHeightForWidth(button8->sizePolicy().hasHeightForWidth());
        button8->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button8, 3, 1, 1, 1);

        button9 = new QPushButton(gridLayoutWidget);
        button9->setObjectName("button9");
        sizePolicy2.setHeightForWidth(button9->sizePolicy().hasHeightForWidth());
        button9->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button9, 3, 2, 1, 1);

        button6 = new QPushButton(gridLayoutWidget);
        button6->setObjectName("button6");
        sizePolicy2.setHeightForWidth(button6->sizePolicy().hasHeightForWidth());
        button6->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button6, 1, 2, 1, 1);

        button3 = new QPushButton(gridLayoutWidget);
        button3->setObjectName("button3");
        sizePolicy2.setHeightForWidth(button3->sizePolicy().hasHeightForWidth());
        button3->setSizePolicy(sizePolicy2);

        numbersLayout->addWidget(button3, 0, 2, 1, 1);

        numbersLayout->setColumnStretch(0, 1);
        numbersLayout->setColumnStretch(1, 1);
        numbersLayout->setColumnStretch(2, 1);
        horizontalLayoutWidget = new QWidget(Form);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(40, 170, 131, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ipv4EditFirstOctate = new QLineEdit(horizontalLayoutWidget);
        ipv4EditFirstOctate->setObjectName("ipv4EditFirstOctate");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ipv4EditFirstOctate->sizePolicy().hasHeightForWidth());
        ipv4EditFirstOctate->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(ipv4EditFirstOctate);

        ipv4EditSecondOctate = new QLineEdit(horizontalLayoutWidget);
        ipv4EditSecondOctate->setObjectName("ipv4EditSecondOctate");
        sizePolicy3.setHeightForWidth(ipv4EditSecondOctate->sizePolicy().hasHeightForWidth());
        ipv4EditSecondOctate->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(ipv4EditSecondOctate);

        ipv4EditThirdOctate = new QLineEdit(horizontalLayoutWidget);
        ipv4EditThirdOctate->setObjectName("ipv4EditThirdOctate");
        sizePolicy3.setHeightForWidth(ipv4EditThirdOctate->sizePolicy().hasHeightForWidth());
        ipv4EditThirdOctate->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(ipv4EditThirdOctate);

        ipv4EditFourthOctate = new QLineEdit(horizontalLayoutWidget);
        ipv4EditFourthOctate->setObjectName("ipv4EditFourthOctate");
        sizePolicy3.setHeightForWidth(ipv4EditFourthOctate->sizePolicy().hasHeightForWidth());
        ipv4EditFourthOctate->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(ipv4EditFourthOctate);

        winLabel = new QLabel(Form);
        winLabel->setObjectName("winLabel");
        winLabel->setGeometry(QRect(170, 60, 81, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe Print")});
        font1.setPointSize(15);
        winLabel->setFont(font1);
        horizontalLayoutWidget_2 = new QWidget(Form);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(310, 0, 91, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        timerLabel = new QLabel(horizontalLayoutWidget_2);
        timerLabel->setObjectName("timerLabel");
        QFont font2;
        font2.setPointSize(15);
        timerLabel->setFont(font2);

        horizontalLayout_2->addWidget(timerLabel);

        errorCountLabel = new QLabel(horizontalLayoutWidget_2);
        errorCountLabel->setObjectName("errorCountLabel");
        errorCountLabel->setFont(font2);

        horizontalLayout_2->addWidget(errorCountLabel);

        backButton = new QPushButton(Form);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(40, 230, 91, 31));
        QFont font3;
        font3.setPointSize(13);
        backButton->setFont(font3);
        loseLabel = new QLabel(Form);
        loseLabel->setObjectName("loseLabel");
        loseLabel->setGeometry(QRect(170, 60, 71, 31));
        loseLabel->setFont(font1);
        playGame = new QPushButton(Form);
        playGame->setObjectName("playGame");
        playGame->setGeometry(QRect(190, 100, 111, 21));
        nameLabel = new QLabel(Form);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setGeometry(QRect(150, 40, 101, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe Print")});
        font4.setPointSize(20);
        nameLabel->setFont(font4);
        bestTimeLabel = new QLabel(Form);
        bestTimeLabel->setObjectName("bestTimeLabel");
        bestTimeLabel->setGeometry(QRect(110, 90, 221, 29));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe Script")});
        font5.setPointSize(15);
        bestTimeLabel->setFont(font5);
        lastGameTimeLabel = new QLabel(Form);
        lastGameTimeLabel->setObjectName("lastGameTimeLabel");
        lastGameTimeLabel->setGeometry(QRect(130, 130, 211, 29));
        lastGameTimeLabel->setFont(font5);
        sudokuTable->raise();
        createGameButton->raise();
        joinGameButton->raise();
        difficultyBox->raise();
        gridLayoutWidget->raise();
        horizontalLayoutWidget->raise();
        winLabel->raise();
        horizontalLayoutWidget_2->raise();
        backButton->raise();
        loseLabel->raise();
        playGame->raise();
        nameLabel->raise();
        bestTimeLabel->raise();
        lastGameTimeLabel->raise();

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        createGameButton->setText(QCoreApplication::translate("Form", "Create game", nullptr));
        joinGameButton->setText(QCoreApplication::translate("Form", "Join game", nullptr));
        difficultyBox->setItemText(0, QCoreApplication::translate("Form", "Easy", nullptr));
        difficultyBox->setItemText(1, QCoreApplication::translate("Form", "Normal", nullptr));
        difficultyBox->setItemText(2, QCoreApplication::translate("Form", "Hard", nullptr));


        const bool __sortingEnabled = sudokuTable->isSortingEnabled();
        sudokuTable->setSortingEnabled(false);
        sudokuTable->setSortingEnabled(__sortingEnabled);

        button2->setText(QCoreApplication::translate("Form", "2", nullptr));
        button1->setText(QCoreApplication::translate("Form", "1", nullptr));
        button4->setText(QCoreApplication::translate("Form", "4", nullptr));
        button5->setText(QCoreApplication::translate("Form", "5", nullptr));
        button7->setText(QCoreApplication::translate("Form", "7", nullptr));
        button8->setText(QCoreApplication::translate("Form", "8", nullptr));
        button9->setText(QCoreApplication::translate("Form", "9", nullptr));
        button6->setText(QCoreApplication::translate("Form", "6", nullptr));
        button3->setText(QCoreApplication::translate("Form", "3", nullptr));
        ipv4EditFirstOctate->setText(QString());
        ipv4EditSecondOctate->setText(QString());
        ipv4EditThirdOctate->setText(QString());
        ipv4EditFourthOctate->setText(QString());
        winLabel->setText(QCoreApplication::translate("Form", "You win!", nullptr));
        timerLabel->setText(QCoreApplication::translate("Form", "00:00", nullptr));
        errorCountLabel->setText(QCoreApplication::translate("Form", "0/3", nullptr));
        backButton->setText(QCoreApplication::translate("Form", "Back", nullptr));
        loseLabel->setText(QCoreApplication::translate("Form", "Wasted", nullptr));
        playGame->setText(QCoreApplication::translate("Form", "Play game", nullptr));
        nameLabel->setText(QCoreApplication::translate("Form", "Sudoku", nullptr));
        bestTimeLabel->setText(QCoreApplication::translate("Form", "The best time: 00:00", nullptr));
        lastGameTimeLabel->setText(QCoreApplication::translate("Form", "Last game: 00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
