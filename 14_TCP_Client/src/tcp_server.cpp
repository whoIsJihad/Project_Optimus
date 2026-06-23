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
    int st;
    // create the socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
    {
        fprintf(stderr, "Socket creation failed\n");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8082);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // bind the port to the socket
    if ((st = bind(sock_fd, (const struct sockaddr *)(&server_addr), sizeof(server_addr))) == -1)
    {
        fprintf(stderr, "%s", (const char *)strerror(errno));

        return 1;
    }
    printf("Binded to the port\n");
    printf("Listening now...\n");

    // listen on that socket
    int lis_sock_fd = listen(sock_fd, 20);

    if (lis_sock_fd == -1)
    {
        fprintf(stderr, "%s", (const char *)strerror(errno));
        return 1;
    }
    printf("Trying to connect to the the client\n");
    // accept the connection
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int acc_sock_fd = accept(sock_fd, (struct sockaddr *)(&client_addr), &addr_len);
    // int acc_sock_fd = accept(sock_fd, (struct sockaddr *)(&client_addr), (socklen_t *)(sizeof client_addr));
    printf("Connected to the client\n");

    // receive bytes
    printf("Starting to receive bytes\n");
    int off = 0;
    size_t bytes_stored = 0;
    const size_t SIZE = 1024;

    char buf[SIZE];

    while ((off = recv(acc_sock_fd, buf + bytes_stored, SIZE - bytes_stored, 0)) > 0)
    {  
        if(off==-1 || off ==0) break;

        printf("received bytes %d\n ", off);
        bytes_stored += off;
    }
    if (off == -1)
    {
        fprintf(stderr, "recv error: %s\n", strerror(errno));
    }

    buf[bytes_stored] = '\0';
    printf("Receiving bytes done \n");
    printf("Recieved : %s \n", buf);

    // send bytes
    printf("Starting to send bytes\n");
    const char *text = " Server :Not garbage is also garbage\n";
    size_t len = strlen(text);
    size_t bytes_sent = 0;
    while (bytes_sent < len)
    {
        // yo, send some bytes
        size_t sb = send(acc_sock_fd, text + bytes_sent, len - bytes_sent, 0);
        if (sb == -1)
            break;
        bytes_sent += sb;
    }
    printf("sending bytes done \n");

    close(sock_fd);
    close(lis_sock_fd);
}