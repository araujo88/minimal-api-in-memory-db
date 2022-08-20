#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/linked_list.h"

void db_sucess(char *msg)
{
    char *current_date;
    time_t t;
    time(&t);
    current_date = ctime(&t);
    current_date[strcspn(current_date, "\n")] = 0;
    printf("[%s] - ", current_date);
    printf("\033[0;32mDatabase success: ");
    printf("\033[0m%s\n", msg);
}

void db_error(char *msg)
{
    char *current_date;
    time_t t;
    time(&t);
    current_date = ctime(&t);
    current_date[strcspn(current_date, "\n")] = 0;
    printf("[%s] - ", current_date);
    printf("\033[0;31mDatabase error: ");
    printf("\033[0m%s\n", msg);
}

node_t *create_new_node(unsigned int id, user User)
{
    node_t *result = (node_t *)malloc(sizeof(node_t));
    result->id = id;
    result->User = User;
    result->next = NULL;
    return result;
}

void insert_at_head(node_t **head, node_t *node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
}

node_t *find_node(node_t *head, unsigned int id)
{
    node_t *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->id == id)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void update_node(node_t *head, unsigned int id, node_t *new_node)
{
    node_t *node_to_update = find_node(head, id);
    if (node_to_update != NULL)
    {
        node_to_update = new_node;
    }
    else
    {
        db_error("Node not found");
    }
}

void delete_node(node_t *head, unsigned int id)
{
    node_t *tmp = head;
    node_t *delnode, *next_node;

    delnode = find_node(head, id);

    if (delnode == NULL)
    {
        db_error("Node not found");
    }
    else
    {
        while (tmp != NULL)
        {
            next_node = tmp->next;
            if (next_node->id == id)
            {
                tmp->next = next_node->next;
                db_sucess("Node deleted");
                break;
            }
            tmp = tmp->next;
        }
        free(delnode);
    }
}