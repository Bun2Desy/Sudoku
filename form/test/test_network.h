#ifndef TEST_NETWORK_H
#define TEST_NETWORK_H

#include "network.h"
#include <QObject>

class ClientObject : public QObject{
	Q_OBJECT

public:
	Client clt;
	std::string lastMessage;
public slots:
	void FormatTime(int timeInSeconds);
	void FormatSudoku(std::string sudoku);
	void FormatCell(std::string cell);
	void ThrowError();
};

class ServerObject : public QObject{
	Q_OBJECT

public:
	Server srv;
	bool secondClientIsConnected = false;
public slots:
	void SecondClientConnected();
};

#endif