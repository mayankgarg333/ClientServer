#include <iostream>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Socket.h"

using namespace std;


int main()
{
	Socket server;	
	cout << "scoket Id : " << server.sockfd << endl;
	
	int new_fd=server.Accept_connection();	

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
	
