#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    // setting the server address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8082);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    // creating the socket
    int sock_fd;
    printf("Creating the socket\n");
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "socket_creation failed\n");
        return -1;
    }

    // create the synchrnous connection
    printf("Connecting to the server at port : %d\n", server_address.sin_port);
    if (connect(sock_fd, (struct sockaddr *)(&server_address), sizeof(server_address)) == -1)
    {
        fprintf(stderr, "socket connection failed\n");
        fprintf(stderr, "%s", strerror(errno));
        return -1;
    }
    printf("Starting to send bytes\n");

    // send some bytes there
    const char *text = "Client: garbage is garbage.\n";
    size_t len = strlen(text);
    size_t bytes_sent = 0;
    printf("Sending total %d bytes\n", len);
    while (bytes_sent < len)
    {
        // yo, send some bytes

        size_t sb = send(sock_fd, text + bytes_sent, len - bytes_sent, 0);
        printf("sent  %d bytes\n", (int)sb);

        if (sb == -1 )
            break;
        bytes_sent += sb;
    }
    shutdown(sock_fd, SHUT_WR);
    printf("Sending bytes done \n");

    printf("Starting to recv bytes\n");

    // receive the request
    size_t off = 0;
    size_t bytes_stored = 0;
    const size_t SIZE = 1024;
    ;
    char buf[SIZE];

    while ((off = recv(sock_fd, buf + bytes_stored, SIZE - bytes_stored, 0)) > 0)
    {
        if (off == -1)
            break;
        bytes_stored += off;
    }
    buf[bytes_stored] = '\0';

    printf("recv bytes done \n");
    printf("recv : %s\n", buf);

    close(sock_fd);
}