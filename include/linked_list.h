#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H 1

#include "models.h"
#include <stdio.h>

typedef struct node
{
    unsigned int id;
    user User;
    struct node *next;
} node_t;

node_t *create_new_node(unsigned int id, user User);
void insert_at_head(node_t **head, node_t *node_to_insert);
node_t *find_node(node_t *head, unsigned int id);
void delete_node(node_t *head, unsigned int id);
void db_sucess(char *msg);
void db_error(char *msg);

#endif