// Client is single threaded, but multiple clients can connect to the server

// Problem: not able to connect differnt threads of same client to the server as individual connection without different sockfd

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>
#include <vector>
#include <thread>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc<2){
		cout << "Input format: ./client csvFileName" << endl;
		exit(-1);
	}
	
	char *filename=argv[1];
	struct sockaddr_in serv_addr;	
	int sockfd;
	

	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	cout << "scoket Id : " << sockfd << endl;
	
	// populating server address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1250);     
	serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);

	int reply=connect(sockfd, (struct sockaddr*) &serv_addr, sizeof serv_addr); // for client
	if(reply==-1){	
		cout << "Server is not available, exiting" << endl;
		exit(-1);
	}
	else
		cout << " Connected to server " << endl;


	// Read file contents in memory
        ifstream myfile(filename);
        vector<string> lines;
        string line;
        int nlines = 0;
        while(getline(myfile,line)) {
            lines.push_back(line);
            nlines++;
        }

	// shoot the file content
	string msg;

	for(int i=0; i<lines.size();i++){
		usleep(1000000); 
		msg = lines[i];
		send(sockfd, msg.c_str(), msg.size(),0);			// sending the msg
		cout << "byte sent: " << msg.size() << ", msg send: " << msg << endl;
		char buffer[512]={};
		int byte=recv(sockfd, buffer,sizeof buffer ,0);		// waiting for the acknoledgement
		cout << "byte received: " << byte << ", msg received: " << buffer << endl;
	}
	cout << "FILE COMPLETE" <<endl;

	while(1) {
	}
	return 0;	
}
