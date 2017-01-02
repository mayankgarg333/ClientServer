#ifndef SOCKET_H
#define SOCKET_H




class Socket{
	
	public:
		int sockfd;
		struct sockaddr_in socket_addr;	
		Socket();
		int Accept_connection();
		int Connect_to_server();
};

	

#endif
