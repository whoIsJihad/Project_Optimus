

## **Track 1: Tooling, Compilation & File Systems (C/C++)** ✓ DONE
*Projects 1-10 complete — solid foundation*

---

## **Track 2a: Network Foundations (Before Socket Programming)**

### 11. TCP/IP Packet Inspector
- **What to build:** Write a program that uses `tcpdump` output (or raw packet bytes) to parse and display the structure of a real TCP/IP packet: source/dest IP, port numbers, sequence numbers, flags. Print a formatted breakdown.
- **Why first:** Understand what's actually flowing over the wire before you write socket code.

### 12. DNS Hostname Resolver
- **What to build:** A CLI tool that takes a hostname (e.g., `google.com`) and resolves it to an IP address using `getaddrinfo()` or `gethostbyname()`. Print the results. No external libraries.
- **Why:** Learn the DNS abstraction layer; understand that sockets work with IP addresses, not names.

### 13. IPv4 Address Parser & Validator
- **What to build:** Parse strings like `"192.168.1.1:8080"` and validate them as legal IPv4 + port. Convert to/from network byte order. Store in a struct.
- **Why:** You'll do this constantly; get it bulletproof.

### 14. Socket Lifecycle Debugger
- **What to build:** A simple TCP client that connects to a remote server (e.g., `google.com:80`), sends `"GET / HTTP/1.0\r\n\r\n"` raw, reads the response in chunks, and prints each step with timing/status.
- **Why:** See the full open→send→recv→close flow before building anything complex.

### 15. Non-Blocking Socket Setup
- **What to build:** A client that opens a socket, sets it to non-blocking mode (`fcntl` or `setsockopt`), attempts a connect, and handles the `EAGAIN` error gracefully.
- **Why:** Critical concept before epoll/select; understand when the kernel says "not ready yet."

### 16. Basic Server: Accept & Echo Single Connection
- **What to build:** A TCP server that listens on `localhost:9999`, accepts one client connection, echoes 3 messages back, then closes. No threading.
- **Why:** Your first real server. Understand bind→listen→accept→read→write→close.

---

## **Track 2b: Network Parsing (Text & Protocol)**

### 17. CRLF Line Splitter (Raw Bytes)
- **What to build:** Read raw binary data from a file or stdin containing `\r\n` delimiters and split into lines. Handle partial lines gracefully.
- **Why:** HTTP headers, SMTP, many protocols use CRLF; you need to recognize it in a byte stream.

### 18. HTTP Request-Line Parser
- **What to build:** Parse `"GET /path?query HTTP/1.1"` into method, target, version. Handle edge cases: missing parts, malformed input.
- **Why:** Core HTTP knowledge; exact parsing matters.

### 19. HTTP Header Map Builder
- **What to build:** Parse a block of HTTP headers into a map/dict. Handle case-insensitive keys, whitespace, missing values. Don't use a third-party HTTP library.
- **Why:** You'll parse headers in your gateway; do it by hand once.

### 20. URL Percent-Decoder
- **What to build:** Convert `%20` → space, `%2F` → `/`, etc. Handle invalid sequences. Return clean strings.
- **Why:** Query strings are URL-encoded; you need to decode them correctly.

### 21. JSON Flat Object Tokenizer
- **What to build:** Hand-parse a flat JSON object (no nesting) like `{"status":200,"message":"ok"}` and extract values. No `json.h` library.
- **Why:** You'll respond with JSON; parse at least one by hand to understand structure.

---

## **Track 2c: Network I/O & Concurrency Prep**

### 22. Multi-Connection Server (Blocking, Sequential)
- **What to build:** A TCP server that accepts 5 clients **sequentially** (one at a time). Each sends a number; you echo back the square. Close and move to the next.
- **Why:** Understand the blocking problem; see why sequential doesn't scale.

### 23. Multi-Packet Stream Receiver
- **What to build:** A server that receives data in arbitrary chunk sizes until it sees the delimiter `[END]`. Buffer and reassemble correctly.
- **Why:** Real data doesn't arrive in one `recv()` call. You need to buffer and detect boundaries.

### 24. Socket Timeout Handler
- **What to build:** A client that connects, sends data, then waits for a response with a 2-second timeout (`SO_RCVTIMEO`). If nothing arrives, log and exit gracefully.
- **Why:** Timeouts prevent hanging; essential in production.

### 25. Port Range Scanner
- **What to build:** Scan `localhost` ports 8000–9000 using non-blocking connect to find which are open. Report results.
- **Why:** Useful tool; teaches non-blocking socket logic.

---

## **Track 3: Concurrency & High-Performance Systems** ✓ READY
*Projects 26-35 can proceed as written, but add these intermediate steps:*

### 26. Thread Basics: Parallel Loop Sum
- **What to build:** Spawn 4 threads, each sums a quarter of an array. Join all threads. Print total. No shared memory issues yet.
- **Why:** Get comfortable with `std::thread`, `join()`, basic lifecycle.

### 27. Mutex & Lock Guard Logging
- **What to build:** 5 threads all write log lines to the same file using a mutex. Show that without the lock, output is garbled.
- **Why:** Hands-on mutexes. See the problem and the fix.

### 28. Condition Variable: Work Queue Wake-Up
- **What to build:** 1 producer thread enqueues tasks every 500ms. 2 worker threads wait on `std::condition_variable` and process tasks. Show that workers sleep when queue is empty.
- **Why:** Understand wait/notify before building a thread pool.

### 29. Thread Pool Implementation
- **What to build:** Pre-spawn 4 threads. Expose `enqueue(task)` that adds to a queue. Threads pull tasks and execute. Keep running until you call `shutdown()`.
- **Why:** Industry-standard pattern; understand it cold.

### 30. Select System Call (Blocking Multiplexing)
- **What to build:** Open 3 local TCP server sockets. Use `select()` to monitor all three in one loop. Accept a connection on whichever becomes ready first.
- **Why:** Before epoll, understand select. It's simpler but slower.

### 31. Epoll Basics: Register & Wait
- **What to build:** Create an epoll instance, register a listening socket, wait for incoming connections. Print each one.
- **Why:** Epoll is Linux power; learn it before edge-triggering.

### 32. Epoll Edge-Triggered (EPOLLET)
- **What to build:** Set a socket to edge-triggered. Show that you must read until `EAGAIN`; if you miss one byte, epoll won't notify again.
- **Why:** Edge-triggered is faster but requires careful handling. See the trap.

### 33. Keep-Alive & Stale Connection Eviction
- **What to build:** Maintain an array of connected clients. Track last activity time. Every second, disconnect clients inactive for >5 seconds. Log evictions.
- **Why:** Real servers must clean up dead connections.

---

## **Track 4a: DevOps & Containerization Foundations**

### 34. What is Docker? Hands-On Exploration
- **What to build:** Pull an existing image (`ubuntu:latest`), run it interactively, install a tool (e.g., `curl`), explore the filesystem. Exit and inspect with `docker inspect`.
- **Why:** Get tactile. Understand what a container IS before you build one.

### 35. Dockerfile Basics: Layer by Layer
- **What to build:** Write a simple `Dockerfile` that uses `FROM ubuntu`, runs `apt-get update && apt-get install -y curl`, adds your compiled binary, sets an entrypoint, and builds it. Run it locally.
- **Why:** Hands-on syntax. Understand `RUN`, `COPY`, `ENTRYPOINT`.

### 36. Multi-Stage Build Optimization
- **What to build:** A `Dockerfile` with two stages: builder (compiles C++), runner (copies only the binary). Compare image sizes before/after. Show the weight savings.
- **Why:** Production images must be lean. Learn why and how.

### 37. Docker Networking: Bridge & Host
- **What to build:** Run your server container on a custom bridge network. Spawn a second container (curl client) and have it connect to your server by container name. Show how DNS resolution works.
- **Why:** Containers talk to each other; understand the networking model.

### 38. Volume Mounts: Persistent Data
- **What to build:** Run a container with a mounted volume (`-v /host/path:/container/path`). Write a file inside; verify it persists on the host. Restart the container; file is still there.
- **Why:** Containers are ephemeral; volumes solve it.

### 39. Docker Compose Basics
- **What to build:** A `docker-compose.yml` that defines two services: your server and a "mock database" container (just a sleep loop). Start with `docker-compose up`. Show both running.
- **Why:** Compose scales beyond one container. Understand service definitions.

### 40. Environment Variables & Configuration
- **What to build:** Modify your server to read `PORT` and `LOG_LEVEL` from environment variables. Update your `Dockerfile` to set defaults. Override with `docker run -e PORT=9000`. Verify behavior changes.
- **Why:** Configuration must be external; teach the pattern.

---

## **Track 4b: CI/CD & Automation**

### 41. Bash Script: Build & Test Pipeline
- **What to build:** A shell script that compiles your C++ code, runs basic tests (e.g., "does the binary exist?"), and reports pass/fail. Emulate a CI step.
- **Why:** Learn what a "pipeline" is before using GitHub Actions or Jenkins.

### 42. Makefile-Based CI
- **What to build:** Extend your Makefile with targets: `make build`, `make test`, `make docker-build`, `make docker-run`. Chain them so `make all` does everything.
- **Why:** Real CI tools call make. Build the right target structure.

### 43. Health Check & Auto-Restart
- **What to build:** A shell script that runs your containerized server, polls it every 3 seconds (`curl localhost:8080/health`), and restarts the container if it's down for >5s.
- **Why:** Production services die; detect and recover.

---

## **Track 5a: ML Foundations (Before Inference)**

### 44. What is a Neural Network? NumPy From Scratch
- **What to build:** Implement a tiny 2-layer neural network (3 inputs → 2 hidden → 1 output) in pure NumPy. Forward pass, sigmoid activation, manual backprop. Train on dummy data (e.g., XOR).
- **Why:** You did this before. **Do it again.** It's your mental model baseline before ONNX.

### 45. Model Serialization: Save & Load
- **What to build:** Train a PyTorch model (linear classifier), save it with `torch.save()`, load it in a fresh Python script, run inference. Verify the weights are identical.
- **Why:** Understand what `.pt` files contain; how to persist and recover a model.

### 46. ONNX Export Walkthrough
- **What to build:** Train a PyTorch model, export to ONNX with `torch.onnx.export()`, inspect the ONNX file structure (node names, input/output specs), load it with `onnxruntime`, run inference.
- **Why:** ONNX is the bridge between training frameworks and inference engines. Understand the conversion.

### 47. Tensor Shape & Batch Semantics
- **What to build:** Write Python code that takes a 1D array, reshapes it to 2D (batch of samples), runs through a dummy model, and reshapes output back. Show how batching works.
- **Why:** Inference engines expect specific tensor shapes. Get this right.

### 48. Quantization & Model Compression
- **What to build:** Take a trained model, quantize it to int8 (using `torch.quantization` or ONNX Tools), compare inference speed and accuracy. Report the trade-off.
- **Why:** Real deployments optimize for speed/size. See the cost-benefit.

---

## **Track 5b: ML Inference Integration**

### 49. Pure C++ Tensor Math (No ONNX)
- **What to build:** Implement matrix multiplication in C++ using raw `float` arrays. Multiply two 3×3 matrices. Print the result. No external libraries.
- **Why:** Understand the computational foundation before wrapping ONNX.

### 50. ONNX Runtime Hello World
- **What to build:** Link against ONNX Runtime C++ library. Load an exported model file. Run inference on hardcoded input. Print output tensor values.
- **Why:** Get the build/link pipeline working. Run your first C++ inference.

### 51. Tensor Memory Layout & Reshaping
- **What to build:** Take a flat byte array (raw image pixels), reshape it into a CHW tensor (channels, height, width) for a model. Verify memory layout correctness.
- **Why:** Real data is flat; you reshape. Get indexing right.

### 52. Inference Latency Profiling
- **What to build:** Run inference 1000 times, measure elapsed time, report average latency, percentile stats (p50, p99). Identify bottlenecks.
- **Why:** Inference optimization is about measurement. Baseline first.

### 53. Batch Inference & Throughput
- **What to build:** Load 100 samples, batch them (B × 3 × 224 × 224 for a vision model), run once. Compare single-sample latency vs. batched throughput.
- **Why:** Batching is the key optimization for throughput. See the speedup.

### 54. Multi-Model Switching
- **What to build:** Load two different ONNX models in memory. Route based on input flag (e.g., `--model=tiny` vs. `--model=large`). Run inference with the right one.
- **Why:** Production gateways need model selection logic.

---

## **The Grand Capstone (Synthesis)**

### High-Performance Asynchronous AI Inference Gateway

Build everything together in one repo:

**Phase 1: Foundation (Projects 1–33)**
- Solid C++ tooling, build automation, file I/O
- Network I/O with epoll and thread pools
- Understand multiplexing and non-blocking I/O

**Phase 2: Containerization (Projects 34–43)**
- Package your gateway in Docker
- Set up automated builds and health checks
- Learn DevOps practices

**Phase 3: Inference (Projects 44–54)**
- Embed ONNX Runtime
- Implement tensor mapping and batching
- Profile and optimize

**Phase 4: Integration (Capstone)**
- HTTP server (epoll + thread pool) listens on port 8080
- Parses POST requests → JSON payload → input tensor
- Runs inference on cached model
- Returns JSON response with latency stats
- Containerized, health-checked, logged comprehensively
- Multi-model support with dynamic routing
- Load-test it; aim for <100ms p99 latency at 1000 req/s

---

## **What Changed**

| Area | Before | After | Why |
|------|--------|-------|-----|
| **Network** | 11–20 (10 projects) | 11–25 (15 projects) | Added TCP/IP basics, DNS, non-blocking concepts, sequential server as contrast |
| **DevOps** | 31–36 (6 projects) | 34–43 (10 projects) | You had zero Docker experience; added fundamentals before containerizing |
| **ML** | 37–45 (9 projects) | 44–54 (11 projects) | One course ≠ inference ready. Added NumPy review, serialization, quantization, actual C++ integration |
| **Total** | 45 | 54 | **9 additional scaffolding projects** |

---

## **How to Sequence This**

**Week 1–2:** Finish nailing 1–25 (tooling + network). You know 1–10; focus on 11–25 in order. Don't jump ahead.

**Week 3:** 26–33 (concurrency). Thread basics → epoll. Watch it all click.

**Week 4:** 34–43 (Docker). Painful but critical. You'll use this forever.

**Week 5:** 44–54 (ML). Refresh your NumPy, then move straight to ONNX Runtime + C++.

**Week 6–8:** Capstone. Integrate everything. Polish. Deploy.

