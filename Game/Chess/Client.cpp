#include <stdio.h>
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
#include <iostream>
#include <vector>
#include "Client.h"

#define SERVER_PORT "4006"
#define SERVER_IP "127.0.0.1"
#define BACKLOG 10
#define BUF_LEN (2 << 16)

static volatile int semaphore = 1;

//Create client & get server socket
void Client::clientconnect(struct addrinfo hints, struct addrinfo* res, int& sockfd){
  int err_status;
	if ( ((err_status = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &res )) != 0)) {
		fprintf(stderr, "listener creation failed: %s\n", gai_strerror(err_status));
		exit(EXIT_FAILURE);
	}
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if( (err_status = connect(sockfd, res->ai_addr, res->ai_addrlen)) < 0){
    perror("Connection failed\n");
    exit(EXIT_FAILURE);
  }
}
//Send to all non-hosting & non-playing clients
//Confirm connection = 1#
//New room = 2#<host-name>#<host-fd>
//Playing = 3#<otherPlayersName>
void Client::receive_server(int server_sockfd, Client* client){
  char buffer[400]; 
  while(1){
  	int n = recv(server_sockfd, buffer, BUF_LEN, 0);
  	switch(n){
  		case (-1) : perror("Client - recv failed\n");
  								exit(EXIT_FAILURE);
  								break;
  	  case (0)	: perror("Client - Server disconnected");
                  return;
                  break;
      default		: char* flag = buffer;
                  std::string clientMessage(buffer);
                  printf("%s\n", buffer);
                  //Request name to be sent
                  if(*flag == '0'){
                    printf("Write your name in the console\n");
                  }
                  //Successful connection after name sent
                  else if(*flag == '1'){
                    if(client->clientState == ClientState::Waiting){
                      std::string clientName = clientMessage.erase(0, 2);
                      std::cout << "connected\n" << std::flush;
                      client->clientState = ClientState::Connected;
                      client->clientName = clientName;
                    }
                  }
                  else if(*flag == '2'){
                    std::string hostName = clientMessage.erase(0, 2);
                    std::cout << "Host name is " << hostName << std::flush;
                    //Confirmation of host room
                    if(client->clientState == ClientState::HostAttempt){
                      std::cout << "In host attempt: name is"  << client->clientName << std::flush;
                      if(hostName == client->clientName){
                        client->clientState = ClientState::Hosting;
                        std::cout << "Successfully hosting room\n" << std::flush;
                      }
                    }
                    //New host room
                    else {
                      std::cout << "New host room created\n" << std::flush;
                      client->lobbyRooms.push(hostName);
                    }
                  }
                  //Game established
                  else if(*flag == '3'){
                    if(client->clientState == ClientState::Hosting){
                      std::cout << "Game established as host\n" << std::flush;
                      client->clientState = ClientState::PlayingAsHost;
                    }
                    else if(client->clientState == ClientState::PlayAttempt){
                      std::cout << "Game established as opponent\n" << std::flush;
                      client->clientState = ClientState::PlayingAsOpponent;
                    }
                  }
                  else if((client->clientState == ClientState::PlayingAsHost) ||
                          (client->clientState == ClientState::PlayingAsOpponent)){
                      client->gameMoves.push(clientMessage);
                  }
                  memset(buffer, 0, 400*sizeof(char));
                  break;
  	}
  }
}



void Client::server_message(std::string message){
  if(message.substr(0,2) == "0#"){
    clientName = message.erase(0,2);
    printf("set new name\n");
  }
  else if (message.substr(0,2) == "1#"){
    clientState = ClientState::HostAttempt;
    printf("attempting to host\n");
  }
  else if (message.substr(0,2) == "2#"){
    clientState = ClientState::PlayAttempt;
    printf("attempting to play\n");
  }
  
}

void Client::server_sendName(){
  std::string name;
  std::getline(std::cin, name);
  INbuffer.push("0#" + name);
}

void Client::server_requestRoom(){
  INbuffer.push("1#");
  clientState = ClientState::HostAttempt;
}
void Client::server_connectRoom(std::string name){
  INbuffer.push("2#" + name);
  clientState = ClientState::PlayAttempt;
}

void Client::send_server(int server_sockfd, Client* client){
  //Lobby room
  while(client->clientState != ClientState::PlayingAsHost && 
        client->clientState != ClientState::PlayingAsOpponent ){
    std::string message;
    std::getline(std::cin, message);
    client->server_message(message);
    send(server_sockfd, message.c_str(), (int) sizeof(message.c_str()), 0);
  }
  //Game input
  while(1){
    if(!client->isEmpty()){
      std::string message = client->INbuffer.front();
      client->INbuffer.pop();
      send(server_sockfd, message.c_str(), (int) sizeof(message.c_str()), 0);
    }
  }
}

bool Client::isEmpty(){
  return INbuffer.empty();
}
std::string Client::gameMoveUpdate(){
  if(gameMoves.empty()){
    return "";
  }
  else {
    std::string move = gameMoves.front();
    gameMoves.pop();
    return move;
  }
}
std::string Client::lobbyRoomUpdate(){
  if(lobbyRooms.empty()){
    return "";
  }
  else {
    std::string message = lobbyRooms.front();
    lobbyRooms.pop();
    return message;
  }
}
 
void Client::run()
{
	struct addrinfo hints, *server_addrinfo;	//hints = specifications,	res = addrinfo pointer
  int server_sockfd;
  std::cout << this << "\n" << std::flush;

	// Initialise addrinfo restrictions
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

  clientconnect(hints, server_addrinfo, server_sockfd);
  printf("connected to port %s at ip %s\n", SERVER_PORT, SERVER_IP);

  //The arguments to the thread function are moved or copied by value.
  //If a reference argument needs to be passed to the thread function, it has to be wrapped (e.g. with std::ref or std::cref).

  std::thread receiver(receive_server, server_sockfd, this);
  std::thread sender(send_server, server_sockfd, this);

  receiver.join();
  sender.join();
}
