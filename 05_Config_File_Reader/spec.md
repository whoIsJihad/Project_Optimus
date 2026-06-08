### The Specification: What You Are Building

You are building a configuration manager that allows a backend application to read its runtime settings (like port numbers, database URLs, or debug flags) from a plain text file, alter those settings in memory while the program runs, and save the updated settings back to the file.

---

### The Architecture: How the Data Flows

```
[On Disk: config.txt] 
       │ 
       ▼ (Read line-by-line using Input File Streams)
[Raw Strings: "port=8080"] 
       │ 
       ▼ (String Processing: Strip spaces, split at '=')
[In-Memory Lookup Table: Key-Value Pairs]  <─── Your application changes values here
       │ 
       ▼ (Serialization: Loop through table, format as "key=value")
[On Disk: config.txt (Updated)]

```

---

### Step 1: Create the Test File (`config.txt`)

Before writing any code, manually create a text file named `config.txt` in your project folder. Paste the following exact content into it:

```text
# Server Deployment Configuration
port=8080
db_host=127.0.0.1
db_port=5432
debug_mode=true
# End of file

```

---

### Step 2: The Reading Phase (Text to Memory)

Your program must open this file, read it line by line, parse the text, and store it in an associative lookup table (a structure that matches a unique string "Key" to a string "Value").

#### Micro-tasks:

1. **File Opening:** Initialize an input file stream object. Attempt to open `config.txt`. If the file doesn't exist or is locked, print an explicit error message and terminate.
2. **Line Looping:** Set up a loop that reads the file line-by-line from top to bottom until it hits the end of the file.
3. **Comment & Empty Line Filtering:** For each line read:
* Check if the line is completely empty. If yes, ignore it and move to the next line.
* Check if the first non-whitespace character is a `#`. If yes, treat it as a comment, ignore it, and move to the next line.


4. **Delimiting/Splitting:** For valid data lines (like `port=8080`), find the exact index position of the equals sign (`=`).
* Extract everything from index `0` up to the `=` index. This string is your **Key** (e.g., `"port"`).
* Extract everything from the index right after the `=` to the end of the line. This string is your **Value** (e.g., `"8080"`).


5. **Storage:** Insert this Key and Value pair into a C++ `std::map` or `std::unordered_map` where both the key and value types are standard strings.

#### What to Google when stuck:

* `"How to read a file line by line in C++ using ifstream"`
* `"C++ string find character index example"`
* `"C++ string substr method parameters"`
* `"How to insert key value pairs into std::map C++"`

---

### Step 3: The Update Phase (In-Memory Mutation)

Once the file is completely read and closed, your program should interact with the data strictly inside the system memory.

#### Micro-tasks:

1. Print the current value of `port` and `db_host` by looking them up in your map structure to verify the reading phase worked perfectly.
2. Simulate a runtime setting change: locate the key `"port"` inside your map and overwrite its associated value string from `"8080"` to `"9090"`.
3. Add a brand new configuration parameter that wasn't in the original file by inserting a new key `"max_connections"` with a value of `"100"` into the map.

#### What to Google when stuck:

* `"How to update value of existing key in std::map C++"`
* `"How to check if a key exists in a C++ map"`

---

### Step 4: The Writing Phase (Memory to Text)

Now, you must take your modified in-memory map data structure and overwrite the old file on your disk so the updates are persistent.

#### Micro-tasks:

1. Initialize an output file stream object. Open the exact same `config.txt` file. Opening a file in standard write mode will completely truncate (wipe clean) its previous text content.
2. Set up a loop that iterates through every key-value pair stored inside your updated map.
3. For every pair, format a clean output string matching this exact pattern: `Key`, followed immediately by an `=`, followed immediately by the `Value`, followed by a newline character (`\n`).
4. Write that formatted line directly into the output file stream.
5. Close the file stream cleanly. Open your raw `config.txt` file in a regular text editor to verify that `port` is now `9090` and `max_connections=100` exists.

#### What to Google when stuck:

* `"How to write text to a file using ofstream in C++"`
* `"How to iterate through a std::map using range based for loop C++"`

---

### How to Diagnose If You Get Stuck

* **Symptom:**  The program runs, but the map is completely empty.
* *Diagnostic Steps:* Put a print statement right inside your line-by-line reading loop that prints `printf("Raw line: %s\n", line.c_str())`. If nothing prints, your pathing is wrong and the program cannot find `config.txt`. Move the text file to the exact directory where your compiled binary executable runs.


* **Symptom:** The final written file contains garbage characters or is completely malformed.
* *Diagnostic Steps:* Isolate the writing loop. Before writing to the file stream, change the target to your terminal stream (`std::cout`). If the format looks broken on your terminal screen, your string concatenation logic inside the loop is broken. Fix it on-screen before directing it back to the file.