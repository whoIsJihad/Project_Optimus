# Case Study: `make` (The Complex Tool)

`make` is a utility with a massive manual. It’s the perfect test for your ability to filter noise and find specific "How-To" information.

## 1. Finding Command-Line Options
Like `grep`, `make` has many flags.
*   **Action**: Inside `man make`, search for the "Dry Run" flag.
*   **Search**: `/dry-run`
*   **Discovery**: Note that `-n`, `--just-print`, and `--recon` all do the same thing. `man` pages list synonyms together.

---

## 2. Understanding the Logic
Manuals for complex tools often have a section explaining the "Algorithm" or "Logic."
*   **Search**: `/updates a target`
*   **Discovery**: Read that paragraph. It explains the core logic of `make`: it only updates a target if it's older than its prerequisites.

---

## 3. The "Jobserver" (Advanced Concepts)
Some `man` pages have sections for advanced features that aren't options.
*   **Search**: `/PARALLEL MAKE`
*   **Discovery**: This section explains how `make -j` coordinates between multiple processes. You don't need to memorize this, but you should know it's where the "Internal Mechanics" are documented.

---

## 🚀 Mastery Exercise
Using **ONLY** the `man make` page, find the answers to these:
1.  How do you tell `make` to use a specific file as a Makefile instead of the default `Makefile`? (Search for: `Use file as a makefile`)
2.  Which flag tells `make` to continue as much as possible even after an error? (Search for: `Continue as much as possible`)
3.  What happens if you run `make` and there is no file named `GNUmakefile`, `makefile`, or `Makefile`? (Look at the **DESCRIPTION** section).
