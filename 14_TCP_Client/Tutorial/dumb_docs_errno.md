# ERRNO - THE ERROR NUMBER SYSTEM

---

## WHAT IS ERRNO?

errno is a **global variable** that stores the last error code from system calls.

**KEY FACTS:**
- Defined in <errno.h>
- Set automatically when system calls fail
- Only meaningful when function returns -1
- Never reset to 0 automatically
- Thread-local in modern systems (each thread has its own)

---

## HOW TO USE ERRNO

**BASIC PATTERN:**
```c
#include <errno.h>
#include <string.h>

int result = connect(sock, addr, len);
if (result == -1) {
    // errno now contains the error code
    printf("Error number: %d\n", errno);
    printf("Error message: %s\n", strerror(errno));
    perror("connect");  // prints "connect: error message"
}
```

**CRITICAL RULE:**
- Check errno IMMEDIATELY after failure
- Any successful system call may reset errno
- Save errno if you need it later:
```c
int saved_errno = errno;  // save it
// do other stuff
// use saved_errno
```

---

## ERRNO CATEGORIES

**PERMANENT ERRORS:** Won't succeed without changing something
- EINVAL: invalid parameter
- EPERM: permission denied
- EBADF: bad file descriptor

**TEMPORARY ERRORS:** May succeed if you retry
- EAGAIN: resource temporarily unavailable
- EINTR: interrupted by signal
- EINPROGRESS: operation in progress

**NETWORK ERRORS:**
- ECONNREFUSED: connection refused
- ETIMEDOUT: operation timed out
- ENETUNREACH: network unreachable

---

## COMPLETE ERRNO LIST FOR SOCKETS

### SOCKET CREATION ERRORS

| Error | Value | Meaning |
|-------|-------|---------|
| EACCES | 13 | Permission denied |
| EAFNOSUPPORT | 97 | Address family not supported |
| EINVAL | 22 | Invalid argument |
| EMFILE | 24 | Too many open files (process limit) |
| ENFILE | 23 | Too many open files (system limit) |
| EPROTONOSUPPORT | 93 | Protocol not supported |
| EPROTOTYPE | 91 | Protocol wrong type for socket |
| ESOCKTNOSUPPORT | 94 | Socket type not supported |

### BIND ERRORS

| Error | Value | Meaning |
|-------|-------|---------|
| EADDRINUSE | 98 | Address already in use |
| EADDRNOTAVAIL | 99 | Address not available |
| EACCES | 13 | Permission denied (ports < 1024 need root) |
| EINVAL | 22 | Socket already bound |

### CONNECT ERRORS

| Error | Value | Meaning |
|-------|-------|---------|
| EINPROGRESS | 115 | Operation in progress (non-blocking) |
| EAGAIN | 11 | Try again (non-blocking) |
| ECONNREFUSED | 111 | Connection refused |
| ETIMEDOUT | 110 | Connection timed out |
| ENETUNREACH | 101 | Network unreachable |
| EHOSTUNREACH | 113 | Host unreachable |
| EADDRINUSE | 98 | Local address already in use |
| EALREADY | 114 | Operation already in progress |
| EISCONN | 106 | Already connected |

### ACCEPT ERRORS

| Error | Value | Meaning |
|-------|-------|---------|
| EAGAIN | 11 | No pending connections (non-blocking) |
| EWOULDBLOCK | 11 | Same as EAGAIN on Linux |
| ECONNABORTED | 103 | Connection aborted |
| EINTR | 4 | System call interrupted |
| EMFILE | 24 | Too many open files |

### SEND ERRORS

| Error | Value | Meaning |
|-------|-------|---------|
| EAGAIN | 11 | Buffer full (non-blocking) |
| EWOULDBLOCK | 11 | Same as EAGAIN |
| EPIPE | 32 | Broken pipe (connection closed) |
| ECONNRESET | 104 | Connection reset by peer |
| EMSGSIZE | 90 | Message too large |
| EINTR | 4 | Interrupted by signal |

### RECV ERRORS

| Error | Value | Meaning |
|-------|-------|---------|
| EAGAIN | 11 | No data (non-blocking) |
| EWOULDBLOCK | 11 | Same as EAGAIN |
| ECONNRESET | 104 | Connection reset |
| EINTR | 4 | Interrupted by signal |
| EINVAL | 22 | Invalid argument |

### CLOSE ERRORS

| Error | Value | Meaning |
|-------|-------|---------|
| EBADF | 9 | Bad file descriptor |
| EINTR | 4 | Interrupted by signal |

### COMMON GENERAL ERRORS

| Error | Value | Meaning |
|-------|-------|---------|
| EPERM | 1 | Operation not permitted |
| ENOENT | 2 | No such file or directory |
| ESRCH | 3 | No such process |
| EINTR | 4 | Interrupted system call |
| EIO | 5 | I/O error |
| ENXIO | 6 | No such device or address |
| E2BIG | 7 | Argument list too long |
| ENOEXEC | 8 | Exec format error |
| EBADF | 9 | Bad file number |
| ECHILD | 10 | No child processes |
| EAGAIN | 11 | Try again |
| ENOMEM | 12 | Out of memory |
| EACCES | 13 | Permission denied |
| EFAULT | 14 | Bad address |
| ENOTBLK | 15 | Block device required |
| EBUSY | 16 | Device or resource busy |
| EEXIST | 17 | File exists |
| EXDEV | 18 | Cross-device link |
| ENODEV | 19 | No such device |
| ENOTDIR | 20 | Not a directory |
| EISDIR | 21 | Is a directory |
| EINVAL | 22 | Invalid argument |
| ENFILE | 23 | File table overflow |
| EMFILE | 24 | Too many open files |
| ENOTTY | 25 | Not a typewriter |
| ETXTBSY | 26 | Text file busy |
| EFBIG | 27 | File too large |
| ENOSPC | 28 | No space left on device |
| ESPIPE | 29 | Illegal seek |
| EROFS | 30 | Read-only file system |
| EMLINK | 31 | Too many links |
| EPIPE | 32 | Broken pipe |
| EDOM | 33 | Math argument out of domain |
| ERANGE | 34 | Math result not representable |

---

## SPECIAL ERRNO BEHAVIORS

### EAGAIN vs EWOULDBLOCK
- On Linux: same value (11)
- On some systems: different values
- Always check both if you want portability:
```c
if (errno == EAGAIN || errno == EWOULDBLOCK) {
    // handle temporary failure
}
```

### EINPROGRESS
- Only for non-blocking connect()
- Means connection started
- Not an error, just need to wait
- Must use select() + getsockopt(SO_ERROR)

### EINTR
- System call interrupted by signal
- Can happen with blocking calls
- Usually safe to retry
- Common with accept(), recv(), send()

---

## HOW TO READ ERRNO VALUES

**METHOD 1: strerror()**
```c
#include <string.h>
printf("%s\n", strerror(errno));
// Output: "Connection refused"
```

**METHOD 2: perror()**
```c
#include <stdio.h>
perror("connect");
// Output: "connect: Connection refused"
```

**METHOD 3: Direct check**
```c
if (errno == ECONNREFUSED) {
    printf("Server not running\n");
}
```

---

## COMPLETE ERROR HANDLING PATTERN

```c
#include <errno.h>
#include <string.h>
#include <stdio.h>

int result = some_system_call();

if (result == -1) {
    int error = errno;  // save immediately
    
    switch(error) {
        case EAGAIN:
        case EWOULDBLOCK:
            // Temporary failure - try again later
            printf("Resource temporarily unavailable\n");
            break;
            
        case EINTR:
            // Interrupted - retry
            printf("Interrupted, retry\n");
            break;
            
        case EINPROGRESS:
            // Operation in progress (non-blocking connect)
            printf("Operation in progress\n");
            break;
            
        case ECONNREFUSED:
            // Server not running
            printf("Connection refused - is server running?\n");
            break;
            
        case ETIMEDOUT:
            // Connection timed out
            printf("Connection timed out\n");
            break;
            
        case EADDRINUSE:
            // Port in use
            printf("Address already in use\n");
            break;
            
        case EPERM:
        case EACCES:
            // Permission issues
            printf("Permission denied\n");
            break;
            
        default:
            // Unknown error
            printf("Error %d: %s\n", error, strerror(error));
            break;
    }
}
```

---

## ERRNO VS RETURN VALUE

| Function Return | Meaning | errno |
|-----------------|---------|-------|
| 0 | Success | Unchanged (may be stale) |
| >0 | Success | Unchanged (may be stale) |
| -1 | Failure | Set to error code |
| NULL | Failure (pointer functions) | Set to error code |

**IMPORTANT:** Only trust errno when function returns error indicator:
```c
// CORRECT
int fd = socket(AF_INET, SOCK_STREAM, 0);
if (fd == -1) {
    // errno is valid
    printf("Error: %s\n", strerror(errno));
}

// INCORRECT - errno may be stale
int fd = socket(AF_INET, SOCK_STREAM, 0);
if (fd > 0) {
    // don't check errno here - it's stale
    printf("errno: %d\n", errno);  // WASTE OF TIME
}
```

---

## COMMON MISTAKES WITH ERRNO

**MISTAKE 1: Checking errno without checking return value**
```c
// WRONG
connect(sock, addr, len);
if (errno == ECONNREFUSED) {  // errno might be stale
    // handle error
}

// CORRECT
if (connect(sock, addr, len) == -1 && errno == ECONNREFUSED) {
    // handle error
}
```

**MISTAKE 2: Not saving errno**
```c
// WRONG
if (some_call() == -1) {
    printf("Error: %s\n", strerror(errno));  // might be overwritten
    some_other_call();  // this might change errno
    if (errno == EAGAIN) {  // now checking wrong error
        // handle
    }
}

// CORRECT
if (some_call() == -1) {
    int saved_errno = errno;
    printf("Error: %s\n", strerror(saved_errno));
    some_other_call();  // can't change saved_errno
    if (saved_errno == EAGAIN) {
        // handle
    }
}
```

**MISTAKE 3: Assuming errno is 0 on success**
```c
// WRONG
errno = 0;
some_call();
if (errno != 0) {  // won't work - errno not reset on success
    // handle error
}

// CORRECT
if (some_call() == -1) {
    // handle error using errno
}
```

---

## PORTABILITY NOTES

- errno values are system-dependent
- Some values differ between Linux, BSD, Solaris
- Use symbolic constants, not numeric values
- strerror() is thread-safe in modern systems
- perror() writes to stderr (not thread-safe)

---

## QUICK REFERENCE CARD

```
check return value first
if (-1) then errno is valid

EAGAIN       = try again later (not error)
EWOULDBLOCK  = same as EAGAIN on Linux
EINPROGRESS  = operation started (non-blocking connect)
EINTR        = interrupted, retry
ECONNREFUSED = server not listening
ETIMEDOUT    = connection took too long
EADDRINUSE   = port already taken
EPIPE        = writing to closed connection
ECONNRESET   = peer closed connection
EINVAL       = bad parameter passed
EACCES       = permission denied
EBADF        = invalid file descriptor

always use strerror() to get readable message
save errno immediately if calling other functions
check both EAGAIN and EWOULDBLOCK for portability
```