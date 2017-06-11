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

#define SERVER_PORT "4006"
#define SERVER_IP "127.0.0.1"
#define BACKLOG 10
#define BUF_LEN (2 << 16)
//Create client & get server socket
void clientconnect(struct addrinfo hints, struct addrinfo* res, int& sockfd){
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

int receive_server(int& server_sockfd, char* buffer){

	int n = recv(server_sockfd, buffer, BUF_LEN, 0) ;
  printf("%s \n", buffer);
	switch(n){
		case (-1) : perror("Client - recv failed\n");
								exit(EXIT_FAILURE);
								break;
	  case (0)	: return 0;
		default		: return 1;
	}
}

int main(int argc, char *argv[])
{
	struct addrinfo hints, *server_addrinfo;	//hints = specifications,	res = addrinfo pointer
  int server_sockfd;

  char buffer[50];
	// Initialise addrinfo restrictions
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

  clientconnect(hints, server_addrinfo, server_sockfd);
  printf("connected to port %s at ip %s\n", SERVER_PORT, SERVER_IP);
  std::string msgstr;
  char msg[50];
  while(1){
    receive_server(server_sockfd, buffer);
    printf("server sock fd : %d\n", server_sockfd);
    std::getline(std::cin, msgstr);
    strcpy(msg, msgstr.c_str());
    send(server_sockfd, msg, (int) sizeof(msg), 0);
    printf("sent\n");
  }
	return 0;
}
