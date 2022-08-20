#include "../include/server.h"
#include "../include/database.h"

int server_socket;

void handle_signal(int sig);

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    signal(SIGINT, handle_signal);

    // test user insertion
    user user1;
    strcpy(user1.name, "John");
    strcpy(user1.surname, "Doe");
    create_user(user1, NULL);

    user user2;
    strcpy(user2.name, "Billy");
    strcpy(user2.surname, "Bob");
    create_user(user2, NULL);

    create_server(server_socket, "0.0.0.0", 8001, 10);
    return 0;
}

void handle_signal(int sig)
{
    printf("\nCaught interrupt signal %d\n", sig);
    printf("Closing socket ...\n");
    if (close(server_socket) == 0)
    {
        puts("Socket closed!");
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("An error occurred while closing the socket: ");
        printf("Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }
}