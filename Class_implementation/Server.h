#ifndef CLIENT_H
#define CLIENT_H

#include "Socket.h"
class Server : public Socket

{
	public:
		Server();
		void Handle_session(int new_fd);
};


#endif
