#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

class Server {
public:
    Server(){}
    void printhostname();
    void printpeerinfo(struct sockaddr* peer_sockaddr, uint* peer_addrlen);
    int initialiselistener(struct addrinfo hints, struct addrinfo* res, int* sockfd_listener);
    int receive_client(int client_sockfd, char* buffer);
    void accept_client(	int* client_sockfd,
        int* server_sockfd,
        struct sockaddr_storage* client_addresses,
        socklen_t* addr_size);
    void request_clientname(std::map<int, std::string> client_names, int sockfd_client);
    void run();
};