#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <mutex>     

#include "Socket.h"
#include "Client.h"

using namespace std;


class Server : public Socket

{
	
	public:
		Server(int port=P);
		void Handle_session(int new_fd, int type);	
		string add_to_catch(string key, string value);
		string look_in_catch(string key);
		string add_to_persistent(string key, string value);
		string send_to_persistent(string key, string value);
		string get_from_persistent(string key);
		string look_in_persistent(string key);
		unordered_map <string, string> mymap;
		mutex mtx;
		int MAX_CATCH_SIZE=50;
		int N=2;
		int R=1;
		int W=N;
		Client *backends1;
		Client *backends2;
		Client **backends;
};


#endif
