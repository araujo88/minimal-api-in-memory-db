#include "../include/views.h"
#include "../include/server.h"
#include "../include/database.h"

void root_view(void *client_socket)
{
    char server_message[BUFFER_SIZE];
    char *content;
    char *current_date;
    time_t t;
    time(&t);
    current_date = ctime(&t);
    current_date[strcspn(current_date, "\n")] = 0;
    content = "Hello from the server!";
    printf("[%s] - ", current_date);
    printf("\033[0;32mHTTP/1.1 200 OK\033[0m\n");
    sprintf(server_message, "HTTP/1.1 200 OK\nDate: %s\nContent-Type: text/html\nContent-Length: %ld\n\n%s", current_date, strlen(content), content);
    send(*(int *)client_socket, &server_message, sizeof(server_message), 0);
    memset(server_message, 0, sizeof(server_message));
}

void get_users_view(void *client_socket)
{
    char server_message[BUFFER_SIZE];
    char content[BUFFER_SIZE / 2] = "";
    char *current_date;
    time_t t;
    time(&t);
    current_date = ctime(&t);
    current_date[strcspn(current_date, "\n")] = 0;
    get_users(content);
    printf("[%s] - ", current_date);
    printf("\033[0;32mHTTP/1.1 200 OK\033[0m\n");
    sprintf(server_message, "HTTP/1.1 200 OK\nDate: %s\nContent-Type: application/json\nContent-Length: %ld\n\n%s", current_date, strlen(content), content);
    send(*(int *)client_socket, &server_message, sizeof(server_message), 0);
    memset(server_message, 0, sizeof(server_message));
}

void get_user_view(void *client_socket, unsigned int id)
{
    char server_message[BUFFER_SIZE];
    char content[BUFFER_SIZE / 2] = "";
    char *current_date;
    time_t t;
    time(&t);
    current_date = ctime(&t);
    current_date[strcspn(current_date, "\n")] = 0;
    get_user(id, content);
    printf("[%s] - ", current_date);
    printf("\033[0;32mHTTP/1.1 200 OK\033[0m\n");
    sprintf(server_message, "HTTP/1.1 200 OK\nDate: %s\nContent-Type: application/json\nContent-Length: %ld\n\n%s", current_date, strlen(content), content);
    send(*(int *)client_socket, &server_message, sizeof(server_message), 0);
    memset(server_message, 0, sizeof(server_message));
}

void delete_user_view(void *client_socket, unsigned int id)
{
    char server_message[BUFFER_SIZE];
    char content[BUFFER_SIZE / 2] = "";
    char *current_date;
    time_t t;
    time(&t);
    current_date = ctime(&t);
    current_date[strcspn(current_date, "\n")] = 0;
    delete_user(id, content);
    printf("[%s] - ", current_date);
    printf("\033[0;32mHTTP/1.1 200 OK\033[0m\n");
    sprintf(server_message, "HTTP/1.1 200 OK\nDate: %s\nContent-Type: application/json\nContent-Length: %ld\n\n%s", current_date, strlen(content), content);
    send(*(int *)client_socket, &server_message, sizeof(server_message), 0);
    memset(server_message, 0, sizeof(server_message));
}

void error_not_found(void *client_socket)
{
    char server_message[BUFFER_SIZE];
    char *content;
    char *current_date;
    time_t t;
    time(&t);
    current_date = ctime(&t);
    current_date[strcspn(current_date, "\n")] = 0;
    content = "<html><h1>Error 404 - not found</h1></html>";
    printf("[%s] - ", current_date);
    printf("\033[0;31mHTTP/1.1 404 Not Found\033[0m\n");
    sprintf(server_message, "HTTP/1.1 404 Not Found\nDate: %s\nContent-Type: text/html\nContent-Length: %ld\n\n%s", current_date, strlen(content), content);
    send(*(int *)client_socket, &server_message, sizeof(server_message), 0);
    memset(server_message, 0, sizeof(server_message));
}