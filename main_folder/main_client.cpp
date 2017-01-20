#include "config.h"
#include "Client.h"

using namespace std;

void handle_client_Session(char* filename);
	
int main(int argc, char *argv[])
{
	
	char *filename;
	
	for(int i=0; i<argc-1;i++){
		filename=argv[i+1];
		/* Launch a thread for each session
		A session in the input file provided.. if  input files are provided then 5 threads will run and each will creat its own client object, Multiple client can also run simultaneously in different terminals with multiple sessions
		*/
		thread(handle_client_Session,filename).detach();		
	
	}
	

	while(1){}
	return 0;	
}

void handle_client_Session(char* filename)
{
	Client client;	// create client object
	client.Handle_session(filename);	// launch the handdle session to serve requests

}
