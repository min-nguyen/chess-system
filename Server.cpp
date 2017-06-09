#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>

#define MY_PORT "4006"
#define BACKLOG 10
#define BUF_LEN (2 << 16)

void printhostname(){
	char hostname[20];
	gethostname(hostname, 20);
	printf("Host name : %s\n\n", hostname);
}

void printpeerinfo(struct sockaddr* peer_sockaddr, uint* peer_addrlen){
	void *addr, *port;
	char* ipver;
	char ipstr[INET6_ADDRSTRLEN];

	if (peer_sockaddr->sa_family == AF_INET) { // IPv4
       struct sockaddr_in* ipv4_socket = (struct sockaddr_in*) peer_sockaddr;
       addr = &(ipv4_socket->sin_addr);
       ipver = (char*) "IPv4";
			 port = &(ipv4_socket->sin_port);
			 inet_ntop(AF_INET, addr, ipstr, INET_ADDRSTRLEN);
  }
	else { // IPv6
        struct sockaddr_in6 *ipv6_socket = (struct sockaddr_in6 *) peer_sockaddr;
        addr = &(ipv6_socket->sin6_addr);
        ipver = (char*) "IPv6";
				port = &(ipv6_socket->sin6_port);
				inet_ntop(AF_INET6, addr, ipstr, INET6_ADDRSTRLEN);
  }
	std::cout << "IP               IP protocol     Port       Address Length\n";
	std::cout << ipstr << " " << ipver << "        	 " << port << "  " << peer_addrlen << "\n";
}

void logclient(int sockfd_clients[BACKLOG], int sockfd_newclient){
	for(int i = 0; i < BACKLOG; i++){
		if(!sockfd_clients[i]){
			sockfd_clients[i] = sockfd_newclient;
			return;
		}
	}
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
	struct sockaddr_storage client_addresses;
	socklen_t addr_size;
	int* sockfd_listener = (int*) malloc(sizeof(int));	//Points to socket descriptor
	int sockfd_clients[BACKLOG];
	void* buffer = malloc(BUF_LEN);
	// Initialise addrinfo restrictions
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	// Set up server
	createlistener(hints, res, sockfd_listener);
	printhostname();

	// Set server to listening mode
	listen(*sockfd_listener, BACKLOG);
	std::cout << "Waiting for connection\n";

	// Allocate empty peer fields for future storage of connected clients
	struct sockaddr* 	peer_sockaddr = (struct sockaddr*) malloc(sizeof(struct sockaddr));
	uint* 						peer_addrlen 	= (uint*) malloc(sizeof(uint));
	int								peer_sockfd		= -1;

	while(1){
		//Accept using listener sockfd and set socketfd for new client
		addr_size = sizeof client_addresses;
		if ( (peer_sockfd =	accept(*sockfd_listener, (struct sockaddr*) &client_addresses,
																	&addr_size)) < 0){
			perror("Server - accepting client failed\n");
			exit(EXIT_FAILURE);
		}

		std::cout << "New client connected with sockfd " << peer_sockfd << " \n";

		//Get struct sockaddr and int addrlen of the client with the corresponding socket descriptor
		getpeername(peer_sockfd, peer_sockaddr, peer_addrlen);
		//Keep track of client sockfd
		logclient(sockfd_clients, peer_sockfd);
		//Print
		printpeerinfo(peer_sockaddr, peer_addrlen);

		//Receive
		if ( (recv(peer_sockfd, buffer, BUF_LEN, 0)) < 0){
			perror("Server - recv failed\n");
			exit(EXIT_FAILURE);
		}
	//	std::cout << "buffer size : " << TEMP_FAILURE_RETRY(recv(peer_sockfd, buffer, BUF_LEN, 0)) << "\n";
		std::cout << "message : " << *((char*) buffer) << "\n";
	}
	return 0;
}
