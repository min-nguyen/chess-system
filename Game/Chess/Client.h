#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>

enum class ClientState{
    Waiting, Connected, Hosting, Playing
};

enum class ServerMessage{
    NameRequest = '1',
    ConnectionConfirmed = '2',
    NewHostRoom = '3',
    GameEstablished = '4'
};

class Client {
public:
    Client(): connected(false){
        std::cout << this << "\n" << std::flush;
    };
    char inBuffer();
    void outBuffer(char c);
    bool isEmpty(); 
    bool isConnected();
    void run();
    ClientState clientState = ClientState::Waiting;
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