/**
 * \file network.h
 * The header file for making networking connection between two clients
 */

#ifndef NETWORK_H
#define NETWORK_H


#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <QObject>

using namespace boost::asio;
using namespace boost::asio::ip;

// bool gameIsEnd = false;
//std::vector<boost::thread*> threads_array;

/*!
    \brief class Session
    \details This class is needed to create session between server and client
*/
class Session {
public:
    tcp::socket sock_;///< server socket
    char buff_[1024];///< buffer for read
public:
    Session(io_context* ioc) : sock_(*ioc){}
};

typedef boost::shared_ptr<Session> pointer;
//std::vector<pointer> sessions;

/*!
    \brief class Server
    \details This class make server side relize
*/
class Server : public QObject{
    Q_OBJECT

public:
    boost::asio::io_context* io_server;///< input-output context pointer for server side
    tcp::endpoint localhost{tcp::v4(), 8001};///< endpoint for server accept
    tcp::acceptor acceptor;///< object for accept connections
    int playerMode;///< single or multiplayer mode
    std::vector<pointer> sessions;///< vector of opened sessions
signals:
    void SecondClientConnect();
public:
    Server() : io_server{new boost::asio::io_context()}, acceptor{*io_server, localhost} {}
    void DoAccept();
    void SimpleServer();
};

/*!
    \brief class Client
    \details This class make client side relize
*/
class Client : public QObject{
    Q_OBJECT

public:
    boost::asio::io_context io;///< input-output context for client side
    tcp::socket socket;///< client socket
    tcp::endpoint ep;///< endpoint to connect client
    //char msg_char[1024];
    std::string msg_ans{""};///< string for write to buffer
    bool gameIsEnd = false;///< game status
    //int bytes{0};
public:
    Client() : socket{io} {}
    void ConnectClient(std::vector<boost::thread*>& threads_array, boost::thread_group& threads, std::string address);
    void ReadMessage();
    void SendMessage();
signals:
    void UpdateSomeData(std::string msg);
    void SudokuTableInBuffer(std::string msg);
    void SolvedSudokuTableInBuffer(std::string msg);
    void GetTimerInfo(int time);
    void ErrorMessage();
public slots:
    void TransferFromGUIToBuffer(std::string messageNum);
    void ServerIsClosed();
};

void UpServer(std::vector<boost::thread*>& threads_array, boost::thread_group& threads, Server* serv);

#endif // NETWORK_H

