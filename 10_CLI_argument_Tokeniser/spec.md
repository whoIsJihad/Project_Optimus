### The Specification: What You Are Building

You are building a custom **Command Line Interface (CLI) Argument Tokenizer and Parser**. When a user launches a backend application from the terminal with complex execution flags (e.g., `./server --port 8080 -v --dir=/tmp`), the operating system handles the raw input and passes it into your program's entry point as a raw array of null-terminated strings (`char* argv[]`).

Your task is to process this array from left to right, classify what each string represents, extract key-value configurations, handle shorthand options, and map them cleanly into a structured, type-safe internal C++ configuration struct.

---

### The Architecture: How the Data Flows

```
[Raw System Input: char* argv[]]
  │   └── Example: ["./server", "--port", "8080", "-v", "--dir=/tmp"]
  │
  ▼ (Token Classification Loop)
[Identify Patterns]
  ├── "--" Prefix ──► Long Flag (Check for attached '=' or lookahead next index)
  ├── "-"  Prefix ──► Short Flag (Boolean flag or compact single-char option)
  └── No   Prefix ──► Raw Value (Positional argument or argument value)
  │
  ▼ (Key-Value Association Engine)
[Lookup Collection] ──► std::unordered_map<std::string, std::string>
  │
  ▼ (Type Mapping & Validation)
[Target Application Configurations Struct]
  ├── port = 8080 (Integer)
  ├── verbose = true (Boolean)
  └── directory = "/tmp" (String)

```

---

### The Mechanical Design (The Target Configurations Struct)

Instead of passing raw strings around your application logic, your parser converts the values into a centralized, immutable application state struct:

```cpp
struct AppConfig {
    int port = 80;               // Default fallback
    bool verbose = false;        // Standard switch toggle
    std::string directory = "."; // Fallback to current working directory
};

```

---

### Step-by-Step Execution Plan

#### Step 1: The Input Loop Setup

* **The Task:** Tap into the core C++ application parameters: `int main(int argc, char* argv[])`. Loop through the indices starting at `i = 1` (since `argv[0]` is always the executable binary path name itself).
* **Verification:** Print out each index number and its string value on a separate line to confirm exactly how the OS splits space-separated inputs into discrete entries.

#### Step 2: Pattern Matching & Token Classification

* **The Task:** Inside your loop, convert each `argv[i]` into a temporary `std::string_view` or `std::string` and evaluate its prefix structure:
1. **Long Flags with Value Assignment:** If it starts with `--` and contains an equals sign `=` (like `--dir=/tmp`), split the string at the `=` symbol. Everything left of `=` is the configuration key; everything right is the value string.
2. **Standard Long/Short Flags:** If it starts with `--` or `-` but does not contain an `=`, it is an option wrapper.
3. **Positional Data:** If it does not start with a dash, it is a standalone token representing an argument value.


* **What to Google when stuck:** `"C++ std::string_view starts_with example"`, `"C++ string find first of character index"`.

#### Step 3: State-Machine Value Association

* **The Task:** When you hit a standalone flag option (like `--port`), your parser doesn't know what its value is until it checks the neighboring slot. Implement a lookahead pattern:
1. When a key token like `--port` is found, check if index `i + 1` exists (i.e., `i + 1 < argc`).
2. Check if the next token at `argv[i + 1]` is a value string or if it starts with a dash.
3. If it is a clean value string (like `"8080"`), save the relationship: `map["port"] = argv[i + 1]`, and advance your main loop iterator counter (`i++`) to skip processing that data token as a standalone flag in the next round.
4. If it's a standalone flag with no value follow-up (like `-v`), save it directly as a truth statement: `map["v"] = "true"`.



#### Step 4: Type Conversion & Struct Population

* **The Task:** Once your raw key-value map is completely built out from the tokens, iterate through your map entries and map them onto your target `AppConfig` memory layout fields:
* Map `"v"` or `"verbose"` directly to `config.verbose = true`.
* Convert the `"port"` string value to an actual operational integer using `std::stoi()`, storing it safely inside `config.port`. Handle potential syntax exceptions gracefully if a user types something broken like `--port abc`.
* Assign the `"dir"` string configuration directly to `config.directory`.



---

### Verification & Test Scenarios

Compile your code and feed it these exact terminal executions to verify your parser's stability:

1. **Test Scenario A (Symmetric Layout):**
```bash
./server --port 9000 -v

```


*Expected Output:* `config.port` should read `9000`, and `config.verbose` must be `true`.
2. **Test Scenario B (Inline Assignments):**
```bash
./server --dir=/var/log/nginx --port 443

```


*Expected Output:* `config.directory` reads `"/var/log/nginx"`, `config.port` reads `443`, and `config.verbose` falls back to its default value of `false`.
3. **Test Scenario C (Input Malformation Overload):**
```bash
./server --port invalid_number

```


*Expected Output:* The parsing routine must intercept the string-to-integer conversion fault gracefully, output a clean error message (`"Error: Port value must be a valid integer"`), and terminate without crashing the terminal shell.

---

### What to Google When Stuck

* `"C++ manual command line argument parsing state machine"`
* `"Convert string to integer exception handling std::stoi"`
* `"How getopt works under the hood under linux"`