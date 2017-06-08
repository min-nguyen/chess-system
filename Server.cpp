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

#define MY_PORT "4006"
#define BACKLOG 10
#define BUF_LEN (2 << 8)

//Create addrinfo and initialise 'res' and bind 'sockfd_listener'
int createlistener(struct addrinfo hints, struct addrinfo* res, int* sockfd_listener){
	int err_status, optval = 1;
	if ((err_status = getaddrinfo(NULL, MY_PORT, &hints, &res ) != 0)) {
		fprintf(stderr, "listener creation failed: %s\n", gai_strerror(err_status));
		return 2;
	}
	*sockfd_listener = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	setsockopt(*sockfd_listener, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if ((err_status = bind(*sockfd_listener, res->ai_addr, res->ai_addrlen)) < 0){
		perror("Server - bind() failed");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	struct addrinfo hints, *res;	//hints = specifications,	res = addrinfo pointer
	struct sockaddr_storage *client_addresses;
	int* sockfd_listener = (int*) malloc(sizeof(int));	//Points to socket descriptor
	void* buffer = malloc(BUF_LEN);
	//char ipstr[INET6_ADDRSTRLEN];

	// Initialise addrinfo restrictions
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	createlistener(hints, res, sockfd_listener);
	listen(*sockfd_listener, BACKLOG);


	while(1){
		accept(*sockfd_listener, (struct sockaddr*) &client_addresses, (socklen_t*) sizeof(struct sockaddr_storage));
		std::cout << "hi\n";
		std::cout << recv(*sockfd_listener, buffer, BUF_LEN, 0) << "\n";
	}
	return 0;
}
