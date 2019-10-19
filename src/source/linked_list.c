#include "header/linked_list.h"

/**
 * create_node - create a new node with @other_message
 * @other_message: the message that node will contain inside
 * 
 * return pointer to new node.
 */
node_t *create_node(sync_message_t *other_message) {
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL)
        exit(EXIT_FAILURE);
    new_node->message = malloc(sizeof(sync_message_t));
    if (new_node->message == NULL)
        exit(EXIT_FAILURE);

    memcpy(new_node->message, other_message, sizeof(sync_message_t));
    new_node->next = NULL;

    return new_node;
}

/**
 * add_node - add a new node
 * @begin:           list head to add it after
 * @other_message:   new message to added
 * 
 * Insert a new node after the begin.
 * This is good for implementing stacks.
 */ 
void add_node(node_t **begin, sync_message_t *other_message) {

    node_t *new_node = create_node(other_message);

    /* If list is empty */
    if (*begin == NULL) {
        *begin = new_node;
    } else {
        new_node->next = (*begin)->next;
        (*begin)->next = new_node;
    }
}

void Test() {

    node_t *list = NULL;

    sync_message_t msg1 = {.op_code = CREATE, .msg_body.mask = 'a'};
    add_node(&list, &msg1);

    sync_message_t msg2 = {.op_code = UPDATE, .msg_body.mask = 'b'};
    add_node(&list, &msg2);

    sync_message_t msg3 = {.op_code = DELETE, .msg_body.mask = 'c'};
    add_node(&list, &msg3);

    puts("Done!");
}

int main() { Test(); }