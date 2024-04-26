#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *confirmation = "Room booked successfully.";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accepting incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        // Reading client's message
        valread = read(new_socket, buffer, 1024);
        printf("%s\n", buffer);

        // Prompting user for number of rooms and number of days
        int num_rooms, num_days;
        printf("Enter number of rooms: ");
        while (scanf("%d", &num_rooms) != 1 || num_rooms < 1 || num_rooms > 10) {
            printf("Invalid input. Enter a number between 1 and 10: ");
            while (getchar() != '\n');
        }
        printf("Enter number of days: ");
        while (scanf("%d", &num_days) != 1 || num_days < 1 || num_days > 7) {
            printf("Invalid input. Enter a number between 1 and 7: ");
            while (getchar() != '\n');
        }

        // Sending confirmation message to client
        send(new_socket, confirmation, strlen(confirmation), 0);
        printf("Confirmation message sent\n");

        // Clearing buffer and closing socket
        memset(buffer, 0, sizeof(buffer));
        close(new_socket);
    }

    return 0;
}
