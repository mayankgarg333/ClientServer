#ifndef SOCKET_H
#define SOCKET_H


#include <string.h>

using namespace std;

class Socket{
	
	public:
		int sockfd;
		struct sockaddr_in socket_addr;	
		Socket();
		void Bind_connection();
		int Accept_connection();
		int Connect_to_server();
		void Write(string msg, int fd);
		string Read(int fd);
		void Read_data(int fd, char* buf,	int to_read);
		void Write_data(int fd, const char* buf,	int to_write);
		

};

	

#endif
