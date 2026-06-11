# Signal Handling in C++

**Last Updated:** 27 Apr, 2026

Signals are a mechanism used by the operating system to notify a process that a specific event has occurred, such as an interrupt from the user (e.g., `Ctrl+C`) or an error condition. A process can handle these signals using signal handlers or allow the default action to occur.

## Introduction

The following program demonstrates a basic loop. By default, when you press `Ctrl+C`, the `SIGINT` signal is generated, and it terminates the program.

```cpp
#include <iostream>

using namespace std;

int main() {
    while(true) {
        cout << "GFG!\n";
    }
    return 0;
}
```

## Common Signals and Operations

C++ provides several predefined signals that you can work with:

| Signal Name | Description | Default Behavior |
| :--- | :--- | :--- |
| **SIGABRT** | Abnormal termination triggered by `abort()` | Terminate |
| **SIGFPE** | Floating-point exception (e.g., division by zero) | Terminate |
| **SIGILL** | Illegal instruction (invalid machine code) | Terminate |
| **SIGINT** | Interrupt signal (triggered by `Ctrl + C`) | Terminate |
| **SIGSEGV** | Segmentation fault (invalid memory access) | Terminate |
| **SIGTERM** | Termination request (sent by `kill`) | Terminate |
| **SIGKILL** | Forceful termination (cannot be caught/ignored) | Terminate |
| **SIGQUIT** | Quit signal (similar to `SIGINT` + core dump) | Terminate + Core |
| **SIGCHLD** | Child process terminated or stopped | Ignore |
| **SIGSTOP** | Stop signal (cannot be caught/ignored) | Stop/Pause |
| **SIGSYS** | Bad system call | Terminate |
| **SIGUSR1** | User-defined signal 1 | Terminate |

---

## Signal Handling in C++

Each signal has a default behavior, but it can be overridden. The process of handling signals manually is called **Signal Handling**. This is done by assigning a "handler function" to a signal using the `signal()` function.

### Syntax
```cpp
signal(signal_type, signal_handler);
```

*   **`signal_type`**: The integer ID of the signal to catch.
*   **`signal_handler`**: The function to call when the signal arrives.

### Example: Catching SIGINT
```cpp
#include <csignal>
#include <iostream>

using namespace std;

// Signal handler function
void signalHandler(int sig) {
    cout << "\nInterrupt received (Signal: " << sig << ")" << endl;
    // Optionally exit the program
    exit(sig);
}

int main() {
    // Register the signal handler
    signal(SIGINT, signalHandler);

    cout << "Press Ctrl+C to trigger the handler..." << endl;

    while (true) {
        // Program continues until signal is received
    }
    return 0;
}
```

---

## Raising Signals Manually

You can also trigger signals programmatically from within your own code.

### 1. The `raise()` Function
The `raise()` function sends a signal to the **current** process.

**Syntax:**
```cpp
raise(signal_type);
```

**Example:**
```cpp
#include <csignal>
#include <iostream>

using namespace std;

void signalHandler(int sig) {
    cout << "Caught signal: " << sig << endl;
    exit(sig);
}

int main() {
    signal(SIGINT, signalHandler);
    
    cout << "Raising SIGINT manually..." << endl;
    raise(SIGINT);
    
    return 0;
}
```

### 2. The `kill()` Function
The `kill()` function is more powerful as it can send signals to **other** processes. It is part of the POSIX standard (available on Linux/Unix).

**Syntax:**
```cpp
kill(pid, signal_type);
```

**Example:**
```cpp
#include <iostream>
#include <csignal>
#include <unistd.h> 

using namespace std;

void handle_signal(int signal_num) {
    cout << "Received signal: " << signal_num << endl;
}

int main() {
    signal(SIGINT, handle_signal);

    // Get the current process's ID
    pid_t pid = getpid();

    cout << "Sending SIGINT to myself (PID: " << pid << ")..." << endl;
    kill(pid, SIGINT);
    
    return 0;
}
```
