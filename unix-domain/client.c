#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <poll.h>

#define SOCKET_PATH "/tmp/chat_socket"
#define BUFFER_SIZE 256

int main() {
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_un address = {
        .sun_family = AF_UNIX,
        .sun_path = SOCKET_PATH
    };

    if (connect(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("connect");
        exit(1);
    }

    struct pollfd fds[2] = {
        { 0, POLLIN, 0 },   
        { sockfd, POLLIN, 0 } 
    };

    char buffer[BUFFER_SIZE] = { 0 };
    
    for (;;) {
        int ret = poll(fds, 2, -1); 

        if (ret == -1) {
            perror("poll");
            exit(1);
        }

        if (fds[0].revents & POLLIN) {
            fgets(buffer, BUFFER_SIZE, stdin);
            
            if (buffer[strlen(buffer) - 1] == '\n') {
                buffer[strlen(buffer) - 1] = '\0';
            }

            send(sockfd, buffer, strlen(buffer), 0);
            fflush(stdout);
        }

        if (fds[1].revents & POLLIN) {
            int bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received == 0) {
                printf("Server disconnected\n");
                break;
            }

            printf("\rSERVER: %s\n", buffer);
            fflush(stdout);
        }
    }
    close(sockfd);
    return 0;
}
