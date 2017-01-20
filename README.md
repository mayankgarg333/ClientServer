# ClientServer
Client Server (front end and back end) implementation in C++ using blocking I/O

(main_folder have the main implementation, Rest of the folders were the intermediate steps)

#Build 
cd main_folder
rm server_511.db /* Remove the data base in case it is already there. This DB file stored in persistent medium at the back end of the server*/
make clear
make

##Execution :

#Server
$ /server <server_type> <server_number>

use server_type = 0 for front end
use server_type = 1 for back end

There is single front end server (primary server), but multiple back ends are available. Use server_number = <1,2,3..> for the servers to be started. 

Define back end server numbers in Config.h file.

#Client

Mutliple clients can be connected to the server. 
$ /client <data_file>

data_file : data file need to be given who have three columns. First is the request GET or PUT and then key, value pair according to the request. 


# Code structure 

		Socket class
		/			\
client class	server class


Same class and same code is used for the front end and back end of the server. The second parameter passed as argument will decide whether it is front end or back end, and code will execute accordingly. 


