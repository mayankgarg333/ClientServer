#include <iostream>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

#include "Server.h"

using namespace std;

void handle_server_Session(Server* server, int new_fd);
int main()
{
	Server server;	
	cout << "scoket Id : " << server.sockfd << endl;
	while(1){
		int new_fd=server.Accept_connection();	
		thread (handle_server_Session,&server,new_fd).detach();
		//thread (&Server::Handle_session,Server(),new_fd).detach();
	}
	return 0;
}
	


void handle_server_Session(Server* server, int new_fd)
{
	server->Handle_session(new_fd);
}

