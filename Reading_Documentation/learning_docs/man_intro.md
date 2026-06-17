# Case Study: `intro` (The Beginner's Map)

`intro` is often the first manual in any section. It provides context for all the other pages in that section. Use `man intro` (or `man 2 intro`, `man 3 intro`) to follow along.

## 1. The Multi-Faceted `intro`
There isn't just one `intro` page. Each section of the manual has its own.
*   **`man 1 intro`**: Introduction to user commands (ls, cp, grep).
*   **`man 2 intro`**: Introduction to system calls (the kernel interface).
*   **`man 3 intro`**: Introduction to library functions (C standard library).

---

## 2. Learning the "Bare Minimum"
The `man 1 intro` page is unique because it contains a tutorial for the command line itself.
*   **Search**: `/A session might go like`
*   **Discovery**: The manual provides a sample session, showing you exactly how the prompt (`$`) looks and how common commands (`ls`, `cat`, `rm`) interact.
*   **Lesson**: If you are ever on a new Unix-like system and don't know the basics, `man intro` is the first command you should run.

---

## 3. Decoding File Permissions in the Manual
`intro` explains the core concepts that other manuals take for granted.
*   **Action**: Search for `ls -l`.
*   **Discovery**: The manual explains what "37 bytes long" means and how "owner and permissions" work. It points you to `chown` and `chmod` for more details.

---

## 4. Understanding Standard Output
The manual defines technical terms like "standard output."
*   **Action**: Search for `stdout`.
*   **Discovery**: It explains that `cat` sends output to "standard output" and points you to `stdout(3)`.
*   **Lesson**: Technical terms in one `man` page are often defined in another. Follow the parenthetical numbers!

---

## 🚀 Mastery Exercise
Using **ONLY** the `man 1 intro` page, find the answers to these:
1.  **Shells**: What is the name of the "standard" shell? (Search for: `standard one is called`)
2.  **Naming**: What is the origin of the name `cat`? (Search for: `concatenate`)
3.  **Removal**: What warning does the manual give about the `rm` command? (Search for: `be careful`)
4.  **Pathnames**: What is the "full pathname" of the example file `tel`? (Search for: `/home/aeb/tel`)
