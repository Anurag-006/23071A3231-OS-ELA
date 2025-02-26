#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<arpa/inet.h>
#include<poll.h>

#define SOCKET_PATH = "/tmp/chat_socket"
#define BUFFER_SIZE = 256

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address = {
        AF_INET,
        htons(9999),
        0
    };

    bind(sockfd, (struct sockaddr*) &address, sizeof(address));

    listen(sockfd, 10);

    int clientfd = accept(sockfd, 0, 0);

    struct pollfd fds[2] = {
        {
            0,
            POLLIN,
            0
        },
        {
            clientfd,
            POLLIN,
            0
        }
    };

    for (;;) {
        char buffer[256] = { 0 };

        poll(fds, 2, 50000);

        if (fds[0].revents & POLLIN) {
            read(0, buffer, 255);

            if (buffer[strlen(buffer) - 1] == '\n') {
                buffer[strlen(buffer) - 1] = '\0';
            }
            send(clientfd, buffer, 255, 0);
            fflush(stdout);
        } else if (fds[1].revents & POLLIN) {
            if (recv(clientfd, buffer, 255, 0) == 0) {
                return 0;
            }
            printf("\rCLIENT: %s\n", buffer);
            fflush(stdout);
        }
    }
    return 0;
}
