
## Track 1: Tooling, Compilation & File Systems (C/C++)

### 1. The Multi-File Greeter

- **What to build:** A program where `main.cpp` calls a function in `hello.cpp` (defined in `hello.h`) to print text. Compile manually using raw `g++` flags without an IDE.
    

### 2. The Dependency Automation File

- **What to build:** A clean `Makefile` that builds the project from Micro-Project 1. It must recompile _only_ when a file changes and include a `clean` target.
    

### 3. The Local Git Sandbox

- **What to build:** Read the actual description from the readme.md of the project


### 4. Binary File Hex Dumper

- **What to build:** A CLI tool that reads any compiled binary file byte-by-byte and prints its contents to the terminal in hexadecimal format (similar to `xxd`).
    

### 5. Config File Reader

- **What to build:** A program that opens, reads, and updates a custom text configuration file (`config.txt`) using standard file streams (`std::fstream`).
    

### 6. Circular Byte Buffer

- **What to build:** A fixed-size FIFO (First-In, First-Out) memory buffer array that allows continuous writing and reading without memory shifting.
    

### 7. Custom Memory Allocator (Arena)

- **What to build:** A memory allocator that pre-allocates a large contiguous block of memory via `malloc` and doles out small chunks when requested, bypassing standard OS overhead.
    

### 8. Directory Content Lister

- **What to build:** A tool that traverses a given Linux folder path using POSIX directory system calls (`opendir`, `readdir`) and lists files along with their sizes.
    

### 9. System Signal Interceptor

- **What to build:** A command-line utility that ignores `Ctrl+C` interrupts (SIGINT), logs a custom message to the console instead, and gracefully exits only when receiving SIGTERM.
    

### 10. CLI Argument Tokenizer

- **What to build:** A parser that takes complex terminal flags (e.g., `--port 8080 -v --dir=/tmp`) from `argv` and organizes them into a clean internal configuration struct.
    

## Track 2: Network Foundations & Text Parsing

### 11. Raw Line Splitter

- **What to build:** A utility that reads a raw block of characters containing text separated by `\r\n` (CRLF) and splits them into distinct line strings.
    

### 12. HTTP Request-Line Extraction

- **What to build:** A parser that takes a single text string (e.g., `"GET /index.html HTTP/1.1"`) and extracts the method, target URL, and protocol version into separate variables.
    

### 13. HTTP Header Key-Value Map

- **What to build:** A parser that takes a block of raw HTTP headers, extracts each line, splits it at the first colon (`:`), and stores them inside a lookup table map.
    

### 14. URL Percent-Decoder

- **What to build:** A helper utility that parses a string containing URL-encoded characters (like transforming `%20` into a space character) back into standard plain text.
    

### 15. JSON Key-Value Tokenizer

- **What to build:** A minimal parser that reads a flat, non-nested JSON string (e.g., `{"status": 200, "msg": "ok"}`) and extracts the individual raw text values without using third-party libraries.
    

### 16. Single-Connection Echo Socket

- **What to build:** A TCP server that opens a network socket on a local port, accepts a single incoming connection, and echoes back whatever bytes it receives.
    

### 17. Multi-Packet Stream Reassembler

- **What to build:** A receiver socket program that handles incoming data chunked into arbitrary byte sizes, buffer-storing them until an explicit end-marker delimiter is encountered.
    

### 18. HTTP Statics Responder

- **What to build:** A server loop that accepts a network connection, reads a request, and writes back a hardcoded `"HTTP/1.1 200 OK\r\n\r\nHello World"` byte packet directly into the socket descriptor.
    

### 19. Local Port Prober

- **What to build:** A network tool that attempts to open TCP connections to a range of local ports sequentially to determine which ones are actively listening.
    

### 20. Socket Timeout Watchdog

- **What to build:** A socket client that configures low-level socket options (`SO_RCVTIMEO`) to forcefully drop a connection if the remote machine stops sending data within 3 seconds.
    

## Track 3: Concurrency & High-Performance Systems

### 21. Multi-Threaded Task Workers

- **What to build:** A program that spins up four native OS threads, distributes a chunk of numbers to each thread, and computes their total sum concurrently.
    

### 22. Thread-Safe Logging System

- **What to build:** A logger console class where multiple execution threads write log statements simultaneously, using mutex locking mechanisms to prevent scrambled lines.
    

### 23. Concurrent Work Queue

- **What to build:** A shared task queue data structure where worker threads safely fetch jobs using condition variables (`std::condition_variable`) to sleep when empty.
    

### 24. Thread Pool Manager

- **What to build:** A static pool of pre-initialized threads that wait for tasks to arrive in a queue, execute them, and instantly return to standby mode.
    

### 25. Non-Blocking File Descriptor Prober

- **What to build:** A polling script that marks multiple open files as non-blocking and checks them in a tight loop without letting the OS halt execution.
    

### 26. Synchronous Multiplexed Watcher (Select)

- **What to build:** A server that monitors multiple open socket connections simultaneously using the classic `select` system call loop.
    

### 27. The Linux Epoll Core

- **What to build:** A clean script that creates a Linux `epoll` instance, registers a listening socket file descriptor, and catches new connection alerts.
    

### 28. Asynchronous Edge-Triggered Consumer

- **What to build:** An `epoll` engine running in edge-triggered mode (`EPOLLET`) that clears a socket buffer using continuous, looping read actions until an `EAGAIN` signal is caught.
    

### 29. Keep-Alive Connection Tracker

- **What to build:** A system component that monitors connected sockets in an active array, recording their last active timestamp to evict stale users.
    

### 30. Shared Memory Inter-Process Comm (IPC)

- **What to build:** Two separate compiled processes that pass text messages back and forth using native Linux shared memory segments (`shmget`, `shmat`).
    

## Track 4: DevOps & Infrastructure Automation

### 31. Isolated Compiler Container

- **What to build:** A basic `Dockerfile` that packages your C++ tool alongside its build dependencies, outputting a runnable software image.
    

### 32. Multi-Stage Production Container

- **What to build:** An optimized, two-stage `Dockerfile` that uses a development image to compile your C++ code, but copies _only_ the finished raw binary into a clean, minimal container image.
    

### 33. Container Port Bridge

- **What to build:** A networking script that boots your server image inside an isolated network container, mapping local port 8080 to container port 80.
    

### 34. Local Automated Pipeline Actions

- **What to build:** A local automated workflow script that verifies code styling compliance and compiles all target source files whenever a simulated check-in happens.
    

### 35. Multi-Container Orchestration

- **What to build:** A deployment file configuration (`docker-compose.yml`) that launches your compiled server container next to an isolated mock database service container.
    

### 36. Automated Production Health Check

- **What to build:** A deployment health script that repeatedly pings a containerized backend server endpoint, automatically triggering a system restart if it receives consecutive error codes.
    

## Track 5: ML Inference Foundations & Integration

### 37. Pure Math Tensor Array

- **What to build:** A lightweight program that represents data as flat multi-dimensional memory arrays (Tensors) and performs direct matrix multiplication calculations.
    

### 38. Isolated Inference Environment

- **What to build:** A Python execution environment script that loads a pre-trained classification model file and runs a single data inference evaluation locally.
    

### 39. Model Serialization Pipeline

- **What to build:** A script that exports an active neural network topology model out of native Python frameworks into an open serialization layout format (`.onnx` or `.pt`).
    

### 40. Dynamic C Library Wrapper

- **What to build:** A small code block that uses external foreign function loading mechanics (`dlopen`, `dlsym`) to execute code from a compiled engine library file at runtime.
    

### 41. Native C++ Inference Engine

- **What to build:** A standalone C++ program that compiles against the ONNX Runtime library, imports your serialized model file, and runs a hardcoded prediction vector.
    

### 42. Real-Time Tensor Memory Mapper

- **What to build:** A memory component that accepts a raw input array stream of data bytes, formats the layout dimensions, and generates a structured native input tensor.
    

### 43. System Metric Monitor

- **What to build:** A lightweight profiling utility that parses the operating system's internal tracking endpoints (`/proc/self/stat`) to export execution memory metrics.
    

### 44. Concurrent Request Batcher

- **What to build:** An optimization module that buffers multiple single incoming inputs over a brief window, packaging them into one matrix block for high-throughput execution.
    

### 45. Multi-Model Route Controller

- **What to build:** A routing controller component that inspects incoming endpoint text signatures and selects which memory-cached model structure evaluates the payload.
    

## The Grand Capstone Project

### High-Performance Asynchronous AI Inference Gateway

Combine all 45 micro-projects into a single production-grade repository:

- **System Architecture:** Build an event-driven HTTP/1.1 server engine utilizing Linux `epoll` and a worker thread pool to manage thousands of concurrent client socket pipelines without blocking.
    
- **Data Pipeline:** Write custom, zero-copy text and JSON parsing modules to isolate and evaluate incoming HTTP POST binary payloads.
    
- **AI Execution:** Embed the native ONNX Runtime C++ library directly into the system layer. Map incoming byte stream payloads to input memory tensors, evaluate them through a cached deep-learning model, and generate JSON response packets.
    
- **Infrastructure:** Automate compilation with clean `Makefiles`, containerize the architecture using efficient multi-stage Docker configurations, and deploy the entire setup via automated production delivery pipelines.