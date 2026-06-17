#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
int main(int argc, char * argv[]) {
    if(argc!=2){
        std::cout<<"Usage : ./v1 <hostname> \n";
        return 1;
    }
    const char *hostname = argv[1];
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    // Setup hints structure
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM; // SOCK_STREAM or SOCK_DGRAM

    // Perform DNS lookup
    if ((status = getaddrinfo(hostname, NULL, &hints, &res)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
        return 1;
    }

    // Print IP addresses
    std::cout << "IP addresses for " << hostname << ":" << std::endl;

    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        // Convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        std::cout << ipstr << std::endl;
    }

    freeaddrinfo(res); // Free the linked list

    return 0;
}
