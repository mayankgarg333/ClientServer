//client_1.cpp takes manual input
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;


int main()
{
	int sockfd;
	struct sockaddr_in serv_addr;	

	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	cout << "scoket Id : " << sockfd << endl;
	
	// populating server address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1250);     
	serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);


	int reply=connect(sockfd, (struct sockaddr*) &serv_addr, sizeof serv_addr); // for client
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
		send(sockfd, msg.c_str(), msg.size(),0);			// sending the msg
		char buffer[512]={};
		int byte=recv(sockfd, buffer,sizeof buffer ,0);		// waiting for the acknoledgement
		cout << "byte received: " << byte << ", msg received " << buffer << endl;
	}
	return 0;	
}


