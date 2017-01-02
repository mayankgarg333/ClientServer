
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "Client.h"

using namespace std;


int main()
{
	
	
	Client client;	
	cout << "Client scoket Id : "  << client.sockfd << endl;
	client.Handle_session();
	
	while(1){}
	return 0;	
}

	
