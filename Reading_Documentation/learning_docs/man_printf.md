# Case Study: `printf` (The Developer's Reference)

Library calls (Section 3) are different from commands. They are API documentation for your code. Use `man 3 printf` to follow along.

## 1. The Contract (SYNOPSIS)
The SYNOPSIS in Section 3 is a **C Header**. It tells you exactly what you need to put in your code to use the function.

*   **Header**: `#include <stdio.h>`
*   **Signature**: `int printf(const char *restrict format, ...);`
    *   `int`: The function returns an integer.
    *   `restrict`: A compiler hint (don't worry about it for now).
    *   `...`: This is a "variadic function"—it takes any number of arguments.

---

## 2. Searching for Specifiers
Section 3 pages are often huge. The `printf` manual is legendary for its length.
*   **Search**: `/Conversion specifiers`
*   **Navigation**: Use `n` to jump through the different types (d, i, o, u, x, etc.).

---

## 3. Return Values: The Error Check
In production code, you should always know what happens when a function fails.
*   **Action**: Jump to the **RETURN VALUE** section.
*   **Discovery**: `printf` returns the number of characters printed. If it fails, it returns a **negative value**.

---

## 🚀 Mastery Exercise
Using **ONLY** the `man 3 printf` page, find the answers to these:
1.  What is the difference between `%d` and `%i` in the `printf` format string? (Search for: `d, i`)
2.  How do you print a pointer address? (Search for: `p`)
3.  Look at the **ATTRIBUTES** section. Is `printf` "Thread-safe"?
4.  Find the **CAVEATS** section. What is the danger of using `sprintf`?
