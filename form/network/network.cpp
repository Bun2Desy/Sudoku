/**
 * \file network.cpp
 * The file for making networking connection between two clients
 */

#include "network.h"
#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

boost::recursive_mutex cs;

/**
 * Load message to writing buffer
 *
 * \param[in]  messageNum  message
 */
void Client::TransferFromGUIToBuffer(std::string messageNum)
{
    msg_ans = messageNum;
}

/**
 * Send a message
 */
void Client::SendMessage()
{
    while (!gameIsEnd) {
        if(msg_ans != ""){
            socket.write_some(boost::asio::buffer(msg_ans));
            msg_ans = "";
        }
    }
    //std::cout << "Thread 1 finish" << std::endl;
}

/**
 * Read a message
 */
void Client::ReadMessage() 
{
    while (true) {
        char msg[1024];
        int bytes = socket.read_some(boost::asio::buffer(msg));
        std::string num(msg, bytes);
        if(num[0] == 't'){
            if(num.length() > 5){
                num = num.substr(num.find(".") + 1);
                emit SudokuTableInBuffer(num);
            } else{
                num = num.substr(1);
                emit GetTimerInfo(std::stoi(num));
            }
        } else if(num.length() == 3){
            emit UpdateSomeData(num);
        } else if(num[0] == 'e'){
            gameIsEnd = true;
            break;
        } else{
            emit SudokuTableInBuffer(num);
        }
    }
    //std::cout << "Thread 2 finish" << std::endl;
}

/**
 * Set server in state for read and write in buffer 
 */
void Server::SimpleServer()
{
    while (true) {
        bool exitFromLoop = false;
        for (int i = 0; i < sessions.size(); i++) {
            if (sessions[i]->sock_.available()) {
                boost::recursive_mutex::scoped_lock lk(cs);
                int bytes = sessions[i]->sock_.read_some(boost::asio::buffer(sessions[i]->buff_));
                std::string ans_string(sessions[i]->buff_, bytes);
                if(ans_string == "end"){
                    sessions[0]->sock_.write_some(boost::asio::buffer("end"));
                    if(playerMode == 2)
                        sessions[1]->sock_.write_some(boost::asio::buffer("end"));
                    exitFromLoop = true;
                    break;
                }
                if(playerMode == 2){
                    if(i == 1)
                        sessions[0]->sock_.write_some(boost::asio::buffer(ans_string));
                    else
                        sessions[1]->sock_.write_some(boost::asio::buffer(ans_string));
                }
            }
        }
        if(exitFromLoop)
            break;
    }
    //std::cout << "Thread 3 finish" << std::endl;
}

/**
 * Set server to state for accept clients
 */
void Server::DoAccept() 
{
    // std::cout << "Start server accept" << std::endl;
    boost::shared_ptr<Session> client1{ new Session(io_server) };
    boost::shared_ptr<Session> client2{ new Session(io_server) };
    acceptor.accept(client1->sock_);
    if(playerMode == 2)
        acceptor.accept(client2->sock_);
    boost::recursive_mutex::scoped_lock lk(cs);
    sessions.push_back(client1);
    if(playerMode == 2){
        sessions.push_back(client2);
        emit SecondClientConnect();
    }
    //std::cout << "Thread 4 finish" << std::endl;
}

/**
 * Create server threads
 *
 * \param[in]      threads_array  threads array
 * \param[in]      threads        group of threads
 * \param[in]      serv           server object pointer
 */
void UpServer(std::vector<boost::thread*>& threads_array, boost::thread_group& threads, Server* serv) 
{
    threads_array.push_back(threads.create_thread(boost::bind(&Server::DoAccept, serv)));
    threads_array.push_back(threads.create_thread(boost::bind(&Server::SimpleServer, serv)));
}

/**
 * Client connection
 *
 * \param[in]      threads_array  threads array
 * \param[in]      threads        group of threads
 * \param[in]  address        ipv4 address for connect
 */
void Client::ConnectClient(std::vector<boost::thread*>& threads_array, boost::thread_group& threads, std::string address = "127.0.0.1") 
{
    tcp::endpoint ep{boost::asio::ip::address::from_string(address), 8001};
    socket.connect(ep);
    // std::cout << "Connect!" << std::endl;
    threads_array.push_back(threads.create_thread(boost::bind(&Client::ReadMessage, this)));
    threads_array.push_back(threads.create_thread(boost::bind(&Client::SendMessage, this)));
}

/**
 * Set state of connection to close
 */
void Client::ServerIsClosed()
{
    gameIsEnd = true;
}

