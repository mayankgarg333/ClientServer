#ifndef CLIENT_H
#define CLIENT_H

#include <unordered_map>
#include <mutex>     

#include "Socket.h"

class Server : public Socket

{
	
	public:
		Server();
		void Handle_session(int new_fd);
		unordered_map <string, string> mymap;

		mutex mtx;
	
};


#endif
