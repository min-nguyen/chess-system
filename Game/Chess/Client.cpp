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

char** deserializeMap(char* buffer){
  char** ary = new char*[20];
  for(int i = 0; i < 20; ++i)
      ary[i] = new char[20];

	for(int i = 0; i < 20; i ++){
		for (int j = 0; j < 20; j++){
      ary[i][j] = *(buffer + (i*10) + j);
    }
  }
  return ary;
}

bool Client::mapQueueIsEmpty(){
  return mapQueue.empty();
}

char** Client::getMap(){
  if(!mapQueue.empty()){
    char** front = mapQueue.front();
    mapQueue.pop();
    return front;
  } 
}

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
      default		: char* check = buffer;
                  if(client->connected){
                      char** map = deserializeMap(check);
                      client->mapQueue.push(map);
                  }
                  //Server requires name
                  else if(*check == '0'){
                    printf("%s\n", buffer);
                  }
                  //Client matched with opponent
                  else if(*check == '1'){
                    std::cout << "connected\n" << std::flush;
                    client->connected = true;
                  }
                  //Server sent game output action
                  else{
                    for(int i = 20; i < 20; i++){
                      std::cout << buffer[i] << std::flush;
                    }
                  }
                  memset(buffer, 0, 400*sizeof(char));
                  break;
  	}
  }
}

bool Client::isConnected(){
  return connected;
}

void Client::send_server(int server_sockfd, Client* client){
  char msg[50];
  std::string msgstr; 
  //Write name
  std::getline(std::cin, msgstr);
  strcpy(msg, msgstr.c_str());
  send(server_sockfd, msg, (int) sizeof(msg), 0);
  //Game input
  while(1){
    if(!(client->OUTbuffer.empty())){
      char c = client->OUTbuffer.front();
      client->OUTbuffer.pop();
      send(server_sockfd, &c, sizeof(char), 0);

    }
  }
}

bool Client::isEmpty(){
  return INbuffer.empty();
}

char Client::inBuffer(){
  if(!INbuffer.empty()){
    char front = INbuffer.front();
    INbuffer.pop();
    return front;
  }
}

void Client::outBuffer(char c){
  OUTbuffer.push(c);
  std::cout << OUTbuffer.front() << std::flush;
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