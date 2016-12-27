#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>


using namespace std;


int main()
{
	int sockfd;
	struct sockaddr_in my_addr;	
    struct sockaddr_storage their_addr;
	socklen_t addr_size;
	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	cout << "scoket Id : " << sockfd << endl;
	
	// populating server own attributes
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(1250);     
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);
	// server binded to the socket and listen for any incoming msg. 
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);
	listen(sockfd,10);	

	// server will accept the new connection on the assigned port it is listening, 
	// and a new connection descriptor will be issue for that connection. 
	// thus it is possible to listen from multiple clients.

	addr_size=sizeof their_addr;
	int new_fd=accept(sockfd, (struct sockaddr *)&their_addr, &addr_size); // return a new socket descriptor

	while(1){
		char buffer[512]={};
		int byte=recv(new_fd, buffer,sizeof buffer ,0); // Wait to receive the msg
		buffer[byte]='\0';
		cout << "byte received: " << byte << ", msg received " << buffer << endl; // display the msg
		
		send(new_fd, buffer, byte ,0); // send acknowledgment
		if(byte==0)
		{
			cout << "Client connection terminated" << endl;
			break;
		}
	}
	return 0;
}


