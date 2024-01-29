CC = gcc
SERVER = server
CLIENT = client
LIBS = -pthread

all: server client

client: $(CLIENT).c 
	gcc -g -o $@.out $^

server: $(SERVER).c
	gcc -g -o $@.out $^ $(LIBS)

clean:
	rm -rf *.out