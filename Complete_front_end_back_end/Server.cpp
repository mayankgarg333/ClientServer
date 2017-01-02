#include<iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>

#include <unordered_map>
#include <mutex>    

#include "Server.h"
#include "Socket.h"
#include "Client.h"

using namespace std;


Server::Server(int port){

}


void Server::Handle_session(int new_fd, int type){	
	// Connect to all back ends
	if(type==0){
		// create N socket and connect to backend as client 
		 Client backends(1355);
		//backends.Connect_to_server();
 	}
	try{
		int byte=1;
		string action, key, value;
		string success;
		string not_found="NOT_FOUND";
		while(1){
			action=this->Read(new_fd);
			if(action=="PUT"){
				key	 = this->Read(new_fd);
				value= this->Read(new_fd);
				if(type==0){
					success=this->add_to_catch(key,value);
				}
				else{
					success=this->add_to_persistent(key,value);
				}
				this->Write(success,new_fd);
			}
			else if(action=="GET"){
				key	 = this->Read(new_fd);
				if(type==0){
					value=this->look_in_catch(key);
				}
				else{
					value=this->look_in_persistent(key);
				}
				this->Write(value,new_fd);
			}
		}
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}
}



// add catch
string Server::add_to_catch(string key, string value){
			string success="SUCCESS";
			mtx.lock();				//mutex
			mymap[key]=value;	
			if (mymap.size()> MAX_CATCH_SIZE){
				mymap.erase(mymap.begin());
			}
			mtx.unlock();
			return success;
}

// look in catch
string Server::look_in_catch(string key){
			string not_found="NOT_FOUND";
			try{
				return mymap.at(key);
			}
			catch (const out_of_range& oor) {	
				return not_found;
			}
}


// add to persistent
string Server::add_to_persistent(string key, string value){
			string success="SUCCESS";
			mtx.lock();				//mutex
			mymap[key]=value;	
			mtx.unlock();
			return success;
}

// look in persistent
string Server::look_in_persistent(string key){
			string not_found="NOT_FOUND";
			try{
				return mymap.at(key);
			}
			catch (const out_of_range& oor) {	
				return not_found;
			}
}
