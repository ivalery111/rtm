#include "definitions.h"

int compare_messages(sync_message_t *lhs, sync_message_t *rhs) {
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