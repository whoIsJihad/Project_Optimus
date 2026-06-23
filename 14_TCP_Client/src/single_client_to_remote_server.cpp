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

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage : ./v1 hostname\n");
        exit(1);
    }
    int st, sock_fd;

    // create the socket
    struct addrinfo hints, *server_info, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // we dont care if it is ipv4 or ipv6
    hints.ai_socktype = SOCK_STREAM; // we are building a tcp socket

    // get the address of the server from the hostname
    if ((st = getaddrinfo(argv[1], "http", &hints, &server_info)) != 0)
    {
        fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(st));
        return 1;
    }

    // server info now contains a linked list of all the results (from the dns query)
    //  walk the serverinfo now and connect to the first addr
    for (p = server_info; p != NULL; p = p->ai_next)
    {
        //creation of the socket
        if ((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            fprintf(stderr, "client :socket");
            continue;
        }
        // connecting to server
        if (connect(sock_fd, p->ai_addr, p->ai_addrlen) == -1)
        {
            perror("client: connect");
            close(sock_fd);
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    freeaddrinfo(server_info);

    // send raw http query to the server 

    const char* req = 
    "GET / HTTP/1.1\r\n"
    "Host: www.google.com\r\n"
    "User-Agent: MyCustomClient/1.0\r\n"
    "Accept: text/html\r\n"
    "Connection: close\r\n"
    "\r\n";


    size_t len = strlen(req);
    size_t sent_bytes=0;
    while (sent_bytes<len)
    {
        size_t sb= send(sock_fd, req+sent_bytes, len-sent_bytes, 0);
        /* code */
        
        sent_bytes+=sb;
    }
    


    // receive the request
    int off = 0;
    const int SIZE=1024;;
    char buf[SIZE];

    while ((off = recv(sock_fd, buf, SIZE - 1, 0)) > 0)
    {
        buf[off] = '\0'; // Null-terminate the string
        printf("%s", buf);
    }

    close(sock_fd);
}