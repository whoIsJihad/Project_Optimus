# Case Study: `standards` (Decoding the Jargon)

When you read a `man` page, you'll often see a **STANDARDS** section with acronyms like `POSIX.1-2001`, `SUSv3`, or `C99`. `man standards` (Section 7) is your glossary for these terms.

## 1. Why Standards Matter in Manuals
Standards tell you if your code will run on other systems (like macOS, BSD, or older Linux versions). If a `man` page says a function is "Non-standard" or a "GNU extension," you should use it with caution.

---

## 2. The Big Three: POSIX, SUS, and C
The manual divides standards into three primary categories.
*   **C Standard (C89, C99, C11)**: Defines the language itself (e.g., `printf` specifiers).
*   **POSIX**: The "Portable Operating System Interface." It defines how the shell and C library interact with the OS.
*   **SUS (Single UNIX Specification)**: A stricter set of standards. If a system meets SUS, it can legally be called "UNIX."

---

## 3. Decoding "BSD" vs "System V"
You'll often see mentions of "BSD" or "SysV" in the **HISTORY** or **NOTES** sections of other manuals.
*   **Search**: `/V7`
*   **Discovery**: The manual explains that after "Version 7 UNIX," the world split into two dialects: **BSD** (Berkeley) and **System V** (AT&T).
*   **Lesson**: If you see a note saying "This behavior follows BSD," it means it might differ on systems that follow System V.

---

## 4. Understanding Feature Test Macros
Manuals for C functions (Section 3) often require you to define a "Feature Test Macro" to use certain features.
*   **Action**: Search for `XOPEN_SOURCE`.
*   **Discovery**: The manual explains that defining these macros "exposes" definitions that are required by specific standards (like POSIX or X/Open).
*   **Lesson**: If a function in `man 3` isn't working, check the **SYNOPSIS** for a required macro and then look it up in `man standards`.

---

## 🚀 Mastery Exercise
Using **ONLY** the `man standards` page, find the answers to these:
1.  **Ambiguity**: Why is the term "ANSI C" considered ambiguous? (Search for: `ANSI C`)
2.  **Naming**: Who coined the term "POSIX"? (Search for: `coined by`)
3.  **Modern C**: When was the `C11` revision of the C language standard ratified? (Search for: `C11`)
4.  **Unix branding**: What level of conformance is required for a system to be branded "UNIX 03"? (Search for: `UNIX 03`)
