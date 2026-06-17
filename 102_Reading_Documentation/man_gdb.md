# Case Study: `gdb` (Navigating Command-Line Debugger Help)

The `gdb` manual is your guide to a complex, stateful environment. Unlike `grep`, which runs and exits, `gdb` is a program you "live" in while debugging. Use `man gdb` to follow along.

## 1. Decoding the SYNOPSIS
`gdb [OPTIONS] [prog|prog procID|prog core]`

This tells you the three main ways to start `gdb`:
1.  **Just the program**: `gdb ./my_app`
2.  **Attach to a running process**: `gdb ./my_app 1234`
3.  **Inspect a crash**: `gdb ./my_app core` (where `core` is a memory dump from a crash).

---

## 2. The "Frequently Needed Commands" Section
The `gdb` manual is helpful because it includes a curated list of commands inside the **DESCRIPTION**.
*   **Search**: `/frequently needed GDB commands`
*   **Discovery**: This section is a "mini-manual" within the manual. It defines the core verbs of debugging: `break`, `run`, `bt`, `print`, `c`, `next`, `step`.

---

## 3. The "Interactive" Nature of the Manual
The manual reminds you that `gdb` has its own built-in help system.
*   **Discovery**: In the **DESCRIPTION**, it mentions using the `help` command *inside* GDB. 
*   **Lesson**: The `man` page is for starting GDB; the internal `help` is for using it.

---

## 4. Initialization Files
How does GDB know your preferences (like TUI mode)?
*   **Search**: `/.gdbinit`
*   **Discovery**: The **FILES** section explains that GDB reads configuration from `.gdbinit`. This is where you store custom shortcuts or setup commands.

---

## 🚀 Mastery Exercise
Using **ONLY** the `man gdb` page, find the answers to these:
1.  **Attachment**: What flag do you use to attach to a process ID directly? (Search for: `attach`)
2.  **Symbols**: What happens if you start GDB with the `-nx` flag? (Search for: `do not execute`)
3.  **Batch**: How do you run GDB in "batch mode" (where it runs commands from a file and exits)? (Search for: `batch`)
4.  **UI**: Find the mention of the "Text User Interface" (TUI). How do you enable it from the command line?
