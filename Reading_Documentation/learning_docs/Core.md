
# Big Picture

Imagine Linux is a giant city.

There are:

* commands (`ls`, `cp`, `grep`)
* C functions (`printf`, `malloc`)
* system calls (`fork`, `read`)
* config files (`passwd`, `fstab`)
* admin tools (`mount`, `fdisk`)

Many of them have the same names.

So Linux needs a library.

`man` is the librarian.

You ask:

```bash
man printf
```

and the librarian says:

> "Which printf? The command or the C function?"

That's why sections exist.

---

# The Most Important Line

This line:

```text
Each page argument given to man is normally the name of a program,
utility or function.
```

means:

```bash
man ls
```

→ show docs for `ls`

```bash
man printf
```

→ show docs for `printf`

```bash
man fork
```

→ show docs for `fork`

---

# Why Sections Exist

Look at:

| Section | Meaning           |
| ------- | ----------------- |
| 1       | Commands          |
| 2       | System calls      |
| 3       | Library functions |

These are the three you'll use constantly.

---

## Section 1

```bash
man 1 ls
```

means:

> Show me the command `ls`.

Example:

```bash
ls -l
```

runs from the shell.

---

## Section 2

```bash
man 2 read
```

means:

> Show me the kernel system call `read`.

This is what xv6 is full of.

Example:

```c
read(fd, buf, n);
```

The process asks the kernel:

> Please read bytes from this file.

---

## Section 3

```bash
man 3 printf
```

means:

> Show me the C library function.

Example:

```c
printf("hello\n");
```

This is from libc.

Not the kernel.

---

# Why This Matters

Suppose:

```bash
man printf
```

returns something weird.

Maybe Linux found:

```text
printf(1)
```

before

```text
printf(3)
```

because both exist.

So:

```bash
man 3 printf
```

removes ambiguity.

You are saying:

> I specifically want the library function.

---

# Understanding SYNOPSIS

This is probably the most important section of any man page.

Example:

```c
int printf(const char *restrict format, ...);
```

This tells you:

1. Function name
2. Return type
3. Parameters
4. Header file (usually shown above)

Almost every time you forget how to call a function:

```bash
man 3 function_name
```

and look only at SYNOPSIS.

---

# Understanding `man -k`

This is a hidden superpower.

Suppose you know:

> There is some function related to printing.

but you forgot the name.

Search:

```bash
man -k print
```

or

```bash
apropos print
```

You get many related manual pages.

Think:

```text
Google search
```

for local documentation.

---

# Understanding `man -f`

Suppose you know the name:

```bash
printf
```

but want a one-line description.

```bash
man -f printf
```

Output:

```text
printf - formatted output conversion
```

Equivalent to:

```bash
whatis printf
```

---

# Understanding `man -K`

Normal search:

```bash
man -k socket
```

searches only titles and descriptions.

But:

```bash
man -K socket
```

searches the actual contents of every man page.

Slow but powerful.

Think:

```text
grep across all documentation
```

---

# The Real Workflow of Experienced Engineers

When you see:

```c
fork();
```

you don't ask AI.

You do:

```bash
man 2 fork
```

When you see:

```c
printf();
```

you do:

```bash
man 3 printf
```

When you forget options for grep:

```bash
man grep
```

When you don't know the command name:

```bash
man -k network
```

or

```bash
apropos network
```

---

# The Only 5 Things I'd Memorize

For now, memorize only these:

```bash
man ls
```

Read docs for a command.

```bash
man 3 printf
```

Read docs for a C function.

```bash
man 2 read
```

Read docs for a system call.

```bash
man -k keyword
```

Search documentation.

```bash
man -f name
```

One-line description.

