#include "header/client.h"

void create_data_socket(int *data_socket) {

    *data_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if ((*data_socket) == -1) {
        perror("create_data_socket");
        exit(EXIT_FAILURE);
    }
}

void connect_socket(struct sockaddr_un *addr, int *data_socket) {

    /* For more portability need to clear the data */
    memset(addr, 0, sizeof(struct sockaddr_un));

    /* Connect socket to socket address */
    addr->sun_family = AF_UNIX;
    strncpy(addr->sun_path, SOCKET_NAME, sizeof(addr->sun_path) - 1);

    int iRet = -1;
    iRet = connect(*data_socket, (const struct sockaddr *)addr,
                   sizeof(struct sockaddr_un));
    if (iRet == -1) {
        perror("down");
        fprintf(stderr, "The Server is DOWN!\n");
        exit(EXIT_FAILURE);
    }
}

void send_arguments(int *data_socket) {
    int i = -1;
    do {
        sync_message_t message;

        /* Fill message from user input */
        get_message_from_user(&message, &i);

        int ret = write(*data_socket, &message, sizeof(sync_message_t));
        if (ret == -1) {
            perror("write");
            exit(EXIT_FAILURE);
            break;
        }

        printf("No' of bytes sent = %d, data sent = %d\n", ret, i);
    } while (i); /* Until i != 0 */
}

void receive_result(int *data_socket) {
    char szBuffer[BUFFER_SIZE];
    memset(szBuffer, 0, BUFFER_SIZE);

    int ret = read(*data_socket, szBuffer, BUFFER_SIZE);
    if (ret == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("Received data from Server: %s\n", szBuffer);
}

void get_message_from_user(sync_message_t *message, int *choice) {

    int choose = -1;
    // do {
    puts("What you want to do?");
    printf("\t1 - Create\n\t2 - Update\n\t3 - Delete\n\t0 - Exit\n->:");
    scanf("%d", &choose);

    switch (choose) {
    case 1: {
        message->op_code = CREATE;
        break;
    }
    case 2: {
        message->op_code = UPDATE;
        break;
    }
    case 3: {
        message->op_code = DELETE;
        break;
    }
    case 0: {
        *choice = choose;
        return;
    }
    default: {
        fprintf(stderr, "Unknown choice!\n");
        break;
    }
    }

    printf("Enter destination address:\n->:");
    fscanf(stdin, "%s", message->msg_body.destination);
    LOG_DEBUG("Destination address was read from user");

    printf("Enter gateway ip address:\n->:");
    fscanf(stdin, "%s", message->msg_body.gateway_ip);
    LOG_DEBUG("Getway ip address was read from user");

    printf("Enter output interface ip address:\n->:");
    fscanf(stdin, "%s", message->msg_body.output_interface);
    LOG_DEBUG("Output interface ip address was read from user");

    printf("Enter a mask:\n->:");
    scanf("%c", &message->msg_body.mask);
    LOG_DEBUG("Mask was read from user");

    // } while (choose != 0);
}

int main(int argc, char *argv[]) {

    int data_socket = -1;
    create_data_socket(&data_socket);

    struct sockaddr_un addr;
    connect_socket(&addr, &data_socket);

    send_arguments(&data_socket);

    receive_result(&data_socket);

    close(data_socket);

    exit(EXIT_SUCCESS);
}
