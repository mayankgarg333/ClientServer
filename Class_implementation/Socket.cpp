#include<iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>



#include "Socket.h"

using namespace std;

Socket::Socket(){
	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(1255);     
	socket_addr.sin_addr.s_addr = INADDR_ANY;
	memset(socket_addr.sin_zero, '\0', sizeof socket_addr.sin_zero);

}

int Socket::Accept_connection(){
	bind(sockfd, (struct sockaddr *)&socket_addr, sizeof socket_addr);
	listen(sockfd,10);
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	addr_size=sizeof their_addr;
	// for loop around it later
	int new_fd=accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
	return new_fd;
}

int Socket::Connect_to_server(){
	return connect(this->sockfd, (struct sockaddr*) &socket_addr, sizeof socket_addr); 
}	
