#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>

enum class ClientState{
    Waiting, Connected, HostAttempt, Hosting, PlayAttempt, PlayingAsHost, PlayingAsOpponent
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
    Client(): clientState(ClientState::Waiting){
        std::cout << this << "\n" << std::flush;
    };
    void run();
    std::string clientName;
    ClientState clientState;
    //Messages to server - uses string buffer
    void server_message(std::string message);
    void server_sendName();
    void server_requestRoom();
    void server_connectRoom(std::string name);
    //Messages from server
    std::string lobbyRoomUpdate();  //Returns any new created rooms
    std::string gameMoveUpdate();
    bool isEmpty(); 
private:
    void clientconnect(struct addrinfo hints, struct addrinfo* res, int& sockfd);
    static void receive_server(int server_sockfd, Client* client);
    static void send_server(int server_sockfd, Client* client);
    //Messages towards server
    std::queue<std::string> INbuffer;
    //Messages from server
    std::queue<std::string> lobbyRooms;
    std::queue<std::string> gameMoves;
};

#endif