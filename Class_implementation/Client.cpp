#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdint.h>

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
		string reply;
		reply=this->Get_func(msg);
		cout << "msg received " << reply << endl;
	}
}



string Client::Get_func(string key){
		this->Write(key,this->sockfd);
		string r=this->Read(this->sockfd);
		return r;
}
