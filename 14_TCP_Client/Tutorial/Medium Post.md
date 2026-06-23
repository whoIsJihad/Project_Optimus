IP/TCP programming is fundamental for creating networked applications, from simple chat programs to sophisticated web servers. Modern C++ offers robust features that simplify network programming. This guide will help you get started with IP/TCP programming using C++.

### Prerequisites

Before diving into the code, make sure you have a basic understanding of C++ and have your development environment set up. You’ll need a C++ compiler that supports C++11 or later.

### Setting Up Your Environment

Ensure you have a compiler installed, such as GCC or Clang on Linux, or Visual Studio on Windows. We’ll be using standard C++ libraries, so no additional libraries are required.

### Creating a Simple TCP Server

Let’s start by creating a simple TCP server. This server will listen for incoming connections and echo any received messages back to the client.
```cpp
#include <iostream>  
#include <string>  
#include <memory>  
#include <cstring>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <unistd.h>  
  
constexpr int PORT = 8080;  
constexpr int BUFFER_SIZE = 1024;  
  
int main() {  
    int server_fd, new_socket;  
    struct sockaddr_in address;  
    int opt = 1;  
    socklen_t addrlen = sizeof(address);  
    char buffer[BUFFER_SIZE] = {0};  
    // Creating socket file descriptor  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
    // Forcefully attaching socket to the port 8080  
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons(PORT);  
    // Bind the socket to the network address and port  
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    // Start listening for incoming connections  
    if (listen(server_fd, 3) < 0) {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
    std::cout << "Server listening on port " << PORT << std::endl;  
    // Accept incoming connection  
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {  
        perror("accept");  
        exit(EXIT_FAILURE);  
    }  
    // Read and echo the received message  
    ssize_t valread = read(new_socket, buffer, BUFFER_SIZE);  
    std::cout << "Received: " << buffer << std::endl;  
    send(new_socket, buffer, valread, 0);  
    std::cout << "Echo message sent" << std::endl;  
    // Close the socket  
    close(new_socket);  
    close(server_fd);  
    return 0;  
}
```

### Creating a Simple TCP Client

Next, let’s create a simple TCP client that connects to the server and sends a message.
```cpp

#include <iostream>  
#include <string>  
#include <memory>  
#include <cstring>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
  
constexpr int PORT = 8080;  
constexpr int BUFFER_SIZE = 1024;  
int main() {  
    int sock = 0;  
    struct sockaddr_in serv_addr;  
    char buffer[BUFFER_SIZE] = {0};  
    // Creating socket file descriptor  
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
        std::cerr << "Socket creation error" << std::endl;  
        return -1;  
    }  
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(PORT);  
    // Convert IPv4 and IPv6 addresses from text to binary form  
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {  
        std::cerr << "Invalid address/ Address not supported" << std::endl;  
        return -1;  
    }  
    // Connect to the server  
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {  
        std::cerr << "Connection Failed" << std::endl;  
        return -1;  
    }  
    std::string hello = "Hello from client";  
    send(sock, hello.c_str(), hello.size(), 0);  
    std::cout << "Hello message sent" << std::endl;  
    ssize_t valread = read(sock, buffer, BUFFER_SIZE);  
    std::cout << "Received: " << buffer << std::endl;  
    // Close the socket  
    close(sock);  
    return 0;  
}
```

### Explanation of the Code

**Socket Creation**:

- Both the server and client create a socket using the `socket` function, specifying the address family (`AF_INET` for IPv4), the socket type (`SOCK_STREAM` for TCP), and the protocol (`0` to use the default protocol for the given socket type).

Press enter or click to view image in full size

![](https://miro.medium.com/v2/resize:fit:413/1*YD439P2R3Zgt_WOy6e3Jng.png)

Entire Steps for creating a Simple Client/Server Module [1]

**Server Binding and Listening**:

- The server sets socket options and binds it to a specific port (`8080`).
- It then listens for incoming connections with the `listen` function.

**Client Connecting**:


- The client specifies the server address and port, converting the IP address to the correct format using `inet_pton`.
- It then connects to the server using the `connect` function.

**Data Transmission**:

- The client sends a message to the server.
- The server reads the message, prints it, and sends the same message back to the client (echo).
- The client reads the echoed message and prints it.

**Socket Closure**:

- Both the server and client close their sockets after communication is done to free up resources.

### Running the Code

**Compile the server and client programs using your C++ compiler.**

g++ -std=c++11 -o server server.cpp   
g++ -std=c++11 -o client client.cpp

**Run the server program first.**

./server

**In another terminal, run the client program.**

./client

You should see the server receiving the message from the client and echoing it back.

### Conclusion

This guide provided a basic introduction to IP/TCP programming using modern C++. By leveraging the standard library and C++ features, you can create efficient and maintainable networked applications. While this example uses basic socket programming, more advanced applications may benefit from higher-level libraries. However, understanding the fundamentals empowers you to build more complex and robust networked systems. Happy coding!