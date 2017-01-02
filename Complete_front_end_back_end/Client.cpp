#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <sstream>

#include "Client.h"

using namespace std;

Client::Client(int port) : Socket(port){

}


void Client::Handle_session(char* filename){
	Client client(1250);	
	int ans=this->Connect_to_server();
	if(ans==-1){	
		cout << "Server is not available, exiting" << endl;
		exit(-1);
	}
	else{
		cout << "Connected to server" <<endl;
	}
	
	// Read file contents in memory
    ifstream myfile(filename);
    vector<string> lines;
    string line;
    int nlines = 0;
    while(getline(myfile,line)) {
        lines.push_back(line);
        nlines++;
    }

	// shoot the file content
	string reply;string msg;
	for(int i=0; i<lines.size();i++){
		msg = lines[i];
		// divide msg in get and put requests
		istringstream ss(msg);
		string token;
		vector <string> myvec;
		string action;
		while(getline(ss, token, ',')) {
		    myvec.push_back(token);
			//cout << "token " << token << endl;
		}
		
		action =myvec[0];
		if(action=="GET")
		{	
			myvec[1].pop_back(); // remove end line character	
			reply=this->Get_func(myvec[1]);
			//cout << "Key send: " << myvec[1] << " ,Value received: " << reply << endl;
			
		}
		else if(action=="PUT")
		{
			myvec[2].pop_back(); // remove end line character	
			reply=this->Put_func(myvec[1],myvec[2]);
			//cout << "Key value send: " << myvec[1] << " , " << myvec[2 ]<< " Reply: " << reply << endl;
			
		}
		else
		{
			cout << "Invalid KEY VALUE " << endl;
		}
	
	}
	
	
}



string Client::Get_func(string key){
		//cout<< "Inside Get function:"<< endl;
		string action="GET";
		this->Write(action,this->sockfd);
		this->Write(key,this->sockfd);
		string r=this->Read(this->sockfd);
		return r;
}

string Client::Put_func(string key, string value){
		//cout<< "Inside Put function:"<< endl;
		string action="PUT";
		this->Write(action,this->sockfd);
		this->Write(key,this->sockfd);
		this->Write(value,this->sockfd);
		string r=this->Read(this->sockfd);
		return r;
}

