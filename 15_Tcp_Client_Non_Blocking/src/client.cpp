#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // 1. Get current flags and add O_NONBLOCK
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 2. Initiate connection
    int res = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (res < 0) {
        // EINPROGRESS means the handshake has started but isn't finished yet
        if (errno == EINPROGRESS) {
            printf("Connection in progress... (Non-blocking mode)\n");
            
            // At this point, the program is free to do other work.
            // When you are ready to check the status, you would use select() or poll().
        } else {
            perror("Connect error");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Connected immediately!\n");
    }

    close(sockfd);
    return 0;
}