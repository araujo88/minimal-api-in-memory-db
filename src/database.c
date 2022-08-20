#include "../include/database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t *head = NULL;
unsigned int global_id = 0;

void get_users(char *buffer)
{
    node_t *tmp = head;

    sprintf(buffer + strlen(buffer), "[");
    while (tmp != NULL)
    {
        sprintf(buffer + strlen(buffer), "{\n");
        sprintf(buffer + strlen(buffer), "\t\"id\": \"%u\",\n", tmp->id);
        sprintf(buffer + strlen(buffer), "\t\"name\": \"%s\",\n", tmp->User.name);
        sprintf(buffer + strlen(buffer), "\t\"surname\": \"%s\"\n", tmp->User.surname);
        sprintf(buffer + strlen(buffer), "},\n");
        tmp = tmp->next;
    }
    sprintf(buffer + strlen(buffer) - 2, "\n]");
}

void get_user(unsigned int id, char *buffer)
{
    node_t *tmp;
    tmp = find_node(head, id);
    if (tmp != NULL)
    {
        sprintf(buffer + strlen(buffer), "{\n");
        sprintf(buffer + strlen(buffer), "\t\"id\": \"%u\",\n", tmp->id);
        sprintf(buffer + strlen(buffer), "\t\"name\": \"%s\",\n", tmp->User.name);
        sprintf(buffer + strlen(buffer), "\t\"surname\": \"%s\"\n", tmp->User.surname);
        sprintf(buffer + strlen(buffer), "}\n");
    }
    else
    {
        db_error("Node not found");
        sprintf(buffer + strlen(buffer), "{\"msg\": \"user not found\"}");
    }
}

void insert_user(user User)
{
    insert_at_head(&head, create_new_node(global_id, User));
    global_id++;
}

void update_user(unsigned int id, user User)
{
    node_t *tmp;
    tmp = find_node(head, id);
    if (tmp != NULL)
    {
        tmp->User = User;
    }
    else
    {
        db_error("Node not found");
    }
}

void delete_user(unsigned int id, char *buffer)
{
    node_t *tmp;
    tmp = find_node(head, id);
    if (tmp != NULL)
    {
        delete_node(head, id);
        sprintf(buffer + strlen(buffer), "{\"msg\": \"user deleted\"}");
    }
    else
    {
        db_error("Node not found");
        sprintf(buffer + strlen(buffer), "{\"msg\": \"user not found\"}");
    }
}