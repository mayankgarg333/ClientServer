#ifndef SERVER_H
#define SERVER_H

#include "config.h"
#include "Socket.h"
#include "Client.h"

using namespace std;


class Server : public Socket

{
	
	public:
		// Server functions 
		Server(int port=P);  //constructor 
		void Handle_session(int new_fd, int type); // session handler

		
		// front end server	
		unordered_map <string, string> mymap;		//MAP for catch (Map is stored at front end)
		mutex mtx;									// mutex to access the map by different threads
		int MAX_CATCH_SIZE=50;						// catch size
		int N=2;									// Number of back ends
		int R=1;									// will read from any server randomly
		int W=N;									// will write to both servers
		
		string add_to_catch(string key, string value);			//Add key value to map (catch)
		string look_in_catch(string key);						//look for key value pair in map
		string send_to_persistent(string key, string value);	//send key value pair to back end to add
		string get_from_persistent(string key);					//get value for a key from back end if not in the catch
		vector <Client> backends;								// Front end will work as client for back end, This vector will have objects to access all the backends for which the front end is a client
	
	

		// Back end server
		string add_to_persistent(string key, string value); //back end will write to database
		string look_in_persistent(string key);				//back end will read from database
		
		

		// Database for the backend
		sqlite3 *db;										// databse pointer
		static int callback(void *data, int argc, char **argv, char **azColName);	// callback function to access database
		void create_database();								// create database	
		string add_to_database(string key, string value);	// add to database
		string get_from_database(string key);				// get from database
		
};


#endif
