#ifndef _DATABASE_H
#define _DATABASE_H 1

#include <models.h>
#include <linked_list.h>

void get_users(char *buffer);
void get_user(unsigned int id, char *buffer);
void insert_user(user User);
void update_user(unsigned int id, user User);
void delete_user(unsigned int id, char *buffer);

#endif