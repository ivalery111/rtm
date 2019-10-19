#ifndef DEFINITION_H
#define DEFINITION_H

/* Operations code */
typedef enum{
    CREATE,
    UPDATE,
    DELETE
} OPCODE;

/* Structure which contains the data */
typedef struct{
    char destination[16];
    char mask;
    char gateway_ip[16];
    char output_interface[32];
}message_body_t;

typedef struct{
    OPCODE op_code;
    message_body_t msg_body;
}sync_message_t;

/**
 *  message_body
 * sync_message
 */

static int compare_messages(sync_message_t *lhs, sync_message_t *rhs) {
    int ret = 0;

    if (lhs == NULL || rhs == NULL)
        return ret;

    if (strcmp(lhs->msg_body.destination, rhs->msg_body.destination) == 0 &&
        strcmp(lhs->msg_body.gateway_ip, rhs->msg_body.gateway_ip) == 0 &&
        strcmp(lhs->msg_body.output_interface,rhs->msg_body.output_interface) == 0 &&
        lhs->msg_body.mask == rhs->msg_body.mask &&
        lhs->op_code == rhs->op_code) {
        ret = 1;
    } else { /* not equal */
        ret = 0;
    }
    return ret;
}

#endif