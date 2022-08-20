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
    user1.name = "John";
    user1.surname = "Doe";
    insert_user(user1);

    user user2;
    user2.name = "Billy";
    user2.surname = "Bob";
    insert_user(user2);

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