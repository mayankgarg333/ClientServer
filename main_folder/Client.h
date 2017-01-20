#ifndef CLIENT_H
#define CLIENT_H

#include "config.h"
#include "Socket.h"
  
using namespace std;

class Client : public Socket

{
	public:
		Client(int port=P); /*Constructor */ 
		void Handle_session(char* filename=NULL);/*Session handler */ 
		string Get_func(string key);/*Get function will request the server to send back the value of the key, In no key is found then value will be NOT FOUND */ 
		string Put_func(string key, string value);/*Put function will place the key value pair in server, and retuen SUCCESS or FAILURE depending on if the operation is successful or not. */ 

};


#endif	
