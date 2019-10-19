#include "header/server.h"
#include "header/debug.h"
#include "header/definitions.h"

/*          API         */
static void initialize_monitor_fd_set() {
    for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
        monitored_fd_set[i] = -1;
    }
}

static void add_to_minitored_fd_set(int socket_fd) {
    for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
        if (monitored_fd_set[i] == -1) {
            continue;
        }
        monitored_fd_set[i] = socket_fd;
        break;
    }
}

static void remove_from_monitored_fd_set(int socket_fd) {
    for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
        if (monitored_fd_set[i] == socket_fd) {
            monitored_fd_set[i] = -1;
            break;
        }
    }
}

static void refresh_fd_set(fd_set *pFD_set) {
    /* All bits to zero */
    FD_ZERO(pFD_set);

    for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
        if (monitored_fd_set[i] != -1) {
            FD_SET(monitored_fd_set[i], pFD_set);
        }
    }
}

static int get_max_fd() {
    int max = -1;
    for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
        if (monitored_fd_set[i] > max) {
            max = monitored_fd_set[i];
        }
    }
    return max;
}
/**
 * Intialization of some resources
 */ 
static void init_server(){
}

/*----------------------*/

int main(void) {
    /* If programm exited not correct in the last time */
    unlink(SOCKET_NAME);

    //initialize_monitor_fd_set();
    //add_to_minitored_fd_set(0);

    /* Create Master Socket */
    int master_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (master_socket == -1) {
        perror("Can't create master socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un name;
    memset(&name, 0, sizeof(struct sockaddr_un));

    /* Specify the socket credentials */
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

    /* Bind socket to SOCKET NAME */
    if ((bind(master_socket, (const struct sockaddr *)&name,
              sizeof(struct sockaddr_un))) == -1) {
        perror("Can't bind socket to SOCKET NAME");
        exit(EXIT_FAILURE);
    }

    if ((listen(master_socket, 20)) == -1) {
        perror("listen()");
        exit(EXIT_FAILURE);
    }

    /* Add master socket to monitored  set of FDs */
    add_to_minitored_fd_set(master_socket);

    fd_set readfds;
    char buffer[BUFFER_SIZE];
    sync_message_t message;

    /* Loop for handling connection */
    for (;;) {

        refresh_fd_set(&readfds);

        LOG_DEBUG("Waiting on select() for incoming connection");

        select(get_max_fd() + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(master_socket, &readfds)) {
            LOG_DEBUG("New connection received, accept the connection");

            int data_socket = accept(master_socket, NULL, NULL);
            if (data_socket == -1) {
                perror("Can't accept");
                exit(EXIT_FAILURE);
            }
            LOG_DEBUG("Connection accepted from client");

            add_to_minitored_fd_set(data_socket);
        } else if (FD_ISSET(0, &readfds)) {
            memset(&buffer, 0, BUFFER_SIZE);

            int ret = read(0, &buffer, BUFFER_SIZE);
            if (ret == -1) {
                perror("Can't read input from console");
                exit(EXIT_FAILURE);
            }
            printf("Input read from console: %s\n", buffer);
        } else { /* Data arrives */

            /* Find the client which sent us the data */
            int request_socket = -1;
            for (int i = 0; i < MAX_CLIENT_SUPPORTED; i++) {
                if (FD_ISSET(monitored_fd_set[i], &readfds)) {
                    request_socket = monitored_fd_set[i];

                    /* Prepare to get the message */
                    memset(&buffer, 0, BUFFER_SIZE);

                    LOG_DEBUG("Waiting for the data from the client");
                    int ret = read(request_socket, &buffer, BUFFER_SIZE);
                    if (ret == -1) {
                        perror("Can't read data from the client");
                        exit(EXIT_FAILURE);
                    }

                    LOG_DEBUG("%d bytes read from client", ret);

                    /* Prepare the message to get the data */
                    memset(&message, 0, sizeof(sync_message_t));

                    memcpy(&message, buffer, sizeof(sync_message_t));

                    LOG_INFO("op_code = %d", message.op_code);
                    LOG_INFO("mask = %c", message.msg_body.mask);

                    /* Stopeed HERE! */
                }
            }
        }
        /* Go to select() */
    }

    close(master_socket);
    remove_from_monitored_fd_set(master_socket);
    LOG_INFO("Connection closed!");

    /* Release resources */
    unlink(SOCKET_NAME);
    exit(EXIT_FAILURE);
}
