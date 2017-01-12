CC=g++
CFLAGS=-pthread -std=c++11 -l sqlite3
DEPS1 = Client.h Socket.h
OBJ1 = main_client.o Client.o Socket.o 
DEPS2 = Server.h Socket.h Client.h
OBJ2 = main_server.o Server.o Socket.o Client.o 
all: client server

%.o: %.cpp $(DEPS1)
	$(CC) -c -o $@ $< $(CFLAGS)

client: $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp $(DEPS2)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	-rm -rf *.o *~
