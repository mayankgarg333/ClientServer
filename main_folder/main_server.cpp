#include <iostream>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <exception>
#include <signal.h>

#include "Server.h"

using namespace std;

void handle_server_Session(Server* server, int new_fd, int type); //type=0, front end, =1 back end
void signal_callback_handler(int signum);
int main(int argc, char * argv[])
{
	signal(SIGPIPE, signal_callback_handler);
    signal(SIGABRT, signal_callback_handler);
	
	if(argc ==1){
		cout << "Input type ./server type" << endl;
		cout << " type = 0 for front end, type = 1 for back end" << endl;
		exit(-1);
	}
	int type=atoi(argv[1]);
	
	try{
		// server obecject will listen at different port depending on front end or back end
		Server *s;
		if(type==0)
			{s=new Server; cout << "I am Fron end" << endl;}
		else
			{int port=atoi(argv[2]);s=new Server(port+3000);cout << "I am back end" << endl;}
		
		s->Bind_connection();
		while(1){
			int new_fd=s->Accept_connection();	
			thread (handle_server_Session,s,new_fd,type).detach();
		}

	}
  	catch (exception& e)
  	{
    	cout << "Standard exception: " << e.what() << endl;
  	}

	return 0;
}
	


void handle_server_Session(Server* server_handle, int new_fd, int type)
{
	try{
		server_handle->Handle_session(new_fd, type);
	}
  	catch (exception& e)
  	{
    	cout << "Standard exception in thread: " << e.what() << endl;
  	}
}


/* Catch Signal Handler function */
void signal_callback_handler(int signum) {
    printf("Caught signal: %d\n",signum);
//    Re-register the signal handler
    signal(signum, signal_callback_handler);
}

