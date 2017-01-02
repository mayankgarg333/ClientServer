#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "Socket.h"
  
using namespace std;

class Client : public Socket

{
	public:
		Client();
		void Handle_session(string filename="");
		string Get_func(string key);
		//string Put_func(string key, string value);

};


#endif
