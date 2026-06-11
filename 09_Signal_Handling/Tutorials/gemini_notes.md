# Signal Handling in C++: From First Principles

## 1. What are Signals?

At its core, a **signal** is a "software interrupt" delivered to a process. It is a notification from the Operating System (OS) or another process that a specific event has occurred.

Think of it like a **telephone call** or a **doorbell**. Your program is running its usual loop, and suddenly "the phone rings." The program must decide:
1.  Ignore it (if possible).
2.  Stop what it's doing, handle the call, then go back to work.
3.  Let the OS handle it (default behavior, usually terminating the program).

### Key Characteristics:
*   **Asynchronous:** Signals can arrive at any time. Your code doesn't "poll" for signals; the OS forces your code to jump to a handler function.
*   **Lightweight:** They carry almost no data—just a signal number (e.g., `SIGINT` is usually `2`).
*   **Inter-Process Communication (IPC):** One process can send a signal to another (e.g., using the `kill` command).

---

## 2. Why are Signals Useful?

Signals are the primary way the OS communicates critical events to your program:

1.  **Hardware Exceptions:** When your code does something "bad" (like dividing by zero or accessing invalid memory), the CPU triggers an exception, and the OS translates it into a signal (`SIGFPE` or `SIGSEGV`).
2.  **External Interrupts:** When a user presses `Ctrl+C`, the terminal driver sends a `SIGINT` to the foreground process.
3.  **Process Lifecycle:** When a child process finishes, the parent gets a `SIGCHLD`.
4.  **Graceful Shutdown:** `SIGTERM` tells your program "Please shut down now," giving it a chance to save files and close database connections.
5.  **Asynchronous Events:** `SIGALRM` acts like a kitchen timer, waking your process after a certain duration.

---

## 3. Core Concepts

### A. Signal Lifetime
1.  **Generation:** An event occurs (e.g., `Ctrl+C`).
2.  **Pending:** The OS has noted the signal but hasn't delivered it yet (maybe signals are "blocked").
3.  **Delivery:** The OS pauses the process's normal execution and forces it to run the **Signal Handler**.

### B. Default Actions
Every signal has a default action:
*   **Term:** Terminate the process.
*   **Core:** Terminate and dump a "core" file (memory snapshot for debugging).
*   **Ign:** Ignore the signal.
*   **Stop:** Pause the process.
*   **Cont:** Resume a paused process.

---

## 4. Signal Handling in C++

### The Legacy Way: `signal()`
The `<csignal>` header provides a simple function to catch signals.

```cpp
#include <iostream>
#include <csignal>
#include <unistd.h>

void my_handler(int signum) {
    // Note: This is technically UNSAFE (see below)
    std::cout << "Received signal " << signum << "\n";
}

int main() {
    signal(SIGINT, my_handler); // Catch Ctrl+C

    while(true) {
        std::cout << "Working hard..." << std::endl;
        sleep(1);
    }
    return 0;
}
```

### The Modern Way: `sigaction()`
On Linux/Unix, `sigaction` is much more robust and predictable than `signal()`. It allows you to block other signals while the handler is running.

---

## 5. The Golden Rule: Async-Signal Safety

This is the most important concept for C++ developers. Since a signal can arrive **anywhere** (even inside a call to `std::cout` or `malloc`), your handler must be extremely careful.

**NEVER** do the following in a signal handler:
*   Use `std::cout`, `printf`, or any I/O.
*   Use `new`, `malloc`, or `free`.
*   Lock a `std::mutex`.

**What CAN you do?**
*   Set a `volatile sig_atomic_t` flag.
*   Call "Async-Signal-Safe" functions (like `write()`, `_exit()`).

### The Recommended Pattern:
```cpp
#include <csignal>
#include <atomic>

// This flag is safe to read/write from handlers
std::atomic<bool> keep_running(true);

void shutdown_handler(int sig) {
    keep_running = false; // Just set a flag and return
}

int main() {
    signal(SIGINT, shutdown_handler);

    while(keep_running) {
        // Do actual work here
    }
    
    // Clean up gracefully out here!
    return 0;
}
```

---

## 6. Common Signal Reference

| Signal | Name | Trigger | Default Action | Use Case |
| :--- | :--- | :--- | :--- | :--- |
| **SIGINT** | Interrupt | `Ctrl+C` | Terminate | Stop program manually. |
| **SIGTERM** | Terminate | `kill pid` | Terminate | Graceful shutdown request. |
| **SIGKILL** | Kill | `kill -9` | Terminate | Forceful stop (cannot be caught). |
| **SIGSEGV** | Segfault | Invalid Memory | Core Dump | Bug detection (Crashes). |
| **SIGHUP** | Hangup | Terminal Closed | Terminate | Often used to trigger "Reload Config". |
| **SIGALRM** | Alarm | `alarm()` timer | Terminate | Timeouts. |
| **SIGCHLD** | Child | Child exited | Ignore | Clean up "zombie" processes. |
