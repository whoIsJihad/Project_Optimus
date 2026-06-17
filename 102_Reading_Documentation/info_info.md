# Case Study: `info` (Mastering Hyperlinked Documentation)

GNU tools (like `gcc`, `make`, and `bash`) often have `man` pages that are just "stubs" or brief summaries. Their real documentation lives in the `info` system. Use `info info` to follow along.

## 1. `info` vs. `man`: The Philosophy
*   **`man`**: A single, long, static page. Great for quick flag lookups.
*   **`info`**: A tree of hyperlinked "nodes." Great for learning complex systems step-by-step.

---

## 2. Navigating the Node Tree
Inside an `info` page, you aren't just scrolling; you are moving through a hierarchy.
*   **`Space` / `Backspace`**: Move forward and backward through the whole document (it will jump between nodes automatically).
*   **`n` / `p`**: Go to the **n**ext or **p**revious node at the same level.
*   **`u`**: Go **u**p one level in the hierarchy.
*   **`Tab`**: Move the cursor to the next hyperlink (called a "Menu Item" or "Cross Reference").
*   **`Enter`**: Follow the hyperlink under the cursor.

---

## 3. The "Breadcrumbs" (The Header)
At the top of every `info` node, you'll see a line like:
`File: make.info,  Node: Rules,  Next: Recipes,  Prev: Targets,  Up: Top`
*   **Lesson**: This tells you exactly where you are in the manual and where the `n`, `p`, and `u` keys will take you.

---

## 4. Searching and Indexing
Because `info` manuals are huge, searching is vital.
*   **`s`**: Search for a string across all nodes.
*   **`i`**: Search the **Index**. This is the fastest way to find a specific concept (e.g., in `info make`, press `i` then type `vpath`).

---

## 🚀 Mastery Exercise
Run `info info` in your terminal and find the answers to these:
1.  **Help**: Which key gives you a "cheat sheet" of all basic key bindings? (Search for: `get started by typing`)
2.  **Naming**: What does the manual call the "hyperlinks" you follow? (Look at the **Menu**)
3.  **Windows**: How do you split the `info` screen into two windows? (Search the Menu for: `Window Commands`)
4.  **Quit**: How do you exit the `info` reader?
