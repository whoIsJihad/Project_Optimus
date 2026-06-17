# Case Study: `find` (Decoding the Expression Manual)

The `find` manual is notoriously difficult because it isn't just a list of flags; it's a manual for a **mini-programming language**. Use `man find` to follow along.

## 1. Decoding the Complex SYNOPSIS
`find [-H] [-L] [-P] [-D debugopts] [-Olevel] [starting-point...] [expression]`

This synopsis reveals a critical distinction that many miss:
*   **Options (`-H`, `-L`, `-P`, etc.)**: Must come **before** the starting point. They control how `find` treats symbolic links.
*   **Starting-point**: Where to begin searching (defaults to `.` if omitted).
*   **Expression**: Everything else. This is where you define *what* to find and *what to do* with it.

---

## 2. Key Concept: Predicates
In the `find` manual, flags are called **Predicates**. They are divided into four types. Search for these headings in the manual:

1.  **Tests**: Return true or false (e.g., `-name`, `-type`, `-size`).
2.  **Actions**: Do something and return true or false (e.g., `-print`, `-exec`, `-delete`).
3.  **Operators**: Join tests together (e.g., `-and`, `-or`, `-not`).
4.  **Positional Options**: Affect the behavior of tests that follow them (e.g., `-regextype`).

---

## 3. Understanding Operators (The Logic)
`find` evaluates expressions from left to right.
*   **Action**: Search for the **OPERATORS** section.
*   **Discovery**: If you provide two tests without an operator (e.g., `-type f -name "*.c"`), `find` assumes a hidden `-and`.
*   **Precedence**: Like math, `find` has a specific order (e.g., `-not` is higher than `-and`).

---

## 4. The `-exec` Syntax
This is the most "encoded" part of the manual.
*   **Action**: Search for `/-exec ;` and `/-exec +`.
*   **Decoding**: 
    *   `{}`: A placeholder for the current filename.
    *   `;`: Ends the command for *each* file.
    *   `+`: Ends the command but passes *all* files at once (faster).

---

## 🚀 Mastery Exercise
Using **ONLY** the `man find` page, find the answers to these:
1.  **Logic**: What is the difference between `-mmin` and `-mtime`? (Search for: `modified since`)
2.  **Permission**: How do you search for files that are exactly `777` permissions? (Search for: `-perm`)
3.  **Depth**: Which option prevents `find` from descending into subdirectories? (Search for: `descend at most`)
4.  **Action**: What happens if you use `-delete`? Does it stay in the current directory or recurse?
