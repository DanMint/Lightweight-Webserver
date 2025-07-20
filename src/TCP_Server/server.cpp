#include <iostream>

#include "../../include/server.h"

Server::Server() : serverSocket(nullptr), clientSocket(nullptr), serverAddr(nullptr), clientAddr(nullptr), clientLen(nullptr) {
    Server::initializeServer();
}

void Server::initializeServer() {
    serverSocket = new int();
    clientSocket = new int();
    serverAddr = new sockaddr_in();
    clientAddr = new sockaddr_in();

    *serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (*serverSocket == -1) {
        std::cerr << "Socket not initialized" << std::endl;
        std::exit(1);
    }

    // using IPV4
    serverAddr->sin_family = AF_INET;
    // binds an avilable net interface
    serverAddr->sin_addr.s_addr = INADDR_ANY;
    // sets a listening port
    serverAddr->sin_port = htons(800);

    // bind socket
    if (bind(*serverSocket, (sockaddr*)serverAddr, sizeof(*serverAddr)) < 0) {
        std::cerr << "Binding failed" << std::endl;
        std::exit(1);
    }

    Server::startServer();
}

void Server::startServer() {
    socklen_t clientLen = sizeof(*clientAddr);  

    if (listen(*serverSocket, 5) < 0) {
        std::cerr << "Listen failed" << std::endl;
        std::exit(1);
    }

    std::cout << "Server listening for connection" << std::endl;

    *clientSocket = accept(*serverSocket, (sockaddr*)clientAddr, &clientLen);
    if (*clientSocket < 0) {
        std::cerr << "Accept Failed" << std::endl;
        std::exit(1);
    }

    std::cout << "Client Connected" << std::endl;

    char buffer[1024] = {0};
    int bytes_read = read(*clientSocket, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) 
        std::cout << "Received:\n" << buffer << "\n";

    close(*clientSocket);
    close(*serverSocket);
}

Server::~Server() {
    delete serverSocket;
    delete clientSocket;
    delete serverAddr;
    delete clientAddr;
}
