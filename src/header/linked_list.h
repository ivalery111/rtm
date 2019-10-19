#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "definitions.h"

typedef struct node{
    sync_message_t* message;
    struct node* next;
}node_t;

node_t* create_node(sync_message_t *other_message);
void add_node(node_t **begin, sync_message_t* other_message);
node_t *find_node(node_t *begin, sync_message_t *search_message);
void delete_node(node_t **list);

#endif