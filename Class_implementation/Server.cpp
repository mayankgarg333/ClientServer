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

using namespace std;


Server::Server(){

}


void Server::Handle_session(int new_fd){
	int byte=1;int excep=0;
	string action, key, value;
	string success="SUCCESS";
	string not_found="NOT_FOUND";
	while(1){
		//cout << " Reading action " << endl;
		action=this->Read(new_fd);
		if(action=="PUT"){
			key	 = this->Read(new_fd);
			value= this->Read(new_fd);
			mtx.lock();				//mutex
			//cout << "inside mutex lock" <<endl;
			mymap[key]=value;	
			mtx.unlock();
			this->Write(success,new_fd);
		}
		else if(action=="GET"){
			excep=0;
			key	 = this->Read(new_fd);
			
			try{
				value=mymap.at(key);
			}
			catch (const out_of_range& oor) {	
				excep=1;
			}

			if (excep==1)
				this->Write(not_found,new_fd);
			else
				this->Write(value,new_fd);
			
		}
		else{
			cout << "Invalid Key" <<endl;
			}

			
	}
}
