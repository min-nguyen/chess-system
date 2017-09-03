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

	return 1;
}

int receive_client(int client_sockfd, char* buffer){
	int n = recv(client_sockfd, buffer, BUF_LEN, 0);
	switch(n){
		case (-1) : perror("Server - recv failed\n");
								exit(EXIT_FAILURE);
								break;
	  	case (0)	: return 0;
		default		: return 1;
	}
}

//Pass everything by reference
void accept_client(	int* client_sockfd,
					int* server_sockfd,
					struct sockaddr_storage* client_addresses,
					socklen_t* addr_size){
	if ( (*client_sockfd =	accept(*server_sockfd, (struct sockaddr*) &(*client_addresses), &(*addr_size))) < 0){
		perror("Server - accepting client failed\n");
		exit(EXIT_FAILURE);
	}
	std::cout << "New client connected with sockfd " << *client_sockfd << "\n";
}

void request_clientname(std::map<int, std::string> client_names, int sockfd_client){
	send(sockfd_client, "Please enter your name", sizeof("Please enter your name"), 0);
}

void fd_pair_match(std::map<int, int>& fd_pairings, std::map<int, int>& fd_reversed, int client_fd){
	std::map<int,int>::iterator it;
	it = fd_pairings.find(-1);
	if(it == fd_pairings.end()){
		fd_pairings.insert(std::pair<int, int>(-1, client_fd));
		printf("Client with fd %d is waiting for an opponent\n", client_fd);
	}
	else{
		int second = it->second;
		fd_pairings.insert(std::pair<int, int>(second, client_fd));
		fd_reversed.insert(std::pair<int, int>(client_fd, second));
		printf("Successful pair matching between %d and %d\n", second, client_fd);
	}
}

void fd_pair_send(std::map<int, int>& fd_pairings, std::map<int, int>& fd_reversed, int client_fd, std::string strng){
	std::map<int,int>::iterator it;
	it = fd_pairings.find(client_fd);
	printf("sending from %d \n", client_fd);
	if(it != fd_pairings.end()){
		send(it->second, strng.c_str(), strlen(strng.c_str()) + 1, 0);
		printf("Sending\n");
	}
	else {
		it = fd_reversed.find(client_fd);
		if(it != fd_reversed.end()){
			send(it->second, strng.c_str(), strlen(strng.c_str()) + 1, 0);
			printf("Sending\n");
		}
	}
}

void fd_pair_disconnect(std::map<int, int>& fd_pairings, std::map<int, int>& fd_reversed, fd_set& connections_fd, int client_fd){
	std::map<int,int>::iterator it;
	it = fd_pairings.find(client_fd);
	close(client_fd);
	FD_CLR(client_fd, &connections_fd);
	//Found client fd in key of fd_pairings
	if(it != fd_pairings.end()){
		int second = it->second;
		fd_pairings.erase(it);
		fd_reversed.erase(second);
	}
	else {
		//Found client fd in value of unmatched fd_pairings
		it = fd_pairings.find(-1);
		if(it != fd_pairings.end()){
			fd_pairings.erase(it);
		}
		//Found client fd in key of fd_reversed pairings
		else{
			it = fd_reversed.find(client_fd);
			if(it != fd_reversed.end()){
				int second = it->second;
				fd_reversed.erase(it);
				fd_pairings.erase(second);
			}
		}
	}
	
}

int main(int argc, char *argv[])
{
	// Create file descriptor sets, one for reading and one for updating the next read
	fd_set connections_fd, reads_fd;
	int max_fd;

	// Client storage
	std::map<int, std::string> client_names;
	std::map<int, int> fd_pairings;
	std::map<int, int> fd_reversed;
	struct sockaddr_storage client_addresses;
	socklen_t addr_size = sizeof client_addresses;

	// Server variables
	struct addrinfo hints, *addrinfo_server;
	int sockfd_server;	//Points to socket descriptor
	char* buffer = (char*) malloc(sizeof(char));

	// Initialise addrinfo restrictions
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	// Set up server
	initialiselistener(hints, addrinfo_server, &sockfd_server);
	FD_ZERO(&connections_fd);
	FD_ZERO(&reads_fd);
	// Add server file descriptor to fd set
	FD_SET(sockfd_server, &connections_fd);
	max_fd = sockfd_server;
	printhostname();

	// Allocate empty peer fields for temporary storage of connected clients
	struct sockaddr* 	client_sockaddr = (struct sockaddr*) malloc(sizeof(struct sockaddr));
	uint* 						client_addrlen 	= (uint*) malloc(sizeof(uint));
	int								client_sockfd		= -1;

	while(1){
		reads_fd = connections_fd;
		//Updates 'reads_fd' to indicate which socket file descriptors are ready to read
		if (select(max_fd + 1, &reads_fd, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
    	}
		//Iterate through client filedescriptors (ws connections)
		for(int i = 0; i < max_fd + 1; i++){
				//Server file descriptor (ws) receives new I/O operation
				if(FD_ISSET(i, &reads_fd)){
					//Fd for Server listener receives ws request
					if (i == sockfd_server){
						accept_client(&client_sockfd, &sockfd_server, &client_addresses, &addr_size);
						FD_SET(client_sockfd, &connections_fd);
						max_fd = (max_fd < client_sockfd) ? client_sockfd : max_fd;
						send(client_sockfd, "0: Please enter your name\n", sizeof("Please enter your name\n"), 0);
					}
					else{
						//Client closed ws
						if(!receive_client(i, buffer)){
							std::cout << "0: Disconnected : " + client_names[i] << std::flush;
							fd_pair_disconnect(fd_pairings, fd_reversed, connections_fd, i);
						}
						//Fd corresponding to client receives new I/O operation
						else{
							std::string strng(buffer);
							fd_pair_match(fd_pairings, fd_reversed, i);
							if(client_names.find(i) == client_names.end()){
								strng = "0: New client : " + strng + "\n";
								client_names[i] = buffer;
							}
							fd_pair_send(fd_pairings, fd_reversed, i, strng);
							printf("%s", strng.c_str());
							memset(buffer, 0, 50*sizeof(char));
						}
					}
				}
			}
	}
	return 0;
}





























//
