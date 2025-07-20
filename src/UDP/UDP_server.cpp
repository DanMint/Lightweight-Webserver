#include <iostream>

#include "../../include/server.h"

Server::Server() : serverSocket(nullptr), clientSocket(nullptr), serverAddr(nullptr), clientAddr(nullptr), clientLen(nullptr) {
    Server::initializeServer();
}

void Server::initializeServer() {
    serverSocket = new int();
    serverAddr = new sockaddr_in();
    clientAddr = new sockaddr_in();

    // creates socket for UDP using 0 (letting the program determine that its UDP)
    *serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (*serverSocket == -1) {
        std::cerr << "Socket not intialized" << std::endl;
        std::exit(1);
    }

    // using IPV4
    serverAddr->sin_family = AF_INET;
    // binds an avilable net interface
    serverAddr->sin_addr.s_addr = INADDR_ANY;
    // sets a listeing port
    serverAddr->sin_port = htons(800);

    // bind socket
    if (bind(*serverSocket, (sockaddr*)serverAddr, sizeof(*serverAddr)) < 0) {
        std::cerr << "Binding failed" << std::endl;
        std::exit(1);
    }

    Server::startServer();
}

void Server::startServer() {
    std::cout << "UDP Server is up and waiting for data" << std::endl;

    char buffer[1024] = {0};
    socklen_t len = sizeof(*clientAddr);
    int bytesReceived = recvfrom(*serverSocket, buffer, sizeof(buffer) - 1, 0, (sockaddr*)clientAddr, &len);

    if (bytesReceived < 0) 
        std::cerr << "Failed to recieve data" << std::endl;
    else {
        buffer[bytesReceived] = '\0'; 

        std::cout << "Received from "
                  << inet_ntoa(clientAddr->sin_addr) << ":"
                  << ntohs(clientAddr->sin_port) << " → "
                  << buffer << std::endl;

        const char* response = "Message received!";
        sendto(*serverSocket, response, strlen(response), 0,
               (sockaddr*)clientAddr, len);
    }

    close(*serverSocket);
}