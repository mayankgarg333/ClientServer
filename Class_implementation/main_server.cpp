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


int main()
{
	Server server;	
	cout << "scoket Id : " << server.sockfd << endl;
	while(1){
		int new_fd=server.Accept_connection();
		thread (&Server::Handle_session,Server(),new_fd).detach();
	}
	return 0;
}
	




