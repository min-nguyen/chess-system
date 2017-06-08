#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

#define SERVER_PORT "4006"
#define BACKLOG 10

//Create client & get server socket
void clientconnect(struct addrinfo hints, struct addrinfo* res, int* sockfd){
  int err_status;
	if ((err_status = getaddrinfo("192.168.0.3", SERVER_PORT, &hints, &res ) != 0)) {
		fprintf(stderr, "listener creation failed: %s\n", gai_strerror(err_status));
		exit(EXIT_FAILURE);
	}
  *sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if((err_status = connect(*sockfd, res->ai_addr, res->ai_addrlen)) < 0){
    perror("Connection failed\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[])
{
	struct addrinfo hints, *res;	//hints = specifications,	res = addrinfo pointer
  int* sockfd = (int*) malloc(sizeof(int));
	// Initialise addrinfo restrictions
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

  clientconnect(hints, res, sockfd);

  char* message = (char*) "hi";
  send(*sockfd, &message, (int) sizeof(message), 0);

	return 0;
}
