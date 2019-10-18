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
