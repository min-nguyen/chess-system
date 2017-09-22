#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <vector>
#include <queue>

enum class ClientState{
    Waiting, 
    Connected, 
    HostAttempt, Hosting, 
    PlayAttempt, PlayingAsHost, PlayingAsOpponent
};

enum class ServerMessage{
    NameRequest = '0',
    ConnectionConfirmed = '1',
    NewHostRoom = '2',
    GameEstablished = '3'
};

enum class ClientMessage{
    NameReceive = '0',
    RoomRequest = '1',
    RoomConnect = '2'
};

class Client {
public:
    Client(): clientState(ClientState::Waiting){};
    void run();
    //Client attributes
    std::string clientName;
    ClientState clientState;
    //Update client state from client request
    void updateState(std::string message);
    //Send game move - called from game api
    void pushGameMove(sf::Vector2i mousePosition);
    //Returns any new created rooms
    std::string lobbyRoomUpdate();  
    //Returns any new opponent moves
    sf::Vector2i gameMoveUpdate();
    //Returns any new opponent moves
    bool gameMovesOutExists(); 
    bool gameMovesInExists(); 
private:
    //Initialise server connection
    void clientconnect(struct addrinfo hints, struct addrinfo* res, int& sockfd);
    //Parse vector move from server message
    static sf::Vector2i extractVector2i(std::string position);
    //Threads for lobby/game communication
    static void receive_server_lobby(int server_sockfd, Client* client);
    static void receive_server_game(int server_sockfd, Client* client);
    static void send_server_lobby(int server_sockfd, Client* client);
    static void send_server_game(int server_sockfd, Client* client);
    //Game moves sent to and from server
    std::queue<std::string> gameMovesIn;
    std::queue<sf::Vector2i> gameMovesOut;
    //New game rooms from server
    std::queue<std::string> lobbyRooms;
};

#endif