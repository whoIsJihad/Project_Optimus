# Case Study: `grep` (Searching the Manual)

Use `man grep` to practice navigating and finding specific details in a dense command-line utility manual.

## 1. Finding Flags Fast
Don't scroll through 300 lines of options.
*   **Action**: Inside `man grep`, type `/-v` and press Enter.
*   **Goal**: Find out what "Invert Match" means.
*   **Observation**: Note how `man` pages usually list the short flag (`-v`) and the long flag (`--invert-match`) together.

---

## 2. Understanding Global Behavior
The **DESCRIPTION** section often contains the "logic" of the tool.
*   **Search**: `/standard input`
*   **Discovery**: How does `grep` behave if you don't provide a filename? (Hint: It reads from stdin).

---

## 3. The "See Also" Rabbit Hole
At the bottom of `man grep`, you'll see a **SEE ALSO** section.
*   **Link**: `regex(7)`
*   **Why it matters**: `grep` uses Regular Expressions, but it doesn't explain them. It expects you to go to the specific manual for regex to learn that "language."

---

## 🚀 Mastery Exercise
Using **ONLY** the `man grep` page, find the answers to these:
1.  How do you search for a pattern that starts with a hyphen (`-`) without `grep` thinking it's an option? (Search for: `protect a pattern`)
2.  Which flag stops searching a file after a specific number of matches? (Search for: `max-count`)
3.  What is the exit status if no matches are found? (Look at section: **EXIT STATUS**)
