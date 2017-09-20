#ifndef SERVER_H
#define SERVER_H 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>

enum class ServerMessage{
    NameRequest = '1',
    ConnectionConfirmed = '2',
    NewHostRoom = '3',
    GameEstablished = '4'
};

enum class ClientMessage{
    NameReceive = '0',
    RoomRequest = '1',
    RoomConnect = '2'
};

enum class PlayerState{
    InLobby, Hosting, Playing
};

class Player {
public:
    Player(int t_fd, std::string t_name): fd(t_fd), name(t_name){};
    int fd, opponent_fd = -1;
    std::string name;
    PlayerState state = PlayerState::InLobby;
};



#endif