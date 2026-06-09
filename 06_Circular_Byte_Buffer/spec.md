### The Specification: What You Are Building

You are building an enterprise-grade **Fixed-Size Ring Buffer (Circular Buffer)** for bytes. This is a foundational data structure used in network drivers, logging engines, and audio processing pipelines. It provides a First-In, First-Out (FIFO) queue of bytes using a static, pre-allocated memory array.

The core constraint: **Memory shifting is strictly forbidden.** You cannot use `memmove` or loops to slide bytes forward when data is read. Instead, you move tracking pointers across the boundary of the array and wrap them back to the beginning using modulo arithmetic.

---

### The Intuition: Linear vs. Circular Memory

In a standard linear queue array, reading a byte from the front forces you to shift every remaining byte in memory one slot to the left to free up space. This is an $O(N)$ operation that destroys performance as the buffer grows.

A circular buffer treats the linear array as if the last index connects directly back to index zero. Instead of moving the data, you move two integer index markers: a **Head** (where new data is written) and a **Tail** (where old data is read).

---

### The Mechanical Design (State Tracking)

To build this, you need a single configuration struct or class containing exactly four variables:

1. **`buffer`**: A raw pointer to a fixed-size byte array (e.g., `char*` or `uint8_t*`) allocated on the heap once during startup.
2. **`capacity`**: The absolute maximum number of bytes the array can hold (e.g., $N$).
3. **`head`**: An integer index tracking where the next incoming byte will be written. Initialized to `0`.
4. **`tail`**: An integer index tracking where the next byte will be read from. Initialized to `0`.

---

### The State Rules

Your tracking logic must strictly maintain these three states based entirely on the relationship between `head` and `tail`:

| Buffer State | Mathematical Condition | Behavioral Rule |
| --- | --- | --- |
| **Empty** | `head == tail` | Reading is completely blocked. Returns an error flag. |
| **Full** | `(head + 1) % capacity == tail` | Writing is blocked (or overwrites old data, depending on policy). |
| **Data Present** | `head != tail` | Bytes can be safely written at `head` or read from `tail`. |

> **Crucial Implementation Note:** Under this standard design, a buffer with a capacity of $N$ bytes can only hold a maximum of $N - 1$ bytes. If you fill the final slot and let `head` equal `tail`, the system will misinterpret the buffer as completely empty. One slot must always be left vacant as a structural boundary marker.

---

### Step-by-Step Execution Plan

#### Step 1: Storage Allocation & Initialization

* **The Task:** Create the layout. Pre-allocate a continuous block of memory of size $N$ bytes. Initialize your `head` and `tail` integers to `0`.
* **Verification:** Ensure that immediately after allocation, your state checker confirms the buffer is empty, and any read attempt gracefully rejects.

#### Step 2: The Wrap-Around Write Operation (`push`)

* **The Task:** Implement the write logic for a single byte:
1. Check if the buffer is full using the state rule. If full, reject the write.
2. Write the incoming byte directly into `buffer[head]`.
3. Update the head index using wrap-around logic: `head = (head + 1) % capacity`.


* **Verification:** Write 3 bytes sequentially into a buffer of capacity 5. Verify that `head` points to index 3, `tail` remains at 0, and the buffer reports it is not full.

#### Step 3: The Wrap-Around Read Operation (`pop`)

* **The Task:** Implement the read logic for a single byte:
1. Check if the buffer is empty. If empty, return a failure indicator.
2. Extract the byte located at `buffer[tail]`.
3. Update the tail index using wrap-around logic: `tail = (tail + 1) % capacity`.
4. Return the extracted byte.


* **Verification:** Read 2 bytes out. Verify that `tail` shifts to index 2. The bytes returned must match the exact first 2 bytes you wrote in Step 2.

#### Step 4: The Boundary Crash Test

* **The Task:** Force the pointers to cross the physical array boundary to prove the circular wrap-around works.
* **The Sequence:**
1. Allocate a tiny buffer with a capacity of `4` (holds max 3 bytes).
2. Push 3 bytes: `['A', 'B', 'C']`. `head` is now at index 3. `tail` is at 0.
3. Pop 2 bytes: `['A', 'B']` are read out. `tail` is now at index 2.
4. Push 2 more bytes: `['D', 'E']`.
* Byte `'D'` goes into index 3. `head` increments to `(3 + 1) % 4`, which wraps it cleanly back to **index 0**.
* Byte `'E'` goes into index 0. `head` increments to `(0 + 1) % 4 = 1`.


5. Read all remaining bytes sequentially. The system must output `['C', 'D', 'E']` in exact chronological order without memory faults.



---

### What to Google When You Get Stuck

* `"ring buffer head tail empty full condition"`
* `"circular buffer modulo arithmetic wrap around"`
* `"thread safe single producer single consumer ring buffer"`