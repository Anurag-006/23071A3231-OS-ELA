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

    unlink(SOCKET_PATH);

    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, 10) == -1) {
        perror("listen");
        exit(1);
    }

    int clientfd = accept(sockfd, NULL, NULL);
    if (clientfd == -1) {
        perror("accept");
        exit(1);
    }

    struct pollfd fds[2] = {
        { 0, POLLIN, 0 },
        { clientfd, POLLIN, 0 }
    };

    for (;;) {
        char buffer[BUFFER_SIZE] = { 0 };

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
