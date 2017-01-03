#include<iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>
#include <algorithm>
#include <unordered_map>
#include <mutex>    
#include <stdlib.h> 
#include "Server.h"
#include "Socket.h"
#include "Client.h"
	
using namespace std;


Server::Server(int port):  Socket(port){

}


void Server::Handle_session(int new_fd, int type){	

	// Connect to all back ends
	if(type==0){
		// create N socket and connect to backend as client 
		backends=new Client*[N];
		for(int i=0; i<N; i++){
			backends[i]= new Client(3001+i);			// use backend.sockfd;
			int ans= backends[i]->Connect_to_server();
			if(ans==-1){	
				cout << "Back end is not available, exiting" << endl;
				exit(-1);
			}
			else{
				cout << "Connected to backend" <<endl;
			}
		}
 	}
	try{
		int byte=1;
		string action, key, value;
		string success;
		string not_found="NOT_FOUND";
		while(1){
			//if(type==1){cout << "This is back end waiting for input" <<endl;}
			action=this->Read(new_fd);
			if(action=="PUT"){
				key	 = this->Read(new_fd);
				value= this->Read(new_fd);
				if(type==0){
					success=this->add_to_catch(key,value);
					//send data to persistent
					success=this->send_to_persistent(key,value);
					
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
					cout<< "Served by Cache"<< endl;
					// if value= not_found get it from persistent
					if(value==not_found)
						value=this->get_from_persistent(key);
				}
				else{
					value=this->look_in_persistent(key);
					cout<< "Served by Persistent"<< endl;
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
			//cout <<"added to local catch"<< endl;
			string success="SUCCESS";
			//mtx.lock();				//mutex
			mymap[key]=value;	
			if (mymap.size()> MAX_CATCH_SIZE){
				mymap.erase(mymap.begin());
			}
			//mtx.unlock();
			return success;
}

// look in catch
string Server::look_in_catch(string key){
			//cout <<"looked in local catch"<< endl;
			string not_found="NOT_FOUND";
			try{
				return mymap.at(key);
			}
			catch (const out_of_range& oor) {	
				return not_found;
			}
}


// add to persistent
string Server::add_to_persistent(string key, string value){			//used by backend
			//cout <<"added to persistent"<< key << " " << value<<endl;
			cout<<"-";cout << flush;
			string success="SUCCESS";
			//mtx.lock();				//mutex
			mymap[key]=value;	
			//mtx.unlock();
			return success;
}

// look in persistent
string Server::look_in_persistent(string key){		//used by backend
			//cout <<"Looked in persisten"<< endl;
			cout<<".";cout << flush;
			string not_found="NOT_FOUND";
			try{
				return mymap.at(key);
			}
			catch (const out_of_range& oor) {	
				return not_found;
			}
}


string Server::send_to_persistent(string key, string value){		//used by front end
	//cout <<"send_to_persistent"<< endl;
	cout<<".";cout << flush;
	string success ="SUCCESS";string reply;
	int arr[N];
	for(int i=0;i<N;i++)
		arr[i]=i;
	random_shuffle(&arr[0], &arr[N]);

	// front end will send data to back end 
	// fron end will use client objects to do so
	// Use client function Get_func and Put_func
	for(int i=0; i<W; i++){
			//cout << "Placing to back end # 1" <<endl;
			reply=backends[arr[i]]->Put_func(key,value);
			//cout << "print reply:" << reply <<endl; 
	}
	return success;
}

string Server::get_from_persistent(string key){				// used by front end
	//cout <<"Get from persistent"<< endl;
	// front end will receive data to back end 
	// fron end will use client objects to do so
	int arr[N];
	for(int i=0;i<N;i++)
		arr[i]=i;
	random_shuffle(&arr[0], &arr[N]);

	return backends[arr[0]]->Get_func(key);
}

