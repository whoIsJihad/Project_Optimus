## Track 1: Tooling, Compilation & File Systems (C/C++)

### 1. The Multi-File Greeter

- **What to build:** A program where `main.cpp` calls a function in `hello.cpp` (defined in `hello.h`) to print text. Compile manually using raw `g++` flags without an IDE.
    
### 2. The Dependency Automation File

- **What to build:** A clean `Makefile` that builds the project from Micro-Project 1. It must recompile _only_ when a file changes and include a `clean` target.
    

### 4. Binary File Hex Dumper

- **What to build:** A CLI tool that reads any compiled binary file byte-by-byte and prints its contents to the terminal in hexadecimal format (similar to `xxd`).
    
### 5. Config File Reader

- **What to build:** A program that opens, reads, and updates a custom text configuration file (`config.txt`) using standard file streams (`std::fstream`).
    

### 6. Circular Byte Buffer

- **What to build:** A fixed-size FIFO (First-In, First-Out) memory buffer array that allows continuous writing and reading without memory shifting.
    
