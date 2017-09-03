#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>

class Client {
public:
    Client(){std::cout << this << "\n" << std::flush;};
    char inBuffer();
    bool isEmpty();
    void outBuffer(char c);
    void run();
private:
    void clientconnect(struct addrinfo hints, struct addrinfo* res, int& sockfd);
    static void receive_server(int server_sockfd, Client* client);
    static void send_server(int server_sockfd, Client* client);
    std::queue<char> INbuffer;
    std::queue<char> OUTbuffer;
};

#endif