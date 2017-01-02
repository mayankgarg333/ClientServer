#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>


#include "Client.h"

using namespace std;

Client::Client(){

}


void Client::Handle_session(string filename){
	int reply=this->Connect_to_server();
	cout<< reply << endl;
	if(reply==-1){	
		cout << "Server is not available, exiting" << endl;
		exit(-1);
	}
	else{
		cout << "Connected to server" <<endl;
	}
	
	
	// start reading msg to send to server
	string msg;		
	while(1)
	{
		cout << "Enter the msg to pass: " <<endl;
		cin >> msg;
		send(this->sockfd, msg.c_str(), msg.size(),0);			// sending the msg
		char buffer[512]={};
		int byte=recv(this->sockfd, buffer,sizeof buffer ,0);		// waiting for the acknoledgement
		cout << "byte received: " << byte << ", msg received " << buffer << endl;
	}
}



