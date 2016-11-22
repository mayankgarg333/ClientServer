#include <iostream>
#include <string>
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
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1250);     
	serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);
	int reply=connect(sockfd, (struct sockaddr*) &serv_addr, sizeof serv_addr); // for client
	cout<< reply << endl;
	// call a thread to execute a function that will communicate with the server. 
	string msg;		
	while(1)
	{
		cout << "Enter the msg to pass: " <<endl;
		cin >> msg;
		send(sockfd, msg.c_str(), msg.size(),0);
	}
	return 0;
}


