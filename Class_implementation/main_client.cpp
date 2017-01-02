
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


int main(int argc, char *argv[])
{
	
	char *filename;
	
	for(int i=0; i<argc-1;i++){
		filename=argv[i+1];
		thread (&Client::Handle_session,Client(),filename).detach();
	}
	

	while(1){}
	return 0;	
}


