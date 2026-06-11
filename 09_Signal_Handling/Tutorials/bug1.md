To understand **Bug #1 (Async-Signal Safety)**, we have to look at how a computer manages memory when running your program, and what happens when a signal suddenly crashes the party.

### The Core Problem: `std::cout` is Global and Shared

`std::cout` is not just a simple print command; it is a complex mechanism (an object) that manages a hidden piece of memory called an **output buffer**.

To save processing power, `std::cout` doesn't write to your screen letter-by-letter. Instead, it collects characters in this buffer (like a bucket filling with water) and pours them onto the screen all at once when the bucket is full or when it hits `std::endl`.

### The Chaos of an Interruption

Because `std::cout` is used in both your main loop and your signal handler, they are both trying to use the **exact same bucket** at the same time.

Here is the nightmare scenario of how they collide:

1. **Step 1:** Your main `while` loop runs and starts printing `"To terminate : kill 1234"`.
2. **Step 2:** `std::cout` opens its internal bucket and begins writing the characters into it.
3. **Step 3 (The Interruption):** Right in the middle of this action—say, right after it writes `"To term"`—the user presses `Ctrl+C`.
4. **Step 4:** The Operating System freezes the main loop instantly. It doesn't wait for `std::cout` to finish. It forces the program to jump straight to your `handler()` function.
5. **Step 5 (The Crash/Deadlock):** Inside `handler()`, you call `std::cout << "Received 2"`. `std::cout` tries to open its internal bucket again.

But the bucket is already locked and half-modified by the main loop!

### What happens next?

Because the internal state of `std::cout` is now broken or locked, one of two terrible things happens:

* **Deadlock (Freeze):** The signal handler waits for the main loop to unlock the bucket. But the main loop is frozen waiting for the signal handler to finish. They wait for each other forever, and your program hangs.
* **Memory Corruption (Crash):** The handler forces its way in, scrambles the memory inside the bucket, and the program crashes instantly with a `Segmentation Fault`.

### The Solution: Async-Signal Safe Functions

The rule of thumb in systems programming is: **Never use complex, shared, or buffered objects inside a signal handler.** Instead, you must only use functions that are certified as **Async-Signal Safe**. These are simple system calls provided by the Operating System that do not use shared buffers and cannot be corrupted if interrupted.

The low-level system call `write()` is one of them:

```cpp
write(1, "Received\n", 9);

```

Unlike `std::cout`, `write()` bypasses all internal C++ application buffers and shoots the data straight to the terminal safely, making it completely immune to this bug.