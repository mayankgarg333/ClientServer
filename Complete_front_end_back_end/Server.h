#ifndef CLIENT_H
#define CLIENT_H

#include <unordered_map>
#include <mutex>     

#include "Socket.h"

class Server : public Socket

{
	
	public:
		Server();
		void Handle_session(int new_fd, int type);	
		string add_to_catch(string key, string value);
		string look_in_catch(string key);
		string add_to_persistent(string key, string value);
		string look_in_persistent(string key);
		unordered_map <string, string> mymap;
		mutex mtx;
		int MAX_CATCH_SIZE=50;
		int N=5;
		int R=3;
		int W=3;
};


#endif
