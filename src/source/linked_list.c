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

node_t *find_node(node_t *begin, sync_message_t *search_message) {

    if (search_message == NULL) {
        perror("Search node is empty");
        exit(EXIT_FAILURE);
    } else {
        for (node_t *current = begin; current != NULL;
             current = current->next) {
            if (compare_messages(current->message, search_message)) {
                return current;
            }
        }
    }
    return NULL;
}

void delete_node(node_t **list) {
    
    node_t *next = NULL;

    if ((*list)->next != NULL) { /* If not last node */
        next = (*list)->next;
        free(*list);
        *list = next;
    }
    else{ 
        if(*list){
            free(*list);
        }
    }
}