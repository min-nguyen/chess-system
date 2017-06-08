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

void viewpeerinfo(struct sockaddr* peer_sockaddr, uint* peer_addrlen){
	void *addr, *port;
	char* ipver;
	if (peer_sockaddr->sa_family == AF_INET) { // IPv4
        struct sockaddr_in *ipv4_socket = (struct sockaddr_in *) peer_sockaddr;
        addr = &(ipv4_socket->sin_addr);
        ipver = (char*) "IPv4";
				port = &(ipv4_socket->sin_port);
  }
	else { // IPv6
        struct sockaddr_in6 *ipv6_socket = (struct sockaddr_in6 *) peer_sockaddr;
        addr = &(ipv6_socket->sin6_addr);
        ipver = (char*) "IPv6";
				port = &(ipv6_socket->sin6_port);
  }
	std::cout << addr << " " << ipver << " " << port << "\n";
}

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

	struct sockaddr* peer_sockaddr;
	uint* peer_addrlen;
	while(1){
		accept(*sockfd_listener, (struct sockaddr*) &client_addresses, (socklen_t*) sizeof(struct sockaddr_storage));

		std::cout << "New client connected\n";
		getpeername(*sockfd_listener, peer_sockaddr, peer_addrlen);
	//	viewpeerinfo(peer_sockaddr, peer_addrlen);


		recv(*sockfd_listener, buffer, BUF_LEN, 0);
	}
	return 0;
}
