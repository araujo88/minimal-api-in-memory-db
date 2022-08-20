#ifndef _VIEWS_H
#define _VIEWS_H 1

void root_view(void *client_socket);
void get_users_view(void *client_socket);
void get_user_view(void *client_socket, unsigned int id);
void delete_user_view(void *client_socket, unsigned int id);
void error_not_found(void *client_socket);

#endif