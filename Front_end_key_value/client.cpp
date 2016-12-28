// KEY Value STORE

#include <iostream>
#include <sstream>
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
void client_handler(char *filename);


int main(int argc, char *argv[])
{
	if(argc<2){
		cout << "Input format: ./client csvFileName" << endl;
		exit(-1);
	}
	
	char *filename;
	
	

	for(int i=0; i<argc-1;i++)
		thread (client_handler,argv[i+1]).detach();

	while(1) {
	}
	return 0;	
}


void client_handler(char *filename) {
	int sockfd;
	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	cout << "scoket Id : " << sockfd << endl;
	
	thread::id this_id = this_thread::get_id();
	cout << "thread id : " << this_id <<" and sockfd " << sockfd << endl;
	
	// populating server address
	struct sockaddr_in serv_addr;	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1254);     
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
		msg = lines[i];
		// divide msg in get and put requests
		istringstream ss(msg);
		string token;
		vector <string> myvec;
		string action;


		while(getline(ss, token, ',')) {
		    myvec.push_back(token);
			//cout << "token " << token << endl;
		}
		
		action =myvec[0];

		// Issue the request		
	
		if(action=="GET")
		{
			send(sockfd, myvec[0].c_str(), myvec[0].size(),0);	
			myvec[1].pop_back();	// remove end line character		
			send(sockfd, myvec[1].c_str(), myvec[1].size(),0);
			char buffer[512]={};
			int b=recv(sockfd, buffer, sizeof buffer ,0);
			buffer[b]='\0';
			cout << "Key send: " << myvec[1] << " ,Value received: " << buffer << endl;
			usleep(400000);
		}

		else if(action=="PUT")
		{
			send(sockfd, myvec[0].c_str(), myvec[0].size() ,0);
			send(sockfd, myvec[1].c_str(), myvec[1].size() ,0);
			myvec[2].pop_back(); // remove end line character
			send(sockfd, myvec[2].c_str(), myvec[2].size() ,0);
			//char buffer[512]={};			// to check if put is successgful
			//recv(sockfd, buffer, sizeof buffer ,0);
		}
		
		else
		{
			cout << "Invalid KEY VALUE " << endl;
		}
		
		if(i%100==0)
			cout << i << endl;
	}
	cout << "FILE COMPLETE" <<endl;
}

