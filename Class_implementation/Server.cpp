#include<iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>


#include "Server.h"

using namespace std;

Server::Server(){

}


void Server::Handle_session(int new_fd){
	int byte=1;
	while(1){
		
		string r=this->Read(new_fd);
		this->Write(r,new_fd);

		if(byte==0)
		{
			cout << "Client connection terminated" << endl;
			break;
		}
	}
}
