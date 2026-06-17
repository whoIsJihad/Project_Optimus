# Case Study: `hier` (Understanding System Geography)

`hier` (Section 7) is a "Miscellaneous" manual. It doesn't describe a command, but a **structure**. Use `man hier` to understand how to find things on your system.

## 1. Why Section 7?
Commands are in Section 1. Tools for admins are in Section 8. Section 7 is for "Overviews and Conventions." `hier` is the overview of where everything else lives.

---

## 2. Navigating the Hierarchy
The manual is structured as a list of paths.
*   **Action**: Search for your most frequent points of interest.
*   **Search**: `/usr/include`
*   **Discovery**: The manual explains that this is where "include files for the C compiler" live. If you ever wonder where `stdio.h` comes from, `hier` points the way.

---

## 3. Decoding Modern vs. Legacy
Linux systems have evolved. `hier` often documents legacy paths that are now symbolic links.
*   **Search**: `/bin`
*   **Discovery**: Note the description of `/bin` as "executable programs needed in single-user mode." Modern systems often link `/bin` to `/usr/bin`, but the manual explains the *purpose* behind the separation.

---

## 4. Understanding `/proc` and `/sys`
These are "virtual" filesystems.
*   **Action**: Search for `/proc`.
*   **Discovery**: The manual describes it as an interface to "process and kernel information." It points you to a specific manual: `proc(5)`. 
*   **Lesson**: `hier` is often a "Table of Contents" that points you to more detailed manuals for specific directories.

---

## 🚀 Mastery Exercise
Using **ONLY** the `man hier` page, find the answers to these:
1.  **Configuration**: Where do "host-specific configuration files" live? (Search for: `configuration files`)
2.  **Libraries**: What is the purpose of the `/usr/local/lib` directory? (Search for: `/usr/local/lib`)
3.  **Logs**: Where are "variable data files" like logs and spool files stored? (Search for: `variable data`)
4.  **Headers**: Find the description for `/usr/include/linux`. What kind of information does it contain?
