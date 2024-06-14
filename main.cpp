#include "form.h"
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QObject>
#include <QTextBlock>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form multiplayer;

    multiplayer.show();
    return a.exec();
}
