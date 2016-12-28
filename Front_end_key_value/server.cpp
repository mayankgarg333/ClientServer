// muti thread version 

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <vector> 
#include <unordered_map>
#include <mutex>          

#define KEYSIZE 2
#define VALUESIZE 2
#define REQSIZE 3

using namespace std;
void server_handler(int new_fd);

unordered_map <string, string> mymap;
mutex mtx;

int main()
{
	int sockfd;
	struct sockaddr_in my_addr;	
    struct sockaddr_storage their_addr;
	socklen_t addr_size;
	addr_size=sizeof their_addr;
	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	cout << "scoket Id : " << sockfd << endl;
	
	// populating server own attributes
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(1254);     
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

	// server binded to the socket and listen for any incoming msg. 
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);
	listen(sockfd,10);

	int new_fd;
	while(1){
		new_fd=accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
		cout << "NEW CONNECTION " << endl;
		thread (server_handler,new_fd).detach();
	}



	while(1)
	{
	
	}

	return 0;
}




void server_handler(int new_fd){
	cout <<"Thread started : "<< endl;
	string Nav="Na";
	string Suc="Su";
	int byte,to_read;
	while(1){
		string action,key, value;
		char buffer[512]={};
		char payload[512]={};
		//cout << "waiting here: " <<endl;
		to_read=REQSIZE;
		while(to_read>0){
			byte=recv(new_fd, buffer, to_read ,0); // Wait to receive
			memcpy(payload+REQSIZE-to_read,buffer,byte);
			to_read=to_read-byte;
		}
		payload[REQSIZE]='\0';
		action = string(buffer);


		if(action=="GET")
		{	
			int excep=0;
			cout << "Inside Get statement " <<endl;
			to_read=KEYSIZE;
			while(to_read>0){
				byte=recv(new_fd, buffer, to_read ,0); // Wait to receive
				memcpy(payload+KEYSIZE-to_read,buffer,byte);
				to_read=to_read-byte;
			}
			payload[KEYSIZE]='\0';
			key=string(payload);
			cout << "KEY : " << key <<endl;
			try{
				value=mymap.at(key);
			}
			catch (const out_of_range& oor) {	
				excep=1;
			}

			if (excep==1)
				send(new_fd, Nav.c_str(), Nav.size() ,0);
			else
				send(new_fd, value.c_str(), VALUESIZE ,0);
			
		}

		else if(action=="PUT")	
		{
			//cout << "Inside Put statement " <<endl;

			to_read=KEYSIZE;
			while(to_read>0){
				byte=recv(new_fd, buffer, to_read ,0); // Wait to receive
				memcpy(payload+KEYSIZE-to_read,buffer,byte);
				to_read=to_read-byte;
			}
			payload[KEYSIZE]='\0';
			key=string(payload);
			//cout << "KEY : " << key <<endl;
		
			to_read=VALUESIZE;
			while(to_read>0){
				byte=recv(new_fd, buffer, to_read ,0); // Wait to receive
				memcpy(payload+VALUESIZE-to_read,buffer,byte);
				to_read=to_read-byte;
			}
			payload[VALUESIZE]='\0';
			value=string(payload);
			mtx.lock();				//mutex
			mymap[key]=value;
			mtx.unlock();
			//cout << "Value : " << value << endl;
			//send(new_fd, Suc.c_str(), Suc.size() ,0);// acknowledgement
		}
		else{
			cout << "Bad Input " << action << " with bytes " << byte << endl;	
		}
	}
}



