#include "../include/server.h"
#include "../include/views.h"
#include "../include/routes.h"
#include "../include/database.h"

void create_server(int server_socket, char *ip, int port, int max_connections)
{
    printf("Creating socket ...\n");
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    check_socket(server_socket);
    printf("Socket created!\n");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip);

    printf("Binding socket ...\n");
    check_bind(server_socket, &server_address);
    printf("Binding done!\n");

    printf("Waiting for incoming requests... (press Ctrl+C to quit)\n");
    while (true)
    {
        check_listen(server_socket, max_connections);

        int *client_socket = malloc(sizeof(int));
        struct sockaddr_in *client_address = NULL;

        check_accept(server_socket, client_socket, (struct sockaddr *)client_address);

        pthread_t t;
        pthread_create(&t, NULL, send_data, (void *)client_socket);
    }
}

void check_socket(int server_socket)
{
    if (server_socket < 0)
    {
        perror("Socket failed: ");
        printf("Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }
}

void check_bind(int server_socket, struct sockaddr_in *server_address)
{
    if ((bind(server_socket, (struct sockaddr *)server_address, sizeof(*server_address))) < 0)
    {
        perror("Bind failed");
        printf("Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }
}

void check_listen(int server_socket, int num_connections)
{
    if ((listen(server_socket, num_connections)) < 0)
    {
        perror("Listen failed");
        printf("Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }
}

void check_accept(int server_socket, int *client_socket, struct sockaddr *client_address)
{
    if ((*client_socket = accept(server_socket, (struct sockaddr *)client_address, (socklen_t *)sizeof(client_address))) < 0)
    {
        perror("Accept failed");
        printf("Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }
}

void *send_data(void *client_socket)
{
    int i;
    char request[BUFFER_SIZE];
    pthread_t self = pthread_self();

    get_request(*(int *)client_socket, request);

    for (i = 0; i < NUM_ROUTES; i++)
    {
        if (strstr(request, routes[i]) != NULL)
        {
            if (strstr(request, "GET / ") != NULL)
            {
                root_view(client_socket);
                close(*(int *)client_socket);
                free(client_socket);
                pthread_exit(&self);
            }
            else if (strstr(request, "GET /users/") != NULL)
            {
                int i = 0;
                char id[256];
                char *tmp;
                strcpy(request, strstr(request, "GET /users/"));
                tmp = request;
                tmp = tmp + strlen("GET /users/");
                while (tmp[i] != 'H')
                {
                    id[i] = tmp[i];
                    i++;
                }
                get_user_view(client_socket, atoi(id));
                close(*(int *)client_socket);
                free(client_socket);
                pthread_exit(&self);
            }
            else if (strstr(request, "DELETE /users/") != NULL)
            {
                int i = 0;
                char id[256];
                char *tmp;
                strcpy(request, strstr(request, "DELETE /users/"));
                tmp = request;
                tmp = tmp + strlen("DELETE /users/");
                while (tmp[i] != 'H')
                {
                    id[i] = tmp[i];
                    i++;
                }
                delete_user_view(client_socket, atoi(id));
                close(*(int *)client_socket);
                free(client_socket);
                pthread_exit(&self);
            }
            else if (strstr(request, "GET /users ") != NULL)
            {
                get_users_view(client_socket);
                close(*(int *)client_socket);
                free(client_socket);
                pthread_exit(&self);
            }
        }
    }
    error_not_found(client_socket);
    pthread_exit(&self);
}

void get_request(int client_socket, char *request)
{
    int i = 0;
    char client_message[BUFFER_SIZE];

    char *current_date;
    time_t t;
    time(&t);
    current_date = ctime(&t);
    current_date[strcspn(current_date, "\n")] = 0;

    memset(client_message, 0, sizeof(client_message));

    if ((recv(client_socket, &client_message, sizeof(client_message), 0)) < 0)
    {
        perror("Receive error:");
        printf("Error code: %d\n", errno);
        exit(1);
    }
    printf("Client message: %s\n", client_message);

    while (client_message[i] != '\n')
    {
        strncat(request, &client_message[i], 1);
        i++;
    }
    printf("[%s] - ", current_date);
    printf("%s\n", request);
    memset(client_message, 0, sizeof(client_message));
}