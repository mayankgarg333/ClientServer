
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "Socket.h"

using namespace std;


int main()
{
	Socket client;	
	cout << "scoket Id : "  << client.sockfd << endl;
	
	int reply=client.Connect_to_server();
	cout<< reply << endl;
	if(reply==-1){	
		cout << "Server is not available, exiting" << endl;
		exit(-1);
	}
	
	
	// start reading msg to send to server
	string msg;		
	while(1)
	{
		cout << "Enter the msg to pass: " <<endl;
		cin >> msg;
		send(client.sockfd, msg.c_str(), msg.size(),0);			// sending the msg
		char buffer[512]={};
		int byte=recv(client.sockfd, buffer,sizeof buffer ,0);		// waiting for the acknoledgement
		cout << "byte received: " << byte << ", msg received " << buffer << endl;
	}
	
	return 0;	
}

	
