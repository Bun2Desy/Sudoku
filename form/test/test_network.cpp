#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "network.h"
#include "test_network.h"
#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <QObject>

void ServerObject::SecondClientConnected()
{
	secondClientIsConnected = true;
}

void ClientObject::FormatTime(int timeInSeconds)
{
	std::string timeMinutes = std::to_string(timeInSeconds / 60);
    if(timeMinutes.length() == 1)
        timeMinutes = "0" + timeMinutes;
    std::string timeSeconds = std::to_string(timeInSeconds - (std::stoi(timeMinutes) * 60));
    if(timeSeconds.length() == 1)
        timeSeconds = "0" + timeSeconds;
    lastMessage = timeMinutes + ":" + timeSeconds;
}

void ClientObject::FormatSudoku(std::string sudoku)
{
	lastMessage = sudoku.substr(0, sudoku.find("."));
}

void ClientObject::FormatCell(std::string cell)
{
	lastMessage = std::string(1, cell[0]) + " " + std::string(1, cell[1]) + " " + std::string(1, cell[2]);
}

void ClientObject::ThrowError()
{
	lastMessage = "Got no valid message";
}

TEST_CASE("Second client connected successfully"){
	ServerObject serv;
	ClientObject clt1;
	ClientObject clt2;
	QObject::connect(&serv.srv, &Server::SecondClientConnect, &serv, &ServerObject::SecondClientConnected, Qt::DirectConnection);
	boost::thread_group threads;
	std::vector<boost::thread*> threads_array;
	serv.srv.playerMode = 2;
	UpServer(threads_array, threads, &serv.srv);
    clt1.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt2.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt1.clt.msg_ans = "end";
    threads.join_all();
    CHECK(serv.secondClientIsConnected == true);
}

TEST_CASE("Second client get correct time format"){
	ServerObject serv;
	ClientObject clt1;
	ClientObject clt2;
	QObject::connect(&clt2.clt, &Client::GetTimerInfo, &clt2, &ClientObject::FormatTime, Qt::DirectConnection);
	boost::thread_group threads;
	std::vector<boost::thread*> threads_array;
	serv.srv.playerMode = 2;
	UpServer(threads_array, threads, &serv.srv);
    clt1.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt2.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt1.clt.msg_ans = "t351.";
    clt2.clt.msg_ans = "end";
    threads.join_all();
    CHECK(clt2.lastMessage == "05:51");
}

TEST_CASE("Second client get sudoku table format 1"){
	ServerObject serv;
	ClientObject clt1;
	ClientObject clt2;
	QObject::connect(&clt2.clt, &Client::SudokuTableInBuffer, &clt2, &ClientObject::FormatSudoku, Qt::DirectConnection);
	boost::thread_group threads;
	std::vector<boost::thread*> threads_array;
	serv.srv.playerMode = 2;
	UpServer(threads_array, threads, &serv.srv);
    clt1.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt2.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt1.clt.msg_ans = "t351.026033045051064078107111142186205214228256272281306334404436448489501549562576632646671708735757766802816827844858869873885.009012026033045051064078087107111123138142154165179186205214228239247256263272281306317329334341352368375383404413422436448455461477489501518525537549553562576584603615624632646659667671688708719721735743757766774782802816827831844858869873885";
    clt2.clt.msg_ans = "end";
    threads.join_all();
    CHECK(clt2.lastMessage == "026033045051064078107111142186205214228256272281306334404436448489501549562576632646671708735757766802816827844858869873885");
}

TEST_CASE("Second client get sudoku table format 2"){
	ServerObject serv;
	ClientObject clt1;
	ClientObject clt2;
	QObject::connect(&clt2.clt, &Client::SudokuTableInBuffer, &clt2, &ClientObject::FormatSudoku, Qt::DirectConnection);
	boost::thread_group threads;
	std::vector<boost::thread*> threads_array;
	serv.srv.playerMode = 2;
	UpServer(threads_array, threads, &serv.srv);
    clt1.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt2.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt1.clt.msg_ans = "026033045051064078107111142186205214228256272281306334404436448489501549562576632646671708735757766802816827844858869873885.009012026033045051064078087107111123138142154165179186205214228239247256263272281306317329334341352368375383404413422436448455461477489501518525537549553562576584603615624632646659667671688708719721735743757766774782802816827831844858869873885";
    clt2.clt.msg_ans = "end";
    threads.join_all();
    CHECK(clt2.lastMessage == "026033045051064078107111142186205214228256272281306334404436448489501549562576632646671708735757766802816827844858869873885");
}

TEST_CASE("Second client get cell info"){
	ServerObject serv;
	ClientObject clt1;
	ClientObject clt2;
	QObject::connect(&clt2.clt, &Client::UpdateSomeData, &clt2, &ClientObject::FormatCell, Qt::DirectConnection);
	boost::thread_group threads;
	std::vector<boost::thread*> threads_array;
	serv.srv.playerMode = 2;
	UpServer(threads_array, threads, &serv.srv);
    clt1.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt2.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt1.clt.msg_ans = "742";
    clt2.clt.msg_ans = "end";
    threads.join_all();
    CHECK(clt2.lastMessage == "7 4 2");
}

TEST_CASE("Second client get no valid message 1"){
	ServerObject serv;
	ClientObject clt1;
	ClientObject clt2;
	QObject::connect(&clt2.clt, &Client::ErrorMessage, &clt2, &ClientObject::ThrowError, Qt::DirectConnection);
	boost::thread_group threads;
	std::vector<boost::thread*> threads_array;
	serv.srv.playerMode = 2;
	UpServer(threads_array, threads, &serv.srv);
    clt1.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt2.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt1.clt.msg_ans = "t14.Hello World!";
    clt2.clt.msg_ans = "end";
    threads.join_all();
    CHECK(clt2.lastMessage == "Got no valid message");
}

TEST_CASE("Second client get no valid message 2"){
	ServerObject serv;
	ClientObject clt1;
	ClientObject clt2;
	QObject::connect(&clt2.clt, &Client::ErrorMessage, &clt2, &ClientObject::ThrowError, Qt::DirectConnection);
	boost::thread_group threads;
	std::vector<boost::thread*> threads_array;
	serv.srv.playerMode = 2;
	UpServer(threads_array, threads, &serv.srv);
    clt1.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt2.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt1.clt.msg_ans = ".....";
    clt2.clt.msg_ans = "end";
    threads.join_all();
    CHECK(clt2.lastMessage == "Got no valid message");
}

TEST_CASE("Second client get no valid message 3"){
	ServerObject serv;
	ClientObject clt1;
	ClientObject clt2;
	QObject::connect(&clt2.clt, &Client::ErrorMessage, &clt2, &ClientObject::ThrowError, Qt::DirectConnection);
	boost::thread_group threads;
	std::vector<boost::thread*> threads_array;
	serv.srv.playerMode = 2;
	UpServer(threads_array, threads, &serv.srv);
    clt1.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt2.clt.ConnectClient(threads_array, threads, "127.0.0.1");
    clt1.clt.msg_ans = "Do exploit";
    clt2.clt.msg_ans = "end";
    threads.join_all();
    CHECK(clt2.lastMessage == "Got no valid message");
}