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

void log_client(int sockfd_clients[BACKLOG], int sockfd_newclient){
	for(int i = 0; i < BACKLOG; i++){
		if(!sockfd_clients[i]){
			sockfd_clients[i] = sockfd_newclient;
			return;
		}
	}
}

//Create addrinfo and initialise 'res' and bind 'sockfd_listener'
int initialiselistener(struct addrinfo hints, struct addrinfo* res, int* sockfd_listener){
	int err_status, optval = 1;
	//Set res to point to server addrinfo
	if ((err_status = getaddrinfo(NULL, MY_PORT, &hints, &res ) != 0)) {
		fprintf(stderr, "listener creation failed: %s\n", gai_strerror(err_status));
		return 2;
	}
	//Create sockfd for the server
	*sockfd_listener = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	setsockopt(*sockfd_listener, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	//Bind the server's sockfd to the server's addrinfo
	if ((err_status = bind(*sockfd_listener, res->ai_addr, res->ai_addrlen)) < 0){
		perror("Server - bind() failed");
		exit(EXIT_FAILURE);
	}
	//Set server to listen on that sockfd
	listen(*sockfd_listener, BACKLOG);
	std::cout << "Waiting for connection\n";
}

void receive_client(int client_sockfd, char* buffer){
	if ( (recv(client_sockfd, buffer, BUF_LEN, 0)) < 0){
		perror("Server - recv failed\n");
		exit(EXIT_FAILURE);
	}
}

//Pass everything by reference
void accept_client(	int* client_sockfd,
										int* server_sockfd,
										struct sockaddr_storage* client_addresses,
										socklen_t* addr_size){
	if ( (*client_sockfd =	accept(*server_sockfd,
																(struct sockaddr*) 	&(*client_addresses),
																 										&(*addr_size))) < 0){
		perror("Server - accepting client failed\n");
		exit(EXIT_FAILURE);
	}
	std::cout << "New client connected with sockfd " << *client_sockfd << "\n";
}

void dos(int& y){

}

int main(int argc, char *argv[])
{
	struct addrinfo hints, *addrinfo_server;	//hints = specifications,	res = addrinfo pointer
	struct sockaddr_storage client_addresses;
	socklen_t addr_size = sizeof client_addresses;
	int sockfd_server;;	//Points to socket descriptor
	int sockfd_clients[BACKLOG];
	char buffer[BUF_LEN];
	// Initialise addrinfo restrictions
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	// Set up server
	initialiselistener(hints, addrinfo_server, &sockfd_server);
	printhostname();

	// Allocate empty peer fields for future storage of connected clients
	struct sockaddr* 	client_sockaddr = (struct sockaddr*) malloc(sizeof(struct sockaddr));
	uint* 						client_addrlen 	= (uint*) malloc(sizeof(uint));
	int								client_sockfd		= -1;
	std::cout << "storage mem #1 : " << &client_addresses << "\n";
	while(1){
		//Accept using listener sockfd and set socketfd for new client
		accept_client(&client_sockfd, &sockfd_server, &client_addresses, &addr_size);
		//Get struct sockaddr and int addrlen of the client with the corresponding socket descriptor
		getpeername(client_sockfd, client_sockaddr, client_addrlen);
		printpeerinfo(client_sockaddr, client_addrlen);
		//Keep track of client sockfd
		log_client(sockfd_clients, client_sockfd);
		//Receive
		receive_client(client_sockfd, buffer);
		printf("Message: %s \n", buffer);
	}
	return 0;
}
