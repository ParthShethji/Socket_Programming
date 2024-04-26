#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connecting to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

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

    // Converting user input to string
    char num_rooms_str[10], num_days_str[10];
    sprintf(num_rooms_str, "%d", num_rooms);
    sprintf(num_days_str, "%d", num_days);

    // Sending user input to server
    send(sock, num_rooms_str, strlen(num_rooms_str), 0);
    send(sock, " ", 1, 0);
    send(sock, num_days_str, strlen(num_days_str), 0);
    printf("User input sent\n");

    // Receiving confirmation message from server
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    return 0;
}
