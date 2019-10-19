CC = gcc
CFLAGS = -g -Wall
ROOTDIR = src
SOURCEDIR = src/source
HEADERDIR = src/header
OBJECTS =  definitions.o linked_list.o server.o
OBJECTSDEBUG = definitions-debug.o linked_list-debug.o server-debug.o

all: clean server client

debug: clean server-debug client-debug

server:
	$(CC) $(CFLAGS) $(ROOTDIR)/server.c -o server.out

client:
	$(CC) $(CFLAGS) $(ROOTDIR)/client.c -o client.out

client-debug:
	$(CC) $(CFLAGS) -DDEBUG $(ROOTDIR)/client.c -o client.out

server-debug: $(OBJECTSDEBUG)
	$(CC) $(OBJECTS) -o server-debug.out

linked_list-debug.o: 
	$(CC) $(CFLAGS) -DDEBUG -I$(HEADERDIR) -c $(SOURCEDIR)/linked_list.c -o linked_list.o

server-debug.o:
	$(CC) $(CFLAGS) -DDEBUG -c $(ROOTDIR)/server.c -o server.o

definitions-debug.o:
	$(CC) $(CFLAGS) -DDEBUG -I$(HEADERDIR) -c $(SOURCEDIR)/definitions.c -o definitions.o

clean:
	rm -f *.out
	rm -f *.o

 