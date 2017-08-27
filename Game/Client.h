#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Client {
private:
    Client(){};
    void clientconnect(struct addrinfo hints, struct addrinfo* res, int& sockfd);
    static void receive_server(int server_sockfd, Client* client);
    static void send_server(int server_sockfd, Client* client);
    void run();
    void checkBuffer();
    char buffer[50];
};