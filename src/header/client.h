/*
 * CLIENT STEPS:
 *  socket()
 *  connect()
 *  send()
 *  recv()
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "definitions.h"


#define SOCKET_NAME "/tmp/ProjectServer"
#define BUFFER_SIZE 128


void create_data_socket(int* data_socket);

/* Connect socket to socket address */
void connect_socket(struct sockaddr_un* addr, int* data_socket);
void send_arguments(int* data_socket);
void receive_result(int* data_socket);