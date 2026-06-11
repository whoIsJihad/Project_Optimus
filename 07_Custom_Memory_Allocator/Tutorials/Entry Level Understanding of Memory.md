## Core

No assumptions. No "you should know this". We start with what memory actually IS.

---

## Chapter 1: What Is Memory, Really?

Imagine a **giant Excel spreadsheet** with millions of cells in a single row. Each cell has:
- An **address** (the column number: 0, 1, 2, 3...)
- A **value** (a byte: 0-255)

That's RAM. A gigantic array of bytes.

```
Address: | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | ...
Value:   | 0 | 0 | 72| 101| 108| 108| 111| 0 | 0 | 0 | ...
          ↑
    Byte at address 2 holds the number 72 (letter 'H' in ASCII)
```

**Key insight:** Everything you've ever stored in a program—integers, strings, objects, arrays, even your function call stack—is just bytes sitting at specific addresses.

---

## Chapter 2: How Variables Eat Memory

When you write:
```cpp
int x = 42;
```

The compiler says: "I need space to store an integer." An integer takes **4 bytes** (on most systems).

```
Address: | 1000 | 1001 | 1002 | 1003 |
Value:   | 42   | 0    | 0    | 0    |
          ↑
     x lives here (address 1000)
```

`sizeof(int)` tells you how many bytes. Run this mentally: `sizeof(char)` = 1 byte, `sizeof(double)` = 8 bytes.

**The critical realization:** When you declare `int x;`, the compiler decides the address at compile time (stack allocation). But what if you don't know how many integers you need until the program runs? That's heap allocation.

---

## Chapter 3: The Heap (Where malloc Takes You)

The heap is a **reservoir of raw bytes** that you can claim at runtime.

`malloc(100)` asks the operating system: "Give me 100 contiguous bytes I can use." The OS finds 100 empty cells in that Excel spreadsheet and returns the STARTING address.

```cpp
void* ptr = malloc(100);  // ptr now holds address 2000
```

Now addresses 2000-2099 belong to YOU.

**But here's the problem:** The OS keeps a LIST of who owns what. Every `malloc()` forces the OS to:
1. Search its list for a free block big enough
2. Mark that block as "used"
3. Update its internal bookkeeping (which takes extra memory!)
4. Return the address

Do this 10,000 times for tiny objects? Your program slows to a crawl.

---

## Chapter 4: The Arena Idea (Your Assignment)

What if you do ONE `malloc()` for a huge block, then manage it YOURSELF?

That's the arena. YOU become the OS inside your program.

**Your state:**
```cpp
char* buffer;      // The big block you got from malloc
size_t capacity;   // Total size (e.g., 1024 bytes)
size_t offset;     // How many bytes you've given out so far
```

**The mental model:** You're standing at the start of a long hallway. Each time someone needs memory, you measure how many feet they need, slide that far down the hallway, mark a spot on the floor, and say "this is yours." Then you stand at the new position, ready for the next request.

When done? You walk back to the start. That's `reset()`.

---

## Chapter 5: Pointers and Bytes (The Confusion Killer)

This trips EVERYONE. Let me clarify:

```cpp
char* buffer = (char*)malloc(100);  // buffer is address 500
buffer[0] = 65;  // Write 'A' at address 500
buffer[1] = 66;  // Write 'B' at address 501
```

`buffer` is a `char*` because `char` = 1 byte. Pointer arithmetic with `char*` moves by bytes:

```cpp
buffer + 5   // Address 505 (500 + 5)
```

If `buffer` were `int*`, adding 1 would add 4 bytes (sizeof(int)):

```cpp
int* int_buffer = (int*)buffer;
int_buffer + 1  // Address 504 (500 + 4)
```

**Your arena must use `char*` or `uint8_t*`** so that `offset` can directly translate to byte addressing.

---

## Chapter 6: Your First Alloc (Without Alignment)

```cpp
void* alloc(size_t bytes) {
    // Is there room?
    if(offset + bytes > capacity) {
        return nullptr;  // Arena full
    }
    
    // Calculate where this allocation starts
    void* result = buffer + offset;  // buffer is char*, so + moves by bytes
    
    // Move the offset forward
    offset += bytes;
    
    return result;
}
```

**Test this mentally:**
- Arena: capacity=100, offset=0
- alloc(10) → returns address 0, offset=10
- alloc(20) → returns address 10, offset=30
- alloc(30) → returns address 30, offset=60
- alloc(40) → fails (60+40=100 > capacity? Actually 100 > 100? No, it's EQUAL. This is an off-by-one bug to fix.)

---

## Chapter 7: The Alignment Problem (Why Simple Breaks)

Let me allocate a `double` (8 bytes) after a `char` (1 byte):

```cpp
alloc(1);   // offset was 0, returns 0, offset=1
alloc(8);   // returns 1, offset=9
```

The `double` lives at address 1. But CPUs read memory in chunks of 8 bytes starting at addresses divisible by 8 (0,8,16,24...).

Address 1 is MISALIGNED. The CPU must do TWO memory reads (0-7 and 8-15) to assemble your double. 2x slower. On some architectures? Crash.

**The fix:** Before returning memory, round UP the current offset to the next multiple of the required alignment.

---

## Chapter 8: The Alignment Formula (Broken Down)

Given current offset 1, need to align to 8:

```cpp
size_t alignForward(size_t offset, size_t alignment) {
    return (offset + (alignment - 1)) & ~(alignment - 1);
}
```

Let's trace with offset=1, alignment=8:

1. `(offset + (alignment - 1))` = 1 + 7 = 8
2. `~(alignment - 1)` = ~7 = ...11111000 (binary, clears last 3 bits)
3. 8 & ...11111000 = 8

Result: 8 (the first multiple of 8 at or after address 1).

Check offset=8, alignment=8:
1. 8 + 7 = 15
2. 15 & ...11111000 = 8

Check offset=9, alignment=8:
1. 9 + 7 = 16
2. 16 & ...11111000 = 16

**Why this works:** `(alignment - 1)` creates a mask (7 = 0b111). Adding it pushes you past the remainder. AND with bitwise NOT clears the lower bits, rounding DOWN to a multiple.

---

## Chapter 9: Your Real Alloc Function

```cpp
void* alloc(size_t bytes, size_t alignment = 8) {
    size_t current_offset = offset;
    
    // Align the starting point
    size_t aligned_offset = alignForward(current_offset, alignment);
    
    // Check capacity after alignment (alignment may push you forward!)
    if(aligned_offset + bytes > capacity) {
        return nullptr;
    }
    
    // Move offset to AFTER this allocation
    offset = aligned_offset + bytes;
    
    // Return the aligned address
    return (char*)buffer + aligned_offset;
}
```

**Critical:** You must store the ALIGNED offset as the returned address, but then move to the end of the allocation. The next allocation starts at `aligned_offset + bytes`, NOT at `offset` from before.

---

## Chapter 10: The Reset

```cpp
void reset() {
    offset = 0;
}
```

That's it. You've forgotten nothing. All previous pointers are now pointing to memory that WILL be overwritten on the next allocation. That's intentional.

---

## Chapter 11: Your Training Exercise (Do This NOW)

Write a tiny program that:

1. Creates an arena with capacity 64 bytes
2. Allocates a char (1 byte, alignment 1)
3. Allocates a double (8 bytes, alignment 8)
4. **Print both addresses** - are they 8 bytes apart? They shouldn't be! The first char takes byte 0, alignment pushes the double to byte 8. You lose 7 bytes of padding.
5. Calculate how much memory you ACTUALLY used vs requested. You'll see overhead.

Then ask yourself: "How would I store an array of 3 doubles back-to-back?" (Hint: alignment only matters for the FIRST element. The next doubles are already aligned if the first was.)

---

## What You'll Get Stuck On (And What To Do)

**Stuck on:** "Why do I need to cast to `char*`?"  
→ Pointer arithmetic with `void*` is illegal in C++. Search: "C++ pointer arithmetic void pointer"

**Stuck on:** "My aligned address calculation is wrong"  
→ Print `offset` before and after. Are you updating offset with the aligned value or the raw value?

**Stuck on:** "The spec says alignment=8 default, but what about 1-byte alignment?"  
→ That's the identity function. `alignForward(anything, 1)` returns the same number.

**Stuck on:** "How do I test if my memory is actually aligned?"  
→ `if((uintptr_t)ptr % alignment == 0)`

---

