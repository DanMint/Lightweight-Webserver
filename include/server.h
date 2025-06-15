#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


class Server {
    public:
        
        Server();

        void initializeServer();

        void startServer();

        ~Server();

    private:
        // Server listening socket
        int *serverSocket;
        // Client created socket
        int *clientSocket;
        // Holds IP + port where server will listen
        sockaddr_in *serverAddr;
        // Clients Info
        sockaddr_in *clientAddr;
        // Stores clients 
        socklen_t *clientLen;

};

#endif