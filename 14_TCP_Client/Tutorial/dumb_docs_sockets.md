# SOCKET SYSTEM CALLS - TECHNICAL REFERENCE

---

## 1. socket()

```
int socket(int domain, int type, int protocol);
```

**PURPOSE:** Create communication endpoint

**PARAMETERS:**
- domain: AF_INET (IPv4), AF_INET6 (IPv6), AF_UNIX (local)
- type: SOCK_STREAM (TCP), SOCK_DGRAM (UDP), SOCK_RAW (raw)
- protocol: 0 (auto-select)

**RETURNS:**
- Success: file descriptor (integer >= 0)
- Failure: -1 (errno set)

**ERRNO VALUES:**
- EACCES: permission denied
- EAFNOSUPPORT: address family not supported
- EINVAL: invalid parameters
- EMFILE: process fd limit reached
- ENFILE: system fd limit reached
- EPROTONOSUPPORT: protocol not supported

**TRADEOFFS:**
- SOCK_STREAM: reliable, ordered, connection-based, flow control, overhead
- SOCK_DGRAM: unreliable, unordered, connectionless, low overhead
- SOCK_RAW: requires root, IP layer access

**RELATED:** fcntl(), close()

---

## 2. bind()

```
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

**PURPOSE:** Assign local address to socket (server only)

**PARAMETERS:**
- sockfd: socket descriptor from socket()
- addr: pointer to sockaddr_in (IP + port) or sockaddr_un
- addrlen: sizeof(addr)

**RETURNS:**
- Success: 0
- Failure: -1 (errno set)

**ERRNO VALUES:**
- EADDRINUSE: port already in use
- EACCES: need root for ports < 1024
- EADDRNOTAVAIL: address invalid
- EINVAL: socket already bound

**TRADEOFFS:**
- SO_REUSEADDR option allows address reuse after close
- Bind to INADDR_ANY to accept from all interfaces
- Bind to specific IP for interface restriction

**RELATED:** setsockopt(), getsockopt()

---

## 3. listen()

```
int listen(int sockfd, int backlog);
```

**PURPOSE:** Start listening for incoming connections

**PARAMETERS:**
- sockfd: bound socket descriptor
- backlog: maximum pending connection queue size

**RETURNS:**
- Success: 0
- Failure: -1 (errno set)

**ERRNO VALUES:**
- EADDRINUSE: socket not bound
- EBADF: invalid socket
- ENOTSOCK: not a socket

**TRADEOFFS:**
- backlog typically 5-128
- System may cap backlog value
- Larger backlog handles connection spikes

**RELATED:** accept(), socket()

---

## 4. accept()

```
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

**PURPOSE:** Accept incoming connection, create new socket

**PARAMETERS:**
- sockfd: listening socket descriptor
- addr: pointer to store client address (may be NULL)
- addrlen: pointer to addr size (must be initialized)

**RETURNS:**
- Success: new socket descriptor for client
- Failure: -1 (errno set)

**ERRNO VALUES:**
- EAGAIN/EWOULDBLOCK: no pending connections (non-blocking)
- ECONNABORTED: connection aborted
- EINTR: interrupted by signal
- EMFILE: process fd limit

**BLOCKING BEHAVIOR:**
- Blocks until client connects (default)
- Returns immediately with EAGAIN (non-blocking)

**RELATED:** listen(), select(), fcntl()

---

## 5. connect()

```
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

**PURPOSE:** Connect socket to remote address

**PARAMETERS:**
- sockfd: socket descriptor
- addr: remote address struct
- addrlen: sizeof(addr)

**RETURNS:**
- Success: 0
- Failure: -1 (errno set)

**ERRNO VALUES (BLOCKING):**
- ECONNREFUSED: server not listening
- ETIMEDOUT: connection timed out
- ENETUNREACH: network unreachable
- EADDRINUSE: local address in use

**ERRNO VALUES (NON-BLOCKING):**
- EINPROGRESS: connection started (not error)
- EAGAIN/EWOULDBLOCK: resource temporarily unavailable

**BLOCKING vs NON-BLOCKING:**
- Blocking: program waits until connected or fails
- Non-blocking: returns immediately with EINPROGRESS
- Check completion with select() + getsockopt(SO_ERROR)

**RELATED:** fcntl(), select(), getsockopt()

---

## 6. fcntl()

```
int fcntl(int fd, int cmd, ... /* arg */);
```

**PURPOSE:** Control file descriptor behavior

**PARAMETERS:**
- fd: socket descriptor
- cmd: F_GETFL (get flags), F_SETFL (set flags)
- arg: flags to set (O_NONBLOCK, O_RDWR)

**RETURNS:**
- F_GETFL: flags value (success), -1 (error)
- F_SETFL: 0 (success), -1 (error)

**FLAGS:**
- O_NONBLOCK: non-blocking mode
- O_RDWR: read/write access

**PATTERN:**
```
int flags = fcntl(sock, F_GETFL, 0);
fcntl(sock, F_SETFL, flags | O_NONBLOCK);  // enable
fcntl(sock, F_SETFL, flags);               // disable
```

**TRADEOFFS:**
- Non-blocking: complex code, responsive program
- Blocking: simple code, program may freeze

**RELATED:** socket(), select()

---

## 7. select()

```
int select(int nfds, fd_set *readfds, fd_set *writefds, 
           fd_set *exceptfds, struct timeval *timeout);
```

**PURPOSE:** Monitor multiple file descriptors for readiness

**PARAMETERS:**
- nfds: highest fd + 1
- readfds: set for read readiness (or NULL)
- writefds: set for write readiness (or NULL)
- exceptfds: set for exceptions (or NULL)
- timeout: wait duration (NULL=forever, {0,0}=poll)

**MACROS:**
- FD_ZERO(set): clear set
- FD_SET(fd, set): add fd to set
- FD_CLR(fd, set): remove fd from set
- FD_ISSET(fd, set): test if fd in set

**RETURNS:**
- >0: number of ready fds
- 0: timeout occurred
- -1: error

**ERRNO VALUES:**
- EINTR: interrupted by signal
- EINVAL: invalid nfds or timeout
- EBADF: invalid fd in set

**TIMEOUT STRUCT:**
```
struct timeval {
    long tv_sec;   // seconds
    long tv_usec;  // microseconds
};
```

**USE WITH CONNECT (NON-BLOCKING):**
- monitor writefds
- after select returns, check SO_ERROR

**LIMITATIONS:**
- FD_SETSIZE limit (typically 1024)
- O(n) scanning
- Use poll() or epoll() for large numbers

**RELATED:** poll(), epoll()


Think of `select()` as a **"waiting room receptionist."**

Instead of you (the program) standing in front of one door (one socket) waiting for something to happen, you go to the receptionist (`select`) and say: *"I have a list of doors (sockets). Tell me which ones actually have someone waiting behind them so I don't waste my time knocking on empty doors."*

---

### What it actually does

It tells the Operating System: **"Watch these lists of file descriptors. Don't return control to me until at least one of them is ready to be used, or until my timer runs out."**

* **`readfds`**: Tell me when I can `read()` from these sockets without blocking.
* **`writefds`**: Tell me when I can `send()` data without blocking.
* **`exceptfds`**: Tell me if something went wrong (like an "out-of-band" data error).
* **`timeout`**: "How long should I wait?" (If you set this to `NULL`, it waits forever).

---

### The "Heavy Syntax" Broken Down

The reason it looks "heavy" is that it uses `fd_set` macros instead of standard integers. You have to "prepare" your list of sockets before calling it.

**The 4-step workflow:**

1. **Clear it:** `FD_ZERO(&readfds);` (Empty the list).
2. **Add it:** `FD_SET(sockfd, &readfds);` (Add your socket to the list).
3. **Wait:** `select(maxfd + 1, &readfds, NULL, NULL, &timeout);` (Ask the OS to watch them).
4. **Check it:** `if (FD_ISSET(sockfd, &readfds))` (Which one is ready?).

---

### Why do we use it?

Without `select()`, if you have 100 clients, you would need 100 threads (one for each client) to constantly check for data. That is incredibly heavy on your RAM and CPU.

With `select()`, you can handle hundreds of connections in **one single thread**. You just put all their file descriptors in a list, call `select()`, and the kernel tells you which ones are ready to talk.

---

### A Simple "Checklist" Analogy

Imagine you are a teacher (the CPU) with 30 students (sockets).

* **Without `select()` (Blocking):** You walk up to Student 1 and wait for them to finish their work. Then you move to Student 2. If Student 1 takes an hour, Students 2-30 are ignored.
* **With `select()`:** You stand at the front of the room. You tell the class, "Raise your hand when you are done." You sit at your desk and do other work. When you see a hand go up, you go to *that specific student* to collect their work.

---

## 8. getsockopt()

```
int getsockopt(int sockfd, int level, int optname, 
               void *optval, socklen_t *optlen);
```

**PURPOSE:** Get socket options/status

**PARAMETERS:**
- sockfd: socket descriptor
- level: SOL_SOCKET (socket-level options)
- optname: option to query
- optval: pointer to store result
- optlen: pointer to size of optval

**CHECK CONNECTION STATUS:**
```
int error = 0;
socklen_t len = sizeof(error);
getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, &len);
// error == 0: connected
// error == EINPROGRESS: still connecting
// error == other: connection failed
```

**COMMON OPTNAMES:**
- SO_ERROR: error status
- SO_REUSEADDR: address reuse
- SO_KEEPALIVE: keep connection alive
- SO_RCVBUF: receive buffer size
- SO_SNDBUF: send buffer size

**RETURNS:**
- Success: 0
- Failure: -1 (errno set)

**RELATED:** setsockopt(), connect()

---

## 9. send()

```
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

**PURPOSE:** Send data on connected socket

**PARAMETERS:**
- sockfd: connected socket descriptor
- buf: data buffer
- len: bytes to send
- flags: MSG_DONTWAIT (non-blocking), MSG_NOSIGNAL (no SIGPIPE)

**RETURNS:**
- '>0': bytes actually sent
- 0: connection closed (TCP)
- -1: error

**ERRNO VALUES:**
- EAGAIN/EWOULDBLOCK: buffer full (non-blocking)
- EPIPE: connection closed by peer
- ECONNRESET: connection reset
- EINTR: interrupted by signal

**BEHAVIOR:**
- May send fewer bytes than requested
- Must loop until all bytes sent
- Blocking: waits until buffer space available
- Non-blocking: returns EAGAIN if buffer full

**RELATED:** recv(), write()

---

## 10. recv()

```
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

**PURPOSE:** Receive data from connected socket

**PARAMETERS:**
- sockfd: connected socket descriptor
- buf: buffer to store data
- len: buffer size
- flags: MSG_DONTWAIT (non-blocking), MSG_PEEK (peek)

**RETURNS:**
- '>0': bytes received
- 0: connection closed by peer
- -1: error

**ERRNO VALUES:**
- EAGAIN/EWOULDBLOCK: no data (non-blocking)
- ECONNRESET: connection reset
- EINTR: interrupted by signal
- EINVAL: invalid parameters

**BEHAVIOR:**
- Returns whatever data is available (may be less than len)
- Blocking: waits for data
- Non-blocking: returns EAGAIN if no data

**RELATED:** send(), read()

---

## 11. close()

```
int close(int fd);
```

**PURPOSE:** Close socket, free resources

**PARAMETERS:**
- fd: socket descriptor to close

**RETURNS:**
- Success: 0
- Failure: -1 (errno set)

**BEHAVIOR:**
- Blocks until all data sent (SO_LINGER)
- Immediately closes with SO_LINGER set to 0
- Frees fd and port for reuse

**ERRNO VALUES:**
- EBADF: invalid fd
- EINTR: interrupted by signal

**RELATED:** shutdown()

---

## 12. setsockopt()

```
int setsockopt(int sockfd, int level, int optname, 
               const void *optval, socklen_t optlen);
```

**PURPOSE:** Set socket options

**PARAMETERS:**
- sockfd: socket descriptor
- level: SOL_SOCKET (socket-level)
- optname: option to set
- optval: pointer to option value
- optlen: size of optval

**COMMON OPTIONS:**
- SO_REUSEADDR: allow address reuse immediately
- SO_KEEPALIVE: send keep-alive probes
- SO_LINGER: control close behavior
- SO_RCVBUF: set receive buffer size
- SO_SNDBUF: set send buffer size

**EXAMPLE:**
```
int reuse = 1;
setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
```

**RETURNS:**
- Success: 0
- Failure: -1 (errno set)

**RELATED:** getsockopt()

---

## SERVER FLOW

**BLOCKING:**
```
socket() -> bind() -> listen() -> accept() [blocks] -> send/recv -> close()
```

**NON-BLOCKING:**
```
socket() -> bind() -> listen() -> fcntl(O_NONBLOCK) -> 
  loop: accept() -> if EAGAIN: do_other_work() else handle_client -> close()
```

---

## CLIENT FLOW

**BLOCKING:**
```
socket() -> connect() [blocks] -> send/recv -> close()
```

**NON-BLOCKING:**
```
socket() -> fcntl(O_NONBLOCK) -> connect() [returns EINPROGRESS] ->
  loop: select() -> getsockopt(SO_ERROR) -> do_other_work() ->
  if connected: send/recv -> close()
```

---

## ERROR HANDLING PATTERNS

**NON-BLOCKING CONNECT:**
```
int result = connect(sock, addr, len);
if (result == -1 && errno == EINPROGRESS) {
    // connection started, wait
    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(sock, &write_fds);
    select(sock + 1, NULL, &write_fds, NULL, &timeout);
    
    int error;
    socklen_t len = sizeof(error);
    getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, &len);
    if (error == 0) {
        // connected
    }
}
```

**NON-BLOCKING ACCEPT:**
```
int client = accept(server_sock, NULL, NULL);
if (client == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    // no clients waiting
} else if (client > 0) {
    // handle client
}
```

**NON-BLOCKING RECV:**
```
int bytes = recv(sock, buffer, sizeof(buffer), 0);
if (bytes == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    // no data yet
} else if (bytes > 0) {
    // data received
} else if (bytes == 0) {
    // connection closed
}
```

---

## BUFFER SIZE CONSTANTS

- BUFSIZ: stdio buffer (typically 8192)
- PATH_MAX: max path length (4096)
- 1024: common for network buffers
- 4096: page size
- 65536: common for larger buffers

---

## ADDRESS STRUCTURES

**IPv4 (AF_INET):**
```
struct sockaddr_in {
    sa_family_t sin_family;  // AF_INET
    in_port_t sin_port;      // htons(port)
    struct in_addr sin_addr; // IP address
};
```

**IPv6 (AF_INET6):**
```
struct sockaddr_in6 {
    sa_family_t sin6_family; // AF_INET6
    in_port_t sin6_port;     // htons(port)
    struct in6_addr sin6_addr;
};
```

**UNIX Domain (AF_UNIX):**
```
struct sockaddr_un {
    sa_family_t sun_family;  // AF_UNIX
    char sun_path[108];      // socket path
};
```

---

## COMPLETE SYSTEM CALL SUMMARY

| Call | Server | Client | Blocking Default | Non-blocking Errno |
|------|--------|--------|------------------|-------------------|
| socket | X | X | N/A | N/A |
| bind | X | | N/A | N/A |
| listen | X | | N/A | N/A |
| accept | X | | blocks | EAGAIN |
| connect | | X | blocks | EINPROGRESS |
| send | X | X | blocks | EAGAIN |
| recv | X | X | blocks | EAGAIN |
| close | X | X | N/A | N/A |