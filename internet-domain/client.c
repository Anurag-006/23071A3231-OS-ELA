#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<poll.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address = {
        AF_INET,
        htons(9999),
        0
    };

    connect(sockfd, (struct sockaddr*) &address, sizeof(address));

    struct pollfd fds[2] = {
        {
            0,
            POLLIN,
            0
        },
        {
            sockfd,
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
            send(sockfd, buffer, 255, 0);
            fflush(stdout);
        } else if (fds[1].revents & POLLIN) {
            if (recv(sockfd, buffer, 255, 0) == 0) {
                return 0;
            }
            printf("\rSERVER: %s\n", buffer);
            fflush(stdout);
        }
    }
    return 0;
}
