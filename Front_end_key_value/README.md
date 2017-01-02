# Client server Implementation

First run server on one terminal  (./server)

Then run client on another terminal and pass different session as argument. (./client sessionfilepath)
(./client data/all_puts.csv data/session_1.scv ..so on)
Client is mupltithreaded. Each session given will start its own connection.
Server is also multi threaded. 
