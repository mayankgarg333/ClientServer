
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <thread>

#include "Client.h"

using namespace std;

void handle_client_Session(char* filename);
	
int main(int argc, char *argv[])
{
	
	char *filename;
	
	for(int i=0; i<argc-1;i++){
		filename=argv[i+1];
		thread(handle_client_Session,filename).detach();
	}
	

	while(1){}
	return 0;	
}

void handle_client_Session(char* filename)
{
	Client client;
	client.Handle_session(filename);

}
