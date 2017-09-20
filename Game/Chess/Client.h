#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>

enum class ClientState{
    Connected, Hosting, Playing
};

class Client {
public:
    Client(): connected(false){
        std::cout << this << "\n" << std::flush;
    };
    char inBuffer();
    bool isEmpty(); 
    bool isConnected();
    void outBuffer(char c);
    void run();
private:
    bool connected;
    std::vector<int> rooms;
    void clientconnect(struct addrinfo hints, struct addrinfo* res, int& sockfd);
    static void receive_server(int server_sockfd, Client* client);
    static void send_server(int server_sockfd, Client* client);
    std::queue<char> INbuffer;
    std::queue<char> OUTbuffer;
};

#endif