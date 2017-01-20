#ifndef SOCKET_H
#define SOCKET_H


#include <string.h>

using namespace std;

class Socket{
	
	public:
		int sockfd;			/* Socket ID*/
		static const int P=1269;	/*PORT number*/
		struct sockaddr_in socket_addr;	


		Socket(int port=P);   			/* Constructor */
		void Bind_connection();			/*Function server uses to bind to a port*/
		int Accept_connection();		/*Function server uses to accept the connection*/
		int Connect_to_server();		/*Function Client uses to connect to the server */
		void Write(string msg, int fd);	/*Write on the socket, using file descriptor*/
		string Read(int fd);			/*Read on the socket, using file descriptor*/
		void Read_data(int fd, char* buf,	int to_read);		/* Function used by READ function to read byte from TCP conenction*/
		void Write_data(int fd, const char* buf,	int to_write);		/* Function used by WRITE function to read byte from TCP conenction*/
		

};


#endif
