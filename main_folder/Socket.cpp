#include "config.h"
#include "Socket.h"

using namespace std;

/*********************** 
Constructor
Fill all the port details in the appropriate data structure 
**************************/

Socket::Socket(int port){
	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(port);     
	//cout<< "Port number is " << port <<endl;
	socket_addr.sin_addr.s_addr = INADDR_ANY;
	memset(socket_addr.sin_zero, '\0', sizeof socket_addr.sin_zero);
	cout << "A socket is created with port " << port << endl;
}


/******************
Function server uses to bind to a port
********************/

void Socket::Bind_connection(){
	bind(sockfd, (struct sockaddr *)&socket_addr, sizeof socket_addr);
	listen(sockfd,20);
}


/***************** 
Function server uses to accept the connection
******************/
int Socket::Accept_connection(){
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	addr_size=sizeof their_addr;
	return accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
	
}

/******************
Function Client uses to connect to the server 
*******************/

int Socket::Connect_to_server(){
	return connect(this->sockfd, (struct sockaddr*) &socket_addr, sizeof socket_addr); 
}	


/*******************
Write on the socket, using file descriptor
*********************/

void Socket::Write(string msg, int fd){
		try{
			int32_t s = msg.size();
			this->Write_data(fd, (const char*)&s, sizeof(int32_t));
			this->Write_data(fd, msg.c_str(), msg.size());			// sending the msg
		}
  		catch (exception& e)
  		{
    		cout << "Standard exception: " << e.what() << endl;
  		}
}


/*******************
Read on the socket, using file descriptor
*********************/
string Socket::Read(int fd){
		try{
			char buffer[512]={};
			this->Read_data(fd,buffer,4);
			int *n=(int*)buffer;
			this->Read_data(fd,buffer,*n);
			return string(buffer);
		}
  		catch (exception& e)
  		{
    		cout << "Standard exception: " << e.what() << endl;
  		}
}

/* Function used by READ function to read byte from TCP conenction*/
void Socket::Read_data(int fd, char* payload,int to_read)
{
	try{
		int byte=0;
		int payload_size=to_read;	
		char buffer[512]={};		// Temperary storage
		while(to_read>0){
			byte=recv(fd, buffer, to_read ,0); // Wait to receive
			if(byte<0) pthread_exit(NULL);
			memcpy(payload+payload_size-to_read,buffer,byte);
			to_read=to_read-byte;
		}
		payload[payload_size]='\0';
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}
}

/* Function used by WRITE function to read byte from TCP conenction*/
void Socket::Write_data(int fd, const char* payload,int to_write)
{	
	try{
		int byte=0;
		int payload_size=to_write;	
	
		while(to_write>0){
			char buffer[512]={};
			strcpy(buffer,payload+payload_size-to_write);	 // Temperary storage
			byte=send(fd, buffer, to_write ,0); // Wait to receive
			if(byte<0) pthread_exit(NULL);
			to_write=to_write-byte;
		}
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}

}
