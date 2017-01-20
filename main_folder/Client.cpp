#include "config.h"
#include "Client.h"

using namespace std;


/****************
Constructor 
***************/ 
Client::Client(int port): Socket(port){
}

/***************
Session handler : Will read the file ans service the get and put requests
*/ 
void Client::Handle_session(char* filename){
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
		//usleep(2000000);
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
			cout << "Key send: " << myvec[1] << " ,Value received: " << reply << endl;
			
		}
		else if(action=="PUT")
		{
			myvec[2].pop_back(); // remove end line character	
			reply=this->Put_func(myvec[1],myvec[2]);
			cout << "Key value send: " << myvec[1] << " , " << myvec[2 ]<< " Reply: " << reply << endl;
			
		}
		else
		{
			cout << "Invalid KEY VALUE " << endl;
		}
	
	}
	
	
}


/**************
Get function will request the server to send back the value of the key, In no key is found then value will be NOT FOUND 
***************/ 
string Client::Get_func(string key){
		//cout<< "Inside Get function:"<< endl;
		string action="GET";
		this->Write(action,this->sockfd);
		this->Write(key,this->sockfd);
		string r=this->Read(this->sockfd);
		return r;
}

/**************
Put function will place the key value pair in server, and retuen SUCCESS or FAILURE depending on if the operation is successful or not. 
****************/ 

string Client::Put_func(string key, string value){
		//cout<< "Inside Put function:"<< endl;
		string action="PUT";
		this->Write(action,this->sockfd);
		this->Write(key,this->sockfd);
		this->Write(value,this->sockfd);
		string r=this->Read(this->sockfd);
		return r;
}

