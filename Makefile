CC = gcc
CFLAGS = -g -Wall
ROOTDIR = src
SOURCEDIR = src/source
HEADERDIR = src/header

all: clean server client

debug: clean server-debug client-debug

server:
	$(CC) $(CFLAGS) $(ROOTDIR)/server.c -o server.out

client:
	$(CC) $(CFLAGS) $(ROOTDIR)/client.c -o client.out

server-debug:
	$(CC) $(CFLAGS) -DDEBUG $(ROOTDIR)/server.c -o server.out
client-debug:
	$(CC) $(CFLAGS) -DDEBUG $(ROOTDIR)/client.c -o client.out

clean:
	rm -f *.out
