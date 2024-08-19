#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345

void sendString(int sockfd, const struct sockaddr_in *server_addr, const char *str)
{
    if (strlen(str) >= BUFFER_SIZE)
    {
        printf("Error:String is too long to sent.\n");
        return;
    }
    if (sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)server_addr, sizeof(*server_addr)) < 0)
    {
        perror("sendto failed");
    }
}
int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    char message[BUFFER_SIZE];
    printf("Enter message to send: ");
    fgets(message, BUFFER_SIZE, stdin);
    message[strcspn(message, "\n")] = 0;

    sendString(sockfd, &server_addr, message);
    close(sockfd);
    return 0;
}