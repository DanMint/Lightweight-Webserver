#include <iostream>
#include <cstdlib>

#include "../include/server.h"

Server::Server() : serverSocket(nullptr), clientSocket(nullptr), serverAddr(nullptr), clientAddr(nullptr), clientLen(nullptr) { Server::initializeServer(); }

void Server::initializeServer() {
    serverSocket = new int();
    clientSocket = new int();
    serverAddr = new sockaddr_in();
    clientAddr = new sockaddr_in();
    
    *serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (*serverSocket == -1) {
        std::cerr << "Socket not intialized" << std::endl;
        std::exit(1);
    }

    serverAddr->sin_family = AF_INET;
    serverAddr->sin_addr.s_addr = INADDR_ANY;
    serverAddr->sin_port = htons(800);
    if (bind(*serverSocket, (sockaddr*)serverAddr, sizeof(*serverAddr)) < 0) {
        std::cerr << "Binding failed" << std::endl;
        std::exit(1);
    }

    Server::startServer();
}

void Server::startServer() {

}

Server::~Server() {
    delete serverSocket;
    delete clientSocket;
    delete serverAddr;
    delte cle
}