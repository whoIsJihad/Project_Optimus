# Self-Sufficiency in Engineering
> A Guide to Documentation Mastery

This directory contains a curated set of **Case Studies** designed to teach you how to master the "Source of Truth": the Linux Manual Pages.

---

## 📚 The Foundational Guide
*   [**`How to Read a Manual`**](man_man.md): **Start here.** Learn the syntax of a SYNOPSIS and the strategy for navigating dense documentation.

---

## 🛠️ Case Studies: Practice Your Literacy
Use these guides alongside the actual `man` command in your terminal. Each one provides specific exercises to help you "crack the code" of professional documentation.

### Level 1: Command Basics
*   [**`grep(1)`**](man_grep.md): Practice searching for flags and understanding exit statuses.
*   [**`find(1)`**](man_find.md): Practice filtering complex options and understanding command-line logic.

### Level 2: Developer References
*   [**`printf(3)`**](man_printf.md): Learn to read C API documentation, function signatures, and return values.
*   [**`make(1)`**](man_make.md): Practice filtering noise in exhaustive manuals for complex build tools.

### Level 3: System Context
*   [**`hier(7)`**](man_hier.md): Learn to navigate the filesystem hierarchy manual to find headers and libraries.

---

## 🚀 The Workflow
1.  **Don't Google yet.**
2.  Open the manual: `man <topic>` (or `man 3 <topic>` for C functions).
3.  **Search** for your keyword: `/keyword`.
4.  **Read the SYNOPSIS** to confirm you're using it correctly.
5.  **Check the RETURN VALUE** to understand failure cases.
