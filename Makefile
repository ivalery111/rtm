CC = gcc
CFLAGS = -g -Wall
ROOTDIR = src
SOURCEDIR = src/source
HEADERDIR = src/header

all: server client

server:
	$(CC) $(CFLAGS) $(ROOTDIR)/server.c -o server.out

client:
	$(CC) $(CFLAGS) $(ROOTDIR)/client.c -o client.out

