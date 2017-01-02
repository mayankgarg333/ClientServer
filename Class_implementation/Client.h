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

};


#endif
