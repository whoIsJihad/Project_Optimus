# Case Study: `syscalls` (The Kernel Interface)

`syscalls` (Section 2) documents the boundary between your code and the Linux Kernel. Use `man syscalls` to understand how the "magic" happens behind the scenes.

## 1. Section 2 vs. Section 3
Many functions have both a **Library Wrapper** (Section 3) and an underlying **System Call** (Section 2).
*   **Section 3 (`man 3 printf`)**: High-level, user-friendly, provided by `glibc`.
*   **Section 2 (`man 2 write`)**: Low-level, talks directly to the kernel, provided by the OS.

---

## 2. Decoding the Wrapper Mystery
The manual explains that you almost never call a system call directly.
*   **Discovery**: In the **DESCRIPTION**, it explains that `glibc` provides a "wrapper function." 
*   **Example**: When you call `chdir()`, you are actually calling a `glibc` function that prepares the processor and then triggers the `chdir` system call.
*   **Lesson**: Section 2 manuals often describe both the C wrapper and the raw kernel interface.

---

## 3. The `errno` Convention
How do system calls report errors? 
*   **Action**: Search for `errno`.
*   **Discovery**: System calls indicate failure by returning a **negative error number**. The `glibc` wrapper then negates this number, saves it in the global `errno` variable, and returns `-1`.
*   **Lesson**: This is why almost every Section 2 and 3 `man` page tells you to check `errno` on failure.

---

## 4. Tracking Kernel History
System calls are added as Linux evolves. The `man syscalls` page is a master list.
*   **Action**: Search for `Kernel` in the table.
*   **Discovery**: The manual tells you exactly which kernel version introduced each call (e.g., `accept4` was added in `2.6.28`).
*   **Lesson**: If your code works on your machine but fails on an older server, check this table to see if the system calls you used even exist there.

---

## 🚀 Mastery Exercise
Using **ONLY** the `man syscalls` page, find the answers to these:
1.  **Direct Call**: Which manual describes how to invoke a system call *directly* without a wrapper? (Search for: `direct invocation`)
2.  **Architecture**: Some system calls are only available on specific processors. Find one that is "ARC only." (Search for: `ARC only`)
3.  **Removal**: Find a system call that was "Removed in 5.5".
4.  **Wrappers**: What happens if a system call is provided by the kernel but `glibc` doesn't have a wrapper for it? (Search for: `syscall(2)`)
