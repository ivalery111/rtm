#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>

/* Must be unique */
#define SOCKET_NAME "/tmp/ProjectServer"
#define BUFFER_SIZE 128

#define MAX_CLIENT_SUPPORTED 32

int monitored_fd_set[MAX_CLIENT_SUPPORTED];
int client_result[MAX_CLIENT_SUPPORTED] = {0};

static void initialize_monitor_fd_set();
static void add_to_minitored_fd_set(int socket_fd);
static void remove_from_monitored_fd_set(int socket_fd);
static void refresh_fd_set(fd_set* pFD_set);
static int get_max_fd();